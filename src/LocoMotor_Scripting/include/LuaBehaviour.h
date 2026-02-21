#pragma once
#ifndef LUABEHAVIOUR_H
#define LUABEHAVIOUR_H
#include "Component.h"
#include <unordered_map>
#include <string>
struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	namespace Scripting {
		class ScriptManager;
	}
	class LuaBehaviour : public Component {
	
		friend class Scripting::ScriptManager;
	public:
		LuaBehaviour();
		~LuaBehaviour();
	protected:
		void awake() override;
		void onEnable() override;
		void start() override;
		void update(float dt) override ;
		void fixedUpdate() override;
		void onDisable() override;
		void onDestroy() override;
		void receiveMessage(const std::string& m) override;
		void OnCollisionEnter(GameObject* other) override;
		void OnCollisionStay(GameObject* other) override;
		void OnCollisionExit(GameObject* other) override;

		bool setParameters(ComponentMap& params) override;
		luabridge::LuaRef getScript() const;
	private:
		bool initBehaviour();
		inline void setLuaContext(lua_State* state) {
			_luaState = state;
		}
		//??
		lua_State* _luaState;
		luabridge::LuaRef* obj = nullptr;
		std::string _name;

	};
}
#endif
