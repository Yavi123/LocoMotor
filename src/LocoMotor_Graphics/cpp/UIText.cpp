#include "UIText.h"
#include "GraphicsManager.h"
#include "OverlayManager.h"
#include "GameObject.h"
#include "LMVector.h"

#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreMaterialManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

#include "OgreResourceManager.h"
#include "OgreResource.h"

using namespace LocoMotor;

LocoMotor::UIText::UIText() : _gfxManager(nullptr), _container(nullptr), _overlayMngr(nullptr), _txtElem(nullptr) {
	_uType = "t";
	_uTxtName = "New Text";
}

LocoMotor::UIText::~UIText() {
	_container->removeChild(_txtElem->getName());
	_overlayMngr->destroyOverlayElement(_container);
	_container = nullptr;
	_overlayMngr->destroy(_overlay->getName());
	_overlay = nullptr;
}

void LocoMotor::UIText::setText(std::string text) {
	_uTxtName = text;
	_txtElem->setCaption(_uTxtName);
}

void LocoMotor::UIText::setFont(std::string nFont) {

	if (nFont == "") return;

	auto a = Ogre::FontManager::getSingletonPtr();

	auto res = a->createOrRetrieve(nFont, "General");

	if (!res.second) {
		_txtElem->setFontName(nFont);
		if (_uType[0] == 'i') _txtElem->getFont()->setType(Ogre::FT_IMAGE);
		else _txtElem->getFont()->setType(Ogre::FT_TRUETYPE);
	}
}

bool LocoMotor::UIText::setParameters(ComponentMap& params) {

	_gfxManager = Graphics::GraphicsManager::GetInstance();
	_overlayMngr = Ogre::OverlayManager::getSingletonPtr();

	_overlay = _overlayMngr->create("overlay_" + _gameObject->getName() + "_txt");

	_container = static_cast<Ogre::OverlayContainer*>(
		_overlayMngr->createOverlayElement("Panel", "UIText_" + _gameObject->getName()));
	_container->initialise();

	_container->setMetricsMode(Ogre::GMM_PIXELS);

	_txtElem = static_cast<Ogre::TextAreaOverlayElement*>(
		  _overlayMngr->createOverlayElement("TextArea", "UITextElem" + _gameObject->getName()));

	_txtElem->setMetricsMode(Ogre::GMM_PIXELS);

	int sortingLayer = 0;
	float rotation = 0.f;
	std::string text = "New Text";
	std::string font = "";
	Ogre::TextAreaOverlayElement::Alignment alignment = Ogre::TextAreaOverlayElement::Alignment::Left;
	Vector3 colTop = Vector3();
	Vector3 colBot = Vector3();

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
		else if (param.first == "Text" || param.first == "text") {
			text = param.second;
		}
		else if (param.first == "Font" || param.first == "font") {
			font = param.second;
		}
		else if (param.first == "Alignment" || param.first == "alignment") {
			if (param.second[0] == 'C' || param.second[0] == 'c') {
				alignment = Ogre::TextAreaOverlayElement::Alignment::Center;
			}
			else if (param.second[0] == 'R' || param.second[0] == 'r') {
				alignment = Ogre::TextAreaOverlayElement::Alignment::Right;
			}
		}
		else if (param.first == "ColorTop" || param.first == "colorTop") {
			colTop = Vector3::stringToVector(param.second);
		}
		else if (param.first == "ColorBot" || param.first == "colorBot") {
			colBot = Vector3::stringToVector(param.second);
		}
	}

	_rectTransform.setParentSize({ (float) _gfxManager->getWindowWidth(), (float) _gfxManager->getWindowHeight() });

	updatePosition();

	setFont(font);
	setText(text);
	Rect totalRect = _rectTransform.getTotalBounds();
	_txtElem->setCharHeight(Ogre::Real(totalRect._downRightPoint.getY() - totalRect._upLeftPoint.getY()));
	_txtElem->setColourTop(Ogre::ColourValue(colTop.getX(), colTop.getY(), colTop.getZ(), 1.f));
	_txtElem->setColourBottom(Ogre::ColourValue(colBot.getX(), colBot.getY(), colBot.getZ(), 1.f));
	_txtElem->setAlignment(alignment);


	_container->addChild(_txtElem);
	_container->show();
	_txtElem->show();

	setSortingLayer(sortingLayer);
	setRotation(rotation);

	_overlay->add2D(_container);

	_overlay->show();
	return true;
}

void LocoMotor::UIText::update(float dT) {
	updatePosition();
}

void LocoMotor::UIText::setAnchorPoint(const Vector2& anc) {
	_rectTransform.setAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIText::setMaxAnchorPoint(const Vector2& anc) {
	_rectTransform.setMaxAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIText::setMinAnchorPoint(const Vector2& anc) {
	_rectTransform.setMinAnchorPoint(anc);
	updatePosition();
}

void LocoMotor::UIText::setDimensions(const Vector2& anc) {
	_rectTransform.setDimensions(anc);
	updatePosition();
}

void LocoMotor::UIText::setUpLeftOffset(const Vector2& anc) {
	_rectTransform.setUpLeftOffset(anc);
	updatePosition();
}

void LocoMotor::UIText::setDownRightOffset(const Vector2& anc) {
	_rectTransform.setDownRightOffset(anc);
	updatePosition();
}

void LocoMotor::UIText::setSortingLayer(int layer) {
	if (layer < 0) layer = 0;
	else if (layer > 650) layer = 650;
	_overlay->setZOrder(Ogre::ushort(layer));
}

void LocoMotor::UIText::setRotation(float radians) {
	_overlay->setRotate(Ogre::Radian(radians));
}

void LocoMotor::UIText::setAlignment(TextAlignment a) {
	
	switch (a) {
		case TextAlignment::LEFT:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Left);
			break;
		case TextAlignment::CENTER:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
			break;
		case TextAlignment::RIGHT:
			_txtElem->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Right);
			break;
		default:
			break;
	}

}

void LocoMotor::UIText::show() {
	_container->show();
}

void LocoMotor::UIText::hide() {
	_container->hide();
}

void LocoMotor::UIText::setColor(Vector3 color) {
	setColorTop(color);
	setColorBottom(color);
}

void LocoMotor::UIText::setColorTop(Vector3 color) {
	_txtElem->setColourTop(Ogre::ColourValue(color.getX(), color.getY(), color.getZ(), 1.f));
}

void LocoMotor::UIText::setColorBottom(Vector3 color) {
	_txtElem->setColourBottom(Ogre::ColourValue(color.getX(), color.getY(), color.getZ(), 1.f));
}

void LocoMotor::UIText::updatePosition() {
	_container->setMetricsMode(Ogre::GMM_PIXELS);

	_rectTransform.refreshBounds();
	Rect totalRect = _rectTransform.getTotalBounds();

	_container->setDimensions(totalRect._downRightPoint.getX() - totalRect._upLeftPoint.getX(), totalRect._downRightPoint.getY() - totalRect._upLeftPoint.getY());

	_container->setPosition(totalRect._upLeftPoint.getX(), totalRect._upLeftPoint.getY());
}


