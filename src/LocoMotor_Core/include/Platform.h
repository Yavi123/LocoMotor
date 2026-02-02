#pragma once
#ifndef LM_PLATFORM
#define LM_PLATFORM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

namespace LocoMotor {

	class Platform {

	public:
		static bool Init();
		static void Release();
		MOTOR_API static Platform* GetInstance();

		MOTOR_API static int getDesiredScreenWidth();
		MOTOR_API static int getDesiredScreenHeight();

	};
}

#endif
