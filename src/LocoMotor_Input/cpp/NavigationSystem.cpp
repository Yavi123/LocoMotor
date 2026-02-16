#include "NavigationSystem.h"
#include "Selectable.h"
#include <cassert>
#include <InputManager.h>
#include <LMInputs.h>

using namespace LocoMotor::Input;
NavigationSystem* NavigationSystem::_instance = nullptr;

bool NavigationSystem::Init() {
	assert(_instance == nullptr);
	_instance = new NavigationSystem();
	return true;
}

void NavigationSystem::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

NavigationSystem* NavigationSystem::GetInstance() {
	return _instance;
}

void NavigationSystem::select(Selectable* s)
{
	if (_currentlySelected != nullptr)
		_currentlySelected->actionUnSelected();
	_currentlySelected = s;
	_currentlySelected->actionSelected();
}

void NavigationSystem::deSelect() {
	_currentlySelected->actionUnSelected();
	_currentlySelected = nullptr;
}

Selectable* NavigationSystem::getSelected() {
	return _currentlySelected;
}

void LocoMotor::Input::NavigationSystem::addSelectable(Selectable* s) {
	_allValidSelectables.push_back(s);
}

void LocoMotor::Input::NavigationSystem::removeSelectable(Selectable* s) {
	_allValidSelectables.remove(s);
}

void NavigationSystem::updateNav() {
	if (_currentlySelected == nullptr) {
		return;
	}

	for (auto a : _allValidSelectables) {
		a->resetAction();
	}
	 
	InputManager* _input = InputManager::GetInstance();

	bool readController;
	readController = _input->getCurrentlyConnectedControllers().size() > 0;

	if ((readController && 
			(_input->GetJoystickValue(0, 0, InputManager::Axis::Vertical) > 0.25f || _input->GetButtonDown(0, LMC_DPAD_UP)))
		|| _input->GetKeyDown(LMKS_W) || _input->GetKeyDown(LMKS_UP)) {

		if (_currentlySelected->getOnUp() != nullptr) {
			select(_currentlySelected->getOnUp());
		}
		else {
			_currentlySelected->actionUp();
		}
		return;
	}
	else if ((readController &&
			 (_input->GetJoystickValue(0, 0, InputManager::Axis::Vertical) < -0.25f || _input->GetButtonDown(0, LMC_DPAD_DOWN)))
		|| _input->GetKeyDown(LMKS_S) || _input->GetKeyDown(LMKS_DOWN)) {

		if (_currentlySelected->getOnDown() != nullptr) {
			select(_currentlySelected->getOnDown());
		}
		else {
			_currentlySelected->actionDown();
		}
		return;
	}
	else if ((readController &&
		   (_input->GetJoystickValue(0, 0, InputManager::Axis::Horizontal) < -0.25f || _input->GetButtonDown(0, LMC_DPAD_LEFT)))
		|| _input->GetKeyDown(LMKS_A) || _input->GetKeyDown(LMKS_LEFT)) {

		if (_currentlySelected->getOnLeft() != nullptr) {
			select(_currentlySelected->getOnLeft());
		}
		else {
			_currentlySelected->actionLeft();
		}
		return;
	}
	else if ((readController &&
		   (_input->GetJoystickValue(0, 0, InputManager::Axis::Horizontal) > 0.25f || _input->GetButtonDown(0, LMC_DPAD_RIGHT)))
		|| _input->GetKeyDown(LMKS_D) || _input->GetKeyDown(LMKS_RIGHT)) {

		if (_currentlySelected->getOnRight() != nullptr) {
			select(_currentlySelected->getOnRight());
		}
		else {
			_currentlySelected->actionRight();
		}
		return;
	}
	else if ((readController &&
			 (_input->GetButtonDown(0, LMC_A)))
		|| _input->GetKeyDown(LMKS_SPACE) || _input->GetKeyDown(LMKS_RETURN)) {

		_currentlySelected->actionSubmit();
		return;
	}
	else if ((readController &&
			 (_input->GetButtonDown(0, LMC_B)))
		|| _input->GetKeyDown(LMKS_ESCAPE) || _input->GetKeyDown(LMKS_BACKSPACE)) {

		_currentlySelected->actionCancel();
		return;
	}
}
