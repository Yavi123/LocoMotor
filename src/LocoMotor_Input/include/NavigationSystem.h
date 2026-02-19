#pragma once
#ifndef LM_NAVIGATION_SYSTEM
#define LM_NAVIGATION_SYSTEM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <list>
#include "LMVector.h"

namespace LocoMotor {
	namespace Input {
		class Selectable;
		class NavigationSystem {
		public:
			static bool Init();
			static void Release();
			static NavigationSystem* GetInstance();

			MOTOR_API void select(Selectable* s);

			void deSelect();
			Selectable* getSelected();

			void addSelectable(Selectable* s);
			void removeSelectable(Selectable* s);

			void updateNav();
		private:

			static NavigationSystem* _instance;

			Selectable* _currentlySelected;
			Vector2 _lastJoystickValues;
			std::list<Selectable*> _allValidSelectables;
		};
	}
}

#endif
