/*!
 * \file LinkWidget.cpp
 * \brief Widget Lien
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"
#include "menu/LinkWidget.hpp"

#include <iostream>

namespace PolyBomber
{
	LinkWidget::LinkWidget(std::string text, unsigned int y, EMenuScreen target) throw(PolyBomberException) :
		TextWidget(text, LINKFONT, y),
		target(target)
	{
		this->previous = NULL;
		this->next = NULL;
		this->selected = false;

		ISkin* skin = PolyBomberApp::getISkin();
		this->setColor(skin->getColor(LINKCOLOR));
	}

	LinkWidget::~LinkWidget()
	{}

	LinkWidget::LinkWidget(const LinkWidget& obj) throw(PolyBomberException) :
		TextWidget(obj.getString(), LINKFONT, obj.getPosition().y),
		target(obj.target)
	{
		this->previous = NULL;
		this->next = NULL;
		this->selected = false;
	}

	LinkWidget& LinkWidget::operator=(const LinkWidget& obj) throw(PolyBomberException)
	{
		return *this;
	}

	void LinkWidget::setSelected(bool selected)
	{
		this->selected = selected;

		ISkin* skin = PolyBomberApp::getISkin();

		if (selected)
			this->setColor(skin->getColor(SELECTEDCOLOR));
		else
			this->setColor(skin->getColor(LINKCOLOR));			
	}

	void LinkWidget::goPrevious()
	{
		if (this->selected && this->previous != NULL)
		{
			setSelected(false);
			this->previous->setSelected(true);
		}
	}

	void LinkWidget::goNext()
	{
		if (this->selected && this->next != NULL)
		{
			setSelected(false);
			this->next->setSelected(true);
		}
	}
}
