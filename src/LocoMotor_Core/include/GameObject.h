#pragma once
#ifndef LOCOMOTOR_GAME_OBJECT
#define LOCOMOTOR_GAME_OBJECT
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif
#include <queue>
#include <unordered_map>
#include <string>
#include "ComponentsFactory.h"

namespace LocoMotor {
	class Component;
	class Transform;
	class Scene;
	class GameObject {
		friend class Scene;
	public:
		/// @brief This method adds a new component to the GameObject
		/// @tparam T The type of the new Component
		/// @param name Name of the Component type
		/// @return returns the Component created. If the component was unique and already on the GameObject
		/// the already created Component will be returned. 
		MOTOR_API Component* addComponent(const std::string& name);
			
		MOTOR_API Component* addComponentWithParams(const std::string& name, std::vector<std::pair<std::string, std::string>>& params);

		MOTOR_API inline Transform* getTransform() const {
			return _transform;
		}

		/// @brief This method erases all the components with the given name on the GameObject
		/// @param name The name of the component to erase
		MOTOR_API void removeComponents(const std::string& name);

		template <typename T>
		MOTOR_API T* getComponent(const std::string& name ="") const {
			if(name == "") { }
			else if (!ComponentsFactory::GetInstance()->getRegistered(name) && _components.count(name) == 0) {
				return nullptr;
			}
			else if (!ComponentsFactory::GetInstance()->getRegistered(name) && _components.count(name) > 0) {
				return dynamic_cast<T*>(_components.at(name));
			}
			auto it = _components.begin();
			T* comp = nullptr;
			while (it != _components.end() && comp == nullptr) {
				comp = dynamic_cast<T*>(it->second);
				it++;
			}
			return comp;
		}

		MOTOR_API Component* getComponentByName(const std::string& name);
		
		/// @brief This method sets the active state of the GameObject. 
		/// @param active The new active state of the GameObject
		MOTOR_API inline void setActive(bool active) {
			active = _active;
		};

		/// @brief Returns the active state of the GameObject
		/// @return 
		MOTOR_API inline bool isActive() const {
			return _active;
		};

		/// @brief Gets the gameobject name
		MOTOR_API std::string getName() const;

		/// @brief This method is automatically called the first frame this gameobject collides
		/// with another gameobject
		void OnCollisionEnter(GameObject* other);
		/// @brief This method is automatically called every frame this gameobject collides
		/// with another gameobject
		void OnCollisionStay(GameObject* other);
		/// @brief This method is automatically called the first frame this gameobject no longer 
		/// collides with another gameobject
		void OnCollisionExit(GameObject* other);
	private:
		
		std::unordered_map<std::string, Component*> _components;
		std::queue<LocoMotor::Component*> _toEnable;
		std::queue<LocoMotor::Component*> _toDisable;
		std::queue<LocoMotor::Component*> _toStart;
		std::queue<LocoMotor::Component*> _toDestroy;
		LocoMotor::Scene* _scene;
		LocoMotor::Transform* _transform;
		bool _active;
		std::string _gobjName;
		bool shouldCallAwake;

		GameObject(std::string name);
		~GameObject();
		/// @brief This method is called every frame 
		/// @param dt The time elapsed since the last frame, measured in ms
		void update(float dt);
		/// @brief This method is called every fixed time step (16ms by default)
		void fixedUpdate();
		/// @brief This method is called every fixed time step (16ms by default)
		void sendMessage(const std::string& m);
		/// @brief This method sets the context (Scene) and the active state for the GameObject 
		/// @param scene Scene which the GO belongs to
		/// @param active Initial active state of the GameObject
		void init(LocoMotor::Scene* scene, bool active);
		/// @brief This method calls the awake method of this GameObject's components
		void awake();

		bool hasToBeDestroyed();
		void setToDestroy();

		void printError(const std::string& method, const std::string& error, const std::string& compName = "");

		bool _toDestroyThis = false;
	};
}
#endif // !LOCOMOTOR_GAME_OBJECT

