#include "ScriptManager.h"

#include <cmath>
#include <cassert>
#include <functional>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"
#include "LuaBehaviour.h"
#include "Transform.h"
#include "LMVector.h"
#include "LMQuaternion.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Engine.h"
#include "InputManager.h"
#include "RigidBody.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "UIImage.h"
#include "UIText.h"
#include "ParticleSystem.h"
#include "AudioListener.h"
#include "AudioSource.h"
#include "EventEmitter.h"
#include "LocalSave.h"

using namespace LocoMotor;
using namespace LocoMotor::Scripting;

ScriptManager* ScriptManager::_instance = nullptr;

ScriptManager::ScriptManager() : _luaState(nullptr) {}
ScriptManager::~ScriptManager() {
	lua_close(_luaState);
}

bool LocoMotor::Scripting::ScriptManager::initLua() {
	std::cout << "init Lua" << std::endl;
	_luaState = luaL_newstate();
	if (_luaState == nullptr) {
		std::cerr << "[Script error] Could not create lua state" << std::endl;
		return false;
	}
	luaL_openlibs(_luaState);
	registerToLua();
	return true;
}

void LocoMotor::Scripting::ScriptManager::registerToLua() {
	registerCore();
	registerApi();
	registerInput();
	registerGraphics();
	registerPhysics();
	registerSound();
	luabridge::getGlobalNamespace(_luaState)
		.deriveClass<LuaBehaviour, Component>("LuaBehaviour")
		.addFunction("getScript", &LuaBehaviour::getScript)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerApi() {
	luabridge::getGlobalNamespace(_luaState)
		.beginClass<Engine>("Engine")
		.addStaticFunction("Instance", &Engine::GetInstance)
		.addFunction("showWindow", &Engine::showWindow)
		.addFunction("quit", &Engine::quit)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerCore() {
	
	luabridge::getGlobalNamespace(_luaState)
		.beginClass<GameObject>("GameObject")
		.addFunction("transform", &GameObject::getTransform)
		.addFunction("addComponent", &GameObject::addComponent)
		.addFunction("getBehaviour", &GameObject::getComponent<LuaBehaviour>)
		.addFunction("getRigidBody", &GameObject::getComponent<RigidBody>)
		.addFunction("getMeshRenderer", &GameObject::getComponent<MeshRenderer>)
		.addFunction("getParticleSystem", &GameObject::getComponent<Camera>)
		.addFunction("getEventEmitter", &GameObject::getComponent<ParticleSystem>)
		.addFunction("getEventEmitter", &GameObject::getComponent<EventEmitter>)
		.addFunction("getAudioSource", &GameObject::getComponent<AudioSource>)
		.addFunction("getAudioListener", &GameObject::getComponent<AudioListener>)
		.addFunction("getUIText", &GameObject::getComponent<UIText>)
		.addFunction("getUIImage", &GameObject::getComponent<UIImage>)
		.addFunction("getComponent", &GameObject::getComponentByName)
		.addFunction("isActive", &GameObject::isActive)
		.addFunction("setActive", &GameObject::setActive)
		.addFunction("removeComponent", &GameObject::removeComponents)
		.addFunction("getName", &GameObject::getName)
		.endClass()

		.beginClass<Component>("Component")
		.addFunction("setEnabled", &Component::setEnabled)
		.addFunction("isEnabled", &Component::isEnabled)
		.addFunction("gameObject", &Component::getGameObject)
		.endClass()

		.beginClass<Vector2>("Vector2")
		.addStaticFunction("new", &Vector2::createVector2)
		.addFunction("__add", (Vector2(Vector2::*)(const Vector2&) const) & Vector2::operator+)
		.addFunction("__sub", (Vector2(Vector2::*)(const Vector2&) const) & Vector2::operator-)
		.addFunction("__mul", (Vector2(Vector2::*)(const float&) const) & Vector2::operator*)
		.addFunction("__div", (Vector2(Vector2::*)(const float&) const) & Vector2::operator/)
		.addProperty("x", &Vector2::getX, &Vector2::setX)
		.addProperty("y", &Vector2::getY, &Vector2::setY)
		.addFunction("magnitude", &Vector2::magnitude)
		.addFunction("normalize", &Vector2::normalize)
		.addFunction("perpendicular", &Vector2::perpendicular2)
		.endClass()

		.beginClass<Vector3>("Vector3")
		.addStaticFunction("new", &Vector3::createVector3)
		.addFunction("__add", (Vector3(Vector3::*)(const Vector3&) const) &Vector3::operator+)
		.addFunction("__sub", (Vector3(Vector3::*)(const Vector3&) const) &Vector3::operator-)
		.addFunction("__mul", (Vector3(Vector3::*)(const float&) const) &Vector3::operator*)
		.addFunction("__div", (Vector3(Vector3::*)(const float&) const) &Vector3::operator/)
		.addProperty("x", &Vector3::getX, &Vector3::setX)
		.addProperty("y", &Vector3::getY, &Vector3::setY)
		.addProperty("z", &Vector3::getZ, &Vector3::setZ)
		.addFunction("magnitude", &Vector3::magnitude)
		.addFunction("normalize", &Vector3::normalize)
		.addFunction("rotate", &Vector3::rotate)
		.addFunction("perpendicular", &Vector3::perpendicular3)
		.addFunction("asRotToQuaternion", &Vector3::asRotToQuaternion)
		.endClass()

		.beginClass<Quaternion>("Quaternion")
		.addStaticFunction("new", &Quaternion::createQuat)
		.addProperty("w", &Quaternion::getW, &Quaternion::setW)
		.addProperty("x", &Quaternion::getX, &Quaternion::setX)
		.addProperty("y", &Quaternion::getY, &Quaternion::setY)
		.addProperty("z", &Quaternion::getZ, &Quaternion::setZ)
		.addFunction("magnitude", &Quaternion::magnitude)
		.addFunction("normalize", &Quaternion::normalize)
		.addFunction("conjugate", &Quaternion::conjugate)
		.addProperty("up", &Quaternion::up)
		.addProperty("right", &Quaternion::right)
		.addProperty("forward", &Quaternion::forward)
		.endClass()

		.deriveClass<Transform,Component>("Transform")
		.addFunction("getPosition", &Transform::getPosition)
		.addFunction("setPosition", &Transform::setPosition)
		.addFunction("getRotation", &Transform::getRotation)
		.addFunction("setRotation", &Transform::setRotation)
		.addFunction("setSize", &Transform::setSize)
		.addFunction("getSize", &Transform::getSize)
		.addFunction("setRotationWithVector", &Transform::setRotationWithVector)
		.addFunction("getEulerRotation", &Transform::getEulerRotation)
		.addFunction("setUpwards", &Transform::setUpwards)
		.addFunction("setForward", &Transform::setForward)
		.endClass()

		.beginClass<Scene>("Scene")
		.addFunction("addGameObject", &Scene::addGameobject)
		.addFunction("removeGameObject", &Scene::removeGameobject)
		.addFunction("getObjectByName", &Scene::getObjectByName)
		.addFunction("name", &Scene::getSceneName)
		.endClass()

		.beginClass<SceneManager>("SceneManager")
		.addStaticFunction("Instance", &SceneManager::GetInstance)
		.addFunction("loadScene", &SceneManager::loadScene)
		.addFunction("changeScene", &SceneManager::changeScene)
		.addFunction("getActiveScene", &SceneManager::getActiveScene)
		.endClass()

		.beginClass<Platform::LocalSave>("LocalSave")
		.addStaticFunction("setInt", &Platform::LocalSave::SetRegisterInt)
		.addStaticFunction("getInt", &Platform::LocalSave::GetRegisterInt)
		.addStaticFunction("setFloat", &Platform::LocalSave::SetRegisterFloat)
		.addStaticFunction("getFloat", &Platform::LocalSave::GetRegisterFloat)
		.addStaticFunction("setString", &Platform::LocalSave::SetRegisterString)
		.addStaticFunction("getString", &Platform::LocalSave::GetRegisterString)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerGraphics() {
	luabridge::getGlobalNamespace(_luaState)
		.deriveClass<MeshRenderer, Component>("MeshRenderer")
		.addFunction("playAnimation", &MeshRenderer::playAnimation)
		.addFunction("setMaterial", &MeshRenderer::setMaterial)
		.addFunction("setMesh", &MeshRenderer::setMesh)
		.addFunction("setVisible", &MeshRenderer::setVisible)
		.endClass()

		.deriveClass<Camera, Component>("Camera")
		.addFunction("setBackgroundColor", &Camera::setBackgroundColor)
		.addFunction("setClippingPlane", &Camera::SetClippingPlane)
		.addFunction("setFOV", &Camera::SetFOV)
		.addFunction("setTarget", &Camera::SetTarget)
		.addFunction("setViewportRatio", &Camera::SetViewportRatio)
		.endClass()

		.deriveClass<ParticleSystem, Component>("ParticleSystem")
		.addFunction("play", &ParticleSystem::play)
		.addFunction("stop", &ParticleSystem::stop)
		.addFunction("setParticle", &ParticleSystem::setParticle)
		.endClass()

		.deriveClass<UIImage, Component>("UIImage")
		.addFunction("setImage", &UIImage::setImage)
		.addFunction("setAnchorPoint", &UIImage::setAnchorPoint)
		.addFunction("setDimensions", &UIImage::setDimensions)
		.addFunction("setSortingLayer", &UIImage::setSortingLayer)
		.addFunction("setRotation", &UIImage::setRotation)
		.addFunction("show", &UIImage::show)
		.addFunction("hide", &UIImage::hide)
		.addFunction("getWidth", &UIImage::getWidth)
		.addFunction("getHeight", &UIImage::getHeight)
		.endClass()

		.deriveClass<UIText, Component>("UIText")
		.addFunction("setText", &UIText::setText)
		.addFunction("setFont", &UIText::setFont)
		.addFunction("setAnchorPoint", &UIText::setAnchorPoint)
		.addFunction("setDimensions", &UIText::setDimensions)
		.addFunction("setSortingLayer", &UIText::setSortingLayer)
		.addFunction("setRotation", &UIText::setRotation)
		.addFunction("show", &UIText::show)
		.addFunction("hide", &UIText::hide)
		.addFunction("setColor", &UIText::setColor)
		.addFunction("setColorTop", &UIText::setColorTop)
		.addFunction("setColorBottom", &UIText::setColorBottom)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerInput() {
	using namespace LocoMotor::Input;
	luabridge::getGlobalNamespace(_luaState)
		.beginClass<InputManager>("InputManager")
		.addStaticFunction("Instance", &InputManager::GetInstance)
		.addFunction("getKeyDown", &InputManager::GetKeyDownStr)
		.addFunction("getKey", &InputManager::GetKeyStr)
		.addFunction("getKeyUp", &InputManager::GetKeyUpStr)
		.addFunction("getButtonDownStr", &InputManager::GetButtonDownStr)
		.addFunction("getButton", &InputManager::GetButton)
		.addFunction("getMouseButtonDown", &InputManager::GetMouseButtonDown)
		.addFunction("getMouseButton", &InputManager::GetMouseButton)
		.addFunction("getMouseButtonUp", &InputManager::GetMouseButtonUp)
		.addFunction("getMouseButtonUp", &InputManager::GetMouseButtonDown)
		.addFunction("getJoystickValue", &InputManager::GetJoystickValueStr)
		.addFunction("getTriggerValue", &InputManager::GetTriggerValue)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerPhysics() {
	luabridge::getGlobalNamespace(_luaState)
		.deriveClass<RigidBody, Component>("RigidBody")
		.addFunction("addForce", &RigidBody::AddForce)
		.addFunction("applyCentralImpulse", &RigidBody::ApplyCentralImpulse)
		.addFunction("applyTorqueImpulse", &RigidBody::ApplyTorqueImpulse)
		.addFunction("useGravity", &RigidBody::UseGravity)
		.addFunction("freezePosition", &RigidBody::FreezePosition)
		.addFunction("freezeRotation", &RigidBody::FreezeRotation)
		.addFunction("beATrigger", &RigidBody::BeATrigger)
		.addFunction("setCollisionGroup", &RigidBody::SetCollisionGroup)
		.addFunction("getCollisionGroup", &RigidBody::GetCollisionGroup)
		//.addFunction("ignoreGroup", &RigidBody::ignoreGroup)
		//.addFunction("getIgnoredGroup", &RigidBody::getIgnoredGroup)
		.addFunction("getLinearVelocity", &RigidBody::GetLinearVelocity)
		.addFunction("setLinearVelocity", &RigidBody::SetLinearVelocity)
		.addFunction("getTotalTorque", &RigidBody::GetTotalTorque)
		.addFunction("getTotalForce", &RigidBody::GetTotalForce)
		.addFunction("getTurnVelocity", &RigidBody::GetTurnVelocity)
		.addFunction("getAngularVelocity", &RigidBody::GetAngularVelocity)
		.addFunction("setAngularVelocity", &RigidBody::SetAngularVelocity)
		.addFunction("setFriction", &RigidBody::SetFriction)
		.addFunction("setMass", &RigidBody::SetMass)
		.addFunction("setSize", &RigidBody::SetSize)
		.addFunction("setLinearDamping", &RigidBody::SetLinearDamping)
		.addFunction("setAngularDamping", &RigidBody::SetAngularDamping)
		.addFunction("setRotation", &RigidBody::SetRotation)
		.addFunction("setPosition", &RigidBody::SetPosition)
		.addFunction("setMass", &RigidBody::SetMass)
		.endClass();
}

void LocoMotor::Scripting::ScriptManager::registerSound() {
	luabridge::getGlobalNamespace(_luaState)
		.deriveClass<AudioListener, Component>("AudioListener")
		.endClass()

		.deriveClass<AudioSource, Component>("AudioSource")
		.addFunction("addSound", &AudioSource::addSound)
		.addFunction("playSound", &AudioSource::playSound)
		.addFunction("playOneShot", &AudioSource::playOneShot)
		.addFunction("playOneShotWithPitch", &AudioSource::playOneShotWithPitch)
		.addFunction("pauseSound", &AudioSource::pauseSound)
		.addFunction("pause", &AudioSource::pause)
		.addFunction("stopSound", &AudioSource::stopSound)
		.addFunction("stop", &AudioSource::stop)
		.addFunction("setSoundVolume", &AudioSource::setSoundVolume)
		.addFunction("setSoundFreq", &AudioSource::setSoundFreq)
		.addFunction("setFrequency", &AudioSource::setFrequency)
		.addFunction("setMode2D", &AudioSource::setMode2D)
		.addFunction("setMode3D", &AudioSource::setMode3D)
		.endClass()

		.deriveClass<EventEmitter, Component>("EventEmmiter")
		.addFunction("setEvent", &EventEmitter::setEvent)
		.addFunction("play", &EventEmitter::play)
		.addFunction("setPitch", &EventEmitter::setPitch)
		.addFunction("setParameter", &EventEmitter::setParameter)
		.addFunction("setVolume", &EventEmitter::setVolume)
		.addFunction("stop", &EventEmitter::stop)
		.endClass();
}

bool ScriptManager::Init() {
	assert(_instance == nullptr);
	_instance = new ScriptManager();
	if (!_instance->initLua()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}
	return true;
}

void ScriptManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

ScriptManager* LocoMotor::Scripting::ScriptManager::GetInstance() {
	return _instance;
}

bool LocoMotor::Scripting::ScriptManager::loadScript(const std::string& name, LuaBehaviour* behaviour) {
	static const std::string basePath = "Assets/Scripts/";
	static const std::string luaExtension = ".lua";
	std::string fullPath = basePath + name + luaExtension;

	
	
	
	luabridge::setGlobal(_luaState, behaviour, "behaviour");
	if (luaL_dofile(_luaState, fullPath.c_str())) {
		std::string error = "Interpretation error at component " + name
			+ "\n" + std::string(lua_tostring(_luaState, -1));
		std::cerr << error << std::endl;
		Engine::GetInstance()->showWindow(2, error);
		return false;
	}
	behaviour->setLuaContext(_luaState);
	return true;
}

