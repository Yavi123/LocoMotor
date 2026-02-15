#include "OverlayManager.h"

#include "OgreOverlay.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayManager.h"
#include "LMVector.h"

#include <cassert>

#include <iostream>

using namespace LocoMotor;

unsigned int Graphics::OverlayManager::_numOfCanvas = 0;
Graphics::OverlayManager* Graphics::OverlayManager::_instance = nullptr;

Graphics::OverlayManager::OverlayManager() : _ovrsys(nullptr) {}

Graphics::OverlayManager::~OverlayManager() {

	delete _ovrsys;
	_ovrsys = nullptr;
}

bool Graphics::OverlayManager::Init() {
	assert(_instance == nullptr);

	_instance = new OverlayManager();

	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	_numOfCanvas++;

	return true;
}

Graphics::OverlayManager* Graphics::OverlayManager::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void Graphics::OverlayManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

bool LocoMotor::Graphics::OverlayManager::IsInitialized() {
	return _instance != nullptr;
}

Vector2 LocoMotor::Graphics::OverlayManager::stringToAnchors(const std::string& s)
{
	Vector2 result = Vector2();
	unsigned char currAxis = 0;
	std::string num = "";
	for (const char c : s) {
		if (c != ' ') {
			num += c;
		}
		else {
			float value = 0.f;
			try {
				value = std::stof(num);
			}
			catch (...) {
				value = 0.f;
				std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
			}
			if (currAxis == 0) {
				result.setX(value);
			}
			else if (currAxis == 1) {
				result.setY(value);
			}
			currAxis++;
			num = "";
			if (currAxis == 2) {
				break;
			}
		}
	}
	float value = 0.0f;
	try {
		value = std::stof(num);
	}
	catch (...) {
		value = 0.0f;
		std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
	}
	if (currAxis == 1)
		result.setY(value);
	return result;
}

Vector2 LocoMotor::Graphics::OverlayManager::stringToPosition(const std::string& s)
{
	Vector2 result = Vector2();
	unsigned char currAxis = 0;
	std::string num = "";
	for (const char c : s) {
		if (c != ' ') {
			num += c;
		}
		else {
			float value = 0.f;
			try {
				value = std::stoi(num);
			}
			catch (...) {
				value = 0.f;
				std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
			}
			if (currAxis == 0) {
				result.setX(value);
			}
			else if (currAxis == 1) {
				result.setY(value);
			}
			currAxis++;
			num = "";
			if (currAxis == 2) {
				break;
			}
		}
	}
	float value = 0.0f;
	try {
		value = std::stoi(num);
	}
	catch (...) {
		value = 0.0f;
		std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from UI anchor/pivot" << "\033[0m" << std::endl;
	}
	if (currAxis == 1)
		result.setY(value);
	return result;
}

Ogre::OverlayManager* LocoMotor::Graphics::OverlayManager::getOgreOverlayManager() {
	return _ogrOverlayManager;
}

Ogre::OverlaySystem* LocoMotor::Graphics::OverlayManager::getOgreSystem() {
	return _ovrsys;
}

bool Graphics::OverlayManager::init() {

	_ovrsys = new Ogre::OverlaySystem();

	_ogrOverlayManager = Ogre::OverlayManager::getSingletonPtr();

	if (_ogrOverlayManager == nullptr) {
		delete _ovrsys;
		_ovrsys = nullptr;
		return false;
	}

	return true;
}
