#pragma once
#ifndef MESH_RENDERER
#define MESH_RENDERER

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif


#include "Component.h"
#include <unordered_map>

namespace Ogre {
	class Entity;
	class MovableObject;
	class Mesh;
	class SceneNode;
	class AnimationState;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
	}

	class MeshRenderer :public LocoMotor::Component {
		friend class Graphics::GraphicsManager;
	public:

		MeshRenderer();
		~MeshRenderer();
		
		MOTOR_API void setMaterial(const std::string& mat);

		MOTOR_API void setMesh(const std::string& mesh);
		
		/// @brief Sets the Mesh renderer visible/invisible
		MOTOR_API void setVisible(bool visible);

		MOTOR_API void init(const std::string& name, const std::string& file, bool istatic);


		MOTOR_API void playAnimation(const std::string& animationName, bool loop);
		MOTOR_API void updateAnimation(double time);

	protected:


		bool setParameters(ComponentMap& params) override;
		void awake() override;
		void onEnable() override;
		void start() override;
		void onDisable() override;
		void update(float dt) override;

	private:
		Ogre::Entity* _mesh;
		std::string _mat;
		std::string _src;
		bool _setStatic;

		bool isSelfVisible;

		Ogre::SceneNode* _node;

		Ogre::MovableObject* getMovObj();

		// Prueba animaciones
		std::unordered_map<std::string, Ogre::AnimationState*> allAnimations;

		// The animation that is currently being played
		Ogre::AnimationState* currentAnimation;

		int numAnimationsActive;
	};
	
}
#endif // !MESH_RENDERER