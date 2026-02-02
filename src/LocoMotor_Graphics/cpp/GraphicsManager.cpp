//Ogre includes
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreGpuProgramManager.h>
#include <OgreShaderGenerator.h>
#include <OgreOverlayManager.h>
#include <OgreOverlaySystem.h>
#include <OgreViewport.h>
#include <OgreMaterialManager.h>
#include <OgreSceneNode.h>
//SDL includes
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
//Std include
#include <iostream>
//Graphics includes
#include "GraphicsManager.h"
#include "SGTechniqueResolverListener.h"
#include "OverlayManager.h"
//Core includes
#include "Screen.h"
#include "LocalSave.h"

#define FULLSCREENMODE_KEY "LM_Graphics_Fullscreen"

using namespace LocoMotor;
using namespace Graphics;

GraphicsManager* GraphicsManager::_instance = nullptr;

GraphicsManager::GraphicsManager() {
	_activeScene = nullptr;
	_mShaderGenerator = nullptr;
	_root = nullptr;
	_nodeRoot = nullptr;
}

GraphicsManager::~GraphicsManager() {
	shutdown();
}

bool LocoMotor::Graphics::GraphicsManager::Init() {
	assert(_instance == nullptr);
	_instance = new GraphicsManager();

	std::string result = _instance->initialize();

	if (result != "") {
		std::cerr << "\033[1;31m" << result << "\033[0m" << std::endl;
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

GraphicsManager* LocoMotor::Graphics::GraphicsManager::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void LocoMotor::Graphics::GraphicsManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

std::string GraphicsManager::initialize() {
	try {
		_root = new Ogre::Root();
	}
	catch (...) {
		return "Error while constructing internal ogre library";
	}

	OverlayManager::Init();

	try {
		_root->showConfigDialog(nullptr);
		_root->restoreConfig();
		_root->initialise(false);
	}
	catch (...) {
		return "Error while initializing internal ogre library";
	}
	return "";
}

void GraphicsManager::createScene(std::string name) {
	if (_scenes.count(name) > 0) {
		std::cerr << "ERROR: Ya hay una escena con el nombre \"" << name << "\". Elige otro nombre por favor\n";
		return;
	}
	Ogre::SceneManager* sM = _root->createSceneManager();
	sM->createStaticGeometry(sM->getName() + "_static");

	_scenes.insert({ name, sM });
	if (_activeScene == nullptr)
		setActiveScene(name);
}

bool GraphicsManager::render() {
	//Si falta la escena no lo consideramos un error fatal
	if (_activeScene == nullptr) return true;

	try {
		_root->renderOneFrame();
	}
	catch (...) {
		// Se que este mensaje de error es una mierda no se como explicar en una linea todo lo que ocurre ;-;
		std::cerr << "\033[1;31m" << "Scene wasn't able to render: \n\tMake sure the folder 'GraphicSettings' exists in the same directory as the game and contains all the shaders needed for the game" << "\033[0m" << std::endl;
		return false;
	}
	return true;
}

Ogre::RenderWindow* GraphicsManager::getRenderWindow() {
	return _mWindow.render;
}

void GraphicsManager::setActiveScene(std::string name) {
	if (_scenes.count(name) == 0) {
		std::cerr << "ERROR: No existe una escena con el nombre \"" << name << "\".\n";
		return;
	}
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		if (it->first == name) {
			_activeScene = it->second;
			_mShaderGenerator->addSceneManager(it->second);
			_nodeRoot = it->second->getRootSceneNode();

			it->second->addRenderQueueListener(OverlayManager::GetInstance()->getOgreSystem());

			return;
		}
	}
}

int GraphicsManager::getWindowHeight() {
	return _mWindow.render->getHeight();
}

int GraphicsManager::getWindowWidth() {
	return _mWindow.render->getWidth();
}

void LocoMotor::Graphics::GraphicsManager::setFullscreen(bool on) {

	SDL_SetWindowFullscreen(_mWindow.native, on ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
	_mWindow.render->setFullscreen(on, 200, 200);

	int valueToSet = on ? 1 : 0;
	Platform::LocalSave::SetRegisterInt(FULLSCREENMODE_KEY, valueToSet);
}

void LocoMotor::Graphics::GraphicsManager::deactivateScene(std::string name) {
	if (_scenes.count(name) == 0) {
		std::cerr << "ERROR: No existe una escena con el nombre \"" << name << "\".\n";
		return;
	}
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		if (it->first == name) {

			for (auto& nameNodePair : _sceneNodes) {
				_nodeRoot->removeAndDestroyChild(nameNodePair.second);
			}
			_sceneNodes.clear();
			it->second->destroyAllCameras();
			it->second->destroyAllParticleSystems();
			it->second->destroyAllAnimations();

			OverlayManager::GetInstance()->getOgreOverlayManager()->destroyAllOverlayElements();
			OverlayManager::GetInstance()->getOgreOverlayManager()->destroyAll();

			it->second->removeRenderQueueListener(OverlayManager::GetInstance()->getOgreSystem());
			_mShaderGenerator->removeSceneManager(it->second);
			_nodeRoot = nullptr;
			_activeScene = nullptr;
			return;
		}
	}
}

void GraphicsManager::loadResources() {
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	Ogre::String sec_name , type_name , arch_name;
	Ogre::ConfigFile::SettingsBySection_ seci = cf.getSettingsBySection();

	for (Ogre::ConfigFile::SettingsBySection_::const_iterator it = seci.cbegin(); it != seci.cend(); ++it) {
		sec_name = it->first;
		Ogre::ConfigFile::SettingsMultiMap settings = it->second;
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings.begin(); i != settings.end(); ++i) {
			type_name = i->first;
			arch_name = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				arch_name , type_name , sec_name);
		}
	}

	sec_name = "Essential";

	arch_name = "./GraphicSettings";
	type_name = "FileSystem";

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch_name, type_name, sec_name);

	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec_name);

	std::string mRTShaderLibPath = arch_name + "/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/materials" , type_name , sec_name);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mRTShaderLibPath + "/GLSL" , type_name , sec_name);

	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	if (Ogre::RTShader::ShaderGenerator::initialize()) {
		_mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		if (mRTShaderLibPath.empty())
			return;

		// Create and register the material manager listener if it doesn't exist yet.
		if (!_mMaterialMgrListener) {
			_mMaterialMgrListener = new SGTechniqueResolverListener(_mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener((Ogre::MaterialManager::Listener*) _mMaterialMgrListener);
		}
	}
	else {
		std::cerr << "\033[1;31m" << "Shaders couldn't be correctly initialized" << "\033[0m" << std::endl;
		throw 1; //Tenemos que hacer esto para que el try/catch lo pillen
	}

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

bool GraphicsManager::initWindow(std::string name) {
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	//Reads from ogre.cfg, we dont like that i would prefer to read from "playerprefs" like in unity
	Ogre::ConfigOptionMap ropts = _root->getRenderSystem()->getConfigOptions();

	Ogre::StringVector possibleResolutions = Ogre::StringVector(ropts["Video Mode"].possibleValues);

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt"))
			std::cout << "Gamecontroller Mappings Loaded" << "\n";
		else
			std::cout << "Gamecontroller Mappings NOT Loaded" << "\n";

		SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	}

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (Platform::LocalSave::GetRegisterInt(FULLSCREENMODE_KEY, 0) == 1) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		w = Platform::Screen::GetDesiredWidth();
		h = Platform::Screen::GetDesiredHeight();
	}
	else {
		Platform::LocalSave::SetRegisterInt(FULLSCREENMODE_KEY, 0);

		w = Platform::Screen::GetDesiredWidth() / 2;
		h = Platform::Screen::GetDesiredHeight() / 2;
	}

	_mWindow.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(_mWindow.native , &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	_mWindow.render = _root->createRenderWindow(name, w, h, (flags & SDL_WINDOW_FULLSCREEN) != 0, &miscParams);

	try {
		loadResources();
	}
	catch (...) {
		return false;
	}

	return true;
}


void GraphicsManager::shutdown() {

	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (_mMaterialMgrListener != nullptr) {
		Ogre::MaterialManager::getSingleton().removeListener((Ogre::MaterialManager::Listener*) _mMaterialMgrListener);
		delete _mMaterialMgrListener;
		_mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (_mShaderGenerator != nullptr) {
		Ogre::RTShader::ShaderGenerator::destroy();
		_mShaderGenerator = nullptr;
	}

	for (auto it = _scenes.begin(); it != _scenes.end(); it = _scenes.erase(it)) {
		if (it->second == _activeScene) {
			_activeScene = nullptr;
		}
		it->second->removeRenderQueueListener(OverlayManager::GetInstance()->getOgreSystem());
		_root->destroySceneManager(it->second);
		//delete it->second;
	}

	if (_mWindow.render != nullptr) {
		_root->destroyRenderTarget(_mWindow.render);
		_mWindow.render = nullptr;
	}

	if (_mWindow.native != nullptr) {
		SDL_DestroyWindow(_mWindow.native);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		_mWindow.native = nullptr;
	}

	OverlayManager::Release();

	delete _root;
	_root = nullptr;
}


Ogre::SceneNode* GraphicsManager::createNode(std::string name) {
	if(name == "Root") {
		std::cerr << "A node with the name " << name << " is already created\n";
		return nullptr;
	}
	if(_sceneNodes.count(name) > 0) {
		return _sceneNodes[name];
	}
	Ogre::SceneNode* node = _nodeRoot->createChildSceneNode(name);
	_sceneNodes.insert({ name,node });

	return node;
}

Ogre::SceneNode* GraphicsManager::getNode(std::string name) {
	if (_sceneNodes.count(name) == 0) {
		std::cerr << "No node with the name " << name << " found\n";
		return nullptr;
	}
	if (name == "Root") {
		return _nodeRoot;
	}

	return _sceneNodes.at(name);
}

void GraphicsManager::destroyNode(std::string name) {
	if (_sceneNodes.count(name) == 0 || name == "Root") {
		std::cerr << "No node with the name " << name << " found\n";
	}
	else {
		_nodeRoot->removeAndDestroyChild(_sceneNodes[name]);
		_sceneNodes.erase(name);
	}
}

Ogre::SceneManager* LocoMotor::Graphics::GraphicsManager::getOgreSceneManager() {
	if (_activeScene == nullptr) {
		std::cerr << "No active scene\n";
		return nullptr;
	}
	return _activeScene;
}

