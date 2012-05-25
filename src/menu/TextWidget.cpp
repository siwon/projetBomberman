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
			WIDTH(800),
			fontStyle(font),
			visible(true)
	{
		init();

		sf::FloatRect rect = this->getLocalBounds();
		
		if (position == RIGHT)
			this->setPosition(this->WIDTH - rect.width, y);
		else if (position == CENTER)
			this->setPosition(this->WIDTH/2 - rect.width/2, y);
	}

	TextWidget::~TextWidget()
	{}

	TextWidget::TextWidget(const TextWidget& obj) throw(PolyBomberException) :
		sf::Text(obj),
		PATH("resources/fonts/"),
		WIDTH(800),
		fontStyle(obj.fontStyle)
	{
		init();
		setPosition(obj.getPosition());
	}

	TextWidget& TextWidget::operator=(const TextWidget& obj) throw(PolyBomberException)
	{
		this->setString(obj.getString());
		this->fontStyle = obj.fontStyle;
		init();
		setPosition(obj.getPosition());
		return *this;
	}

	void TextWidget::setY(unsigned int y)
	{
		this->setPosition(this->getPosition().x, y);
	}

	void TextWidget::init() throw(PolyBomberException)
	{
		// Initialisation des tables
		this->fontFiles[TITLEFONT] = "strong.ttf";
		this->fontFiles[TEXTFONT] = "normal.ttf";
		this->fontFiles[LINKFONT] = "normal.ttf";
		this->fontFiles[ERRORFONT] = "normal.ttf";

		this->sizes[TITLEFONT] = 40;
		this->sizes[TEXTFONT] = 20;
		this->sizes[LINKFONT] = 25;
		this->sizes[ERRORFONT] = 20;

		// Chargement de la police et mise en forme
		if (!this->font.loadFromFile(this->PATH + this->fontFiles[this->fontStyle]))
			throw PolyBomberException("Impossible de charger la police " + this->PATH + this->fontFiles[this->fontStyle]);
		
		this->setFont(this->font);
		this->setCharacterSize(this->sizes[this->fontStyle]);
	}

	void TextWidget::setVisible(bool visible)
	{
		this->visible = visible;
		sf::Color color = this->getColor();

		if (visible)
			color.a = 255;
		else
			color.a = 0;

		this->setColor(color);
	}
}

