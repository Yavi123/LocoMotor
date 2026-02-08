#pragma once
#ifndef AUDIOMANAGER
#define AUDIOMANAGER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <unordered_map>
#include <map>
#include <string>

namespace FMOD {
	class System;
	class ChannelGroup;
	class Channel;
	class Sound;
	namespace Studio {
		class System;
	}
}

namespace LocoMotor {

	class AudioListener;

	namespace Json {
		class JSONValue;
		typedef std::map<std::string, JSONValue*> JSONObject;
	}

	namespace Audio {

		class AudioManager {

		public:

			/// @brief Initializes the instance of the singleton
			/// @return true if it was initialized correctly
			static bool Init();

			/// @brief Initializes the instance of the singleton
			/// @return true if it was initialized correctly
			static bool Init(const Json::JSONObject& audioData);

			/// @brief Gets the instance to the singleton if it was initialized
			MOTOR_API static AudioManager* GetInstance();

			/// @brief Releases everything and deletes the singleton instance
			static void Release();

			/// @brief Updates the Fmod API to change channel output depending on positions and velocity
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short update();

			/// @brief Adds a sound to the system, for later use
			/// @param Name that will be used to refer to this sound upon being created
			/// @param File to get the sound from
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short addSound(const char* fileName, bool ui = false);

			/// @brief Plays an already added sound
			/// @param Name of the sound to play
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short playSound(const char* id);

			/// @brief Plays an already added sound, but gives access to the channel its being played
			/// @param Name of the sound to play
			/// @return A number that by passing it to GetError(unsigned short) you can get more info if there was an error
			unsigned short playSoundwChannel(const char* id, FMOD::Channel** channel);

			/// @brief Searches the folder for any file named 'Master.strings.bank', and then it searches for all the banks contained in this file in the same folder. Usually by building FMOD Studio in a folder all the banks are placed in the same folder.
			/// @param fmodPath: path to where the fmod build is located, without placing the '/' character at the end of the path ("Assets/Sounds/FMODStudioBuild")
			MOTOR_API void loadFMODBuild(const char* fmodPath);

			/// @brief Gets the FMOD::System object from this manager
			/// @return The System in question
			FMOD::System* getSystem() const;

			/// @brief Gets the FMOD::Studio::System object from this manager
			/// @return The System in question
			FMOD::Studio::System* getStudioSystem() const;

			/// @brief Gets the sound using an id
			FMOD::Sound* getSound(const char* id);

			/// @brief Get the fmod error corresponding to the param passed
			/// @param errorCode Param to get the Fmod error corresponding to it
			/// @return The Fmod error message
			const char* getError(const unsigned short& errorCode);

		private:

			/// @brief Initializes the instance of the singleton
			/// @return true if it was initialized correctly
			static bool Init(int numChannels, bool initialiseStudio);

			static AudioManager* _instance;

			FMOD::System* _sys = nullptr;
			FMOD::Studio::System* _studioSys = nullptr;
			FMOD::ChannelGroup* _main = nullptr;

			std::unordered_map<std::string, FMOD::Sound*> _soundLib;

			/// @brief Constructor is set to private, use the 'GetInstance' method for access to the instance of this object
			AudioManager();

			~AudioManager();

			bool init(int numChannels, bool useStudio);

		};
	}
}

#endif // !AUDIOMANAGER
