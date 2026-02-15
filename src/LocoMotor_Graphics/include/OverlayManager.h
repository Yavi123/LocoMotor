#pragma once
#ifndef OVERLAY_MANAGER
#define OVERLAY_MANAGER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace Ogre {
	class SceneManager;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
	class OverlayContainer;
}

namespace LocoMotor {

	template<typename int>
	class Vector;
	using Vector2 = Vector<2>;

	namespace Graphics {

		class MOTOR_API OverlayManager {
		public:
			OverlayManager();
			~OverlayManager();

			/// @brief Inits the canvas to the sceneManager
			/// @return whether it went well or not (abort)
			static bool Init();

			/// @brief Get a reference to the singleton instance
			/// @return bru h
			static OverlayManager* GetInstance();

			/// @brief Destroys the canvas
			static void Release();

			/// @brief Returns true if there is an instance of the singleton active
			static bool IsInitialized();

			static Vector2 stringToAnchors(const std::string& s);
			static Vector2 stringToPosition(const std::string& s);

			Ogre::OverlayManager* getOgreOverlayManager();
			Ogre::OverlaySystem* getOgreSystem();

		private:

			bool init();

			Ogre::OverlaySystem* _ovrsys;

			Ogre::OverlayManager* _ogrOverlayManager;

			static OverlayManager* _instance;

			static unsigned int _numOfCanvas;

		};
	}

}

#endif