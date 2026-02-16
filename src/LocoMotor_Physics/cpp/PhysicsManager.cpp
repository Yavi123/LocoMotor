#include "PhysicsManager.h"
#include "RigidBody.h"
#include "GameObject.h"

#include "assert.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "CallBackBullet.h"
#include "math.h"
#include <BulletVectorConverter.h>
using namespace LocoMotor;
using namespace Physics;
PhysicsManager* PhysicsManager::_instance = nullptr;

bool RaycastHitInfo::hasHit() const {
	return (collider != nullptr);
}

bool PhysicsManager::Init() {
	assert(_instance == nullptr);
	_instance = new PhysicsManager();

	if (!_instance->init()) {
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

PhysicsManager* PhysicsManager::GetInstance() {
	assert(_instance != nullptr);
	return _instance;
}

void PhysicsManager::Release() {
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

void LocoMotor::Physics::PhysicsManager::update(double dt) {

	const btCollisionObjectArray& objectArray = _dynamicWorld->getCollisionObjectArray();

	for (int i = 0; i < objectArray.size(); i++) {
		GameObject* rb = static_cast<GameObject*>(objectArray.at(i)->getUserPointer());
		if (rb != nullptr) {
			RigidBody* body = rb->getComponent<RigidBody>();
			if (body) {
				body->prePhysUpdate();
			}
		}
	}

	_dynamicWorld->stepSimulation(btScalar(dt / 1000.f), 0);

	for (int i = 0; i < objectArray.size(); i++) {
		GameObject* rb = static_cast<GameObject*>(objectArray.at(i)->getUserPointer());
		if (rb != nullptr) {
			RigidBody* body = rb->getComponent<RigidBody>();
			if (body) {
				body->posPhysUpdate();
			}
		}
	}
}

void LocoMotor::Physics::PhysicsManager::setWorldGravity(const Vector3& gravity) {
	_dynamicWorld->setGravity(LmToBullet(gravity));
}

RaycastHitInfo LocoMotor::Physics::PhysicsManager::raycast(const Vector3& origin, const Vector3& to) {
	return raycastFilter(origin, to, std::vector<std::string>());
}

MOTOR_API RaycastHitInfo LocoMotor::Physics::PhysicsManager::raycastFilter(const Vector3& origin, const Vector3& to, const std::vector<std::string>& layersToIgnore) {
	btCollisionWorld::ClosestRayResultCallback result = btCollisionWorld::ClosestRayResultCallback(LmToBullet(origin), LmToBullet(to));
	result.m_collisionFilterGroup = btBroadphaseProxy::AllFilter;

	if (layersToIgnore.size() > 0) {
		int res = btBroadphaseProxy::AllFilter;
		for (int i = 0; i < layersToIgnore.size(); i++) {
			int pot = PhysicsManager::GetInstance()->getlayerNumber(layersToIgnore[i]);
			res = res ^ pot;
		}
		result.m_collisionFilterMask = res;
	}

	_dynamicWorld->rayTest(LmToBullet(origin), LmToBullet(to), result);

	if (!result.hasHit()) {
		return RaycastHitInfo();
	}

	else {
		auto hitInfo = RaycastHitInfo();
		GameObject* rb = static_cast<GameObject*>(result.m_collisionObject->getUserPointer());
		if (rb != nullptr) {
			RigidBody* body = rb->getComponent<RigidBody>();
			if (body) {
				hitInfo.collider = body;
			}
		}
		if (hitInfo.collider == nullptr) {
			return hitInfo;
		}
		hitInfo.normal = BulletToLm(result.m_hitNormalWorld);
		hitInfo.hitPoint = BulletToLm(result.m_hitPointWorld);

		return hitInfo;
	}
}

std::list<RaycastHitInfo> LocoMotor::Physics::PhysicsManager::raycastAll(const Vector3& origin, const Vector3& to) {
	return raycastAllFilter(origin, to, std::vector<std::string>());
}

std::list<RaycastHitInfo> LocoMotor::Physics::PhysicsManager::raycastAllFilter(const Vector3& origin, const Vector3& to, const std::vector<std::string>& layersToIgnore) {
	btCollisionWorld::AllHitsRayResultCallback result = btCollisionWorld::AllHitsRayResultCallback(LmToBullet(origin), LmToBullet(to));
	result.m_collisionFilterGroup = btBroadphaseProxy::AllFilter;

	if (layersToIgnore.size() > 0) {
		int res = btBroadphaseProxy::AllFilter;
		for (int i = 0; i < layersToIgnore.size(); i++) {
			int pot = PhysicsManager::GetInstance()->getlayerNumber(layersToIgnore[i]);
			res = res ^ pot;
		}
		result.m_collisionFilterMask = res;
	}

	_dynamicWorld->rayTest(LmToBullet(origin), LmToBullet(to), result);

	if (!result.hasHit()) {
		return std::list<RaycastHitInfo>();
	}
	else {
		auto hitInfoList = std::list<RaycastHitInfo>();
		for (int i = 0; i < result.m_collisionObjects.size(); i++) {

			auto hitInfo = RaycastHitInfo();
			GameObject* rb = static_cast<GameObject*>(result.m_collisionObject->getUserPointer());
			if (rb != nullptr) {
				RigidBody* body = rb->getComponent<RigidBody>();
				if (body) {
					hitInfo.collider = body;
				}
			}
			if (hitInfo.collider == nullptr) {
				continue;
			}
			hitInfo.normal = BulletToLm(result.m_hitNormalWorld[i]);
			hitInfo.hitPoint = BulletToLm(result.m_hitPointWorld[i]);

			hitInfoList.push_back(hitInfo);
		}

		return hitInfoList;
	}
}

btDynamicsWorld* LocoMotor::Physics::PhysicsManager::getDynamicWorld() {
	return _dynamicWorld;
}

void LocoMotor::Physics::PhysicsManager::setContactStartCallback(ContactStartedCallback funtion) {
	//gContactStartedCallback = funtion;
}

void LocoMotor::Physics::PhysicsManager::setContactProcessCallback(ContactProcessedCallback funtion) {
	//gContactProcessedCallback = funtion;
}

void LocoMotor::Physics::PhysicsManager::setContactEndedCallback(ContactEndedCallback funtion) {
	//gContactEndedCallback = funtion;
}

int LocoMotor::Physics::PhysicsManager::getlayerNumber(std::string layer) {
	if(_layers.find(layer)!=_layers.end())
		return _layers[layer];
	else {
		if (_layerCount < 32) {
			_layers[layer] = (int)pow(2, _layerCount);
			_layerCount++;
			return _layers[layer];
		}
		else //Si ha creado demasiadas capas de collsion que se sobresale de los limites de bullet.
			return -1; //-1	significa AllFilter , que colisiona con todo.
	}
}


LocoMotor::Physics::PhysicsManager::PhysicsManager() : _dynamicWorld(nullptr), _solver(nullptr), _overlappingPairCache(nullptr), _dispatcher(nullptr), _collisionConfiguration(nullptr), _layerCount(0) {

}

LocoMotor::Physics::PhysicsManager::~PhysicsManager() {
	delete _dynamicWorld;
	delete _solver;
	delete _overlappingPairCache;
	delete _dispatcher;
	delete _collisionConfiguration;
}

bool LocoMotor::Physics::PhysicsManager::init() {
	//Set default configuration
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_overlappingPairCache = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver();
	//Create Dynamic world
	_dynamicWorld = new btDiscreteDynamicsWorld(_dispatcher, _overlappingPairCache, _solver, _collisionConfiguration);
	//Set default gravity
	_dynamicWorld->setGravity(btVector3(0, -9.8f, 0));
	gContactStartedCallback = LMcontactStart;
	gContactProcessedCallback = LMcontactProcessed;
	gContactEndedCallback = LMcontactExit;
	_layers["default"] = 1;
	_layers["static"] = 2;
	_layerCount = 2;
	return true;
}
