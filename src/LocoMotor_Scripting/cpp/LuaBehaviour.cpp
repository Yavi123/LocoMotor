#include "LuaBehaviour.h"
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>
#include "ScriptManager.h"
#include "Engine.h"


LocoMotor::LuaBehaviour::LuaBehaviour() : _luaState(nullptr) {
}

LocoMotor::LuaBehaviour::~LuaBehaviour() {
	if (obj != nullptr) delete obj;
}

void LocoMotor::LuaBehaviour::awake() {
	try {
		luabridge::LuaRef luaAwake = (*obj)["awake"];
		if (!luaAwake.isFunction()) {

			return;
		}
		luaAwake(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
	}
}

void LocoMotor::LuaBehaviour::onEnable() {
	
	try {
		luabridge::LuaRef luaEnable = (*obj)["onEnable"];
		if (!luaEnable.isFunction()) {

			return;
		}
		luaEnable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::start() {
	
	
	try {
		luabridge::LuaRef luaStart = (*obj)["start"];
		if (!luaStart.isFunction()) {
			return;
		}
		luaStart(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;
		
	}
}

void LocoMotor::LuaBehaviour::update(float dt) {
	
	try {
		luabridge::LuaRef luaUpdate = (*obj)["update"];
		if (!luaUpdate.isFunction()) {

			return;
		}
		luaUpdate(*obj, dt);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::fixedUpdate() {
	
	try {
		luabridge::LuaRef luaFixed = (*obj)["fixedUpdate"];
		if (!luaFixed.isFunction()) {

			return;
		}
		luaFixed(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDisable() {
	
	try {
		luabridge::LuaRef luaDisable = (*obj)["onDisable"];
		if (!luaDisable.isFunction()) {

			return;
		}
		luaDisable(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::onDestroy() {
	try {
		luabridge::LuaRef luaDestroy = (*obj)["onDestroy"];
		if (!luaDestroy.isFunction()) {

			return;
		}
		luaDestroy(*obj);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionEnter(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollEnter = (*obj)["onCollisionEnter"];
		if (!luaCollEnter.isFunction()) {
			return;
		}
		luaCollEnter(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionStay(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollStay = (*obj)["onCollisionStay"];
		if (!luaCollStay.isFunction()) {
			return;
		}
		luaCollStay(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

void LocoMotor::LuaBehaviour::OnCollisionExit(GameObject* other) {
	
	try {
		luabridge::LuaRef luaCollExit = (*obj)["onCollisionExit"];
		if (!luaCollExit.isFunction()) {
			return;
		}
		luaCollExit(*obj, other);
	}
	catch (luabridge::LuaException& e) {
		std::cout << e.what() << std::endl;

	}
}

bool LocoMotor::LuaBehaviour::setParameters(ComponentMap& params) {
	for (auto it = params.begin(); it != params.end(); ) {
		if ((*it).first == "scriptName") {
			_name = (*it).second;
			if (!Scripting::ScriptManager::GetInstance()->loadScript(_name, this)) {
				return false;
			}
			if (!initBehaviour()) {
				std::cout << _name << " was not a table" << std::endl;
				return false;
			}
			params.erase(it);
			break;
		
		}
		else {
			++it;
		}
	}
	if (params.size() == 0) return true;
	//Si se esta inicializando con parametros (desde la carga de mapas) creo una tabla de lua con los parametros, porque LuaBridge no tiene un
	//wrapper para poder pasar std::pairs a Lua
	luabridge::LuaRef paramsTable = luabridge::newTable(_luaState);
	for (auto& param : params) {
		paramsTable[param.first] = param.second;
	}
	try {	
		luabridge::LuaRef luaSetParams = (*obj)["setParameters"];
		if (!luaSetParams.isFunction()) {
			std::cout << "Lua Warning: " << "You must define a function called " << _name << ":setParameters(params) in " << _name << ".lua" <<
				"if you want to set the parameters from this component from the scene files" << std::endl;
			return false;
		}
		luabridge::LuaRef ret = luaSetParams(*obj, paramsTable);
		if (ret.isBool()) {
			return ret;
		}
		else {
			std::cout << "Lua Warning: " << _name << ":setParameters should return a boolean. Else it will be assumed to have executed correctly" << std::endl;
			return true;
		}
	}
	catch (luabridge::LuaException e) {
		std::cout << e.what() << std::endl;;
	}
	return true;
	
}

luabridge::LuaRef LocoMotor::LuaBehaviour::getScript() const {
	return *obj;
}

bool LocoMotor::LuaBehaviour::initBehaviour() {

	obj = new luabridge::LuaRef(luabridge::getGlobal(_luaState, _name.c_str()));
	if (!obj->isTable()) {
		std::cout << "Lua Interpreter Warning: No table called " << _name << " on the lua script " << _name << ".lua" << std::endl;
		return false;
	}
	if(obj->isUserdata()) {
		std::cout << "userdata" << _name << std::endl;
	}
	luabridge::setGlobal(_luaState, *obj, _name.c_str());
	return true;
}
