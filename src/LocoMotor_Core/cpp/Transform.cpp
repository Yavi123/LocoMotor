#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "GraphicsManager.h"
#include <iostream>



LocoMotor::Transform::Transform() {
	_position = Vector3();
	_direction = Quaternion();
	_scale = Vector3(1.f, 1.f, 1.f);
}

LocoMotor::Transform::~Transform() {}


void LocoMotor::Transform::initComponent() {
	//_gameObject->registerTransform(this);
}


bool LocoMotor::Transform::setParameters(ComponentMap& params) {
	//_gameObject->registerTransform(this);

	for (const auto& pair : params) {
		if (pair.first == "pos" || pair.first == "position") {
			_position = Vector3::stringToVector(pair.second);
		}
		else if (pair.first == "rot" || pair.first == "rotation") {
			_direction = Vector3::stringToVector(pair.second).asRotToQuaternion();
			_direction.normalize();
		}
		else if (pair.first == "size" || pair.first == "scale") {
			_scale = Vector3::stringToVector(pair.second);
		}
	}
	return true;
}

void LocoMotor::Transform::initRuntime(Vector3 initPos, Vector3 initRot, Vector3 initScale) {
	//_gameObject->registerTransform(this);

	_position = initPos;
	_direction = initRot.asRotToQuaternion();
	_scale = initScale;
}

void LocoMotor::Transform::start() {
}

void LocoMotor::Transform::update(const float dt) {}


LocoMotor::Vector3 LocoMotor::Transform::getPosition() {
	return _position;
}

void LocoMotor::Transform::setPosition(const Vector3& newPosition) {

	//Sets Position In World Coordinates
	_position = newPosition;
}

//GETTERS
LocoMotor::Quaternion LocoMotor::Transform::getRotation(){
	return _direction;
}
LocoMotor::Vector3 LocoMotor::Transform::getEulerRotation() {
	return _direction.toEuler();
}

//SET ROTATIONS

void LocoMotor::Transform::setRotationWithVector(const Vector3& newRotation) {
	setRotation(newRotation.asRotToQuaternion());
}

void LocoMotor::Transform::setRotation(const Quaternion& newRotation) {


	// Si alguno de los valores no es valido, no realizar la operacion
	if (std::isnan(newRotation.getW()) || std::isnan(newRotation.getX()) || std::isnan(newRotation.getX()) || std::isnan(newRotation.getZ()))
		return;

	_direction = newRotation;
	_direction.normalize();
}



LocoMotor::Vector3 LocoMotor::Transform::getSize() {
	return _scale;
}

void LocoMotor::Transform::setSize(const Vector3& newSize) {
	_scale = newSize;
}

void LocoMotor::Transform::setUpwards(const Vector3& newUpward) {
	float angle = getRotation().up().angle(newUpward);
	if (angle == 0.f) return;

	Vector3 v1 = getRotation().up();
	Vector3 v2 = newUpward;
	Vector3 axis = Vector3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX());

	setRotation(getRotation().rotate(axis, angle));
}


void LocoMotor::Transform::setForward(const Vector3& newForward) {
	float angle = getRotation().forward().angle(newForward);
	if (angle == 0.f) return;

	Vector3 v1 = getRotation().forward();
	Vector3 v2 = newForward;
	Vector3 axis = Vector3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX());

	setRotation(getRotation().rotate(axis, angle));
}


void LocoMotor::Transform::lookAt(const Vector3& lookPos) {
	Vector3 newForward = lookPos - getPosition();
	setForward(newForward);
}


void LocoMotor::Transform::lookAt(const Vector3& lookPos, const Vector3& up) {
	setUpwards(up);
	Vector3 newForward = lookPos - getPosition();
	setForward(newForward);
}
