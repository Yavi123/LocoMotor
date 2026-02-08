#include <iostream>
#include "Engine.h"

#include "windows.h"

// Para que no salga la consola hay que cambiar una propiedad en vinculador->sistema, y utilizar la funcion main de windows (WinMain)
// Como solo queremos que pase en release, hacemos este #ifdef
#ifdef _DEBUG
#include "CheckML.h"
#define LocoMotor_Main	main
#define Main_Args       //HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#else

#define LocoMotor_Main	WinMain
#define Main_Args		HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow
#endif

// typedef de los metodos que vamos a encontrar en la dll del Juego
typedef const char* (CALLBACK* InitJuegoFunc)(LocoMotor::Engine* m);

static bool loadGameFromDLL(HINSTANCE& g6Game) {
	LPCWSTR dllName;
	InitJuegoFunc initJuego;

#ifdef _DEBUG
	dllName = L"g6Game_d";
#else
	dllName = L"g6Game";
#endif // _DEBUG

	g6Game = LoadLibrary(dllName);
	if (g6Game != NULL) {

		// Buscamos la funcion, notese que no hace falta hacer lo de Wide Char
		LPCSTR functionName = LPCSTR("InitJuego");
		initJuego = (InitJuegoFunc) GetProcAddress(g6Game, functionName);

		if (initJuego != NULL) {

			auto result = initJuego(LocoMotor::Engine::GetInstance());
			std::cout << "\033[1;36m" << result << "\033[0m" << std::endl;

			return true;
		}
		else {
			std::cerr << "\033[1;31m" << "DLL EXPLICIT LOADING ERROR: '" << functionName << "' function couldn't be executed" << "\033[0m" << std::endl;
		}
	}
	else {
		// Conversion de LPCWSTR a string, por legibilidad
		int strLength
			= WideCharToMultiByte(CP_UTF8, 0, dllName, -1,
								  nullptr, 0, nullptr, nullptr);

		// Create a std::string with the determined length 
		std::string str(strLength, 0);

		// Perform the conversion from LPCWSTR to std::string 
		WideCharToMultiByte(CP_UTF8, 0, dllName, -1, &str[0],
							strLength, nullptr, nullptr);
		std::cerr << "\033[1;31m" << "DLL EXPLICIT LOADING ERROR: '" << str << "' wasn't found" << "\033[0m" << std::endl;
	}

	return false;
}


int LocoMotor_Main(Main_Args) {

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	bool dllLoaded = false;

	//Load the "Project Settings" file and pass it to the Init

	if (!LocoMotor::Engine::Init()) {
		std::cerr << "\033[1;31m" << "Algo no se inicializó correctamente" << "\033[0m" << std::endl;
		return -1;
	}

	HINSTANCE g6Game = NULL;
	bool successfullyLoaded = loadGameFromDLL(g6Game);

	if (!LocoMotor::Engine::GetInstance()->mainLoop()) {
		LocoMotor::Engine::Release();
		std::cerr << "\033[1;31m" << "Algo salió mal en el bucle principal" << "\033[0m" << std::endl;
		return -1;
	}

	LocoMotor::Engine::Release();

	if (g6Game != NULL) {
		FreeLibrary(g6Game);
	}

	return 0;
}
