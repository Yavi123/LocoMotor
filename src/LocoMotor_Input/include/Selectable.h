#pragma once
#ifndef LM_NAVIGATION_SELECTABLE
#define LM_NAVIGATION_SELECTABLE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"

namespace LocoMotor {
	namespace Input {
		class NavigationSystem;
		class Selectable : public Component {
		public:
			Selectable();
			~Selectable();

			MOTOR_API bool upTriggered() const;
			MOTOR_API bool downTriggered() const;
			MOTOR_API bool leftTriggered() const;
			MOTOR_API bool rightTriggered() const;
			MOTOR_API bool submitTriggered() const;
			MOTOR_API bool cancelTriggered() const;
			MOTOR_API bool onSelected() const;
			MOTOR_API bool onDeselected() const;

			MOTOR_API void setSelected();

			void actionUp();
			void actionDown();
			void actionLeft();
			void actionRight();
			void actionSubmit();
			void actionCancel();
			void actionSelected();
			void actionUnSelected();

			void resetAction();

			Selectable* getOnUp();
			Selectable* getOnDown();
			Selectable* getOnLeft();
			Selectable* getOnRight();

		protected:

			bool setParameters(ComponentMap& params) override;

			void start() override;
			void onEnable() override;
			void update(float dT) override { };
			void onDisable() override;

		private:
			bool _startSelected;

			Selectable* _up;
			Selectable* _down;
			Selectable* _left;
			Selectable* _right;

			std::string _upName;
			std::string _downName;
			std::string _leftName;
			std::string _rightName;

			__int8 _actionsThisFrame;

			NavigationSystem* _navSystem;
		};
	}
}

#endif
