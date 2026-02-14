#pragma once
#ifndef AUDIOSOURCE
#define AUDIOSOURCE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <unordered_map>
#include "Component.h"
#include "LMVector.h"

namespace FMOD {
	class Channel;
}
namespace LocoMotor {

	namespace Audio {
		class AudioManager;
	}

	struct ChannelData {
		FMOD::Channel* channel;
		float ogFrec;
	};

	class AudioSource : public Component {
	public:

		AudioSource();
		~AudioSource();

		/// @brief Adds a sound to the manager's system, for later use
		/// @param Name that will be used to refer to this sound upon being created
		/// @param File to get the sound from
		MOTOR_API void addSound(const char* fileName);

		/// @brief Plays a sound from this source
		/// @param fileName The sound to play
		/// @param loops Amount of loops the sound will do (-1 for infinite)
		/// @param loopBegin When should the sound begin its loop section (in miliseconds)
		/// @param loopEnd When should the sound end its loop section (in miliseconds)
		MOTOR_API void playSound(const char* fileName, int loops = 0, unsigned int loopBegin = 0, unsigned int loopEnd = 0xffffffff);

		/// @brief Plays a sound independently of this source, meaning i won´t update its position, with a randomized pitch
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		MOTOR_API void playOneShot(const char* fileName, const Vector3& position, const float volume = 1.f);

		/// @brief Plays a sound independently of this source, meaning it won´t update its position
		/// @param fileName The sound to play
		/// @param position Position where the sound will come from
		/// @param volume Volume modifier of the sound
		/// @param pitch Pitch modifier of the sound
		MOTOR_API void playOneShotWithPitch(const char* fileName, const Vector3& position, const float volume, const float pitch);

		/// @brief Pauses a specific sound playing in this source
		/// @param fileName The sound to play
		/// @param pause should the sound be paused? or unpaused?
		MOTOR_API void pauseSound(const char* fileName, bool pause = true);

		/// @brief Pauses all sounds playing in this source
		/// @param pause should the sound be paused? or unpaused)
		MOTOR_API void pause(bool pause = true);

		/// @brief Stop a specific sound playing in this source
		/// @param fileName The sound to stop
		MOTOR_API void stopSound(const char* fileName);

		/// @brief Stop all sounds playing in this source
		MOTOR_API void stop();

		/// @brief Set the volume of a specific sound playing in this source
		/// @param fileName The sound to set the volume to
		/// @param volume 0.f = mute, 1.f = max volume
		MOTOR_API void setSoundVolume(const char* fileName, const float volume);

		/// @brief Set the volume of all sounds that are playing and will play from this source
		/// @param volume 0.f = mute, 1.f = max volume
		MOTOR_API void setVolume(const float volume);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		MOTOR_API void setSoundFreq(const char* fileName, const float freqMult);

		/// @brief Vary the frequency of a specific sound that is already playing
		/// @param id The id of the sound to modify
		/// @param freqMult The value that will be multiplied to the original frequency
		MOTOR_API void setFrequency(const float freqMult);

		/// @brief Set the source to play sounds in world space
		MOTOR_API void setMode3D();

		/// @brief Set the source to play sounds with no regard of its position
		MOTOR_API void setMode2D();

	protected:

		bool setParameters(ComponentMap& params) override;
		void start() override;
		void update(float dT) override;

	private:

		Audio::AudioManager* _man;

		std::unordered_map<const char*, ChannelData> _chMap;

		float _volumeMult;

		int _mode;

		std::string _playOnStart;

		int _loops = 0;
		int _loopStart = 0;
		int _loopEnd = 0xffffffff;
	};
}


#endif // !AUDIOSOURCE


