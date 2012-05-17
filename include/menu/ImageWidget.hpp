#ifndef _IMAGEWIDGET
#define _IMAGEWIDGET

/*!
 * \file ImageWidget.hpp
 * \brief Classe du widget Image
 * \author Maxime GUIHAL
 */

#include "menu/IWidgetMenu.hpp"

namespace PolyBomber
{
	/*!
	 * \class ImageWidget
	 * \brief Classe du widget Image
	 */
	class ImageWidget : public IWidgetMenu
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			ImageWidget(sf::Texture* texture);

			/*!
			 * \brief Destructeur
			 */
			~ImageWidget();

			/*!
			 * \brief Constructeur de copie
			 */
			ImageWidget(const ImageWidget& obj);

			/*!
			* \brief Opérateur d'affectation
			*/
			ImageWidget& operator=(const ImageWidget& obj);
	};
}

#endif



