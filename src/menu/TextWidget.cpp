/*!
 * \file TextWidget.cpp
 * \brief Widget Texte
 * \author Maxime GUIHAL
 */

#include "menu/TextWidget.hpp"

namespace PolyBomber
{
	TextWidget::TextWidget(std::string text, ETextFont font, unsigned int y, ETextPosition position)
		throw(PolyBomberException) :
			sf::Text(text),
			PATH("resources/fonts/"),
			WIDTH(800)
	{
		init(font, position);
		setY(y);
	}

	TextWidget::~TextWidget()
	{}

	TextWidget::TextWidget(const TextWidget& obj) throw(PolyBomberException) :
		sf::Text(obj),
		PATH("resources/fonts/"),
		WIDTH(800)		
	{
		init(obj.fontStyle, obj.position);
	}

	TextWidget& TextWidget::operator=(const TextWidget& obj) throw(PolyBomberException)
	{
		this->setString(obj.getString());
		init(obj.fontStyle, obj.position);
		return *this;
	}

	void TextWidget::setY(unsigned int y)
	{
		this->setPosition(this->getPosition().x, y);
	}

	void TextWidget::init(ETextFont font, ETextPosition position) throw(PolyBomberException)
	{
		// Initialisation des tables
		this->fontFiles[TITLEFONT] = "strong.ttf";
		this->fontFiles[TEXTFONT] = "normal.ttf";
		this->fontFiles[LINKFONT] = "normal.ttf";

		this->sizes[TITLEFONT] = 40;
		this->sizes[TEXTFONT] = 20;
		this->sizes[LINKFONT] = 25;

		this->position = position;
		this->fontStyle = font;

		// Chargement de la police et mise en forme
		if (!this->font.loadFromFile(this->PATH + this->fontFiles[font]))
			throw PolyBomberException("Impossible de charger la police " + this->PATH + this->fontFiles[font]);
		
		this->setFont(this->font);
		this->setCharacterSize(this->sizes[font]);

		sf::FloatRect rect = this->getLocalBounds();

		if (position == RIGHT)
			this->setPosition(this->WIDTH - rect.width, 0);
		else if (position == CENTER)
			this->setPosition(this->WIDTH/2 - rect.width/2, 0);
	}
}

