#include "LocalSave.h"
#include <windows.h>

std::string LocoMotor::Platform::LocalSave::_lastKeyName = "Testing";

void LocoMotor::Platform::LocalSave::SetRegisterInt(const std::string& key, int val) {

	SetRegisterGeneric(key, &val, sizeof(int));
}

int LocoMotor::Platform::LocalSave::GetRegisterInt(const std::string& key, int defaultValue) {

	return *(int*)(GetRegisterGeneric(key, &defaultValue, sizeof(int)));
}

void LocoMotor::Platform::LocalSave::SetRegisterFloat(const std::string& key, float val) {

	SetRegisterGeneric(key, &val, sizeof(float));
}

float LocoMotor::Platform::LocalSave::GetRegisterFloat(const std::string& key, float defaultValue) {

	return *(float*)(GetRegisterGeneric(key, &defaultValue, sizeof(float)));
}

void LocoMotor::Platform::LocalSave::SetRegisterString(const std::string& key, const std::string& val) {

}

std::string LocoMotor::Platform::LocalSave::GetRegisterString(const std::string& key, const std::string& defaultValue) {
	return std::string();
}

void LocoMotor::Platform::LocalSave::SetRegisterGeneric(const std::string& key, void* val, int size) {

	DWORD dataSize = DWORD(size);

	auto st = std::string("SOFTWARE\\LocoMotor\\") + _lastKeyName;

	int retCode = ::RegSetKeyValue(
		HKEY_CURRENT_USER,
		LPCWSTR(std::wstring(st.begin(), st.end()).c_str()),
		LPCWSTR(std::wstring(key.begin(), key.end()).c_str()),
		REG_DWORD,
		val,
		dataSize
	);

	if (retCode != ERROR_SUCCESS) {
		return;
	}
}

void* LocoMotor::Platform::LocalSave::GetRegisterGeneric(const std::string& key, void* defVal, int size) {

	DWORD dataSize = DWORD(size);

	auto st = std::string("SOFTWARE\\LocoMotor\\") + _lastKeyName;

	int retCode = ::RegGetValue(
		HKEY_CURRENT_USER,
		LPCWSTR(std::wstring(st.begin(), st.end()).c_str()),
		LPCWSTR(std::wstring(key.begin(), key.end()).c_str()),
		RRF_RT_REG_DWORD,
		nullptr,
		defVal,
		&dataSize
	);

	if (retCode != ERROR_SUCCESS) {

	}

	return defVal;
}
