#include "EventEmitter.h"
#include "AudioManager.h"
#include "Transform.h"
#include "LMVector.h"
#include "GameObject.h"

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor;

EventEmitter::EventEmitter() : _currentEvent(nullptr), _studioSys(nullptr), playOnStart(false) {}

EventEmitter::~EventEmitter() {
	if (_currentEvent != nullptr) {
		_currentEvent->stop(FMOD_STUDIO_STOP_IMMEDIATE);
		_currentEvent->release();
	}
}

void LocoMotor::EventEmitter::setEvent(const char* eventID) 
{
	_studioSys = Audio::AudioManager::GetInstance()->getStudioSystem();
	if (_studioSys == nullptr) {
		return;
	}

	FMOD::Studio::EventDescription* desc;

#ifndef _DEBUG

	_studioSys->getEvent(eventID, &desc);

#else

	FMOD_RESULT err;
	err = _studioSys->getEvent(eventID, &desc);

	if (err != FMOD_OK) {
		std::cerr << "AUDIO: Event with ID '" << eventID << "' could not be loaded: \n\t" << FMOD_ErrorString(err) << std::endl;
	}

#endif // !_DEBUG

	desc->createInstance(&_currentEvent);
}

void EventEmitter::play() {
	if (_currentEvent == nullptr) return;
	_currentEvent->start();
}

void EventEmitter::setVolume(float vol) {
	if (_currentEvent == nullptr) return;
	_currentEvent->setVolume(vol);
}

void EventEmitter::setPitch(float pitch) {
	if (_currentEvent == nullptr) return;
	_currentEvent->setPitch(pitch);
}

void EventEmitter::setParameter(const char* paramName, float value) {
	if (_currentEvent == nullptr) return;
	_currentEvent->setParameterByName(paramName, value);
}

float EventEmitter::getParameter(const char* paramName) {
	if (_currentEvent == nullptr) return 0.f;
	float val;
	if (_currentEvent->getParameterByName(paramName, &val) != FMOD_OK)
		return 0.f;
	return val;
}

void EventEmitter::stop() {
	if (_currentEvent == nullptr) return;
	_currentEvent->stop(FMOD_STUDIO_STOP_IMMEDIATE);
}

bool LocoMotor::EventEmitter::setParameters(ComponentMap& params) {
	_studioSys = Audio::AudioManager::GetInstance()->getStudioSystem();
	if (_studioSys == nullptr) {
	#ifdef _DEBUG
		std::cerr << "Attempted to create an EventEmitter component without studio initialized, removing component" << std::endl;
	#endif
		return false;
	}

	for (auto& parameter : params) {
		if (parameter.first == "EventID") {
			setEvent(parameter.second.c_str());
		}
		else if (parameter.first == "Volume") {
			try {
				if (_currentEvent)
					_currentEvent->setVolume(std::stof(parameter.second));
			}
			catch (...) {
				_currentEvent->setVolume(1);
			}
		}
		else if (parameter.first == "Start" || parameter.first == "Play") {
			playOnStart = true;
		}
	}
	return true;
}

void LocoMotor::EventEmitter::start() {
	if (_studioSys == nullptr) {
		_gameObject->removeComponents("EventEmitter");
		return;
	}
	if (playOnStart)
		play();
}

void LocoMotor::EventEmitter::update(float dT) {
	if (_currentEvent == nullptr)
		return;
	FMOD_3D_ATTRIBUTES at;
	_currentEvent->get3DAttributes(&at);

	Vector3 newPos = _gameObject->getComponent<Transform>()->getPosition();

	at.velocity.x = (newPos.getX() - at.position.x) / dT;
	at.velocity.y = (newPos.getY() - at.position.y) / dT;
	at.velocity.z = (newPos.getZ() - at.position.z) / dT;

	at.position.x = newPos.getX();
	at.position.y = newPos.getY();
	at.position.z = newPos.getZ();

	Vector3 forward = _gameObject->getComponent<Transform>()->getRotation().forward();

	at.forward.x = forward.getX();
	at.forward.y = forward.getY();
	at.forward.z = forward.getZ();

	Vector3 up = _gameObject->getComponent<Transform>()->getRotation().up();

	at.up.x = up.getX();
	at.up.y = up.getY();
	at.up.z = up.getZ();

	_currentEvent->set3DAttributes(&at);
}

