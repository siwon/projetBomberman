/*!
 * \file LinkWidget.cpp
 * \brief Widget Lien
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"
#include "menu/LinkWidget.hpp"

namespace PolyBomber
{
	LinkWidget::LinkWidget(std::string text, unsigned int y, EMenuScreen target) throw(PolyBomberException) :
		TextWidget(text, LINKFONT, y),
		ClickableWidget(),
		target(target)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		this->setColor(skin->getColor(LINKCOLOR));
	}

	LinkWidget::~LinkWidget()
	{}

	LinkWidget::LinkWidget(const LinkWidget& obj) throw(PolyBomberException) :
		TextWidget(obj.getString(), LINKFONT, obj.getPosition().y),
		ClickableWidget(obj),
		target(obj.target)
	{}

	LinkWidget& LinkWidget::operator=(const LinkWidget& obj) throw(PolyBomberException)
	{
		this->target = obj.target;
		return *this;
	}

	void LinkWidget::setSelected(bool selected)
	{
		ClickableWidget::setSelected(selected);

		ISkin* skin = PolyBomberApp::getISkin();
		
		if (selected)
			this->setColor(skin->getColor(SELECTEDCOLOR));
		else
			this->setColor(skin->getColor(LINKCOLOR));			
	}
	
	EMenuScreen LinkWidget::activate()
	{
		ISound* sound = PolyBomberApp::getISound();
		sound->playSound(CLICKSOUND);
		
		return this->target;
	}
}
