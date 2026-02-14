#include "Light.h"
#include "GraphicsManager.h"
#include "Transform.h"
#include "GameObject.h"
#include <OgreSceneManager.h>
#include <OgreStaticGeometry.h>
#include <OgreLight.h>

LocoMotor::Light::Light() {
	_setStatic = false;
	isSelfVisible = true;
	_node = nullptr;
	_light = nullptr;
}

LocoMotor::Light::~Light() {
}

MOTOR_API void LocoMotor::Light::setLightType(const LightType& t) {
	_light->setType((Ogre::Light::LightTypes) toOgreType(t));
}

bool LocoMotor::Light::setParameters(ComponentMap& params) {
	Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
	_node = man->createNode(_gameObject->getName());

	if (Graphics::GraphicsManager::GetInstance()->getOgreSceneManager() == nullptr)
		return false;
	if (_node == nullptr) {
		Graphics::GraphicsManager* man = Graphics::GraphicsManager::GetInstance();
		_node = man->createNode(_gameObject->getName());
	}

	_light = LocoMotor::Graphics::GraphicsManager::GetInstance()->getOgreSceneManager()->createLight(_gameObject->getName());
	if (_light != nullptr) {
		_node->attachObject(_light);
	}
	else {
		std::cerr << "\033[1;31m" << "Couldn't create light in gameObject '" << _gameObject->getName() << "'" << "\033[0m" << std::endl;
		return false;
	}

	LightType t = POINT;
	LMVector3 spec = LMVector3();
	LMVector3 diff = LMVector3();

	for (auto& param : params) {
		if (param.first == "type" || param.first == "Type") {
			if (param.second.find("dir") != std::string::npos || param.second.find("Dir") != std::string::npos) {
				t = DIRECTIONAL;
			}
			else if (param.second.find("spo") != std::string::npos || param.second.find("Spo") != std::string::npos) {
				t = SPOT;
			}
		}
		else if (param.first.find("spec") != std::string::npos || param.first.find("Spec") != std::string::npos) {
			spec = LMVector3::stringToVector(param.second);
		}
		else if (param.first.find("diff") != std::string::npos || param.first.find("Diff") != std::string::npos) {
			diff = LMVector3::stringToVector(param.second);
		}
	}

	_light->setAttenuation(1000.f, 1.f, 1.f, 1.f);
	_light->setDiffuseColour(Ogre::ColourValue(diff.getX(), diff.getY(), diff.getZ(), 1.f));
	_light->setSpecularColour(Ogre::ColourValue(spec.getX(), spec.getY(), spec.getZ(), 1.f));
	_light->setType((Ogre::Light::LightTypes) toOgreType(t));
	_light->setVisible(true);

	return true;
}

void LocoMotor::Light::awake() {
	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}
}

void LocoMotor::Light::onEnable() {
	_light->setVisible(true);
}

void LocoMotor::Light::start() {
}

void LocoMotor::Light::onDisable() {
	_light->setVisible(false);
}

void LocoMotor::Light::update(float dt) {
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	if (_setStatic) {
		auto sceneMan = Graphics::GraphicsManager::GetInstance()->getOgreSceneManager();
		auto staticGeom = sceneMan->getStaticGeometry(sceneMan->getName() + "_static");
		staticGeom->addSceneNode(_node);
		_setStatic = false;
	}

	LMVector3 pos = _gameObject->getComponent<Transform>()->getPosition();
	_node->setPosition(pos.getX(), pos.getY(), pos.getZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	quat.w = _gameObject->getComponent<Transform>()->getRotation().getW();
	quat.x = _gameObject->getComponent<Transform>()->getRotation().getX();
	quat.y = _gameObject->getComponent<Transform>()->getRotation().getY();
	quat.z = _gameObject->getComponent<Transform>()->getRotation().getZ();
	_node->setOrientation(quat);

	LMVector3 size = _gameObject->getComponent<Transform>()->getSize();
	_node->setScale(size.getX(), size.getY(), size.getZ());
}

Ogre::MovableObject* LocoMotor::Light::getMovObj() {
	return _light;
}

unsigned char LocoMotor::Light::toOgreType(const LightType& t) {
	switch (t) {

		case (LightType::DIRECTIONAL):
			return Ogre::Light::LightTypes::LT_DIRECTIONAL;

		case (LightType::POINT):
			return Ogre::Light::LightTypes::LT_POINT;

		case (LightType::SPOT):
			return Ogre::Light::LightTypes::LT_SPOTLIGHT;

		default:
			return Ogre::Light::LightTypes::LT_DIRECTIONAL;
	}
}
