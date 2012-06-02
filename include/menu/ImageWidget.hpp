#ifndef _IMAGEWIDGET
#define _IMAGEWIDGET

/*!
 * \file ImageWidget.hpp
 * \brief Classe du widget Image
 * \author Maxime GUIHAL
 */

#include <SFML/Graphics/Sprite.hpp>

namespace PolyBomber
{
	/*!
	 * \class ImageWidget
	 * \brief Classe du widget Image
	 */
	class ImageWidget : public sf::Sprite
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			ImageWidget();

			/*!
			 * \brief Destructeur
			 */
			~ImageWidget();

			/*!
			 * \brief Constructeur de copie
			 * \param obj : Objet à copier
			 */
			ImageWidget(const ImageWidget& obj);

			/*!
			* \brief Opérateur d'affectation
			* \param obj : Objet à copier
			*/
			ImageWidget& operator=(const ImageWidget& obj);

			/*!
			 * \brief Définit la texture de l'image
			 * \param texture : Texture de l'image
			 */
			void setImage(sf::Texture* texture);

			/*!
			 * \brief Définit la visibilité de l'image
			 * \param visible : True si l'image est visible
			 */
			void setVisible(bool visible);
	};
}

#endif



