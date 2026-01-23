#include "Engine.h"
#include "GraphicsManager.h"
#include "ComponentsFactory.h"
#include "PhysicsManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LMInputs.h"

#include "AudioSource.h"
#include "EventEmitter.h"
#include "AudioListener.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "Rigidbody.h"
#include "UIImage.h"
#include "UIText.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMVector.h"
#include "LuaParser.h"
#include "ScriptManager.h"
#include "LuaBehaviour.h"

#include <iostream>
#include <SDL_messagebox.h>

using namespace LocoMotor;

Engine* Engine::_instance = nullptr;

Engine::Engine() {
	_gameName = "No window title";
	_startingSceneFile = "";
	_startingSceneName = "";
	_scnManager = nullptr;
	_startScene = "";
	_exit = false;
}

Engine::~Engine() {

}

bool Engine::Init() {

	assert(_instance == nullptr);
	_instance = new Engine();
	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	return true;
}
bool Engine::init(){
	if (!Graphics::GraphicsManager::Init()) {
		return false;
	}

	if (!Scripting::ScriptManager::Init()) {
		Graphics::GraphicsManager::Release();
		return false;
	}

	if (!Audio::AudioManager::Init(true)) {
		Scripting::ScriptManager::Release();
		Graphics::GraphicsManager::Release();
		
		return false;
	}

	//Physics::PhysicsManager::Init();
	if (!Physics::PhysicsManager::Init()) {
		Physics::PhysicsManager::Release();
		Scripting::ScriptManager::Release();
		Graphics::GraphicsManager::Release();
		return false;
	}
	//PhysicsManager::GetInstance()->SetContactStartCallback(LMcontactStart);
	//PhysicsManager::GetInstance()->SetContactProcessCallback(LMcontactProcessed);
	//PhysicsManager::GetInstance()->SetContactEndedCallback(LMcontactExit);
	//InputManager::Init();
	//SceneManager::Init();
	//ScriptManager::Init();

	if (!ComponentsFactory::Init()) {
		Physics::PhysicsManager::Release();
		Audio::AudioManager::Release();
		Scripting::ScriptManager::Release();
		Graphics::GraphicsManager::Release();
		Physics::PhysicsManager::Release();
		//InputManager::Release();
		//SceneManager::Release();
		//ScriptManager::Release();
		return false;
	}
	ComponentsFactory* cmpFac = ComponentsFactory::GetInstance();

	if (!SceneManager::Init()) {
		ComponentsFactory::Release();
		cmpFac = nullptr;
		Physics::PhysicsManager::Release();
		Audio::AudioManager::Release();
		Scripting::ScriptManager::Release();
		Graphics::GraphicsManager::Release();
		return false;
	}
	
	_scnManager = SceneManager::GetInstance();

	// Inicializar inputManager
	if (!Input::InputManager::Init()) {
		SceneManager::Release();
		ComponentsFactory::Release();
		cmpFac = nullptr;
		Physics::PhysicsManager::Release();
		Audio::AudioManager::Release();
		Scripting::ScriptManager::Release();
		Graphics::GraphicsManager::Release();
		return false;
	}


	cmpFac->registerComponent<EventEmitter>("EventEmitter");
	cmpFac->registerComponent<AudioSource>("AudioSource");
	cmpFac->registerComponent<AudioListener>("AudioListener");
	cmpFac->registerComponent<Camera>("Camera");
	cmpFac->registerComponent<MeshRenderer>("MeshRenderer");
	cmpFac->registerComponent<ParticleSystem>("ParticleSystem");
	cmpFac->registerComponent<RigidBody>("RigidBody");
	cmpFac->registerComponent<Transform>("Transform");
	cmpFac->registerComponent<UIText>("UIText");
	cmpFac->registerComponent<UIImage>("UIImage");
	cmpFac->registerComponent<LuaBehaviour>("LuaBehaviour");

	return true;
}

Engine* LocoMotor::Engine::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void LocoMotor::Engine::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

void LocoMotor::Engine::setWindowName(const std::string& name) {
	_gameName = name;
}

void LocoMotor::Engine::setStartingScene(const std::string& file, const std::string& name) {
	_startingSceneFile = file;
	_startingSceneName = name;
}

std::string LocoMotor::Engine::getStartingSceneFile() {
	return _startingSceneFile;
}

bool Engine::mainLoop() {

	

	if (!Graphics::GraphicsManager::GetInstance()->initWindow(_gameName)) {
		std::cerr << "\033[1;31m" << "Error creating game window" << "\033[0m" << std::endl;
		_exit = true;
	}
	else if (_startingSceneFile != "" && _startingSceneName != "") {
		_scnManager->loadScene(_startingSceneFile, _startingSceneName);
		_scnManager->changeScene(_startingSceneName);
	}

	float _dt;
	float _lastFrameTime = clock() / (float) CLOCKS_PER_SEC;

	bool shown = false;
	const float fixedTimeStep = 16.666f;
	float fixedTime = 0.f;
	while (!_exit) {
		if (_scnManager->getActiveScene() == nullptr) {
			std::cerr << "\033[1;31m" << "No scene has been loaded. Exiting now" << "\033[0m" << std::endl;
			_exit = true;
			break;
		}

		float time = clock() / (float) CLOCKS_PER_SEC;
		_dt = time - _lastFrameTime;
		_dt *= 1000.0;
		fixedTime += _dt;
		_lastFrameTime = time;
		while (fixedTime >= fixedTimeStep) {
			Physics::PhysicsManager::GetInstance()->update(fixedTimeStep);
			_scnManager->fixedUpdate();
			fixedTime -= fixedTimeStep;
		}

		if (Input::InputManager::GetInstance()->RegisterEvents()) {
			_exit = true;
		}

		_scnManager->update(_dt);

		Audio::AudioManager::GetInstance()->update();

		if (!Graphics::GraphicsManager::GetInstance()->render()) {
			_exit = true;
		}
	}



	Input::InputManager::Release();
	SceneManager::Release();
	ComponentsFactory::Release();
	Physics::PhysicsManager::Release();
	Audio::AudioManager::Release();
	Scripting::ScriptManager::Release();
	Graphics::GraphicsManager::Release();
	
	return true;
}

int Engine::showWindow(int type, std::string msg) {
	const SDL_MessageBoxButtonData buttons[] = {
		{0, 1, "Close Game" },
		{0, 0, "Ok" },

	};
	const SDL_MessageBoxButtonData buttons2[] = {
		{0, 1, "Close Game" },

	};
	const SDL_MessageBoxColorScheme colorScheme = { {0, 29, 112} };


	SDL_MessageBoxData messageBoxData;
	if (type == 0) {
		messageBoxData = {
			SDL_MESSAGEBOX_INFORMATION,
			NULL,
			"Info",
			msg.c_str(),
			SDL_arraysize(buttons),
			buttons,
			&colorScheme
		};
	}
	else if (type == 1) {
		messageBoxData = {
			SDL_MESSAGEBOX_WARNING,
			NULL,
			"Warning",
			msg.c_str(),
			SDL_arraysize(buttons),
			buttons,
			&colorScheme
		};
	}
	else {
		messageBoxData = {
			SDL_MESSAGEBOX_ERROR,
			NULL,
			"Error",
			msg.c_str(),
			SDL_arraysize(buttons2),
			buttons2,
			&colorScheme
		};
	}
	int butId = -1;
	SDL_ShowMessageBox(&messageBoxData, &butId);

	return butId;
}

void Engine::quit() {
	_exit = true;
}