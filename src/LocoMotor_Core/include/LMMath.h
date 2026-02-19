#pragma once
#ifndef LM_MATH
#define LM_MATH

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

namespace LocoMotor {

	struct DampedSpringResult {
		DampedSpringResult() : position(0.f), velocity(0.f) {
		}
		float getPosition() const {
			return position;
		}
		float getVelocity() const {
			return velocity;
		}
		void setPosition(float p) {
			position = p;
		}
		void setVelocity(float p) {
			velocity = p;
		}
		float position;
		float velocity;
	};

	class Math {
	public:
		static DampedSpringResult CalculateDampedSpring(const DampedSpringResult& startingState, float targetPos, float deltaTime, float angularFreq, float damping);
		static float Lerp(float origin, float dest, float t);
		static float Clamp(float target, float min, float max);
	};
}

#endif
