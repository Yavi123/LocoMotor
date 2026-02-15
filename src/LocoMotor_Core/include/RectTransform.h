#pragma once
#ifndef LM_RECTTRANSFORM
#define LM_RECTTRANSFORM

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <string>
#include "LMVector.h"

namespace LocoMotor {

	struct Rect {
	public:
		Vector2 _upLeftPoint;
		Vector2 _downRightPoint;
	};

	class RectTransform {
	public:
		RectTransform();

		void setParam(const std::string& name, const std::string& value);

		Rect getTotalBounds();

		void setParentSize(const Vector2& p);

		/// @brief Sets the anchor point of the element
		void setAnchorPoint(const Vector2& anc);
		void setMaxAnchorPoint(const Vector2& anc);
		void setMinAnchorPoint(const Vector2& anc);

		/// @brief Sets the size of the entity on the UI
		void setDimensions(const Vector2& anc);
		void setUpLeftOffset(const Vector2& anc);
		void setDownRightOffset(const Vector2& anc);

		void refreshBounds();

	private:
		Rect _totalBounds;

		Vector2 _parentSize;

		Vector2 _maxAnchor = Vector2(0.5f, 0.5f);
		Vector2 _minAnchor = Vector2(0.5f, 0.5f);

		Vector2 _upLeftOffset = Vector2(25.f, 25.f);
		Vector2 _downRightOffset = Vector2(25.f, 25.f);
	};
}

#endif
