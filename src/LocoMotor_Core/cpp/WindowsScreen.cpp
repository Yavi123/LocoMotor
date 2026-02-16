#include "Screen.h"
#include <windows.h>

int LocoMotor::Porting::Screen::GetTotalWidth() {
	return GetSystemMetrics(SM_CXSCREEN);
}

int LocoMotor::Porting::Screen::GetTotalHeight() {
	return GetSystemMetrics(SM_CYSCREEN);
}

int LocoMotor::Porting::Screen::GetDesiredWidth() {
	return GetSystemMetrics(SM_CXSCREEN);
}

int LocoMotor::Porting::Screen::GetDesiredHeight() {
	return GetSystemMetrics(SM_CYSCREEN);
}

LocoMotor::Porting::Screen::~Screen() {
}
