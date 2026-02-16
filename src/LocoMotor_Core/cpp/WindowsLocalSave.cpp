#include "LocalSave.h"
#include "Platform.h"
#include <windows.h>

std::string LocoMotor::Porting::LocalSave::lastKeyName = "Testing";
LocoMotor::Platform* LocoMotor::Platform::_instance = nullptr;

void LocoMotor::Porting::LocalSave::SetRegisterInt(const std::string& key, int val) {

	SetRegisterGeneric(key, &val, sizeof(int));
}

int LocoMotor::Porting::LocalSave::GetRegisterInt(const std::string& key, int defaultValue) {

	return *(int*)(GetRegisterGeneric(key, &defaultValue, sizeof(int)));
}

void LocoMotor::Porting::LocalSave::SetRegisterFloat(const std::string& key, float val) {

	SetRegisterGeneric(key, &val, sizeof(float));
}

float LocoMotor::Porting::LocalSave::GetRegisterFloat(const std::string& key, float defaultValue) {

	return *(float*)(GetRegisterGeneric(key, &defaultValue, sizeof(float)));
}

void LocoMotor::Porting::LocalSave::SetRegisterString(const std::string& key, const std::string& val) {

}

std::string LocoMotor::Porting::LocalSave::GetRegisterString(const std::string& key, const std::string& defaultValue) {
	return std::string();
}

void LocoMotor::Porting::LocalSave::SetRegisterGeneric(const std::string& key, void* val, int size) {

	DWORD dataSize = DWORD(size);

	auto st = std::string("SOFTWARE\\LocoMotor\\") + lastKeyName;

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

void* LocoMotor::Porting::LocalSave::GetRegisterGeneric(const std::string& key, void* defVal, int size) {

	DWORD dataSize = DWORD(size);

	auto st = std::string("SOFTWARE\\LocoMotor\\") + lastKeyName;

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
