#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <cstdint>
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <string>

union SDL_Event;
typedef struct _SDL_GameController SDL_GameController;

namespace LocoMotor {

	namespace Input {

		class NavigationSystem;

		enum LMScanCode;
		class InputManager {

			// Identidicador de mando
			//using ControllerId = SDL_JoystickID;

		public:
			enum MOTOR_API Axis {
				Horizontal, Vertical
			};

			using ControllerId = int32_t;
			using ListenerFunction = std::function<void(void)>;

			/// @brief Initializes the InputManager singleton
			/// @return Whether the initialize went well or not.
			static bool Init();
			/// @brief Returns the instance of the InputManager singleton
			MOTOR_API static InputManager* GetInstance();
			/// @brief Deletes the instance of the InputManager singleton
			static void Release();



			// KEYBOARD
			/// @brief Returns true only in the frame that key is pressed
			MOTOR_API bool GetKeyDown(const LMScanCode& scanCode);
			/// @brief Returns true when key is pressed
			MOTOR_API bool GetKey(const LMScanCode& scanCode);
			/// @brief Returns true when key is stop pressed
			MOTOR_API bool GetKeyUp(const LMScanCode& scanCode);

			// MOUSE
			/// @brief Returns true only in the frame that mouse is pressed
			MOTOR_API bool GetMouseButtonDown(const int& buttonCode);
			/// @brief Returns true when mouse is pressed
			MOTOR_API bool GetMouseButton(const int& buttonCode);
			/// @brief Returns true when mouse is stop pressed
			MOTOR_API bool GetMouseButtonUp(const int& buttonCode);
			/// @brief Returns the position of the mouse in screen
			MOTOR_API std::pair<int, int> GetMousePos();

			// Controller

			/// @brief Returns true only in the frame that controller button is pressed
			MOTOR_API bool GetButtonDown(ControllerId controllerId, const int& buttonCode);
			/// @brief Returns true when controller button is pressed
			MOTOR_API bool GetButton(ControllerId controllerId, const int& buttonCode);
			/// @brief Returns true when controller button is stop pressed
			MOTOR_API bool GetButtonUp(ControllerId controllerId, const int& buttonCode);
			/// @brief Returns the inclination value of the joystick
			/// @param joystickIndex 0 -> left joystick | 1 ->right joystick
			/// @param axis Horizontal o Vertical
			MOTOR_API float GetJoystickValue(ControllerId controllerId, const int& joystickIndex, const Axis& axis);
			/// @brief Returns the inclination value of the joystick
			/// @param triggerIndex 0 -> left trigger | 1 ->right trigger
			MOTOR_API float GetTriggerValue(ControllerId controllerId, const int& triggerIndex);


			// EVENT MANAGER

			/// @brief Register all input related events and save it in the respective value
			bool RegisterEvents();

			/// @brief Manages keyboard events
			void ManageKeyboardEvents(const SDL_Event& event);
			/// @brief Manages controller events
			void ManageControllerEvents(const SDL_Event& event);
			/// @brief Manages mouse events
			void ManageMouseEvents(const SDL_Event& event);

			/// @brief Returns true if controller is ready to use
			void ControllerDeviceAdded(const ControllerId& controller);
			/// @brief Removes the controller
			void ControllerDeviceRemoved(const ControllerId& controller);

			// Las teclas que hayan llamado a los eventos SDL_KEYDOWN y SDL_KEYUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame keyboard inputs boolean
			void ResetKeyboardInputs();
			// Los botones que hayan llamado a los eventos SDL_MOUSEBUTTONDOWN y SDL_MOUSEBUTTONUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame mouse inputs boolean
			void ResetMouseInputs();
			// Los botones que hayan llamado a los eventos SDL_CONTROLLERBUTTONDOWN y SDL_CONTROLLERBUTTONUP en el frame anterior,
			// Tienen las variables de Down/Up activas, solo queremos que esten activas un frame, por lo tanto
			// la funcion de este metodo es resetear esas variables y ponerlas a False

			/// @brief Resets the last frame controller inputs boolean
			void ResetControllerInputs();


			// EXTRA CONTROLLER UTILITY

			/// @brief Sets the controller led in RGB
			MOTOR_API void SetControllerLedColor(ControllerId controllerId, int r, int g, int b);

			/// @brief Sets the controller rumble with a intensity and a duration in seconds
			MOTOR_API void RumbleController(ControllerId controllerId, const float& intensity, const float& durationInSec);


			// Devuelve los id de todos los mandos que se hayan desconectado este frame
			MOTOR_API const std::list<ControllerId>& getCurrentlyConnectedControllers() {
				return _controllers;
			}

			// Devuelve los id de todos los mandos que se hayan conectado este frame
			MOTOR_API const std::list<ControllerId>& getOnConnectControllers() {
				return _connectedControllers;
			}

			// Devuelve los id de todos los mandos que se hayan desconectado este frame
			MOTOR_API const std::list<ControllerId>& getOnDisconnectControllers() {
				return _disconnectedControllers;
			}

			MOTOR_API static ControllerId invalidControllerId() {
				return -1;
			}


			// Suscribe un metodo para ser notificado cuando se conecte/desconecte un mando
			MOTOR_API void addListener(const ListenerFunction& listener) {
				_listeners.push_back(listener);
			}

			void onControllersChange() {
				for (const auto& listener : _listeners)
					listener();
			}

			// Methods for Lua Scripting, since it doesn't support enums
			/// @brief Returns true only in the frame that key is pressed
			MOTOR_API bool GetKeyDownStr(const std::string& scanCode);
			/// @brief Returns true when key is pressed
			MOTOR_API bool GetKeyStr(const std::string& scanCode);
			/// @brief Returns true when key is stop pressed
			MOTOR_API bool GetKeyUpStr(const std::string& scanCode);
			//Controller
			/// @brief Returns true only in the frame that controller button is pressed
			MOTOR_API bool GetButtonDownStr(ControllerId controllerId, const std::string& buttonCode);
			/// @brief Returns true when controller button is pressed
			MOTOR_API bool GetButtonStr(ControllerId controllerId, const std::string& buttonCode);
			/// @brief Returns true when controller button is stop pressed
			MOTOR_API bool GetButtonUpStr(ControllerId controllerId, const std::string& buttonCode);
			/// @brief Returns the inclination value of the joystick
			/// @param joystickIndex 0 -> left joystick | 1 ->right joystick
			/// @param axis Horizontal o Vertical
			MOTOR_API float GetJoystickValueStr(ControllerId controllerId, const int& joystickIndex, const std::string& axis);
		protected:

			static InputManager* _instance;

			/// @brief Creates a new InputManager.
			InputManager();
			~InputManager() {};

			bool init();

			void initStrsMaps();
			void initScanCodesStr();
			void initControllerStr();
			void initAxisStr();

			struct KeyState {
				bool down = false;
				bool isPressed = false;
				bool up = false;
			};

			// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de las teclas
			KeyState _keyboardKeys[512];
			// Almacena el estado del raton
			KeyState _mouseButtons[6];
			// Vector que almacena que teclas deben ser refrescadas despues de cada frame
			std::vector<int> _keyboardInputs_ToReset;
			// Vector que almacena que botones del raton deben ser refrescadas despues de cada frame
			std::vector<int> _mouseInputs_ToReset;

			// Posicion del raton en la pantalla
			std::pair<int, int>_mousePos;


			// Joysticks
			const int _JOYSTICKDEADZONE_MIN = 10000;
			const int _JOYSTICKDEADZONE_MAX = 32000;

			// Triggers
			const int _TRIGGERSVALUE_MIN = 0;
			const int _TRIGGERSVALUE_MAX = 64000;


			struct LMController {

				// Almacena el estado de todas las teclas en un mismo array ordenadas por el ScanCode de los botones del mando
				KeyState _controllerButtons[21];

				// Vector que almacena que botones del mando deben ser refrescadas despues de cada frame
				std::vector<int> _controllerInputs_ToReset;

				// Joysticks
				float _joystickAxis[4]; // cuatro espacios : dos ejes en cada uno de los dos joysticks

				// Triggers
				float _triggersValue[2]; // dos espacios : uno por cada trigger en el mando
			};


			// Contiene todos los mandos conectados actualmente segun su identificador de sdl
			std::unordered_map<ControllerId, LMController> _currentControllers;

			// Contiene los Ids de los mandos, ordenados por orden de conexion
			std::list<ControllerId> _controllers;

			// Ids de los mandos que se han conectado este frame
			std::list<ControllerId> _connectedControllers;
			// Ids de los mandos que se han desconectado este frame
			std::list<ControllerId> _disconnectedControllers;

			std::vector<ListenerFunction> _listeners;

			std::unordered_map<std::string, LMScanCode> _scanCodeStrs;
			std::unordered_map<std::string, int> _ctlrCodeStrs;
			std::unordered_map<std::string, Axis> _axisStrs;

			NavigationSystem* _nav;
		};
	}
}

#endif