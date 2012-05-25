/*!
 * \file InputWidget.cpp
 * \brief Widget de saisie
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"
#include "menu/InputWidget.hpp"

namespace PolyBomber
{
	InputWidget::InputWidget(ETextFont font, unsigned int y, ETextPosition position, unsigned int width) :
		ClickableWidget(),
		text("", font, 0, LEFT),
		WIDTH(800)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		
		area.setSize(sf::Vector2f(width, 35));
		area.setFillColor(skin->getColor(BGCOLOR));
		area.setOutlineColor(skin->getColor(TEXTCOLOR));
		area.setOutlineThickness(3);

		text.setString("Juconil");
		text.setPosition(5, 5);
		text.setColor(skin->getColor(TEXTCOLOR));

		if (position == RIGHT)
			setPosition(this->WIDTH - width, y);
		else if (position == CENTER)
			setPosition(this->WIDTH/2 - (width)/2, y);
	}

	InputWidget::~InputWidget()
	{}

	InputWidget::InputWidget(const InputWidget& obj) :
		ClickableWidget(),
		text(obj.text),
		area(obj.area),
		WIDTH(800)	
	{}

	InputWidget& InputWidget::operator=(const InputWidget& obj)
	{
		this->visible = obj.visible;
		this->area = obj.area;
		this->text = obj.text;
		return *this;
	}
			
	void InputWidget::setSelected(bool selected)
	{
		ISkin* skin = PolyBomberApp::getISkin();
		ClickableWidget::setSelected(selected);

		if (selected)
		{
			area.setFillColor(skin->getColor(SELECTEDBGCOLOR));
			area.setOutlineColor(skin->getColor(SELECTEDCOLOR));
			text.setColor(skin->getColor(SELECTEDCOLOR));
		}
		else
		{
			area.setFillColor(skin->getColor(BGCOLOR));
			area.setOutlineColor(skin->getColor(TEXTCOLOR));
			text.setColor(skin->getColor(TEXTCOLOR));
		}
	}

	void InputWidget::setVisible(bool visible)
	{
		this->visible = visible;
		sf::Color bgColor = area.getFillColor();
		sf::Color textColor = text.getColor();

		if (visible)
		{
			bgColor.a = 255;
			textColor.a = 255;
		}
		else
		{
			bgColor.a = 0;
			textColor.a = 0;
		}

		area.setFillColor(bgColor);
		area.setOutlineColor(textColor);
		text.setColor(textColor);				
	}

	void InputWidget::clear()
	{

	}

	void InputWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(this->area, states);
		target.draw(this->text, states);
	}	
}
