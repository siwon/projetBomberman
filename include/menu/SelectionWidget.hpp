#ifndef _SELECTIONWIDGET
#define _SELECTIONWIDGET

/*!
 * \file SelectionWidget.hpp
 * \brief Classe du widget de sélection
 * \author Maxime GUIHAL
 */

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "menu/TextWidget.hpp"
#include "menu/ClickableWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class SelectionWidget
	 * \brief Classe du widget de sélection
	 *
	 * Ce widget permet de sélectionner une valeur parmi une liste
	 */
	class SelectionWidget : public sf::Drawable,
							public sf::Transformable,
							public ClickableWidget
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param font : Police des items
			 * \param y : Ordonnée du widget
			 * \param position : Position du widget
			 * \param widthItem : Largeur des items
			 */
			SelectionWidget(ETextFont font, unsigned int y, ETextPosition position = CENTER, unsigned int widthItem = 1);

			/*!
			 * \brief Destructeur
			 */
			~SelectionWidget();

			/*!
			 * \brief Constructeur de copie
			 * \param obj : objet à copier
			 */
			SelectionWidget(const SelectionWidget& obj);

			/*!
			* \brief Opérateur d'affectation
			* \param obj : objet à copier
			*/
			SelectionWidget& operator=(const SelectionWidget& obj);

			/*!
			 * \brief Ajoute un item à la liste
			 * \param text : Texte du nouvel item
			 */
			void push_back(std::string text);

			/*!
			 * \brief Sélectionne l'item indiqué
			 * \param index : item à sélectionner (commençant à 0)
			 */
			void setCurrentItem(unsigned int index);

			/*!
			 * \brief Récupère l'index de l'item sélectionné
			 * \return L'index de l'item sélectionné (commençant à 0)
			 */
			inline unsigned int getCurrentItem() {return this->selectedItem;}

			/*!
			 * \brief Sélectionne l'item suivant si le widget est sélectionné
			 */
			void goNextItem();

			/*!
			 * \brief Sélectionne l'item précédent si le widget est sélectionné
			 */
			void goPreviousItem();

			/*!
			 * \brief Sélectionne ou désélectionne le widget
			 * \param selected : True si le widget est sélectionné
			 */			
			void setSelected(bool selected);

			/*!
			 * Indique si le texte est visible ou non
			 * \return True si le texte est visible
			 */
			inline bool isVisible() {return this->visible;}

			/*!
			 * \brief Permet de définir la visibilité du widget
			 * \param visible : True si le widget est visible
			 */
			void setVisible(bool visible);

			/*!
			 * \brief Permet de vider les items de la liste
			 */
			void clear();

		private:
			/*!
			 * \brief Méthode de dessin
			 * \param target : Conteneur du widget
			 * \param states : Etat de rendu
			 */
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			ETextFont font; /*!< Police utilisée par les items */
			ETextPosition position; /*!< Position des items */

			std::vector<TextWidget> list; /*!< Liste des items */

			unsigned int selectedItem; /*!< Item sélectionné */

			TextWidget leftArrow; /*!< Flèche gauche */
			TextWidget rightArrow; /*!< Flèche droite */

			unsigned int widthItem; /*!< Largeur maximale d'item */

			bool visible; /*!< Indique si le texte est visible */
			
			const unsigned int WIDTH; /*!< Largeur de la fenêtre */
	};
}

#endif




