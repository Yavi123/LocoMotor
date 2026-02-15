#include "Scene.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "MeshRenderer.h"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneDefs.h"
#include <iostream>


using namespace LocoMotor;

LocoMotor::Scene::Scene(std::string name, std::string path) {
	_name = name;
	_path = path;
}

Scene::~Scene() {
	std::unordered_map<std::string, GameObject*>::const_iterator it;
	for (it = _gameObjList.cbegin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}
	for (it = _gameObjBufferList.cbegin(); it != _gameObjBufferList.end(); it = _gameObjBufferList.erase(it)) {
		delete it->second;
	}
}

void Scene::update(float dt) {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;
	}
	//End of loop, once all objects are Updated, add buffered objects
	for (auto& obj : _gameObjBufferList) {
		_gameObjList.insert(obj);
		obj.second->awake();
	}
	_gameObjBufferList.clear();

	std::queue<std::string> destroyedObjs = std::queue<std::string>();
	int numDestroyed = 0;

	for (auto& obj : _gameObjList) {
		if (obj.second->hasToBeDestroyed()) {
			destroyedObjs.push(obj.first);
			numDestroyed++;
		}
	}

	for (auto i = 0; i < numDestroyed; i++) {
		deleteGameObject(destroyedObjs.front());
		destroyedObjs.pop();
	}
	
	for (auto& obj : _gameObjList) {
		obj.second->update(dt);
	}
}

void LocoMotor::Scene::fixedUpdate() {
	//si no esta activa que no haga nada
	if (!_isActiveScene) {
		return;
	}
	for (auto& obj : _gameObjList) {
		obj.second->fixedUpdate();
	}
	//End of loop, once all objects are Updated, add buffered objects
	for (auto& obj : _gameObjBufferList) {
		_gameObjList.insert(obj);
		obj.second->awake();
	}
	_gameObjBufferList.clear();
}

void Scene::render() {
	Graphics::GraphicsManager::GetInstance()->render();
}


void Scene::deactivate() {
	_toDestroy = true;
}


bool LocoMotor::Scene::toDestroy() {
	return _toDestroy;
}

void Scene::build() {
	_toDestroy = false;
	_isActiveScene = true;
	Graphics::GraphicsManager::GetInstance()->setActiveScene(_name);

	for (auto& objPair : _sceneDef) {
		GameObject* gObj = addGameobject(objPair.first);
		for (auto& cmpPair : objPair.second) {
			Component* cmp = gObj->addComponentWithParams(cmpPair.first, cmpPair.second);
		}
		if (gObj->getComponent<Transform>() == nullptr) {
			Transform* tr = dynamic_cast<Transform*>(gObj->addComponent("Transform"));
			tr->initRuntime();
		}
	}

	for (auto& gObj : _gameObjList)gObj.second->awake();
}

void Scene::destroy() {
	_isActiveScene = false;
	std::unordered_map<std::string, GameObject*>::iterator it;
	for (it = _gameObjList.begin(); it != _gameObjList.end(); it = _gameObjList.erase(it)) {
		delete it->second;
	}
	Graphics::GraphicsManager::GetInstance()->deactivateScene(_name);
}

void Scene::initialize(const SceneMap& data) {
	_sceneDef = data;
	Graphics::GraphicsManager::GetInstance()->createScene(_name);
}

void LocoMotor::Scene::deleteGameObject(const std::string& name) {
	if (_gameObjList.count(name) == 0) {
	#ifdef _DEBUG
		std::cerr << "No existe un objeto con el nombre " << name << std::endl;
	#endif // DEBUG
		return;
	}
	delete _gameObjList[name];
	_gameObjList.erase(name);
	Graphics::GraphicsManager::GetInstance()->destroyNode(name);
}

bool Scene::getActiveStatus() {
	return _isActiveScene;
}


std::string Scene::getSceneName() {
	return _name;
}

std::string LocoMotor::Scene::getScenePath() {
	return _path;
}


GameObject* LocoMotor::Scene::addGameobject(std::string name) {
	if (_gameObjList.count(name) > 0) {
	#ifdef DEBUG
		std::cerr << "Ya existe un objeto con el nombre " << name << " se retornara" << std::endl;
	#endif // DEBUG
		return _gameObjList[name];
	}
	GameObject* newObj = new GameObject(name);
	newObj->init(this, true);
	_gameObjList.insert({ name, newObj });
	return newObj;
}
GameObject* LocoMotor::Scene::addGameobjectRuntime(std::string name) {
	//Return already existing gameObject
	if (_gameObjList.count(name) > 0) return _gameObjList[name];
	if (_gameObjBufferList.count(name) > 0) return _gameObjBufferList[name];

	//Create new Object, add to bufferList first
	GameObject* newObj = new GameObject(name);
	newObj->init(this, true);
	//newObj->addComponent("Transform");
	_gameObjBufferList.insert({ name, newObj });

	return newObj;
}

void LocoMotor::Scene::removeGameobject(std::string name) {
	if (_gameObjList.count(name) == 0) {
	#ifdef _DEBUG
		std::cerr << "No existe un objeto con el nombre " << name << std::endl;
	#endif // DEBUG
		return;
	}
	_gameObjList[name]->setToDestroy();
}


GameObject* LocoMotor::Scene::getObjectByName(std::string name) {
	if (_gameObjList.count(name) == 0)
		return nullptr;
	return _gameObjList[name];
}

