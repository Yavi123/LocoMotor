#include "RectTransform.h"

using namespace LocoMotor;

LocoMotor::RectTransform::RectTransform() : _parentSize() {
	refreshBounds();
}

void RectTransform::setParam(const std::string& name, const std::string& value) {

	if (name.find("nchor") != std::string::npos) {

		auto vec = Vector2::stringToVector(value);
		if (name.find("ax") != std::string::npos) {
			_maxAnchor = vec;
		}
		else if (name.find("in") != std::string::npos) {
			_minAnchor = vec;
		}
		else {
			_maxAnchor = vec;
			_minAnchor = vec;
		}
	}
	else if (name.find("ize") != std::string::npos) {

		auto vec = Vector2::stringToVector(value);
		_upLeftOffset = vec / 2.f;
		_downRightOffset = vec / 2.f;
	}
	else if (name.find("pleft") != std::string::npos || name.find("pLeft") != std::string::npos) {
		auto vec = Vector2::stringToVector(value);
		_upLeftOffset = vec;
	}
	else if (name.find("ownright") != std::string::npos || name.find("ownRight") != std::string::npos) {
		auto vec = Vector2::stringToVector(value);
		_downRightOffset = vec;
	}
}

Rect RectTransform::getTotalBounds() {
	return _totalBounds;
}

void LocoMotor::RectTransform::setParentSize(const Vector2& p) {
	_parentSize = p;
}

void RectTransform::setAnchorPoint(const Vector2& anc) {
	_maxAnchor = anc;
	_minAnchor = anc;
}

void RectTransform::setMaxAnchorPoint(const Vector2& anc) {
	_maxAnchor = anc;
}

void RectTransform::setMinAnchorPoint(const Vector2& anc) {
	_minAnchor = anc;
}

void RectTransform::setDimensions(const Vector2& anc) {
	_upLeftOffset = anc / 2.f;
	_downRightOffset = anc / 2.f;
}

void RectTransform::setUpLeftOffset(const Vector2& anc) {
	_upLeftOffset = anc;
}

void RectTransform::setDownRightOffset(const Vector2& anc) {
	_downRightOffset = anc;
}

void LocoMotor::RectTransform::refreshBounds() {

	_totalBounds._upLeftPoint.setX(_parentSize.getX() * _minAnchor.getX() - _upLeftOffset.getX());
	_totalBounds._upLeftPoint.setY(_parentSize.getY() * _minAnchor.getY() - _upLeftOffset.getY());

	_totalBounds._downRightPoint.setX(_totalBounds._upLeftPoint.getX() + (_upLeftOffset.getX() + (_parentSize.getX() * (_maxAnchor.getX() - _minAnchor.getX())) + _downRightOffset.getX()));
	_totalBounds._downRightPoint.setY(_totalBounds._upLeftPoint.getY() + (_upLeftOffset.getY() + (_parentSize.getY() * (_maxAnchor.getY() - _minAnchor.getY())) + _downRightOffset.getY()));
}
