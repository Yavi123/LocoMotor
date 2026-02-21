#include "GameObject.h"
#include "Component.h"
#include "ComponentsFactory.h"
#include "Transform.h"
#include <vector>
#include <iostream>
LocoMotor::Component* LocoMotor::GameObject::addComponent(const std::string& name) {
	ComponentsFactory* factory = LocoMotor::ComponentsFactory::GetInstance();
	if (_components.count(name) > 0) {
		return _components[name];
	}
	else {
		Component* comp = factory->createComponent(name);
		if (comp == nullptr) {
			comp = factory->createComponent("LuaBehaviour");
			auto params = ComponentMap();
			params.push_back({ "scriptName", name });
			try {
				if (!comp->setParameters(params)) {
					delete comp;
					return nullptr;
				}
			}
			catch (const std::exception& ex) {
				printError("setParameters", ex.what(), name);
				delete comp;
				return nullptr;
			}
			catch (const std::string& ex) {
				printError("setParameters", ex, name);
				delete comp;
				return nullptr;
			}
			catch (...) {
				printError("setParameters", "non std exception :)", name);
				delete comp;
				return nullptr;
			}
		}
		comp->init(this, true);
		_toStart.push(comp);
		_components.insert({ name, comp });
		if (name == "Transform") {
			_transform = static_cast<Transform*>(comp);
		}
		return comp;
	}
}

LocoMotor::Component* LocoMotor::GameObject::addComponentWithParams(const std::string& name,std::vector<std::pair<std::string, std::string>>& params)
{
	ComponentsFactory* factory = LocoMotor::ComponentsFactory::GetInstance();
	if (_components.count(name) > 0) {
		return _components[name];
	}
	else {
		Component* comp = factory->createComponent(name);
		if (comp == nullptr) {
			comp = factory->createComponent("LuaBehaviour");
			params.insert(params.begin(), { "scriptName", name });
		}
		comp->init(this, true);
		if (!comp->setParameters(params)) {
			delete comp;
			return nullptr;
		}
		_toStart.push(comp);
		_components.insert({ name, comp });
		if (name == "Transform"){
			_transform = static_cast<Transform*>(comp);
		}
	return comp;
	}
}

void LocoMotor::GameObject::removeComponents(const std::string& name) {
	if (_components.count(name) == 0) {
		return;
	}
	auto comps = _components.equal_range(name);
	for (auto comp = comps.first; comp != comps.second; ++comp) {
		_toDestroy.push(comp->second);
	}
	_components.erase(comps.first, comps.second);
}

LocoMotor::Component* LocoMotor::GameObject::getComponentByName(const std::string& name) {
	if(_components.count(name) == 0)
		return nullptr;

	return _components[name];
}

LocoMotor::GameObject::GameObject(std::string name) : _components(), _toEnable(), _toDisable(), _toStart(), _toDestroy(), _scene(nullptr), _transform(nullptr), _active(true), _gobjName(name), shouldCallAwake(true) {}

LocoMotor::GameObject::~GameObject() {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		cmp->onDisable();
		cmp->onDestroy();
		delete cmp;
		cmp = nullptr;
		
	}
	_components.clear();
}

void LocoMotor::GameObject::update(float dt) {

	while (!_toDestroy.empty()) {
		Component* cmp = _toDestroy.front();
		try {
			cmp->onDisable();
		}
		catch (const std::exception& ex) {
			printError("onDisable", ex.what());
		}
		catch (const std::string& ex) {
			printError("onDisable", ex);
		}
		catch (...) {
			printError("onDisable", "non std exception :)");
		}
		//========
		try {
			cmp->onDestroy();
		}
		catch (const std::exception& ex) {
			printError("onDestroy", ex.what());
		}
		catch (const std::string& ex) {
			printError("onDestroy", ex);
		}
		catch (...) {
			printError("onDestroy", "non std exception :)");
		}
		delete cmp;
		_toDestroy.pop();
	}
	while (!_toDisable.empty()) {
		Component* cmp = _toDisable.front();
		try {
			cmp->onDisable();
		}
		catch (const std::exception& ex) {
			printError("onDisable", ex.what());
		}
		catch (const std::string& ex) {
			printError("onDisable", ex);
		}
		catch (...) {
			printError("onDisable", "non std exception :)");
		}
		_toDisable.pop();
	}
	while (!_toStart.empty()) {
		Component* cmp = _toStart.front();
		try {
			cmp->onEnable();
		}
		catch (const std::exception& ex) {
			printError("onEnable", ex.what());
		}
		catch (const std::string& ex) {
			printError("onEnable", ex);
		}
		catch (...) {
			printError("onEnable", "non std exception :)");
		}
		//=========
		try {
			cmp->start();
		}
		catch (const std::exception& ex) {
			printError("start", ex.what());
		}
		catch (const std::string& ex) {
			printError("start", ex);
		}
		catch (...) {
			printError("start", "non std exception :)");
		}
		_toStart.pop();
	}
	while (!_toEnable.empty()) {
		Component* cmp = _toEnable.front();
		try {
			cmp->onEnable();
		}
		catch (const std::exception& ex) {
			printError("onEnable", ex.what());
		}
		catch (const std::string& ex) {
			printError("onEnable", ex);
		}
		catch (...) {
			printError("onEnable", "non std exception :)");
		}
		_toEnable.pop();
	}
	for (auto& pair : _components) {

		Component* cmp = pair.second;
		if (cmp->isEnabled()) {
			try {
				cmp->update(dt);
			}
			catch (const std::exception& ex) {
				printError("update", ex.what());
			}
			catch (const std::string& ex) {
				printError("update", ex);
			}
			catch (...) {
				printError("update", "non std exception :)");
			}
		}
	}
}

void LocoMotor::GameObject::fixedUpdate() {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		if (cmp->isEnabled()) {
			try {
				cmp->fixedUpdate();
			}
			catch (const std::exception& ex) {
				printError("fixedUpdate", ex.what());
			}
			catch (const std::string& ex) {
				printError("fixedUpdate", ex);
			}
			catch (...) {
				printError("fixedUpdate", "non std exception :)");
			}
		}
	}
}

void LocoMotor::GameObject::sendMessage(const std::string& m) {

	for (auto& pair : _components) {
		Component* cmp = pair.second;
		try {
			cmp->receiveMessage(m);
		}
		catch (const std::exception& ex) {
			printError("sendMessage", ex.what());
		}
		catch (const std::string& ex) {
			printError("sendMessage", ex);
		}
		catch (...) {
			printError("sendMessage", "non std exception :)");
		}
	}
}

void LocoMotor::GameObject::init(LocoMotor::Scene* scene, bool active) {
	_scene = scene;
	_active = active;
}

void LocoMotor::GameObject::awake() {
	for (auto& cmp : _components) {
		try {
			cmp.second->awake();
		}
		catch (const std::exception& ex) {
			printError("awake", ex.what());
		}
		catch (const std::string& ex) {
			printError("awake", ex);
		}
		catch (...) {
			printError("awake", "non std exception :)");
		}
	}
}

bool LocoMotor::GameObject::hasToBeDestroyed() {
	return _toDestroyThis;
}

void LocoMotor::GameObject::setToDestroy() {
	_toDestroyThis = true;
}

void LocoMotor::GameObject::printError(const std::string& method, const std::string& error, const std::string& compName) {

	if (compName != "")
		std::cerr << "\033[1;31m" << "Exception while executing '" << method << "' on component '" << compName << "':" << error << "\033[0m" << std::endl;
	else 
		std::cerr << "\033[1;31m" << "Exception while executing '" << method << "':" << error << "\033[0m" << std::endl;
}

std::string LocoMotor::GameObject::getName() const {
	return _gobjName;
}

void LocoMotor::GameObject::OnCollisionEnter(GameObject* other) {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		if (cmp->isEnabled()) {
			try {
				cmp->OnCollisionEnter(other);
			}
			catch (const std::exception& ex) {
				printError("OnCollisionEnter", ex.what());
			}
			catch (const std::string& ex) {
				printError("OnCollisionEnter", ex);
			}
			catch (...) {
				printError("OnCollisionEnter", "non std exception :)");
			}
		}
	}
}

void LocoMotor::GameObject::OnCollisionStay(GameObject* other) {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		if (cmp->isEnabled()) {
			try {
				cmp->OnCollisionStay(other);
			}
			catch (const std::exception& ex) {
				printError("OnCollisionStay", ex.what());
			}
			catch (const std::string& ex) {
				printError("OnCollisionStay", ex);
			}
			catch (...) {
				printError("OnCollisionStay", "non std exception :)");
			}
		}
	}
}

void LocoMotor::GameObject::OnCollisionExit(GameObject* other) {
	for (auto& pair : _components) {
		Component* cmp = pair.second;
		if (cmp->isEnabled()) {
			try {
				cmp->OnCollisionExit(other);
			}
			catch (const std::exception& ex) {
				printError("OnCollisionExit", ex.what());
			}
			catch (const std::string& ex) {
				printError("OnCollisionExit", ex);
			}
			catch (...) {
				printError("OnCollisionExit", "non std exception :)");
			}
		}
	}
}
