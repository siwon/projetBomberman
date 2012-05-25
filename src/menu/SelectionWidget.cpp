/*!
 * \file SelectionWidget.cpp
 * \brief Widget de sélection
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"
#include "menu/SelectionWidget.hpp"

namespace PolyBomber
{
	SelectionWidget::SelectionWidget(ETextFont font, unsigned int y, ETextPosition position, unsigned int widthItem) :
		ClickableWidget(),
		font(font),
		position(position),
		selectedItem(0),
		leftArrow("<", font, 0, LEFT),
		rightArrow(">", font, 0, LEFT),
		widthItem(widthItem),
		WIDTH(800)
	{
		float widthArrow = this->leftArrow.getLocalBounds().width;
		this->rightArrow.setPosition(widthArrow + this->widthItem + 40, 0);

		ISkin* skin = PolyBomberApp::getISkin();
		this->leftArrow.setColor(skin->getColor(LINKCOLOR));
		this->rightArrow.setColor(skin->getColor(LINKCOLOR));
		
		setPosition(this->WIDTH/2 - (this->widthItem + 2*widthArrow + 40)/2, y);
	}

	SelectionWidget::~SelectionWidget()
	{}

	SelectionWidget::SelectionWidget(const SelectionWidget& obj) :
		ClickableWidget(obj),
		font(obj.font),
		position(obj.position),
		selectedItem(obj.selectedItem),
		leftArrow(obj.leftArrow),
		rightArrow(obj.rightArrow),
		widthItem(obj.widthItem),
		WIDTH(obj.WIDTH)
	{}

	SelectionWidget& SelectionWidget::operator=(const SelectionWidget& obj)
	{
		this->font = obj.font;
		this->position = obj.position;
		this->selectedItem = obj.selectedItem;
		this->leftArrow = obj.leftArrow;
		this->rightArrow = obj.rightArrow;
		this->widthItem = obj.widthItem;
		return *this;
	}

	void SelectionWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		if (this->list.size() > 0)
			target.draw(this->list[this->selectedItem], states);

		if (this->selectedItem > 0)
			target.draw(this->leftArrow, states);

		if (this->selectedItem < this->list.size() - 1)
			target.draw(this->rightArrow, states);
	}

	void SelectionWidget::push_back(std::string text)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		float widthArrow = this->leftArrow.getLocalBounds().width;

		this->list.push_back(TextWidget(text, this->font, 0, LEFT));
		this->list[this->list.size()-1].setColor(skin->getColor(TEXTCOLOR));

		// Positionnement de l'item
		float widthItem = this->list[this->list.size()-1].getLocalBounds().width;
		this->list[this->list.size()-1].setPosition(widthArrow + 20 + this->widthItem/2.f - widthItem/2.f, 0);
		
		// Redimensionnement du widget
		if (widthItem > this->widthItem)
		{
			this->widthItem = widthItem;
			this->rightArrow.setPosition(widthArrow + widthItem + 40, 0);

			std::vector<TextWidget>::iterator it;
			for (it = this->list.begin(); it != this->list.end(); it++)
			{
				float widthCurrent = (*it).getLocalBounds().width;
				(*it).setPosition(widthArrow + 20 + widthItem/2.f - widthCurrent/2.f, 0);
			}

			setPosition(this->WIDTH/2 - (this->widthItem + 2*widthArrow + 40)/2, getPosition().y);
		}
	}

	void SelectionWidget::setCurrentItem(unsigned int index)
	{
		if (index < this->list.size())
			this->selectedItem = index;
	}

	void SelectionWidget::goNextItem()
	{
		if (getSelected())
		{
			if (this->selectedItem + 1 < this->list.size())
				this->selectedItem++;
		}
	}

	void SelectionWidget::goPreviousItem()
	{
		if (getSelected())
		{
			if (this->selectedItem > 0)
				this->selectedItem--;
		}
	}

	void SelectionWidget::setSelected(bool selected)
	{
		ClickableWidget::setSelected(selected);

		ISkin* skin = PolyBomberApp::getISkin();

		if (selected)
		{
			this->leftArrow.setColor(skin->getColor(SELECTEDCOLOR));
			this->rightArrow.setColor(skin->getColor(SELECTEDCOLOR));
		}
		else
		{
			this->leftArrow.setColor(skin->getColor(LINKCOLOR));
			this->rightArrow.setColor(skin->getColor(LINKCOLOR));
		}

		std::vector<TextWidget>::iterator it;
		for (it = this->list.begin(); it != this->list.end(); it++)
		{
			if (selected)
				(*it).setColor(skin->getColor(SELECTEDCOLOR));
			else
				(*it).setColor(skin->getColor(TEXTCOLOR));
		}					
	}

	void SelectionWidget::setVisible(bool visible)
	{
		this->visible = visible;
		sf::Color arrowColor = this->leftArrow.getColor();
		sf::Color itemColor = this->list[0].getColor();

		if (visible)
		{
			arrowColor.a = 255;
			itemColor.a = 255;
		}
		else
		{
			arrowColor.a = 0;
			itemColor.a = 0;
		}

		this->leftArrow.setColor(arrowColor);
		this->rightArrow.setColor(arrowColor);

		std::vector<TextWidget>::iterator it;
		for (it = this->list.begin(); it != this->list.end(); it++)
			(*it).setColor(itemColor);
	}

	void SelectionWidget::clear()
	{
		this->list.clear();
		this->selectedItem = 0;
	}
}

