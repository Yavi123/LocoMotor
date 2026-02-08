#pragma once
#ifndef LOCOMOTOR_ENGINE
#define LOCOMOTOR_ENGINE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor {
	class SceneManager;
	class GameObject;

	namespace Json {
		class JSONValue;
	}

	class Engine {
	public:
		

		/// @brief Method to call before calling the InitGame Function in the game dll
		/// @return if false, abort
		MOTOR_API static bool Init();

		/// @brief Returns the instance of the Engine singleton
		MOTOR_API static Engine* GetInstance();

		/// @brief Deletes the instance of the Engine singleton
		MOTOR_API static void Release();

		/// @brief Set the title the game window will display
		MOTOR_API void setWindowName(const std::string& name);

		/// @brief Set a scene to be loaded and started upon the game launching
		/// @param file: where the scene data is located
		/// @param name: the name of the scene inside the file
		MOTOR_API void setStartingScene(const std::string& file, const std::string& name);

		/// @brief get the scene the game starts with
		MOTOR_API std::string getStartingSceneFile();

		/// @brief Creates the game window and begins the gameloop, will exit when called the quit method or window is closed
		MOTOR_API bool mainLoop();

		/// @brief Shows a display window showing the message displayed. This is a blocking call, meaning the code will be paused until the window is closed
		/// @param type: an int indicating type of message: 0 = message, 1 = warning, 2 = error
		/// @param msg: the text to show at the window
		/// @return an int indicating which button on the window was pressed: 0 = Ok, 1 = Close Game, -1 window was closed any other way
		MOTOR_API int showWindow(int type,std::string msg);

		/// @brief Method to exit the gameloop cleanly
		MOTOR_API void quit();
	private:

		Engine();
		~Engine();

		bool init();
		void initializeStartingDataFromJson(Json::JSONValue* executableData);
		bool initializeGraphics(Json::JSONValue* executableData);
		bool initializeAudio(Json::JSONValue* executableData);
		Json::JSONValue* readDataJson();

		std::string _gameName;

		std::string _startingSceneFile;
		std::string _startingSceneName;

		LocoMotor::SceneManager* _scnManager;

		std::string _startScene;
		bool _exit;
		static Engine* _instance;
	};
}

#endif // !LOCOMOTOR_ENGINE
