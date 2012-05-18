#ifndef _TEXTWIDGET
#define _TEXTWIDGET

/*!
 * \file TextWidget.hpp
 * \brief Classe du widget Texte
 * \author Maxime GUIHAL
 */

#include <map>

#include <SFML/Graphics/Text.hpp>

#include "PolyBomberException.hpp"
#include "menu/ETextFont.hpp"
#include "menu/ETextPosition.hpp"

namespace PolyBomber
{
	/*!
	 * \class TextWidget
	 * \brief Classe du widget Texte
	 */
	class TextWidget : public sf::Text
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param text : Texte à afficher
			 * \param font : Style de police à utiliser
			 * \param y : Ordonnée du texte
			 * \param position : Position du texte
			 */
			TextWidget(std::string text, ETextFont font, unsigned int y, ETextPosition position = CENTER)
				throw(PolyBomberException);

			/*!
			 * \brief Destructeur
			 */
			~TextWidget();

			/*!
			 * \brief Constructeur de copie
			 */
			TextWidget(const TextWidget& obj) throw(PolyBomberException);

			/*!
			* \brief Opérateur d'affectation
			*/
			TextWidget& operator=(const TextWidget& obj) throw(PolyBomberException);

			/*!
			 * \brief Réglage de l'ordonnée
			 * \param unsigned int y
			 */
			void setY(unsigned int y);

		private:
			std::map<ETextFont, std::string> fontFiles; /*!< Liste des fichiers de police */
			std::map<ETextFont, unsigned int> sizes; /*!< Liste des tailles de police */

			const std::string PATH; /*!< Chemin d'accès aux polices */
			const unsigned int WIDTH; /*!< Largeur de la fenêtre */

			sf::Font font; /*!< Police du texte */
			ETextFont fontStyle; /*!< Style de la police */
			ETextPosition position; /*!< Position du texte */

			/*!
			 * \brief Méthode d'initialisation
			 * \param font : Style de police à utiliser
			 * \param position : Position du texte
			 */
			void init(ETextFont font, ETextPosition position) throw(PolyBomberException);
	};
}

#endif




