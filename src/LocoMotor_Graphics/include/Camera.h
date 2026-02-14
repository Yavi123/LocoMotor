#pragma once
#ifndef CAMERA
#define CAMERA

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"
#include "LMVector.h"
#include "LMQuaternion.h"



namespace Ogre {
	class Camera;
	class Viewport;
	class SceneNode;
}

namespace LocoMotor{

	namespace Graphics {
		class GraphicsManager;
	}
	
	class MOTOR_API Camera : public Component {

		friend class Graphics::GraphicsManager;

	public:

		Camera();
		~Camera();

		/// @brief Set the target and offset for the camera of a LocoMotor object.
		/// @param target A pointer to a GameObject that the camera will follow as its target.
		/// @param offset The offset is a vector that represents the distance and direction from the target
		/// object's position where the camera should be positioned. It is used to adjust the camera's position
		/// relative to the target object.
		void SetTarget(GameObject* target, const Vector3& offset);

		/// @brief Sets the field of view (FOV) of a camera object.
		/// @param newFov newFov is a float variable representing the new field of view (FOV) value that will be
		/// set for the camera. FOV is the extent of the observable world that is seen at any given moment
		/// through the camera lens. It is usually measured in degrees and determines how much of the scene
		void SetFOV(float newFov);

		void SetViewportRatio(int viewportIndex, int modeIndex);

		/// @brief Set the clipping plane of a camera object.
		/// @param nearPlane The distance from the camera to the nearest visible object in the scene. Any object
		/// closer than this distance will not be visible in the rendered image.
		/// @param farPlane The far clipping plane is the maximum distance from the camera at which objects will
		/// be rendered. Any objects beyond this distance will not be visible in the rendered image.
		void SetClippingPlane(int nearPlane, int farPlane);

		/// @brief Sets the color of the viewport when nothing is seen
		/// @param r Red value
		/// @param g Green value
		/// @param b Blue value
		void setBackgroundColor(float r, float g, float b);

		void init()/* override*/;
	protected:

		bool setParameters(ComponentMap& params) override;
		void onEnable() override;
		void update(float dT) override;
		// Heredado via Component
		void start() override;
		void onDisable() override;

	private:

		GameObject* _target;
		Vector3 _offset;
		Quaternion _nodeRotation;

		Ogre::Camera* _mCamera;
		Ogre::Viewport* _vp;

		Ogre::SceneNode* _node;

		Graphics::GraphicsManager* _man;

		void render();
	};

}
#endif // !CAMERA