#include "MeshRenderer.h"
#include "OgreEntity.h"
#include <OgreMovableObject.h>
#include "GraphicsManager.h"
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreStaticGeometry.h>

#include "GameObject.h"
#include "Transform.h"

#include <iostream>

LocoMotor::MeshRenderer::MeshRenderer() {
	_name = "";
	_src = "";
	_mesh = nullptr;
	_setStatic = false;
	isSelfVisible = true;
	_node = nullptr;

	currentAnimation = nullptr;
	numAnimationsActive = 0;
}

LocoMotor::MeshRenderer::~MeshRenderer() {
}

bool LocoMotor::MeshRenderer::setParameters(ComponentMap& params) {
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());

	std::string meshName = "";
	std::string matName = "";

	bool visible = true;

	for (auto& param : params) {
		if (param.first == "Mesh" || param.first == "mesh") {
			meshName = param.second;
		}
		else if (param.first == "Material" || param.first == "material") {
			matName = param.second;
		}
		else if ((param.first == "Static" || param.first == "static") && (param.second == "true" || param.second == "True" || param.second == "1")) {
			_setStatic = true;
		}
		else if ((param.first == "Invisible" || param.first == "invisible") && (param.second == "true" || param.second == "True" || param.second == "1")) {
			visible = false;
		}
	}

	if (meshName != "") {
		setMesh(meshName);

		setMaterial(matName);
		setVisible(visible);
	}
	return true;
}

void LocoMotor::MeshRenderer::awake() {

	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}
}

void LocoMotor::MeshRenderer::init(const std::string& name, const std::string& file, bool istatic) {
	_name = name;
	_src = file;
	_setStatic = istatic;
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());

	//int i = 0;
}

void LocoMotor::MeshRenderer::playAnimation(const std::string& animationName, bool loop) {

	// Sets the current animation to the specified one by name "animationName"
	currentAnimation = allAnimations[animationName];
	currentAnimation->setEnabled(true);
	currentAnimation->setLoop(loop);

	// Disable the other animations of this mesh
	for (const auto& thisAnimation : allAnimations)
		if (thisAnimation.second != currentAnimation)
			thisAnimation.second->setEnabled(false);
}

void LocoMotor::MeshRenderer::updateAnimation(double dt) {

	if (currentAnimation != nullptr)
		currentAnimation->addTime(Ogre::Real(dt));

		//int num = 0;
		//auto it = allAnimations.begin();
		//while (num != numAnimationsActive) {
		//	if (it->second->getEnabled()) {
		//		it->second->addTime(Ogre::Real(dt));
		//		num++;
		//	}
		//	it++;
		//}
}

void LocoMotor::MeshRenderer::start() {
	if (_gameObject->getComponent<Transform>() == nullptr) {

		std::cerr << "\033[1;31m" << "GameObject with name '" << _gameObject->getName() << "' has no Transform component" << "\033[0m" << std::endl;
		return;
	}
}

void LocoMotor::MeshRenderer::onEnable() {
	// si, ya se, este isEnabled() es sospechoso, por que onEnable se llama el primer frame aunque se haya desactivado antes
	if (isSelfVisible && _mesh != nullptr && isEnabled()) 
		_mesh->setVisible(true);
}

void LocoMotor::MeshRenderer::onDisable() {
	if (_mesh != nullptr && !isEnabled()) {
		_mesh->setVisible(false);
	}
}

void LocoMotor::MeshRenderer::update(float dt) {
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}

	Vector3 pos = _gameObject->getComponent<Transform>()->getPosition();
	_node->setPosition(pos.getX(), pos.getY(), pos.getZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	quat.w = _gameObject->getComponent<Transform>()->getRotation().getW();
	quat.x = _gameObject->getComponent<Transform>()->getRotation().getX();
	quat.y = _gameObject->getComponent<Transform>()->getRotation().getY();
	quat.z = _gameObject->getComponent<Transform>()->getRotation().getZ();
	_node->setOrientation(quat);

	Vector3 size = _gameObject->getComponent<Transform>()->getSize();
	_node->setScale(size.getX(), size.getY(), size.getZ());
}

void LocoMotor::MeshRenderer::setVisible(bool visible) {
	isSelfVisible = visible;
	if (_mesh != nullptr && this->isEnabled()) {
		_mesh->setVisible(visible);
	}
}
void LocoMotor::MeshRenderer::setMaterial(const std::string& mat) {
	if (_mesh != nullptr) {
		if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(mat)) {
			_mesh->setMaterialName(mat);
		}
		else {
			std::cerr << "\033[1;31m" << "Material of name '" << mat << "' wasn't found in any known .material script: In gameObject '" << _gameObject->getName() << "'" << "\033[0m" << std::endl;
		}
	}
}

void LocoMotor::MeshRenderer::setMesh(const std::string& mesh) {
	if (_node == nullptr) {
		Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
		_node = man->createNode(_gameObject->getName());
	}
	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return;
	if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(mesh)) {
		_mesh = LocoMotor::Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createEntity(mesh);
		if (_mesh != nullptr) {
			_node->attachObject(_mesh);
		}
		else {
			std::cerr << "\033[1;31m" << "Mesh in file '" << mesh << "' couldn't be set in gameObject '" << _gameObject->getName() << "'" << "\033[0m" << std::endl;
		}
	}
	else {
		std::cerr << "\033[1;31m" << "Mesh in file '" << mesh << "' couldn't be found in gameObject '" << _gameObject->getName() << "'" << "\033[0m" << std::endl;
	}

	if (_mesh == nullptr) return;

	// Inicializar animaciones
	allAnimations = std::unordered_map<std::string, Ogre::AnimationState*>();
	if (_mesh->getAllAnimationStates() != nullptr) {
		Ogre::AnimationStateMap mapa = _mesh->getAllAnimationStates()->getAnimationStates();

		std::cout << "ANIMATIONS LOADED : \n";

		for (auto it = mapa.begin(); it != mapa.end(); it++) {
			allAnimations.insert({ it->first, it->second });
			std::cout << it->first << "\n";
		}
		std::cout << "\n";
	}
}

Ogre::MovableObject* LocoMotor::MeshRenderer::getMovObj() {
	return _mesh;
}
