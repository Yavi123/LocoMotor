#include "RigidBody.h"
#include <iostream>
#include "PhysicsManager.h"
#include "btBulletDynamicsCommon.h"
#include "BulletVectorConverter.h"

#include "GameObject.h"
#include "Transform.h"
#include "math.h"

using namespace LocoMotor;
using namespace Physics;

LocoMotor::RigidBody::RigidBody() : _body(nullptr), _mass(1.f) {
	info = RigidBodyInfo();
}

LocoMotor::RigidBody::~RigidBody() {
	if (_body == nullptr)return;
	_body->setUserPointer(nullptr);
	Physics::PhysicsManager::GetInstance()->getDynamicWorld()->removeRigidBody(_body);
	if (_body && _body->getMotionState()) {
		delete _body->getMotionState();
	}
	delete _body->getCollisionShape();
	delete _body;
}

bool LocoMotor::RigidBody::setParameters(ComponentMap& params) {

	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "mass") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_mass = num;
			info.mass = num;
		}
		else if (params[i].first == "damping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			SetLinearDamping(num);
		}
		else if (params[i].first == "angDamping") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			SetAngularDamping(num);
		}
		else if (params[i].first == "gravity") {
			float num = 0.;
			try {
				num = std::stof(params[i].second);
			}
			catch (std::invalid_argument) {
				num = 0.;
			}
			_gravity = num;
		}
		else if (params[i].first == "usedAsRaycast") {
			_raycast = true;
		}
		else if (params[i].first == "isTrigger") {
			_beATrigger = true;
		}
		else if (params[i].first == "size" || params[i].first == "scale") {
			 info.boxSize= Vector3::stringToVector(params[i].second);
		}
		else if (params[i].first == "pos" || params[i].first == "center" || params[i].first == "origin") {
			info.origin = Vector3::stringToVector(params[i].second);
		}
		else if (params[i].first == "sphereSize") {
			info.sphereSize = std::stof(params[i].second);
		}
		else if (params[i].first == "capsuleHeight") {
			info.capsuleHeight = std::stof(params[i].second);
		}
		else if (params[i].first == "capsuleRadius") {
			info.capsuleRadius = std::stof(params[i].second);
		}
		else if (params[i].first == "group" || params[i].first=="collisionGroup"){
			_collisionGroup = params[i].second;
		}
		else if (params[i].first == "ignoreGroup") {
			_ignoreGroup.push_back(params[i].second);
		}
	}
	_body = CreateRigidBody(info);
	_body->setUserPointer(_gameObject);
	return true;
}

void LocoMotor::RigidBody::awake() {
	if (_body == nullptr) {
		info.origin = _gameObject->getComponent<Transform>()->getPosition();
		_body = CreateRigidBody(info);
		_body->setUserPointer(_gameObject);
	}
	SetPosition(_gameObject->getComponent<Transform>()->getPosition());
	SetRotation(_gameObject->getComponent<Transform>()->getRotation());
}

void LocoMotor::RigidBody::start() {}

void LocoMotor::RigidBody::update(float dt) {
}

void LocoMotor::RigidBody::fixedUpdate() {

}

void LocoMotor::RigidBody::prePhysUpdate() {
	SetPosition(_gameObject->getComponent<Transform>()->getPosition());
	SetRotation(_gameObject->getComponent<Transform>()->getRotation());
}

void LocoMotor::RigidBody::posPhysUpdate() {
	_gameObject->getComponent<Transform>()->setPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	_gameObject->getComponent<Transform>()->setRotation(BulletToLm(_body->getWorldTransform().getRotation()));
}

btRigidBody* LocoMotor::RigidBody::CreateRigidBody(RigidBodyInfo info) {
	btCollisionShape* shape = nullptr;
	if (info.capsuleHeight > 0.0)
		shape = new btCapsuleShapeZ(info.capsuleRadius, info.capsuleHeight);
	else if (info.sphereSize <= 0.0)
		shape = new btBoxShape(LmToBullet(info.boxSize));
	else if (info.sphereSize)
		shape = new btSphereShape(info.sphereSize);
	if (shape == nullptr)return nullptr;
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(LmToBullet(info.origin));

	btScalar mass(info.mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);
	else {
		_collisionGroup = "static";
	}

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* rigidbody = new btRigidBody(rbInfo);

	//add the body to the dynamics world;
	LocoMotor::Physics::PhysicsManager::GetInstance()->getDynamicWorld()->addRigidBody(rigidbody);
	rigidbody->setDamping(0.7f, 0.7f);

	if (isDynamic) {
		rigidbody->setCcdMotionThreshold(0.0000001f);//0.0000001f
		rigidbody->setCcdSweptSphereRadius(0.5f);
	}
	rigidbody->getBroadphaseProxy()->m_collisionFilterGroup = PhysicsManager::GetInstance()->getlayerNumber(_collisionGroup);
	if (_ignoreGroup.size() > 0) {
		int res = btBroadphaseProxy::AllFilter;
		for (int i = 0; i < _ignoreGroup.size(); i++) {
			int pot = PhysicsManager::GetInstance()->getlayerNumber(_ignoreGroup[i]);
			res = res ^ pot;
		}
		rigidbody->getBroadphaseProxy()->m_collisionFilterMask = res;
	}
	if (_beATrigger) {
		rigidbody->setCollisionFlags(rigidbody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
	rigidbody->setGravity({ 0,_gravity,0 });
	rigidbody->setUserPointer(_gameObject);
	return rigidbody;
}

LocoMotor::RigidBodyInfo::RigidBodyInfo() {
	type = 0;
	boxSize = Vector3(1.f, 1.f, 1.f);
	sphereSize = 0.f;
	capsuleRadius = 0.f;
	capsuleHeight = 0.f;
	origin = Vector3();
	mass = 0.f;
}
void LocoMotor::RigidBody::AddForce(Vector3 force) {
	_body->activate();
	_body->applyCentralForce(LmToBullet(force));
}
void LocoMotor::RigidBody::SetRotation(Quaternion rot) {
	_body->getWorldTransform().setRotation(LmToBullet(rot));
}


void LocoMotor::RigidBody::SetPosition(Vector3 pos) {
	_body->getWorldTransform().setOrigin(LmToBullet(pos));
}


void LocoMotor::RigidBody::UseGravity(Vector3 gravity) {

	_body->setGravity(LmToBullet(gravity));
}


void LocoMotor::RigidBody::FreezePosition(Vector3 freezeAxis) {
	_body->setLinearFactor(LmToBullet(freezeAxis));
}


void LocoMotor::RigidBody::FreezeRotation(Vector3 freezeAxis) {
	_body->setAngularFactor(LmToBullet(freezeAxis));
}


bool LocoMotor::RigidBody::CheckCollision(GameObject* other) {
	if (other != nullptr) {
		return _body->checkCollideWith(other->getComponent<RigidBody>()->GetBody());
	}
	return false;
}
btRigidBody* LocoMotor::RigidBody::GetBody() {
	return _body;
}

void LocoMotor::RigidBody::BeATrigger() {
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}
void LocoMotor::RigidBody::SetCollisionGroup(std::string group) {
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = PhysicsManager::GetInstance()->getlayerNumber(group);
}


std::string LocoMotor::RigidBody::GetCollisionGroup() {
	return _collisionGroup;
}

void LocoMotor::RigidBody::ignoreGroup(std::string mask) {
	_ignoreGroup.push_back(mask);
	if (_ignoreGroup.size() > 0) {
		int res = btBroadphaseProxy::AllFilter;
		for (int i = 0; i < _ignoreGroup.size(); i++) {
			int pot = PhysicsManager::GetInstance()->getlayerNumber(_ignoreGroup[i]);
			res = res ^ pot;
		}
		_body->getBroadphaseProxy()->m_collisionFilterMask = res;
	}
}


std::vector<std::string> LocoMotor::RigidBody::getIgnoredGroup() {
	return _ignoreGroup;
}


Vector3 LocoMotor::RigidBody::GetLinearVelocity() {
	return BulletToLm(_body->getLinearVelocity());
}
void LocoMotor::RigidBody::SetLinearVelocity(Vector3 newLinearVelocity) {
	_body->activate();
	_body->setLinearVelocity(LmToBullet(newLinearVelocity));
}


Vector3 LocoMotor::RigidBody::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}

Vector3 LocoMotor::RigidBody::GetTotalForce() {
	return BulletToLm(_body->getTotalForce());
}


Vector3 LocoMotor::RigidBody::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}


Vector3 LocoMotor::RigidBody::GetAngularVelocity() {
	return BulletToLm(_body->getAngularVelocity());
}


void LocoMotor::RigidBody::SetAngularVelocity(Vector3 newAngularVelocity) {
	_body->activate();
	_body->setAngularVelocity(LmToBullet(newAngularVelocity));
}


void LocoMotor::RigidBody::ApplyTorqueImpulse(Vector3 impulse) {
	_body->activate();
	_body->applyTorqueImpulse(LmToBullet(impulse));
}

void LocoMotor::RigidBody::ApplyCentralImpulse(Vector3 impulse) {
	_body->activate();
	_body->applyCentralImpulse(LmToBullet(impulse));
}


void LocoMotor::RigidBody::SetFriction(float fric) {
	_body->setFriction(fric);
}

void LocoMotor::RigidBody::SetMass(float mass) {
	info.mass = mass;
}

void LocoMotor::RigidBody::SetSize(Vector3 size) {
	info.boxSize = size;
}

void LocoMotor::RigidBody::SetLinearDamping(float linearDamping) {

	_damping = linearDamping;
	_body->setDamping(_damping, _angDamping);
}

void LocoMotor::RigidBody::SetAngularDamping(float angularDamping) {

	_angDamping = angularDamping;
	_body->setDamping(_damping, _angDamping);
}

