#include "Screen.h"
#include <windows.h>

int LocoMotor::Platform::Screen::GetTotalWidth() {
	return GetSystemMetrics(SM_CXSCREEN);
}

int LocoMotor::Platform::Screen::GetTotalHeight() {
	return GetSystemMetrics(SM_CYSCREEN);
}

int LocoMotor::Platform::Screen::GetDesiredWidth() {
	return GetSystemMetrics(SM_CXSCREEN);
}

int LocoMotor::Platform::Screen::GetDesiredHeight() {
	return GetSystemMetrics(SM_CYSCREEN);
}

LocoMotor::Platform::Screen::~Screen() {
}
