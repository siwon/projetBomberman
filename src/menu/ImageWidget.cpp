/*!
 * \file ImageWidget.cpp
 * \brief Widget Image
 * \author Maxime GUIHAL
 */

#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	ImageWidget::ImageWidget(sf::Texture* texture) : sf::Sprite(*texture)
	{}

	ImageWidget::~ImageWidget()
	{}

	ImageWidget::ImageWidget(const ImageWidget& obj) : sf::Sprite(*(obj.getTexture()))
	{}

	ImageWidget& ImageWidget::operator=(const ImageWidget& obj)
	{
		this->setTexture(*(obj.getTexture()));
		return *this;
	}
}
