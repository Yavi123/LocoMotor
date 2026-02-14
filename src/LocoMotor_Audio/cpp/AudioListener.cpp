#include "AudioListener.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "LMQuaternion.h"
#include <fmod_common.h>
#include <fmod.hpp>
#include "fmod_errors.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace LocoMotor;

std::list<AudioListener*> AudioListener::_listeners = std::list<AudioListener*>();

bool LocoMotor::AudioListener::setParameters(ComponentMap& params) {
	_man = Audio::AudioManager::GetInstance();
	_fSys = _man->getSystem();
	return true;
}

void AudioListener::onEnable() {
	_fIndex = _listeners.size();
	_listeners.push_back(this);

	_fSys->set3DNumListeners((int) _listeners.size());

	_thisIT = _listeners.end();
	_thisIT--;
}

void LocoMotor::AudioListener::start() {}

void AudioListener::update(float dT) {

	if (dT == 0.f)
		dT += 0.000001f;

	FMOD_VECTOR lastPosition;
	_fSys->get3DListenerAttributes((int)_fIndex, &lastPosition, NULL, NULL, NULL);

	Transform* transform = _gameObject->getComponent<Transform>();

	FMOD_VECTOR newPosition = toFModVector(transform->getPosition());

	FMOD_VECTOR newVel = FMOD_VECTOR();
	newVel.x = (newPosition.x - lastPosition.x) / dT;
	newVel.y = (newPosition.y - lastPosition.y) / dT;
	newVel.z = (newPosition.z - lastPosition.z) / dT;

	auto forward = toFModVector(transform->getRotation().forward());
	auto up = toFModVector(transform->getRotation().up());

#ifdef _DEBUG
	unsigned short err = _fSys->set3DListenerAttributes((int) _fIndex, &newPosition, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cerr << "Listener error: " << _man->getError(err) << std::endl;
	}
#else
	_fSys->set3DListenerAttributes((int) _fIndex, &newPosition, &newVel, &forward, &up);
#endif // _DEBUG

}

void AudioListener::onDisable() {
	auto listenerIt = _listeners.erase(_thisIT);
	int nIndex = (int)_fIndex;

	unsigned short err = 0;

	while (listenerIt != _listeners.end()) {
		err = (*listenerIt)->changeIndex(nIndex);

	#ifdef _DEBUG
		if (err != 0) {
			std::cerr << "AUDIO: Trying to update listeners while removing number '" << _fIndex << "' caused fmod exception: " << FMOD_ErrorString((FMOD_RESULT) err) << std::endl;
		}
	#endif // _DEBUG
		listenerIt++;
		nIndex++;
	}
	_fSys->set3DNumListeners((int) _listeners.size());
}

AudioListener::AudioListener() : _fIndex(0), _man(nullptr), _fSys(nullptr), _thisIT() {
}

AudioListener::~AudioListener() {
}

unsigned short AudioListener::setTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up) {

#ifdef _DEBUG
	unsigned short err = _man->getSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
	if (err != FMOD_OK) {
		std::cerr << "Listener error: " << _man->getError(err) << std::endl;
	}
	return err;
#else
	return _man->getSystem()->set3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);
#endif // _DEBUG
}

FMOD_VECTOR LocoMotor::AudioListener::toFModVector(const Vector3& a) {
	FMOD_VECTOR res = FMOD_VECTOR();
	res.x = a.getX();
	res.y = a.getY();
	res.z = a.getZ();
	return res;
}

unsigned short AudioListener::changeIndex(int index) {
	FMOD_VECTOR newPos; FMOD_VECTOR newVel; FMOD_VECTOR forward; FMOD_VECTOR up;

	unsigned short err = _man->getSystem()->get3DListenerAttributes((int)_fIndex, &newPos, &newVel, &forward, &up);

	if (err == 0)
		err = _man->getSystem()->set3DListenerAttributes(index, &newPos, &newVel, &forward, &up);

	_fIndex = (size_t)index;

	return err;
}
