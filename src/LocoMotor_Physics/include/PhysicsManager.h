#pragma once
#ifndef _PHYSICS_MANAGER_H
#define _PHYSICS_MANAGER_H
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include "LMVector.h"
#include <unordered_map>
#include <list>
#include <vector>
#include <string>
class btVector3;
class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;

class btPersistentManifold;
class btManifoldPoint;

typedef void(*ContactStartedCallback)(btPersistentManifold* const&);
typedef bool(*ContactProcessedCallback)(btManifoldPoint&, void*, void*);
typedef void(*ContactEndedCallback)(btPersistentManifold* const&);
namespace LocoMotor {

	class RigidBody;

	namespace Physics{

		struct RaycastHitInfo {
			RaycastHitInfo() : collider(nullptr), normal(), hitPoint(){ }
			bool hasHit() const;
			RigidBody* getCollider() const {
				return collider;
			}
			Vector3 getNormal() const {
				return normal;
			}
			Vector3 getHitPoint() const {
				return hitPoint;
			}
			RigidBody* collider;
			Vector3 normal;
			Vector3 hitPoint;
		};

		class PhysicsManager {
		public:
			static bool Init();
			MOTOR_API static PhysicsManager* GetInstance();
			static void Release();
			/// @brief Update the physics world , steps the physic simulation
			void update(double dt);
			/// @brief Sets the worlds gravity
			/// @param gravity The Vector3 gravity you want to set
			MOTOR_API void setWorldGravity(const Vector3& gravity);
			/// @brief Casts a ray that collides with a Rigidbody
			/// @param origin: from where the ray is cast
			/// @param to: to where the ray is cast
			/// @return A struct containing hit information
			MOTOR_API RaycastHitInfo raycast(const Vector3& origin, const Vector3& to);
			/// @brief Casts a ray that collides with a Rigidbody
			/// @param origin: from where the ray is cast
			/// @param to: to where the ray is cast
			/// @param layersToIgnore: Array of layer names to ignore
			/// @return A struct containing hit information
			MOTOR_API RaycastHitInfo raycastFilter(const Vector3& origin, const Vector3& to, const std::vector<std::string>& layersToIgnore);
			/// @brief Casts a ray that collides with several Rigidbodies
			/// @param origin: from where the ray is cast
			/// @param to: to where the ray is cast
			/// @return A struct containing hit information
			MOTOR_API std::list<RaycastHitInfo> raycastAll(const Vector3& origin, const Vector3& to);
			/// @brief Casts a ray that collides with several Rigidbodies
			/// @param origin: from where the ray is cast
			/// @param to: to where the ray is cast
			/// @param layersToIgnore: Array of layer names to ignore
			/// @return A struct containing hit information
			MOTOR_API std::list<RaycastHitInfo> raycastAllFilter(const Vector3& origin, const Vector3& to, const std::vector<std::string>& layersToIgnore);
			/// @brief Gets dynamic World
			btDynamicsWorld* getDynamicWorld();
			/// @brief Sets the callback when two body starts contact
			void setContactStartCallback(ContactStartedCallback funtion);
			/// @brief Sets the callback when two body is in contact
			void setContactProcessCallback(ContactProcessedCallback funtion);
			/// @brief Sets the callback when two body ends contact
			void setContactEndedCallback(ContactEndedCallback funtion);
			/// @brief Gets the number of a layer in Bullet by name
			/// @param layer Name of the layer
			int getlayerNumber(std::string layer);
		private:
			static PhysicsManager* _instance;
			btDefaultCollisionConfiguration* _collisionConfiguration = nullptr;
			btCollisionDispatcher* _dispatcher = nullptr;
			btBroadphaseInterface* _overlappingPairCache = nullptr;
			btSequentialImpulseConstraintSolver* _solver = nullptr;
			btDynamicsWorld* _dynamicWorld = nullptr;
			int _layerCount;
			std::unordered_map<std::string, int> _layers;
			PhysicsManager();
			~PhysicsManager();
			bool init();

		};
	}
}
#endif // !1
