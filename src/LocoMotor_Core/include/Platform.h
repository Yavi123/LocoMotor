#pragma once
#include <list>
#include <functional>
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
		static bool Init() {
			_instance = new Platform();
			return true;
		};
		static void Release() {
			delete _instance;
			_instance = nullptr;
		};
		static Platform* GetInstance() {
			return _instance;
		};

		std::function<void(int, int)> windowResize;
		std::function<void(int, int)> windowMove;

	private:

		static Platform* _instance;
	};
}

#endif
