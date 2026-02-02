#pragma once
#ifndef _GRAPHICS_MANAGER_H
#define _GRAPHICS_MANAGER_H

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <map>

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
	class SceneNode;
	class OverlaySystem;
	class Entity;
	class Camera;
	class Light;

	namespace RTShader {
		class ShaderGenerator;
	}
}

struct SDL_Window;
namespace LocoMotor {

	namespace Graphics {

		struct NativeWindowPair {
			Ogre::RenderWindow* render = nullptr;
			SDL_Window* native = nullptr;
		};
		class GraphicsManager {
		public:

			/// @brief Initializes the GraphicsManager singleton
			/// @return Whether the initialize went well or not.
			static bool Init();
			/// @brief Returns the instance of the GraphicsManager singleton
			MOTOR_API static GraphicsManager* GetInstance();
			/// @brief Deletes the instance of the GraphicsManager singleton
			static void Release();
			/// @brief Creates a scene, if you try to create a scene with an already used name, the method will return that scene instead.
			/// @param name Name for the new scene.
			/// @return The newly created scene.
			///	If the name is already taken, the scene with that name will be returned instead.
			void createScene(std::string name);
			/// @brief Renders a frame.
			bool render();
			/// @brief Initializes the window
			/// @param name The Window title
			/// @return
			bool initWindow(std::string name);
			/// @brief 
			/// Returns RenderWindow
			/// @return Render window of Ogre
			Ogre::RenderWindow* getRenderWindow();
			/// @brief
			/// Sets the active scene for the manager
			/// @param name The name of the scene to become active
			void setActiveScene(std::string name);
			/// @brief Returns the render window height
			MOTOR_API int getWindowHeight();
			/// @brief Returns the render window width
			MOTOR_API int getWindowWidth();
			/// @brief Set the fullscreen status of the game
			MOTOR_API void setFullscreen(bool on);
			/// @brief Deactivates a scene
			/// @param name The name of the scene
			void deactivateScene(std::string name);
			/// @brief Creates a node with a name
			Ogre::SceneNode* createNode(std::string name);
			/// @brief Returns a LocoMotor node
			/// @param name The name of the node
			Ogre::SceneNode* getNode(std::string name);
			/// @brief Destroys a node
			/// @param name The name of the node to be destroyed
			void destroyNode(std::string name);
			/// @brief Returns the SceneManager of Ogre
			Ogre::SceneManager* getOgreSceneManager();

		protected:
			Ogre::Root* _root;

			NativeWindowPair _mWindow;

			Ogre::SceneNode* _nodeRoot;

			std::map<std::string , Ogre::SceneManager*> _scenes;

			std::map<std::string, Ogre::SceneNode*> _sceneNodes;

			Ogre::SceneManager* _activeScene;

			Ogre::RTShader::ShaderGenerator* _mShaderGenerator;

			void* _mMaterialMgrListener = nullptr;

			static GraphicsManager* _instance;

			/// @brief Creates a new OgreManager.
			/// @param name The name for the window
			GraphicsManager();
			~GraphicsManager();
			/// @brief Initializes the Ogre library
			/// @return Empty string if success, error message in any other case
			std::string initialize();
			/// @brief Loads the resouces and initializes the RTShaderSytem
			void loadResources();
			/// @brief
			/// Shuts down Ogre and releases all the memory related to it
			void shutdown();



		};
	}
}

#endif
