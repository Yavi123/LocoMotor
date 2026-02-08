#include "InputManager.h"
#include <iostream>
#include <algorithm>

#include <SDL.h>
#include "LMInputs.h"
#include "GamepadMappings.h"

#include <cassert>

using namespace LocoMotor;
using namespace Input;

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() {
	_mousePos.first = 0;
	_mousePos.second = 0;
}

bool InputManager::Init() {
	assert(_instance == nullptr);
	_instance = new InputManager();

	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

bool InputManager::init() {

	if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER)) {

		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);

		if (SDL_GameControllerAddMapping(GAMEPAD_MAPPINGS) >= 0)
			std::cout << "Gamecontroller Mappings Loaded" << "\n";
		else
			std::cerr << "\033[1;31m" << "Gamecontroller Mappings NOT Loaded" << "\033[0m" << std::endl;
	}

	initStrsMaps();
	return true;
}

void LocoMotor::Input::InputManager::initStrsMaps() {
	initScanCodesStr();
	initControllerStr();
	initAxisStr();
}

void LocoMotor::Input::InputManager::initScanCodesStr() {
	_scanCodeStrs = std::unordered_map<std::string, LMScanCode>();
	_scanCodeStrs.insert({ "A", LMKS_A });
	_scanCodeStrs.insert({ "B", LMKS_B });
	_scanCodeStrs.insert({ "C", LMKS_C });
	_scanCodeStrs.insert({ "D", LMKS_D });
	_scanCodeStrs.insert({ "E", LMKS_E });
	_scanCodeStrs.insert({ "F", LMKS_F });
	_scanCodeStrs.insert({ "G", LMKS_G });
	_scanCodeStrs.insert({ "H", LMKS_H });
	_scanCodeStrs.insert({ "I", LMKS_I });
	_scanCodeStrs.insert({ "J", LMKS_J });
	_scanCodeStrs.insert({ "K", LMKS_K });
	_scanCodeStrs.insert({ "L", LMKS_L });
	_scanCodeStrs.insert({ "M", LMKS_M });
	_scanCodeStrs.insert({ "N", LMKS_N });
	_scanCodeStrs.insert({ "O", LMKS_O });
	_scanCodeStrs.insert({ "P", LMKS_P });
	_scanCodeStrs.insert({ "Q", LMKS_Q });
	_scanCodeStrs.insert({ "R", LMKS_R });
	_scanCodeStrs.insert({ "S", LMKS_S });
	_scanCodeStrs.insert({ "T", LMKS_T });
	_scanCodeStrs.insert({ "U", LMKS_U });
	_scanCodeStrs.insert({ "V", LMKS_V });
	_scanCodeStrs.insert({ "W", LMKS_W });
	_scanCodeStrs.insert({ "X", LMKS_X });
	_scanCodeStrs.insert({ "Y", LMKS_Y });
	_scanCodeStrs.insert({ "Z", LMKS_Z });
	_scanCodeStrs.insert({ "RETURN", LMKS_RETURN });
	_scanCodeStrs.insert({ "ESCAPE", LMKS_ESCAPE });
	_scanCodeStrs.insert({ "BACKSPACE", LMKS_BACKSPACE });
	_scanCodeStrs.insert({ "TAB", LMKS_TAB });
	_scanCodeStrs.insert({ "SPACE", LMKS_SPACE });
	_scanCodeStrs.insert({ "MINUS", LMKS_MINUS });
	_scanCodeStrs.insert({ "EQUALS", LMKS_EQUALS });
	_scanCodeStrs.insert({ "LEFTBRACKET", LMKS_LEFTBRACKET });
	_scanCodeStrs.insert({ "RIGHTBRACKET", LMKS_RIGHTBRACKET });
	_scanCodeStrs.insert({ "BACKSLASH", LMKS_BACKSLASH });
	_scanCodeStrs.insert({ "SEMICOLON", LMKS_SEMICOLON });
	_scanCodeStrs.insert({ "APOSTROPHE", LMKS_APOSTROPHE });
	_scanCodeStrs.insert({ "GRAVE", LMKS_GRAVE });
	_scanCodeStrs.insert({ "COMMA", LMKS_COMMA });
	_scanCodeStrs.insert({ "PERIOD", LMKS_PERIOD });
	_scanCodeStrs.insert({ "SLASH", LMKS_SLASH });
	_scanCodeStrs.insert({ "CAPSLOCK", LMKS_CAPSLOCK });
	_scanCodeStrs.insert({ "F1", LMKS_F1 });
	_scanCodeStrs.insert({ "F2", LMKS_F2 });
	_scanCodeStrs.insert({ "F3", LMKS_F3 });
	_scanCodeStrs.insert({ "F4", LMKS_F4 });
	_scanCodeStrs.insert({ "F5", LMKS_F5 });
	_scanCodeStrs.insert({ "F6", LMKS_F6 });
	_scanCodeStrs.insert({ "F7", LMKS_F7 });
	_scanCodeStrs.insert({ "F8", LMKS_F8 });
	_scanCodeStrs.insert({ "F9", LMKS_F9 });
	_scanCodeStrs.insert({ "F10", LMKS_F10 });
	_scanCodeStrs.insert({ "F11", LMKS_F11});
	_scanCodeStrs.insert({ "F12", LMKS_F12 });
	_scanCodeStrs.insert({ "PRINTSCREEN", LMKS_PRINTSCREEN });
	_scanCodeStrs.insert({ "SCROLLLOCK", LMKS_SCROLLLOCK });
	_scanCodeStrs.insert({ "PAUSE", LMKS_PAUSE });
	_scanCodeStrs.insert({ "INSERT", LMKS_INSERT });
	_scanCodeStrs.insert({ "HOME", LMKS_HOME });
	_scanCodeStrs.insert({ "PAGEUP", LMKS_PAGEUP });
	_scanCodeStrs.insert({ "DELETE", LMKS_DELETE });
	_scanCodeStrs.insert({ "END", LMKS_END });
	_scanCodeStrs.insert({ "PAGEDOWN", LMKS_PAGEDOWN });
	_scanCodeStrs.insert({ "RIGHT", LMKS_RIGHT });
	_scanCodeStrs.insert({ "LEFT", LMKS_LEFT });
	_scanCodeStrs.insert({ "DOWN", LMKS_DOWN });
	_scanCodeStrs.insert({ "UP", LMKS_NUMLOCKCLEAR });
	_scanCodeStrs.insert({ "KP_DIVIDE", LMKS_KP_DIVIDE });
	_scanCodeStrs.insert({ "KP_MULTIPLY", LMKS_KP_MULTIPLY });
	_scanCodeStrs.insert({ "KP_MINUS", LMKS_KP_MINUS });
	_scanCodeStrs.insert({ "KP_PLUS", LMKS_KP_PLUS });
	_scanCodeStrs.insert({ "KP_ENTER", LMKS_KP_ENTER });
	_scanCodeStrs.insert({ "KP_1", LMKS_KP_1 });
	_scanCodeStrs.insert({ "KP_2", LMKS_KP_2 });
	_scanCodeStrs.insert({ "KP_3", LMKS_KP_3 });
	_scanCodeStrs.insert({ "KP_4", LMKS_KP_4 });
	_scanCodeStrs.insert({ "KP_5", LMKS_KP_5 });
	_scanCodeStrs.insert({ "KP_6", LMKS_KP_6 });
	_scanCodeStrs.insert({ "KP_7", LMKS_KP_7 });
	_scanCodeStrs.insert({ "KP_8", LMKS_KP_8 });
	_scanCodeStrs.insert({ "KP_9", LMKS_KP_9 });
	_scanCodeStrs.insert({ "KP_0", LMKS_KP_0 });
	_scanCodeStrs.insert({ "KP_PERIOD", LMKS_KP_PERIOD });
	_scanCodeStrs.insert({ "LCTRL", LMKS_LCTRL });
	_scanCodeStrs.insert({ "LSHIFT", LMKS_LSHIFT });
	_scanCodeStrs.insert({ "LALT", LMKS_LALT });
	_scanCodeStrs.insert({ "LGUI", LMKS_LGUI });
	_scanCodeStrs.insert({ "RCTRL", LMKS_RCTRL });
	_scanCodeStrs.insert({ "RSHIFT", LMKS_RSHIFT });
	_scanCodeStrs.insert({ "RALT", LMKS_RALT });
	_scanCodeStrs.insert({ "RGUI", LMKS_RGUI });
	_scanCodeStrs.insert({ "MODE", LMKS_MODE });
}

void LocoMotor::Input::InputManager::initControllerStr() {
	_ctlrCodeStrs = std::unordered_map<std::string, int>();
	_ctlrCodeStrs.insert({ "CONTROLLER_A", LMC_A });
	_ctlrCodeStrs.insert({ "CONTROLLER_B", LMC_B });
	_ctlrCodeStrs.insert({ "CONTROLLER_X", LMC_X });
	_ctlrCodeStrs.insert({ "CONTROLLER_Y", LMC_Y });
	_ctlrCodeStrs.insert({ "CONTROLLER_BACK", LMC_BACK });
	_ctlrCodeStrs.insert({ "CONTROLLER_GUIDE", LMC_GUIDE });
	_ctlrCodeStrs.insert({ "CONTROLLER_START", LMC_START });
	_ctlrCodeStrs.insert({ "CONTROLLER_LEFTSTICK", LMC_LEFTSTICK });
	_ctlrCodeStrs.insert({ "CONTROLLER_RIGHTSTICK", LMC_RIGHTSTICK });
	_ctlrCodeStrs.insert({ "CONTROLLER_LEFTSHOULDER", LMC_LEFTSHOULDER });
	_ctlrCodeStrs.insert({ "CONTROLLER_RIGHTSHOULDER", LMC_RIGHTSHOULDER });
	_ctlrCodeStrs.insert({ "CONTROLLER_DPAD_UP", LMC_DPAD_UP });
	_ctlrCodeStrs.insert({ "CONTROLLER_DPAD_DOWN", LMC_DPAD_DOWN });
	_ctlrCodeStrs.insert({ "CONTROLLER_DPAD_LEFT", LMC_DPAD_LEFT });
	_ctlrCodeStrs.insert({ "CONTROLLER_DPAD_RIGHT", LMC_DPAD_RIGHT });
	_ctlrCodeStrs.insert({ "CONTROLLER_MISC1", LMC_MISC1 });
	_ctlrCodeStrs.insert({ "CONTROLLER_PADDLE1", LMC_PADDLE1 });
	_ctlrCodeStrs.insert({ "CONTROLLER_PADDLE2", LMC_PADDLE2 });
	_ctlrCodeStrs.insert({ "CONTROLLER_PADDLE3", LMC_PADDLE3 });
	_ctlrCodeStrs.insert({ "CONTROLLER_PADDLE4", LMC_PADDLE4 });
	_ctlrCodeStrs.insert({ "CONTROLLER_TOUCHPAD", LMC_TOUCHPAD });
}

void LocoMotor::Input::InputManager::initAxisStr() {
	_axisStrs = std::unordered_map<std::string, Axis>();
	_axisStrs.insert({ "HORIZONTAL", Horizontal });
	_axisStrs.insert({ "VERTICAL", Vertical });
}

InputManager* InputManager::GetInstance() {
	return _instance;
}

void InputManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

// KEYBOARD
bool InputManager::GetKeyDown(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].down;
}

bool InputManager::GetKey(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].isPressed;
}

bool InputManager::GetKeyUp(const LMScanCode& scanCode) {
	return _keyboardKeys[scanCode].up;
}

// MOUSE
bool InputManager::GetMouseButtonDown(const int& buttonCode) {
	return _mouseButtons[buttonCode].down;
}

bool InputManager::GetMouseButton(const int& buttonCode) {
	return _mouseButtons[buttonCode].isPressed;
}

bool InputManager::GetMouseButtonUp(const int& buttonCode) {
	return _mouseButtons[buttonCode].up;
}

std::pair<int, int> InputManager::GetMousePos() {
	return _mousePos;
}

// CONTROLLER

	// BUTTONS
bool InputManager::GetButtonDown(ControllerId controllerId, const int& buttonCode) {
	return _currentControllers[controllerId]._controllerButtons[buttonCode].down;
}

bool InputManager::GetButton(ControllerId controllerId, const int& buttonCode) {
	return _currentControllers[controllerId]._controllerButtons[buttonCode].isPressed;
}

bool InputManager::GetButtonUp(ControllerId controllerId, const int& buttonCode) {
	return _currentControllers[controllerId]._controllerButtons[buttonCode].up;
}

	// JOYSTICKS
float InputManager::GetJoystickValue(ControllerId controllerId, const int& joystickIndex, const Axis& axis) {

	if (joystickIndex == 0) {

		if (axis == Horizontal)
			return _currentControllers[controllerId]._joystickAxis[0];
		else if (axis == Vertical)
			return _currentControllers[controllerId]._joystickAxis[1];
	}
	else if (joystickIndex == 1) {

		if (axis == Horizontal)
			return _currentControllers[controllerId]._joystickAxis[2];
		else if (axis == Vertical)
			return _currentControllers[controllerId]._joystickAxis[3];
	}
	return 0.f;
}

	// TRIGGER
float InputManager::GetTriggerValue(ControllerId controllerId, const int& triggerIndex) {
	if (triggerIndex == 0 || triggerIndex == 1)
		return _currentControllers[controllerId]._triggersValue[triggerIndex];
		//return _triggersValue[triggerIndex];
	else
		return 0.0f;
}


bool InputManager::RegisterEvents() {

	// RESETEAR TECLAS Y BOTONES

	// Si hay al menos una tecla del frame anterior que necesite ser reseteada
	if (_keyboardInputs_ToReset.size() != 0)
		ResetKeyboardInputs();

	if (_mouseInputs_ToReset.size() != 0)
		ResetMouseInputs();

	// Borrar los inputs a resetear de cada mando conectado
	ResetControllerInputs();

	// RESETEAR LISTAS DE MANDOS
	_connectedControllers.clear();
	_disconnectedControllers.clear();


	// Recoger todos los eventos de esta ejecucion y procesarlos uno a uno
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		SDL_Scancode scanCode = event.key.keysym.scancode;

		// Eventos para salir del bucle principal
		if (event.type == SDL_QUIT)
			return true;


		// Manejar todos los tipos de eventos

		// Almacenar eventos de teclado en el array "keyboardKeys"
		ManageKeyboardEvents(event);

		// Gestionar eventos del raton
		ManageMouseEvents(event);

		// Almacenar eventos de mando en el array "controllerButtons" (a parte de eventos Add/Remove del mando)
		ManageControllerEvents(event);
	}
	return false;
}

void InputManager::ManageKeyboardEvents(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisKey.isPressed) {
			thisKey.down = true;
			thisKey.isPressed = true;
			_keyboardInputs_ToReset.push_back(scanCode);
		}
	}

	else if (event.type == SDL_KEYUP) {
		SDL_Scancode scanCode = event.key.keysym.scancode;
		KeyState& thisKey = _keyboardKeys[scanCode];

		thisKey.isPressed = false;
		thisKey.up = true;
		_keyboardInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ManageControllerEvents(const SDL_Event& event) {

	if (event.type == SDL_CONTROLLERDEVICEADDED) {

		// Mando que ha generado el evento
		SDL_GameController* handler = SDL_GameControllerOpen(event.cdevice.which);
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(handler);
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
		ControllerId connectedDevice = joystickID;

		ControllerDeviceAdded(connectedDevice);
		std::cout << "Controller added" << "\n";
	}

	if (event.type == SDL_CONTROLLERDEVICEREMOVED) {

		// Mando que ha generado el evento
		SDL_GameController* handler = SDL_GameControllerFromInstanceID(event.cdevice.which);
		SDL_Joystick* joystick = SDL_GameControllerGetJoystick(handler);
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
		ControllerId disconnectedDevice = joystickID;

		// Cerrar mando de SDL
		SDL_GameControllerClose(handler);

		ControllerDeviceRemoved(disconnectedDevice);
		std::cout << "Controller removed" << "\n";
	}

	if (event.type == SDL_CONTROLLERBUTTONDOWN) {

		int buttonCode = event.cbutton.button;
		ControllerId id = 0;
		KeyState& thisButton = _currentControllers[event.jaxis.which]._controllerButtons[buttonCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;

			_currentControllers[event.jaxis.which]._controllerInputs_ToReset.push_back(buttonCode);
		}
	}

	if (event.type == SDL_CONTROLLERBUTTONUP) {

		int buttonCode = event.cbutton.button;
		ControllerId id = 0;
		KeyState& thisButton = _currentControllers[event.cdevice.which]._controllerButtons[buttonCode];

		// Actualizar valores
		thisButton.isPressed = false;
		thisButton.up = true;

		_currentControllers[event.jaxis.which]._controllerInputs_ToReset.push_back(buttonCode);
	}

	if (event.type == SDL_CONTROLLERAXISMOTION) {

		Sint16 joystickValue = event.caxis.value;

		// Limitador maximo
		if (joystickValue > _JOYSTICKDEADZONE_MAX)
			joystickValue = _JOYSTICKDEADZONE_MAX;
		else if (joystickValue < -_JOYSTICKDEADZONE_MAX)
			joystickValue = -_JOYSTICKDEADZONE_MAX;




		int axis = event.caxis.axis;
		if (axis < 4) {
			// Si se inclina el joystick lo suficiente, guardar su valor
			if (joystickValue > _JOYSTICKDEADZONE_MIN
				|| joystickValue < -_JOYSTICKDEADZONE_MIN) {

				float absJoystickValue = fabsf(joystickValue);
				int sign = (int) (joystickValue / absJoystickValue);

				// Convertir el valor en un valor entre 0 y 1
				float normalizedValue = ((float) (absJoystickValue - _JOYSTICKDEADZONE_MIN)) / ((float) (_JOYSTICKDEADZONE_MAX - _JOYSTICKDEADZONE_MIN));

				normalizedValue *= sign;

				_currentControllers[event.jaxis.which]._joystickAxis[axis] = normalizedValue;
			}
			else
				_currentControllers[event.jaxis.which]._joystickAxis[axis] = 0;
		}

	}
	if (event.type == SDL_JOYAXISMOTION) {

		Sint16 triggerValue = event.jaxis.value;

		int axis = event.jaxis.axis;
		if (axis > 3) {
			axis -= 4;
			float auxValue = triggerValue + _TRIGGERSVALUE_MAX / 2.f;
			float finalValue = std::clamp(auxValue / _TRIGGERSVALUE_MAX, 0.0f, 1.0f);

			if (axis == 0 || axis == 1)
				_currentControllers[event.jaxis.which]._triggersValue[axis] = finalValue;
		}
	}

}

void InputManager::ManageMouseEvents(const SDL_Event& event) {
	if (event.type == SDL_MOUSEMOTION) {
		_mousePos.first = event.motion.x;
		_mousePos.second = event.motion.y;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		// Comprobar si la tecla no esta siendo presionada actualmente
		if (!thisButton.isPressed) {
			thisButton.down = true;
			thisButton.isPressed = true;
			_mouseInputs_ToReset.push_back(scanCode);
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		int scanCode = event.button.button;
		KeyState& thisButton = _mouseButtons[scanCode];

		thisButton.isPressed = false;
		thisButton.up = true;
		_mouseInputs_ToReset.push_back(scanCode);
	}
}

void InputManager::ControllerDeviceAdded(const ControllerId& controllerAdded) {

	_controllers.push_back(controllerAdded);

	_connectedControllers.push_back(controllerAdded);

	_currentControllers.insert({ controllerAdded, LMController() });
}

void InputManager::ControllerDeviceRemoved(const ControllerId& controllerRemoved) {

	_controllers.remove(controllerRemoved);

	_disconnectedControllers.push_back(controllerRemoved);

	_currentControllers.erase(controllerRemoved);
}


// RESET

void InputManager::ResetKeyboardInputs() {
	for (int i = 0; i < _keyboardInputs_ToReset.size(); i++) {
		// Saber el codigo de la tecla almacenado en el vector "keysToReset"
		int scanCode = _keyboardInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisKey = _keyboardKeys[scanCode];
		thisKey.up = false;
		thisKey.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_keyboardInputs_ToReset.clear();
}

void InputManager::ResetMouseInputs() {
	for (int i = 0; i < _mouseInputs_ToReset.size(); i++) {
		// Saber el codigo del boton del mando
		int buttonCode = _mouseInputs_ToReset[i];
		// Crear una referencia a la tecla y resetear sus variables a false
		KeyState& thisButton = _mouseButtons[buttonCode];
		thisButton.up = false;
		thisButton.down = false;
	}

	// Limpiar las teclas ya reseteadas
	_mouseInputs_ToReset.clear();
}

void InputManager::ResetControllerInputs() {

	for (auto& pair : _currentControllers) {

		LMController& thisController = pair.second;

		for (int i = 0; i < thisController._controllerInputs_ToReset.size(); i++) {
			// Saber el codigo del boton del mando
			int buttonCode = thisController._controllerInputs_ToReset[i];
			// Crear una referencia a la tecla y resetear sus variables a false
			KeyState& thisButton = thisController._controllerButtons[buttonCode];

			thisButton.up = false;
			thisButton.down = false;
		}

		// Limpiar las teclas ya reseteadas
		thisController._controllerInputs_ToReset.clear();
	}
}



// FUNCIONALIDADES DE MANDO EXTRA

// Luz LED
void InputManager::SetControllerLedColor(ControllerId controllerId, int r, int g, int b) {

	SDL_GameController* gameController = SDL_GameControllerFromInstanceID(controllerId);

	if (gameController != nullptr && SDL_GameControllerHasLED(gameController))
		SDL_GameControllerSetLED(gameController, r, g, b);
	else
		std::cout << "[ERROR] Could not change LED color of controller, it has not LED support";
}

// Vibracion
void InputManager::RumbleController(ControllerId controllerId, const float& intensity, const float& durationInSec) {

	if (intensity > 1 || intensity < 0) {
		std::cout << "[ERROR] Could not Rumble controller: Rumble intensity out of range";
		return;
	}

	SDL_GameController* gameController = SDL_GameControllerFromInstanceID(controllerId);

	//if (_currentController != nullptr) {

	if (gameController != nullptr && SDL_GameControllerHasRumble(gameController)) {

		Uint16 rumbleIntensity = (Uint16) (intensity * UINT16_MAX);
		SDL_GameControllerRumble(gameController, rumbleIntensity, rumbleIntensity, (Uint32) (durationInSec * 1000));
	}
	else
		std::cout << "[ERROR] Could not Rumble controller, it has not Rumble support";
}

bool LocoMotor::Input::InputManager::GetKeyDownStr(const std::string& scanCode) {
	if (_scanCodeStrs.count(scanCode) == 0) {
		std::cout << "Cant recognize scancode " << scanCode << std::endl;
		return false;
	}
	return GetKeyDown(_scanCodeStrs[scanCode]);
}

bool LocoMotor::Input::InputManager::GetKeyStr(const std::string& scanCode) {
	if (_scanCodeStrs.count(scanCode) == 0) {
		std::cout << "Cant recognize scancode " << scanCode << std::endl;
		return false;
	}
	return GetKey(_scanCodeStrs[scanCode]);
}

bool LocoMotor::Input::InputManager::GetKeyUpStr(const std::string& scanCode) {
	if (_scanCodeStrs.count(scanCode) == 0) {
		std::cout << "Cant recognize scancode " << scanCode << std::endl;
		return false;
	}
	return GetKeyUp(_scanCodeStrs[scanCode]);
}

bool LocoMotor::Input::InputManager::GetButtonDownStr(const ControllerId controllerId, const std::string& buttonCode) {
	if (_ctlrCodeStrs.count(buttonCode) == 0) {
		std::cout << "Cant recognize button code " << buttonCode << std::endl;
		return false;
	}
	return GetButtonDown(controllerId, _ctlrCodeStrs[buttonCode]);
}

bool LocoMotor::Input::InputManager::GetButtonStr(ControllerId controllerId, const std::string& buttonCode) {
	if (_ctlrCodeStrs.count(buttonCode) == 0) {
		std::cout << "Cant recognize button code " << buttonCode << std::endl;
		return false;
	}
	return GetButton(controllerId, _ctlrCodeStrs[buttonCode]);
}

bool LocoMotor::Input::InputManager::GetButtonUpStr(ControllerId controllerId, const std::string& buttonCode) {
	if (_ctlrCodeStrs.count(buttonCode) == 0) {
		std::cout << "Cant recognize button code " << buttonCode << std::endl;
		return false;
	}
	return GetButtonUp(controllerId, _ctlrCodeStrs[buttonCode]);
}

float LocoMotor::Input::InputManager::GetJoystickValueStr(ControllerId controllerId, const int& joystickIndex, const std::string& axis) {
	if (_axisStrs.count(axis) == 0) {
		std::cout << "Cant recognize axis " << axis << std::endl;
		return false;
	}
	return GetJoystickValue(controllerId,joystickIndex,_axisStrs[axis]);
}
