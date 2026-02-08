#pragma once
#ifndef LM_LOCALSAVE
#define LM_LOCALSAVE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor::Platform {

	class LocalSave {

	public:
		MOTOR_API static const std::string& GetLocalSaveDataPath();

		MOTOR_API static void SetRegisterInt(const std::string& key, int val);
		MOTOR_API static int GetRegisterInt(const std::string& key, int defaultValue = 0);

		MOTOR_API static void SetRegisterFloat(const std::string& key, float val);
		MOTOR_API static float GetRegisterFloat(const std::string& key, float defaultValue = 0.f);

		MOTOR_API static void SetRegisterString(const std::string& key, const std::string& val);
		MOTOR_API static std::string GetRegisterString(const std::string& key, const std::string& defaultValue);

		static std::string lastKeyName;

	private:
		LocalSave();
		~LocalSave();

		static void SetRegisterGeneric(const std::string& key, void* val, int size);
		static void* GetRegisterGeneric(const std::string& key, void* defVal, int size);
	};
}

#endif // LM_LOCALSAVE
