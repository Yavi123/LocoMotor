#include "LMVector.h"
#include "LMQuaternion.h"
#include <cmath>
#include <iostream>
#include <list>

#pragma region Vector
// Getter functions
// Get the X value of the LocoMotor::Vector
template <int dims>
inline LocoMotor::Vector<dims>::Vector() {
	for (int i = 0; i < dims; ++i)
		_values[i] = 0.f;
}

template<int dims>
template<typename ...Args>
inline LocoMotor::Vector<dims>::Vector(Args ...args) {
	static_assert(sizeof...(args) == dims, "Wrong number of arguments");
	float tmp[dims] = { static_cast<float>(args)... };
	for (int i = 0; i < dims; ++i)
		_values[i] = tmp[i];
}

#pragma region Getters / Setters
// Getter functions
// Get the X value of the LocoMotor::Vector
template <int dims>
float LocoMotor::Vector<dims>::getX() const {
	return _values[0];
}
// Get the Y value of the LocoMotor::Vector
template <int dims>
float LocoMotor::Vector<dims>::getY() const {
	return _values[1];
}

// Get the Z value of the LocoMotor::Vector
float LocoMotor::Vector<3>::getZ() const {
	return _values[2];
}

// Get the W value of the LocoMotor::Vector
float LocoMotor::Vector<4>::getZ() const {
	return _values[2];
}
// Get the W value of the LocoMotor::Vector
float LocoMotor::Vector<4>::getW() const {
	return _values[3];
}

// Setter functions
// Set the X value of the LocoMotor::Vector
template <int dims>
void LocoMotor::Vector<dims>::setX(float x) {
	this->_values[0] = x;
}
// Set the Y value of the LocoMotor::Vector
template <int dims>
void LocoMotor::Vector<dims>::setY(float y) {
	this->_values[1] = y;
}

// Set the Z value of the LocoMotor::Vector
void LocoMotor::Vector<3>::setZ(float z) {
	this->_values[2] = z;
}

// Set the Z value of the LocoMotor::Vector
void LocoMotor::Vector<4>::setZ(float z) {
	this->_values[2] = z;
}
// Set the Z value of the LocoMotor::Vector
void LocoMotor::Vector<4>::setW(float w) {
	this->_values[3] = w;
}

#pragma endregion

#pragma region Operands
// Sum
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator+(const LocoMotor::Vector<dims>& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] + other._values[i];
	return result;
}

template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator+(const float& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] + other;
	return result;
}

// Sub
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator-(const LocoMotor::Vector<dims>& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] - other._values[i];
	return result;
}
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator-(const float& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] - other;
	return result;
}

// Mul
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator*(const LocoMotor::Vector<dims>& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] * other._values[i];
	return result;
}
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator*(const float& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] * other;
	return result;
}

// Div
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator/(const LocoMotor::Vector<dims>& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] / other._values[i];
	return result;
}
template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::operator/(const float& other) const {
	LocoMotor::Vector<dims> result;
	for (int i = 0; i < dims; ++i)
		result._values[i] = _values[i] / other;
	return result;
}

#pragma endregion

// Dot product
template <int dims>
float LocoMotor::Vector<dims>::dot(const LocoMotor::Vector<dims>& other) const {
	float result = 0.f;
	for (int i = 0; i < dims; i++) {
		result += this->_values[i] * other._values[i];
	}
	return result;
}

// Cross product
LocoMotor::Vector<3> LocoMotor::Vector<3>::cross(const LocoMotor::Vector<3>& other) const {
	return LocoMotor::Vector<3>(this->_values[1] * other._values[2] - this->_values[2] * other._values[1],
					 this->_values[2] * other._values[0] - this->_values[0] * other._values[2],
					 this->_values[0] * other._values[1] - this->_values[1] * other._values[0]);
}
// Cross product
LocoMotor::Vector<3> LocoMotor::Vector<3>::cross(const LocoMotor::Vector<3>& other, const LocoMotor::Vector<3>& axis) const {
	LocoMotor::Vector<3> currentCross = cross(other);
	if (currentCross.dot(axis) < 0) {
		currentCross = currentCross * -1;
	}
	return currentCross;
}

// Magnitude
template <int dims>
float LocoMotor::Vector<dims>::magnitude() const {
	float sqrMag = 0.f;
	for (int i = 0; i < dims; i++) {
		sqrMag += _values[i] * _values[i];
	}
	return sqrtf(sqrMag);
}

// Normalize
template <int dims>
void LocoMotor::Vector<dims>::normalize() {
	float mag = magnitude();
	if (mag > 0) {
		for (int i = 0; i < dims; i++) {
			this->_values[i] /= mag;
		}
	}
}

// Angle between two LocoMotor::Vectors
template <int dims>
float LocoMotor::Vector<dims>::angle(const LocoMotor::Vector<dims>& other) const {
	float currentDot = dot(other);
	float mag = magnitude() * other.magnitude();
	if (mag > 0) {
		return acos(currentDot / mag);
	}
	return 0;
}

//Angle between two LocoMotor::Vectors
float LocoMotor::Vector<3>::angle(const LocoMotor::Vector<3>& other, const LocoMotor::Vector<3>& axis) const {

	static float pi = 3.14159265f;

	float currentAngle = angle(other);
	LocoMotor::Vector<3> currentCross = cross(other);
	if (currentCross.dot(axis) < 0) {
		currentAngle = -currentAngle;
	}

	currentAngle = currentAngle * (float) (180 / pi);

	return currentAngle;
}


//Angle between two LocoMotor::Vectors in degrees
float LocoMotor::Vector<3>::angle(const LocoMotor::Vector<3>& other, const LocoMotor::Vector<3>& normal, const LocoMotor::Vector<3>& axis) const {
	float currentAngle = angle(other, normal);
	LocoMotor::Vector<3> currentCross = cross(other, normal);
	if (currentCross.dot(axis) < 0) {
		currentAngle = -currentAngle;
	}

	static float pi = 3.14159265f;
	currentAngle = currentAngle * (float) (180.f / pi);

	return currentAngle;
}

// Rotate a LocoMotor::Vector around an axis in degrees
LocoMotor::Vector<3> LocoMotor::Vector<3>::rotate(const LocoMotor::Vector<3>& axis, float angle) {
	LocoMotor::Vector<3> cross = axis.cross(*this);
	LocoMotor::Vector<3> dot = axis * axis.dot(*this);
	LocoMotor::Vector<3> cross2 = axis.cross(cross);
	static float pi = 3.14159265f;
	LocoMotor::Vector<3> a = dot + cross * ((float) sin(angle * pi / 180.)) + cross2 * ((float) (1 - cos(angle * pi / 180.)));

	this->_values[0] = a.getX();
	this->_values[1] = a.getY();
	this->_values[2] = a.getZ();

	return a;
}

LocoMotor::Vector<2> LocoMotor::Vector<2>::perpendicular2() const {
	return LocoMotor::Vector<2>(this->_values[1], -this->_values[0]);
}

//Get the perpendicular LocoMotor::Vector from two LocoMotor::Vectors
LocoMotor::Vector<3> LocoMotor::Vector<3>::perpendicular3(const LocoMotor::Vector<3>& other) const {
	return cross(other).cross(*this);
}


LocoMotor::Quaternion LocoMotor::Vector<3>::asRotToQuaternion() const {
	// Abbreviations for the various angular functions

	static float pi = 3.14159265f;
	// Degree to Radian
	LocoMotor::Vector<3> aux = *this;
	aux = aux * (float) (pi / 180);

	double cr = cos(aux.getX() * 0.5);
	double sr = sin(aux.getX() * 0.5);
	double cp = cos(aux.getY() * 0.5);
	double sp = sin(aux.getY() * 0.5);
	double cy = cos(aux.getZ() * 0.5);
	double sy = sin(aux.getZ() * 0.5);

	Quaternion q;
	q.setW((float) (cr * cp * cy + sr * sp * sy));
	q.setX((float) (sr * cp * cy - cr * sp * sy));
	q.setY((float) (cr * sp * cy + sr * cp * sy));
	q.setZ((float) (cr * cp * sy - sr * sp * cy));

	return q;
}

template <int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::stringToVector(const std::string& s) {

	std::list<std::string> nums = std::list<std::string>();
	size_t lastFoundOn = 0;
	size_t newFound = 0;
	std::string foundStr = "";
	while (newFound != std::string::npos) {
		newFound = s.find_first_of(' ', lastFoundOn);
		foundStr = s.substr(lastFoundOn, newFound);
		std::remove(foundStr.begin(), foundStr.end(), ',');
		std::remove(foundStr.begin(), foundStr.end(), '(');
		std::remove(foundStr.begin(), foundStr.end(), ')');
		nums.push_back(foundStr);
		lastFoundOn = newFound + 1;
	}

	LocoMotor::Vector<dims> result = LocoMotor::Vector<dims>();
	unsigned char currAxis = 0;
	for (std::string stValue : nums) {

		float value = 0.f;
		try {
			value = std::stof(stValue);
		}
		catch (...) {
			value = 0.f;
			std::cerr << "\033[1;31m" << "Invalid value detected in axis number '" << std::to_string(currAxis) << "' loading a float from a LocoMotor::Vector3" << "\033[0m" << std::endl;
		}
		result._values[currAxis] = value;
		currAxis++;
		if (currAxis == dims) {
			break;
		}
	}

	return result;
}

template<int dims>
LocoMotor::Vector<dims> LocoMotor::Vector<dims>::lerp(const LocoMotor::Vector<dims>& start, const LocoMotor::Vector<dims>& end, float t) {
	LocoMotor::Vector<dims> result = LocoMotor::Vector<dims>();
	float diff = 0.f;
	for (int i = 0; i < dims; i++) {
		result._values[i] = start._values[i] + t * (end._values[i] - start._values[i]);
	}
	return result;
}

template <int dims>
inline float LocoMotor::Vector<dims>::distance(const LocoMotor::Vector<dims>& v1, const LocoMotor::Vector<dims>& v2) {
	float sqrdDistance = 0.f;
	float diff = 0.f;
	for (int i = 0; i < dims; i++) {
		diff = v2._values[i] - v1._values[i];
		sqrdDistance += (diff * diff);
	}
	return std::sqrt(sqrdDistance);
}

template <int dims>
bool LocoMotor::Vector<dims>::operator==(const LocoMotor::Vector<dims>& other) const {
	for (int i = 0; i < dims; i++) {
		if (this->_values[i] != other._values[i])
			return false;
	}
	return true;
}

#pragma endregion

template class LocoMotor::Vector<2>;
template class LocoMotor::Vector<3>;
template class LocoMotor::Vector<4>;
