#include "RectTransform.h"
#include "UIImage.h"
#include "GameObject.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"
#include <iostream>

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"

using namespace LocoMotor;

LocoMotor::UIImage::UIImage() : _gfxManager(nullptr), _container(nullptr), _overlayMngr(nullptr), _overlay(nullptr), _rectTransform() {
}

LocoMotor::UIImage::~UIImage() {
	_overlayMngr->destroyOverlayElement(_container);
	_container = nullptr;
	Ogre::OverlayManager::getSingletonPtr()->destroy(_overlay->getName());
	_overlay = nullptr;
}

void LocoMotor::UIImage::setImage(const std::string& nImage) {
	if (Ogre::MaterialManager::getSingletonPtr()->resourceExists(nImage))
		_container->setMaterialName(nImage);
	else {
		_container->setMaterialName(Ogre::MaterialManager::getSingleton().getDefaultMaterial()->getName());
	#ifdef _DEBUG
		std::cerr << "\033[1;31m" << "Material '" << nImage << "' wasn't found in any known .material script. UIImage at gameObject: " << _gameObject->getName() << "\033[0m" << std::endl;
	#endif
	}
}

bool LocoMotor::UIImage::setParameters(ComponentMap& params) {

	_gfxManager = Graphics::GraphicsManager::GetInstance();
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();

	_overlay = _overlayMngr->create("overlay_" + _gameObject->getName() + "_img");

	_container = static_cast<Ogre::OverlayContainer*>(_overlayMngr->createOverlayElement("Panel", "UIImage" + _gameObject->getName()));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);

	std::string imageName = "";
	int sortingLayer = 0;
	float rotation = 0.f;

	for (auto& param : params) {
		if (param.first.find("ect") != std::string::npos) {
			_rectTransform.setParam(param.first, param.second);
		}
		else if (param.first == "SortingLayer" || param.first == "sortingLayer") {
			try {
				sortingLayer = std::stoi(param.second);
			}
			catch (...) {
				sortingLayer = 0;
			}
		}
		else if (param.first == "Rotation" || param.first == "rotation") {
			try {
				rotation = std::stof(param.second);
			}
			catch (...) {
				rotation = 0.f;
			}
		}
		else if (param.first == "Image" || param.first == "image") {
			imageName = param.second;
		}
	}

	_rectTransform.setParentSize({ (float)_gfxManager->getWindowWidth(), (float)_gfxManager->getWindowHeight() });

	updatePosition();

	setImage(imageName);

	setSortingLayer(sortingLayer);
	setRotation(rotation);

	_overlay->add2D(_container);

	_overlay->show();
	return true;
}

void LocoMotor::UIImage::update(float dT) {
	updatePosition();
}

void LocoMotor::UIImage::setAnchorPoint(const Vector2& anc) {
	_rectTransform.setAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIImage::setMaxAnchorPoint(const Vector2& anc) {
	_rectTransform.setMaxAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIImage::setMinAnchorPoint(const Vector2& anc) {
	_rectTransform.setMinAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIImage::setDimensions(const Vector2& anc) {
	_rectTransform.setDimensions(anc);
	updatePosition();
}

void LocoMotor::UIImage::setUpLeftOffset(const Vector2& anc) {
	_rectTransform.setUpLeftOffset(anc);
	updatePosition();
}

void LocoMotor::UIImage::setDownRightOffset(const Vector2& anc) {
	_rectTransform.setDownRightOffset(anc);
	updatePosition();
}

void LocoMotor::UIImage::setSortingLayer(int layer) {
	if (layer < 0) layer = 0;
	else if (layer > 650) layer = 650;
	_overlay->setZOrder(Ogre::ushort(layer));
}

void LocoMotor::UIImage::setRotation(float radians) {
	_overlay->setRotate(Ogre::Radian(radians));
}

void LocoMotor::UIImage::show() {
	_container->show();
}

void LocoMotor::UIImage::hide() {
	_container->hide();
}

int LocoMotor::UIImage::getWidth() {
	Rect totalRect = _rectTransform.getTotalBounds();
	return totalRect._downRightPoint.getX() - totalRect._upLeftPoint.getX();
}

int LocoMotor::UIImage::getHeight() {
	Rect totalRect = _rectTransform.getTotalBounds();
	return totalRect._downRightPoint.getY() - totalRect._upLeftPoint.getY();
}

void LocoMotor::UIImage::updatePosition() {
	_container->setMetricsMode(Ogre::GMM_PIXELS);

	_rectTransform.refreshBounds();
	Rect totalRect = _rectTransform.getTotalBounds();

	_container->setDimensions(totalRect._downRightPoint.getX() - totalRect._upLeftPoint.getX(), totalRect._downRightPoint.getY() - totalRect._upLeftPoint.getY());

	_container->setPosition(totalRect._upLeftPoint.getX(), totalRect._upLeftPoint.getY());
}
