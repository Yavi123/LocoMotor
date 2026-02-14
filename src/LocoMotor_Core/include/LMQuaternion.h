#pragma once
#ifndef LM_QUATERNION
#define LM_QUATERNION

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

namespace LocoMotor {
	template<typename int>
	class Vector;

	//Quaternion class to be used with LocoMotor
	class Quaternion {

	public:
		// Default constructor initializes quaternion to (1, 0, 0, 0)
		/// @brief Create a new Quaternion with everything Set to default
		Quaternion();

		// Constructor initializes quaternion to specified values
		/// @brief Create a new Quaternion
		Quaternion(float w, float x, float y, float z);

		/// @brief Hack para crear Quaternions desde lua
		/// @param w 
		/// @param x 
		/// @param y 
		/// @param z 
		/// @return 
		static inline Quaternion createQuat(float w, float x, float y, float z) {
			return Quaternion(w, x, y, z);
		}
		// Getter functions
		/// @brief Get the W value of the Quaternion
		float getW() const;
		/// @brief Get the X value of the Quaternion
		float getX() const;
		/// @brief Get the Y value of the Quaternion
		float getY() const;
		/// @brief Get the Z value of the Quaternion
		float getZ() const;

	//Setter functions
		/// @brief Set the W value of the Quaternion
		void setW(float w);
		/// @brief Set the X value of the Quaternion
		void setX(float x);
		/// @brief Set the Y value of the Quaternion
		void setY(float y);
		/// @brief Set the Z value of the Quaternion
		void setZ(float z);

		//Equal operators of quaternions
		Quaternion operator=(const Quaternion& other);

		// Add operators of quaternions
		Quaternion operator+(const Quaternion& other) const;

		// Sub operators of quaternions
		Quaternion operator-(const Quaternion& other) const;

		// Mul operators of quaternions
		Quaternion operator*(const Quaternion& other) const;
		Quaternion operator*(float scalar) const;
		Vector<3> operator*(const LocoMotor::Vector<3>& other) const;

		// Div operators of quaternions
		Quaternion operator/(float scalar) const;

		// Conjugate
		/// @brief Get the Conjugate of a Quaternion
		Quaternion conjugate() const;

		// Magnitude
		/// @brief Get the Magnitude of a Quaternion
		float magnitude() const;

		// Normalize
		/// @brief Normalize a Quaternion
		void normalize();

		// Rotate
		/// @brief Rotate a Quaternion
		/// @param axis The Axis to rotate around
		/// @param angle The Angle to rotate by (degrees)
		Quaternion rotate(const Vector<3>& axis, float angle) const;

		// Rotate a vector by this quaternion
		/// @brief Rotate a Vector by this Quaternion
		/// @param vector The Vector to be rotated
		Vector<3> rotate(const Vector<3>& vector) const;

		// Up vector from Quaternion
		/// @brief Get the Up Vector from a Quaternion
		Vector<3> up() const;

		// Right vector from Quaternion
		/// @brief Get the Right Vector from a Quaternion
		Vector<3> right() const;

		// Forward vector from Quaternion
		/// @brief Get the Forward Vector from a Quaternion
		Vector<3> forward() const;

		/// @brief Returns the Quaternion to Euler vector3
		Vector<3> toEuler() const;
	private:
		float _w = 0, _x = 0, _y = 0, _z = 0;
	};
}

#endif
