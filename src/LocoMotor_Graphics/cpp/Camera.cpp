#include "Camera.h"
#include <OgreCamera.h>
#include <OgreViewport.h>
#include "GraphicsManager.h"
#include "OgreSceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include <OgreRenderWindow.h>
#include <iostream>


LocoMotor::Camera::Camera() : _mCamera(nullptr), _target(nullptr), _vp(nullptr), _node(nullptr), _man(nullptr) {
	_offset = Vector3();
	_nodeRotation = Quaternion();
}

LocoMotor::Camera::~Camera() {
	_man->getOgreSceneManager()->destroyCamera(_mCamera);
	_man->getRenderWindow()->removeViewport(0);
}

void LocoMotor::Camera::SetTarget(GameObject* target, const Vector3& offset)
{
	_target = target;
	_offset = offset;
}

void LocoMotor::Camera::SetFOV(float newFov)
{
	_mCamera->setFOVy(Ogre::Radian(newFov * 3.14f / 180));
}

void LocoMotor::Camera::SetViewportRatio(int viewportIndex, int modeIndex)
{
	if (modeIndex == 0) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 1) {
		_vp->setDimensions(0.0f, 0.0f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 2) {
		_vp->setDimensions(0.0f, 0.5f, 1.0f, 0.5f);
		_vp->update();
		_mCamera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
}

void LocoMotor::Camera::SetClippingPlane(int nearPlane, int farPlane) {
	_mCamera->setNearClipDistance(Ogre::Real(nearPlane));
	_mCamera->setFarClipDistance(Ogre::Real(farPlane));
}

void LocoMotor::Camera::setBackgroundColor(float r, float g, float b) {
	_vp->setBackgroundColour(Ogre::ColourValue(r, g, b));
}

void LocoMotor::Camera::start() {
	if (_gameObject->getComponent<Transform>() == nullptr) {
		std::cerr << "GameObject with name '" << _gameObject->getName() << "' has no Transform component\n";
		return;
	}
}

bool LocoMotor::Camera::setParameters(ComponentMap& params) {
	init();
	for (auto& param : params) {
		if (param.first == "CameraMode") {
			try {
				int modeIndex = std::stoi(param.second);
				SetViewportRatio(1, modeIndex); //ViewportIndex = 1 TEMPORAL
			}
			catch (...) {
			}
		}
		else if (param.first == "FOV" || param.first == "fov") {
			try {
				float fov = std::stof(param.second);
				SetFOV(fov);
			}
			catch (...) {
			}
		}
		else if (param.first == "Background" || param.first == "background") {
			Vector3 col = Vector3::stringToVector(param.second);
			setBackgroundColor(col.getX(), col.getY(), col.getZ());
		}
	}
	return true;
}

void LocoMotor::Camera::render() {
	_vp->update();
}

// Funcionalidad componentes

void LocoMotor::Camera::init()
{
	_man = Graphics::GraphicsManager::GetInstance();
	_node = _man->createNode(_gameObject->getName());
	_mCamera = _man->getOgreSceneManager()->createCamera(_gameObject->getName() + "_cam");
	_mCamera->setNearClipDistance(0.1f);
	_node->attachObject(_mCamera);
	_target = nullptr;
	_offset = Vector3();
	_vp = _man->getRenderWindow()->addViewport(_mCamera, 0);
	_vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
}
void LocoMotor::Camera::onEnable()
{
}
void LocoMotor::Camera::update(float dT)
{
	if (_gameObject->getComponent<Transform>() == nullptr)return;

	Vector3 pos = _gameObject->getComponent<Transform>()->getPosition();
	_node->setPosition(pos.getX(), pos.getY(), pos.getZ());

	Ogre::Quaternion quat = Ogre::Quaternion();
	quat.w = _gameObject->getComponent<Transform>()->getRotation().getW();
	quat.x = _gameObject->getComponent<Transform>()->getRotation().getX();
	quat.y = _gameObject->getComponent<Transform>()->getRotation().getY();
	quat.z = _gameObject->getComponent<Transform>()->getRotation().getZ();
	_node->setOrientation(quat);

	Vector3 size = _gameObject->getComponent<Transform>()->getSize();
	_node->setScale(size.getX(), size.getY(), size.getZ());

	int w = Graphics::GraphicsManager::GetInstance()->getWindowWidth();
	int h = Graphics::GraphicsManager::GetInstance()->getWindowHeight();

	_mCamera->setAspectRatio(w / (float)h);
}
void LocoMotor::Camera::onDisable()
{
}
