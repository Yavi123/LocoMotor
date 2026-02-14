#pragma once
#ifndef AUDIOLISTENER
#define AUDIOLISTENER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <list>
#include "Component.h"
#include "LMVector.h"

struct FMOD_VECTOR;

namespace FMOD {
	class System;
}

namespace LocoMotor {

	namespace Audio {
		class AudioManager;
	}

	class AudioListener : public Component {

		friend class Audio::AudioManager;

	public:

		AudioListener();
		~AudioListener();


	protected:

		bool setParameters(ComponentMap& params) override;
		void onEnable() override;
		void start() override;
		void update(float dT) override;
		void onDisable() override;

	private:

		size_t _fIndex;

		Audio::AudioManager* _man;

		FMOD::System* _fSys;

		std::list<AudioListener*>::iterator _thisIT;

		static std::list<AudioListener*> _listeners;

		/// @brief Change the index this listener is associated with in the manager
		/// @param index The new index of the listener
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short changeIndex(int index);

		/// @brief Set the world attributes of the listener
		/// @param newPos The new position of the listener (pass NULL or 0 to not update position)
		/// @param newVel The new velocity of the listener (pass NULL or 0 to not update velocity)
		/// @param forward The direction the listener is facing MUST BE NORMALIZED (pass NULL or 0 to not update)
		/// @param up The new upwards direction of the listener MUST ALSO BE NORMALIZED (pass NULL or 0 to not update)
		/// @return A number that by passing it to AudioManager::GetError(unsigned short) you can get more info if there was an error
		unsigned short setTransform(const FMOD_VECTOR& newPos, const FMOD_VECTOR& newVel, const FMOD_VECTOR& forward, const FMOD_VECTOR& up);

		FMOD_VECTOR toFModVector(const Vector3& a);

	};
}

#endif