/*!
 * \file ImageWidget.cpp
 * \brief Widget Image
 * \author Maxime GUIHAL
 */

#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	ImageWidget::ImageWidget(sf::Texture* texture)
	{
		this->setTexture(*texture);
	}

	ImageWidget::~ImageWidget()
	{}

	ImageWidget::ImageWidget(const ImageWidget& obj)
	{
	}

	ImageWidget& ImageWidget::operator=(const ImageWidget& obj)
	{
		return *this;
	}
}
