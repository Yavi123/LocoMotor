#pragma once
#ifndef LM_SCREEN
#define LM_SCREEN

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor::Platform {

	class Screen {

	public:
		MOTOR_API static int GetTotalWidth();
		MOTOR_API static int GetTotalHeight();

		MOTOR_API static int GetDesiredWidth();
		MOTOR_API static int GetDesiredHeight();

	private:
		Screen();
		~Screen();
	};
}

#endif // LM_LOCALSAVE
