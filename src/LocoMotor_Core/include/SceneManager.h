#pragma once
#ifndef LOCOMOTOR_SCENEMANAGER
#define LOCOMOTOR_SCENEMANAGER
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <string>
#include <unordered_map>
#include "SceneDefs.h"

namespace LocoMotor {
	class Scene;

	class SceneManager {
	public:
		static bool Init();
		static void Release();
		MOTOR_API static SceneManager* GetInstance();

		/// @brief Changes to the scene with the given name, if it is not found, nothing will happen.
		/// @param name Name of the scene
		MOTOR_API void changeScene(const std::string& name);

		MOTOR_API void reloadScene();

		// En la primera iteracion da error no esta asignada esta variable
		MOTOR_API Scene* getActiveScene() {
			return _activeScene;
		}

		/// @brief Loads a scene form the given file
		/// @param path Path to a .lua file defining the scene
		/// @param name Name of the scene inside the Lua file
		MOTOR_API void loadScene(const std::string& path, const std::string& name);
		/// @brief updates the state of the scenes
		void update(float dT);
		/// @brief This method is called every fixed time step (16ms by default)
		void fixedUpdate();
	private:
		static SceneManager* _instance;
		SceneManager();
		~SceneManager();

		/// @brief Creates a new scene with the name provided. Method created for testing pursposes
		/// @param name Name for the scene
		/// @param sceneMap Map with the info to generate the scene when needed
		Scene* createScene(const std::string& name, const std::string& path, const SceneMap& sceneMap);

		std::unordered_map<std::string, Scene*> _scenes;
		Scene* _activeScene;
		Scene* _toStart;
		float _lastFrameTime;
		float _dt;
	};
}
#endif