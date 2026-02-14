#pragma once
#ifndef LOCOMOTOR_LIGHT
#define LOCOMOTOR_LIGHT

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"

namespace Ogre {
	class Entity;
	class MovableObject;
	class SceneNode;
	class Light;
}

namespace LocoMotor {

	namespace Graphics {
		class GraphicsManager;
	}

	MOTOR_API enum LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	class Light :public LocoMotor::Component {
		friend class Graphics::GraphicsManager;
	public:

		Light();
		~Light();

		MOTOR_API void setLightType(const LightType& t);

	protected:


		bool setParameters(ComponentMap& params) override;
		void awake() override;
		void onEnable() override;
		void start() override;
		void onDisable() override;
		void update(float dt) override;

	private:
		bool _setStatic;

		bool isSelfVisible;

		Ogre::SceneNode* _node;

		Ogre::Light* _light;

		Ogre::MovableObject* getMovObj();

		static unsigned char toOgreType(const LightType& t);
	};

}

#endif // !LOCOMOTOR_LIGHT
