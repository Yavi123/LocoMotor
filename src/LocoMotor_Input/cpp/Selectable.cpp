#include "Selectable.h"
#include "NavigationSystem.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"

#define UP          0x01
#define DOWN        0x02
#define LEFT        0x04
#define RIGHT       0x08
#define SUBMIT      0x10
#define CANCEL      0x20
#define SELECTED    0x40
#define DESELECTED  0x80

using namespace LocoMotor::Input;

Selectable::Selectable() {
	_startSelected = false;
    _actionsThisFrame = 0;

    _up = nullptr;
    _down = nullptr;
    _left = nullptr;
    _right = nullptr;

	_upName		= "";
	_downName	= "";
	_leftName	= "";
	_rightName	= "";

    _navSystem = nullptr;
}

Selectable::~Selectable() {
}

bool Selectable::upTriggered() const {
    return _actionsThisFrame & UP;
}

bool Selectable::downTriggered() const {
    return _actionsThisFrame & DOWN;
}

bool Selectable::leftTriggered() const {
    return _actionsThisFrame & LEFT;
}

bool Selectable::rightTriggered() const {
    return _actionsThisFrame & RIGHT;
}

bool Selectable::submitTriggered() const {
    return _actionsThisFrame & SUBMIT;
}

bool Selectable::cancelTriggered() const {
    return _actionsThisFrame & CANCEL;
}

bool Selectable::onSelected() const {
    return _actionsThisFrame & SELECTED;
}

bool Selectable::onDeselected() const {
    return _actionsThisFrame & DESELECTED;
}

void Selectable::setSelected() {
    _navSystem->select(this);
}

void Selectable::actionUp() {
	_actionsThisFrame = UP;
}

void Selectable::actionDown() {
	_actionsThisFrame = DOWN;
}

void Selectable::actionLeft() {
	_actionsThisFrame = LEFT;
}

void Selectable::actionRight() {
	_actionsThisFrame = RIGHT;
}

void Selectable::actionSubmit() {
	_actionsThisFrame = SUBMIT;
}

void Selectable::actionCancel() {
	_actionsThisFrame = CANCEL;
}

void Selectable::actionSelected() {
    _actionsThisFrame = SELECTED;
}

void Selectable::actionUnSelected() {
    _actionsThisFrame = DESELECTED;
}

void Selectable::resetAction() {
	_actionsThisFrame = 0;
}

Selectable* Selectable::getOnUp() {
	return _up;
}

Selectable* Selectable::getOnDown() {
	return _down;
}

Selectable* Selectable::getOnLeft() {
	return _left;
}

Selectable* Selectable::getOnRight() {
	return _right;
}

bool Selectable::setParameters(ComponentMap& params) {

	_navSystem = NavigationSystem::GetInstance();

	for (auto& p : params) {
		if (p.first.find("eft") != std::string::npos) {
			_leftName = p.second;
		}
		else if (p.first.find("ight") != std::string::npos) {
			_rightName = p.second;
		}
		else if (p.first.find("own") != std::string::npos) {
			_downName = p.second;
		}
		else if (p.first.find("up") != std::string::npos || p.first.find("Up") != std::string::npos) {
			_upName = p.second;
		}
		else if (p.first.find("irst") != std::string::npos) {
			if (p.second.find("alse") == std::string::npos)
				_startSelected = true;
		}
	}
	return true;
}

void Selectable::start() {

	::LocoMotor::Scene* currentScene = SceneManager::GetInstance()->getActiveScene();

	GameObject* target = currentScene->getObjectByName(_upName);
	if (target != nullptr)
		_up = target->getComponent<Selectable>();

	target = currentScene->getObjectByName(_downName);
	if (target != nullptr)
		_down = target->getComponent<Selectable>();

	target = currentScene->getObjectByName(_leftName);
	if (target != nullptr)
		_left = target->getComponent<Selectable>();

	target = currentScene->getObjectByName(_rightName);
	if (target != nullptr)
		_right = target->getComponent<Selectable>();

	if (_startSelected)
		setSelected();
}

void Selectable::onEnable() {
	_navSystem->addSelectable(this);
}

void Selectable::onDisable() {
	if (_navSystem->getSelected() == this) {
		_navSystem->deSelect();
	}
	_navSystem->removeSelectable(this);
}
