#include "LMMath.h"
#include <corecrt_math.h>

LocoMotor::DampedSpringResult LocoMotor::Math::CalculateDampedSpring(const LocoMotor::DampedSpringResult& startingState, float targetPos, float deltaTime, float angularFreq, float damping) {

	const float epsilon = 0.0001f;

	// force values into legal range
	if (damping < 0.0f) damping = 0.0f;
	if (angularFreq < 0.0f) angularFreq = 0.0f;

	float m_posPosCoef = 1.f;
	float m_posVelCoef = 0.f;
	float m_velPosCoef = 0.f;
	float m_velVelCoef = 1.f;

	// if there is no angular frequency, the spring will not move and we can
	// return identity
	if (angularFreq >= epsilon) {
		if (damping > 1.0f + epsilon) {
			// over-damped
			float za = -angularFreq * damping;
			float zb = angularFreq * sqrtf(damping * damping - 1.0f);
			float z1 = za - zb;
			float z2 = za + zb;

			float e1 = expf(z1 * deltaTime);
			float e2 = expf(z2 * deltaTime);

			float invTwoZb = 1.0f / (2.0f * zb); // = 1 / (z2 - z1)

			float e1_Over_TwoZb = e1 * invTwoZb;
			float e2_Over_TwoZb = e2 * invTwoZb;

			float z1e1_Over_TwoZb = z1 * e1_Over_TwoZb;
			float z2e2_Over_TwoZb = z2 * e2_Over_TwoZb;

			m_posPosCoef = e1_Over_TwoZb * z2 - z2e2_Over_TwoZb + e2;
			m_posVelCoef = -e1_Over_TwoZb + e2_Over_TwoZb;

			m_velPosCoef = (z1e1_Over_TwoZb - z2e2_Over_TwoZb + e2) * z2;
			m_velVelCoef = -z1e1_Over_TwoZb + z2e2_Over_TwoZb;
		}
		else if (damping < 1.0f - epsilon) {
			// under-damped
			float omegaZeta = angularFreq * damping;
			float alpha = angularFreq * sqrtf(1.0f - damping * damping);

			float expTerm = expf(-omegaZeta * deltaTime);
			float cosTerm = cosf(alpha * deltaTime);
			float sinTerm = sinf(alpha * deltaTime);

			float invAlpha = 1.0f / alpha;

			float expSin = expTerm * sinTerm;
			float expCos = expTerm * cosTerm;
			float expOmegaZetaSin_Over_Alpha = expTerm * omegaZeta * sinTerm * invAlpha;

			m_posPosCoef = expCos + expOmegaZetaSin_Over_Alpha;
			m_posVelCoef = expSin * invAlpha;

			m_velPosCoef = -expSin * alpha - omegaZeta * expOmegaZetaSin_Over_Alpha;
			m_velVelCoef = expCos - expOmegaZetaSin_Over_Alpha;
		}
		else {
			// critically damped
			float expTerm = expf(-angularFreq * deltaTime);
			float timeExp = deltaTime * expTerm;
			float timeExpFreq = timeExp * angularFreq;

			m_posPosCoef = timeExpFreq + expTerm;
			m_posVelCoef = timeExp;

			m_velPosCoef = -angularFreq * timeExpFreq;
			m_velVelCoef = -timeExpFreq + expTerm;
		}
	}

	LocoMotor::DampedSpringResult result = LocoMotor::DampedSpringResult();
	float relativeStartingPos = startingState.position - targetPos;
	result.position = (relativeStartingPos * m_posPosCoef) + (startingState.velocity * m_posVelCoef) + targetPos;
	result.velocity = (relativeStartingPos * m_velPosCoef) + (startingState.velocity * m_velVelCoef);

	return result;
}

float LocoMotor::Math::Lerp(float origin, float dest, float t) {
	t = Clamp(t, 0.f, 1.f);
	return ((dest - origin) * t) + origin;
}

float LocoMotor::Math::Clamp(float target, float min, float max) {
	return target;
}
