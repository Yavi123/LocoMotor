
namespace LocoMotor {
	template<typename int>
	class Vector;
	typedef Vector<3> Vector3;
	class Quaternion;
}
class btVector3;
class btQuaternion;

LocoMotor::Vector3 BulletToLm(const btVector3& bulletVector);
/// @brief Converts an lmVector to Bullet vector
btVector3 LmToBullet(const LocoMotor::Vector3& lmVector);
/// @brief Converts an LMQuaternion to Bullet vector
btQuaternion LmToBullet(const LocoMotor::Quaternion& LMQuaternion);

LocoMotor::Quaternion BulletToLm(const btQuaternion& bulletQuaternion);