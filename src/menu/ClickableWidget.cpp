/*!
 * \file ClickableWidget.cpp
 * \brief Widget interactif
 * \author Maxime GUIHAL
 */

#include "menu/ClickableWidget.hpp"

#include <iostream>

namespace PolyBomber
{
	ClickableWidget::ClickableWidget()
	{
		this->previous = NULL;
		this->next = NULL;
		this->selected = false;
	}

	ClickableWidget::~ClickableWidget()
	{}

	ClickableWidget::ClickableWidget(const ClickableWidget& obj)
	{
		this->previous = obj.previous;
		this->next = obj.next;
		this->selected = obj.selected;
	}

	ClickableWidget& ClickableWidget::operator=(const ClickableWidget& obj)
	{
		this->previous = obj.previous;
		this->next = obj.next;
		this->selected = obj.selected;
		return *this;
	}

	void ClickableWidget::goPrevious()
	{
		if (this->selected && this->previous != NULL)
		{
			setSelected(false);
			this->previous->setSelected(true);
		}
	}

	void ClickableWidget::goNext()
	{
		if (this->selected && this->next != NULL)
		{
			setSelected(false);
			this->next->setSelected(true);
		}
	}
}
