#pragma once
#ifndef LM_VECTOR
#define LM_VECTOR

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>

namespace LocoMotor {
	class MOTOR_API Quaternion;

	//Vector class to be used with LocoMotor
	template<int dims>
	class MOTOR_API Vector {

	public:
		Vector();

		template<typename... Args>
		Vector(Args... args);

		// Getter functions
		/// @brief Get the X value of the Vector
		float getX() const;
		/// @brief Get the Y value of the Vector
		float getY() const;
		/// @brief Get the Z value of the Vector
		float getZ() const;
		/// @brief Get the W value of the Vector
		float getW() const;

		// Setter functions
		/// @brief Set the X value of the Vector
		void setX(float x);
		/// @brief Set the Y value of the Vector
		void setY(float y);
		/// @brief Set the Z value of the Vector
		void setZ(float z);
		/// @brief Set the W value of the Vector
		void setW(float w);

		// Equal operators of vectors

		// Sum operators of vectors
		Vector operator+(const Vector& other) const;
		Vector operator+(const float& other) const;
		// Sub operators of vectors
		Vector operator-(const Vector& other) const;
		Vector operator-(const float& other) const;

		// Mul operators of vectors
		Vector operator*(const Vector& other) const;
		Vector operator*(const float& other) const;

		// Div operators of vectors
		Vector operator/(const Vector& other) const;
		Vector operator/(const float& other) const;

		// Dot product
		///	@brief Get the Dot Product of two Vectors
		/// @param other The other Vector
		float dot(const Vector<dims>& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param other The other Vector
		Vector cross(const Vector<dims>& other) const;

		// Cross product
		///	@brief Get the Cross Product of two Vectors
		/// @param normal The normal Vector
		/// @param other The other Vector
		Vector cross(const Vector<dims>& other, const Vector<dims>& normal) const;

		// Magnitude
		///	@brief Get the Magnitude of a Vector
		float magnitude() const;

		// Normalize
		///	@brief Normalize a Vector
		void normalize();

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		float angle(const Vector<dims>& other) const;

		// Angle
		///	@brief Get the Angle between two Vectors
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		float angle(const Vector<3>& other, const Vector<3>& normal) const;

		// Angle
		///	@brief Get the Angle between two Vectors in degrees
		/// @param other The other Vector to measure from
		/// @param normal The normal Vector
		/// @param axis The axis to measure by
		float angle(const Vector<3>& other, const Vector<3>& normal, const Vector<3>& axis) const;

		// rotate
		///	@brief Rotate a Vector
		/// @param axis The axis to rotate around
		/// @param angle The angle to rotate (degrees)
		Vector rotate(const Vector<dims>& axis, float angle);

		// perpendicular
		///	@brief Get the perpendicular
		Vector<2> perpendicular2() const;

		// perpendicular
		///	@brief Get the perpendicular vector from two Vectors
		/// @param other The other Vector
		Vector<3> perpendicular3(const Vector<3>& other) const;


		/// @brief Convert a rotation vector to Quaternion
		Quaternion asRotToQuaternion() const;

		/// @brief Converts a String to a vector
		/// @param s String to convert
		/// @return Vector converted
		static Vector<dims> stringToVector(const std::string& s);

		static Vector<dims> lerp(const Vector<dims>& start, const Vector<dims>& end, float t);

		static float distance(const Vector<dims>& v1, const Vector<dims>& v2);

		bool operator==(const Vector<dims>& other) const;

		/// @brief Hack para poder crear un vector con lua
		/// @param x 
		/// @param y 
		/// @param z 
		/// @return 
		static inline Vector<2> createVector2(float x, float y) {
			return Vector<2>(x, y);
		}
		static inline Vector<3> createVector3(float x, float y, float z) {
			return Vector<3>(x, y, z);
		}
		static inline Vector<4> createVector4(float x, float y, float z, float w) {
			return Vector<4>(x, y, z, w);
		}

	private:
		float _values[dims];
	};

	using Vector2 = Vector<2>;
	using Vector3 = Vector<3>;
	using Vector4 = Vector<4>;

	extern template class MOTOR_API Vector<2>;
	extern template class MOTOR_API Vector<3>;
	extern template class MOTOR_API Vector<4>;
}

#endif 