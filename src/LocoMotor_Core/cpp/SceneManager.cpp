#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include <iostream>
#include "LuaParser.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
LocoMotor::SceneManager* LocoMotor::SceneManager::_instance = nullptr;

bool LocoMotor::SceneManager::Init() {
    assert(_instance == nullptr);
    _instance = new SceneManager();
    return true;
}

void LocoMotor::SceneManager::Release() {
    assert(_instance != nullptr);

    delete _instance;
    _instance = nullptr;
}

LocoMotor::SceneManager* LocoMotor::SceneManager::GetInstance() {
    assert(_instance != nullptr);
    return _instance;
}

LocoMotor::Scene* LocoMotor::SceneManager::createScene(const std::string& name, const std::string& path, const SceneMap& sceneMap) {
    Scene* newScene = nullptr;
    if (_scenes.count(name) > 0) newScene = _scenes[name];
    else newScene = new Scene(name, path);

    newScene->initialize(sceneMap);
    if (_activeScene == nullptr) {
        _activeScene = newScene;
        _activeScene->build();
    }
    if (_scenes.count(name) == 0) {
        _scenes.insert({ name,newScene });
    }
    return newScene;
}

void LocoMotor::SceneManager::changeScene(const std::string& name) {
    if (_scenes.count(name) == 0) {
        std::cerr << "Scene \"" << name << "\", doesn't exist, call createScene(name) before trying to access a scene.\n";
        return;
    }
    else {
        _toStart = _scenes[name];
    }
}

void LocoMotor::SceneManager::reloadScene() {
    std::string name = getActiveScene()->getSceneName();
    std::string path = getActiveScene()->getScenePath();
    loadScene(path, name);
    changeScene(name);
}

void LocoMotor::SceneManager::loadScene(const std::string& path, const std::string& name)
{
    LuaParser parser= LuaParser();
    auto sceneMap = parser.loadSceneFromFile(path, name);
    if (!sceneMap.has_value()) {
        //TODO: Error fatal;
        return;
    }
    createScene(name, path, sceneMap.value());
}

void LocoMotor::SceneManager::update(float dT) {
    if (_toStart != nullptr) {
        if (_activeScene != nullptr) 
            _activeScene->destroy();
        _activeScene = _toStart;
        _toStart->build();
        _toStart = nullptr;
    }
    if (_activeScene == nullptr) return; 

    _activeScene->update(dT);

}

void LocoMotor::SceneManager::fixedUpdate() {
    if (_activeScene == nullptr) return;
    _activeScene->fixedUpdate();
}

LocoMotor::SceneManager::SceneManager() : _scenes(), _activeScene(nullptr), _toStart(nullptr), _lastFrameTime(0), _dt(0.001f) {}

LocoMotor::SceneManager::~SceneManager() {

    for (auto scene : _scenes)
        delete scene.second;
}
