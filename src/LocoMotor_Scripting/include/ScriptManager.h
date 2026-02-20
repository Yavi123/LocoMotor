#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
struct lua_State;
#include <functional>
#include <vector>
#include <iostream>
namespace LocoMotor {
	class LuaBehaviour;
	namespace Scripting {
		class MOTOR_API ScriptManager {
		public:
			static bool Init();
			static void Release();
			static ScriptManager* GetInstance();
			void gcCollect();
			bool loadScript(const std::string& name, LuaBehaviour* behaviour);

		private:
			ScriptManager();
			~ScriptManager();
			bool initLua();
			void registerToLua();
			void registerApi();
			void registerCore();
			void registerGraphics();
			void registerInput();
			void registerPhysics();
			void registerSound();
			static ScriptManager* _instance;
			lua_State* _luaState;
		};
	}
}
#endif