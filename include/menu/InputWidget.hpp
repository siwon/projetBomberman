#ifndef _INPUTWIDGET
#define _INPUTWIDGET

/*!
 * \file InputWidget.hpp
 * \brief Classe du widget de saisie
 * \author Maxime GUIHAL
 */

#include <string>

#include <SFML/Graphics.hpp>

#include "menu/TextWidget.hpp"
#include "menu/ClickableWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class InputWidget
	 * \brief Classe du widget de saisie
	 *
	 * Ce widget permet à l'utilisateur d'écrire du texte,
	 * supportant les caractères alphanumériques
	 */
	class InputWidget : public sf::Drawable,
						public sf::Transformable,
						public ClickableWidget
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param font : Police du texte
			 * \param y : Ordonnée du widget
			 * \param position : Position du widget
			 * \param width : Largeur du widget
			 */
			InputWidget(ETextFont font, unsigned int y, ETextPosition position = CENTER, unsigned int width = 300);

			/*!
			 * \brief Destructeur
			 */
			~InputWidget();

			/*!
			 * \brief Constructeur de copie
			 * \param obj : Objet à copier
			 */
			InputWidget(const InputWidget& obj);

			/*!
			* \brief Opérateur d'affectation
			* \param obj : Objet à copier
			*/
			InputWidget& operator=(const InputWidget& obj);

			/*!
			 * \brief Sélectionne ou désélectionne le widget
			 * \param selected : True si le widget est sélectionné
			 */			
			void setSelected(bool selected);

			/*!
			 * Indique si le texte est visible ou non
			 * \return True si le widget est visible
			 */
			inline bool isVisible() {return this->visible;}

			/*!
			 * \brief Permet de définir la visibilité du widget
			 * \param visible : True si le widget est visible
			 */
			void setVisible(bool visible);

			/*!
			 * \brief Permet de vider la zone de texte
			 */
			void clear();

			/*!
			 * \brief Méthode de saisie d'un caractère
			 */
			void writeChar();

			/*!
			 * \brief Méthode permettant de récupérer le texte
			 * \return Le texte saisi
			 */
			inline std::string getString() {return this->text.getString();}

			/*!
			 * \brief Méthode permettant de déterminer le texte
			 * \param text Le texte
			 */
			inline void setString(std::string text) {this->text.setString(text);}

			/*!
			 * \brief Méthode pour savoir la longueur maximale du texte
			 * saisi
			 * \return La longueur maximale
			 */
			inline unsigned int getMaxLength() {return this->maxLength;}

			/*!
			 * \brief Méthode pour déterminer la longueur maximale du texte
			 * saisi
			 * \param length : Longueur maximale
			 */
			inline void setMaxLength(unsigned int length) {this->maxLength = length;}

		private:
			/*!
			 * \brief Méthode de dessin
			 * \param target : Conteneur du widget
			 * \param states : Etat de rendu
			 */
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			TextWidget text; /*!< Texte affiché */
			sf::RectangleShape area; /*!< Fond de la zone de saisie */

			bool visible; /*!< Indique si le widget est visible */

			unsigned int maxLength; /*!< Longueur maximale du texte saisi */
			
			const unsigned int WIDTH; /*!< Largeur de la fenêtre */
	};
}

#endif




