#include "BulletVectorConverter.h"
#include "LMVector.h"
#include "LMQuaternion.h"
#include "btBulletDynamicsCommon.h"

LocoMotor::Vector3 BulletToLm(const btVector3& bulletVector) {
    return LocoMotor::Vector3(bulletVector.x(), bulletVector.y(), bulletVector.z());
}

btVector3 LmToBullet(const LocoMotor::Vector3& lmVector) {
    return btVector3((float) lmVector.getX(), (float) lmVector.getY(), (float) lmVector.getZ());
}
btQuaternion LmToBullet(const LocoMotor::Quaternion& LMQuaternion) {
    return btQuaternion((float) LMQuaternion.getX(), (float) LMQuaternion.getY(), (float) LMQuaternion.getZ(), (float) LMQuaternion.getW());
}

LocoMotor::Quaternion BulletToLm(const btQuaternion& bulletQuaternion)
{
    return LocoMotor::Quaternion(bulletQuaternion.w(), bulletQuaternion.x(), bulletQuaternion.y(), bulletQuaternion.z());
}
