/*!
 * \file ImageWidget.cpp
 * \brief Widget Image
 * \author Maxime GUIHAL
 */

#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	ImageWidget::ImageWidget() : sf::Sprite()
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

	void ImageWidget::setImage(sf::Texture* texture)
	{
		this->setTexture(*texture);
	}
}
