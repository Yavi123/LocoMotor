#define _USE_MATH_DEFINES

#include "LMQuaternion.h"
#include "LMVector.h"
#include <cmath>
#include <iostream>

using namespace LocoMotor;

#pragma region Quaternion

//Quaternion class to be used with LocoMotor

// Default constructor initializes quaternion to (1, 0, 0, 0)
Quaternion::Quaternion() : _w(1), _x(0), _y(0), _z(0) {
}

// Constructor initializes quaternion to specified values
Quaternion::Quaternion(float w, float x, float y, float z) : _w(w), _x(x), _y(y), _z(z) {
}

// Getter functions
float Quaternion::getW() const {
	return _w;
}
float Quaternion::getX() const {
	return _x;
}
float Quaternion::getY() const {
	return _y;
}
float Quaternion::getZ() const {
	return _z;
}

//Setter functions
void Quaternion::setW(float w) {
	this->_w = w;
}
void Quaternion::setX(float x) {
	this->_x = x;
}
void Quaternion::setY(float y) {
	this->_y = y;
}
void Quaternion::setZ(float z) {
	this->_z = z;
}

// Quaternion equal
Quaternion Quaternion::operator=(const Quaternion& other) {
	_w = other._w;
	_x = other._x;
	_y = other._y;
	_z = other._z;
	return *this;
}



// Quaternion addition
Quaternion Quaternion::operator+(const Quaternion& other) const {
	return Quaternion(_w + other._w, _x + other._x, _y + other._y, _z + other._z);
}


// Quaternion subtraction
Quaternion Quaternion::operator-(const Quaternion& other) const {
	return Quaternion(_w - other._w, _x - other._x, _y - other._y, _z - other._z);
}


// Quaternion multiplication
Quaternion Quaternion::operator*(const Quaternion& other) const {
	float newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
	float newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
	float newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
	float newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
	return Quaternion(newW, newX, newY, newZ);
}
// Scalar multiplication
Quaternion Quaternion::operator*(float scalar) const {
	return Quaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

// Scalar division
Quaternion Quaternion::operator/(float scalar) const {
	return Quaternion(_w / scalar, _x / scalar, _y / scalar, _z / scalar);
}



Vector<3> Quaternion::operator*(const Vector<3>& other) const {
	float num = this->_x * 2.f;
	float num2 = this->_y * 2.f;
	float num3 = this->_z * 2.f;
	float num4 = this->_x * num;
	float num5 = this->_y * num2;
	float num6 = this->_z * num3;
	float num7 = this->_x * num2;
	float num8 = this->_x * num3;
	float num9 = this->_y * num3;
	float num10 = this->_w * num;
	float num11 = this->_w * num2;
	float num12 = this->_w * num3;
	Vector<3> result = Vector<3>();
	result.setX((1.f - (num5 + num6)) * other.getX() + (num7 - num12) * other.getY() + (num8 + num11) * other.getZ());
	result.setY((num7 + num12) * other.getX() + (1.f - (num4 + num6)) * other.getY() + (num9 - num10) * other.getZ());
	result.setZ((num8 - num11) * other.getX() + (num9 + num10) * other.getY() + (1.f - (num4 + num5)) * other.getZ());
	return result;
}

// Conjugate
Quaternion Quaternion::conjugate() const {
	return Quaternion(_w, -_x, -_y, -_z);
}

// Magnitude
float Quaternion::magnitude() const {
	return sqrt(_w * _w + _x * _x + _y * _y + _z * _z);
}

// Normalize
void Quaternion::normalize() {
	float mag = magnitude();
	if (mag > 0) {
		_w /= mag;
		_x /= mag;
		_y /= mag;
		_z /= mag;
	}
}

//Rotate a quaternion
Quaternion Quaternion::rotate(const Vector<3>& axis, float angle) const {
	Quaternion q;
	float halfAngle = (float) (angle * (M_PI / 180.0f)) / 2.0f;
	float sinHalfAngle = sin(halfAngle);
	q.setW(cos(halfAngle));
	q.setX(axis.getX() * sinHalfAngle);
	q.setY(axis.getY() * sinHalfAngle);
	q.setZ(axis.getZ() * sinHalfAngle);
	return q * (*this);
}

// Rotate a vector by this quaternion
Vector<3> Quaternion::rotate(const Vector<3>& vector) const {
	Quaternion vectorQuat(0, vector.getX(), vector.getY(), vector.getZ());
	Quaternion result = (*this) * vectorQuat * conjugate();
	return Vector<3>(result.getX(), result.getY(), result.getZ());
}

// Up vector of this quaternion
Vector<3> Quaternion::up() const {
	return rotate(Vector<3>(0.f, 1.f, 0.f));
}

// Right vector of this quaternion
Vector<3> Quaternion::right() const {
	return rotate(Vector<3>(1.f, 0.f, 0.f));
}

// Forward vector of this quaternion
Vector<3> Quaternion::forward() const {
	return rotate(Vector<3>(0.f, 0.f, -1.f));
}

Vector<3> Quaternion::toEuler() const {
	Vector<3> angles;

// roll (x-axis rotation)
	float sinr_cosp = 2 * (this->_w * this->_x + this->_y * this->_z);
	float cosr_cosp = 1 - 2 * (this->_x * this->_x + this->_y * this->_y);
	angles.setX(std::atan2(sinr_cosp, cosr_cosp));

	// pitch (y-axis rotation)
	float sinp = std::sqrt(1 + 2 * (this->_w * this->_y - this->_x * this->_z));
	float cosp = std::sqrt(1 - 2 * (this->_w * this->_y - this->_x * this->_z));
	angles.setY(2 * std::atan2(sinp, cosp) - (float) M_PI / 2.f);

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (this->_w * this->_z + this->_x * this->_y);
	float cosy_cosp = 1 - 2 * (this->_y * this->_y + this->_z * this->_z);
	angles.setZ(std::atan2(siny_cosp, cosy_cosp));

	return angles;
}

#pragma endregion