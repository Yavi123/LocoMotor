#pragma once
#ifndef LM_TRANSFORM
#define LM_TRANSFORM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Component.h"
#include "LMVector.h"
#include "LMQuaternion.h"

namespace LocoMotor {
	class MOTOR_API Transform : public Component {

	public:

		Transform();
		~Transform();
		/// @brief Initializes a component for a game object and registers its transform.
		void initComponent();
		/// @brief Initializes the position, rotation, and scale of a game object's transform based on input parameters.
		/// @param params A vector of pairs, where each pair contains a string representing a parameter nameand
		/// a string representing the value of that parameter.The function uses these parameters to initialize
		/// the position, rotation, and scale of a transform component.
		void initRuntime(Vector3 initPos = Vector3(0.f, 0.f, 0.f), Vector3 initRot = Vector3(0.f, 0.f, 0.f), Vector3 initScale = Vector3(1.f, 1.f, 1.f));

		/// @brief  Returns the World position of the LocoMotor object.
		/// @return vector
		Vector3 getPosition();
		/// @brief Sets the world position of the LocoMotor object.
		/// @param newPosition The new position 
		void setPosition(const Vector3& newPosition);

		/// @brief Returns the rotation of the LocoMotor object.
		/// @return quaterinion
		Quaternion getRotation();
		/// @brief Returns the Rotation in Euler Degrees of the LocoMotor object.
		/// @return vector 
		Vector3 getEulerRotation();
		/// @brief Sets the rotation of the LocoMotor object.
		/// @param newRotation The new rotation
		
		void setRotation(const Quaternion& newRotation);
		void setRotationWithVector(const Vector3& newRotation);

		/// @brief Returns the size of the LocoMotor object.
		/// @return vector
		Vector3 getSize();
		/// @brief Sets the size of the LocoMotor object.
		/// @param newSize The new size
		void setSize(const Vector3& newSize);
		/// @brief Sets up a new upward direction for a LocoMotor object by calculating the rotation
		/// needed to align the current upward direction with the new one.
		/// @param newUpward A LMVector3 representing the new upward direction to set for the LocoMotor object.
		void setUpwards(const Vector3& newUpward);
		/// @brief Sets the forward direction of a LocoMotor object by calculating the rotation needed to
		/// align the current forward direction with a new given direction.
		/// @param newForward  A LMVector3 representing the new forward direction that the LocoMotor should face.
		void setForward(const Vector3& newForward);
		/// @brief Updates the forward vector of a LocoMotor object.
		/// @param lookPos A LMVector3 representing the position to look at.
		void lookAt(const Vector3& lookPos);
		/// @brief Sets the forward and upward vectors of a transform to look at a specified position with
		/// a specified upward direction.
		/// @param lookPos A LMVector3 representing the position that the LocoMotor's Transform should be
		/// looking at.
		/// @param up The "up" parameter is a LMVector3 that represents the direction that is considered "up" in
		/// the world space.This is used to ensure that the object being transformed maintains a consistent
		/// orientation, even if it is rotated.
		void lookAt(const Vector3& lookPos, const Vector3& up);

	protected:

		bool setParameters(ComponentMap& params) override;
		void start() override;
		void update(const float dt) override;

	private:

		Vector3 _position;
		Vector3 _scale;
		Quaternion _direction;
	};
}

#endif