#ifndef _CLICKABLEWIDGET
#define _CLICKABLEWIDGET

/*!
 * \file ClickableWidget.hpp
 * \brief Classe du widget interactif
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{
	/*!
	 * \class ClickableWidget
	 * \brief Classe du widget interactif
	 */
	class ClickableWidget
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			ClickableWidget();

			/*!
			 * \brief Destructeur
			 */
			~ClickableWidget();

			/*!
			 * \brief Constructeur de copie
			 */
			ClickableWidget(const ClickableWidget& obj);

			/*!
			* \brief Opérateur d'affectation
			*/
			ClickableWidget& operator=(const ClickableWidget& obj);

			/*!
			 * \brief Sélectionne ou désélectionne le widget
			 * \param selected : True si le widget est sélectionné
			 */
			virtual void setSelected(bool selected) {this->selected = selected;}

			/*!
			 * \brief Récupère l'état de sélection du widget
			 * \return True si le widget est sélectionné
			 */
			inline bool getSelected() {return this->selected;}
			
			/*!
			 * \brief Définit le widget précédent
			 * \param previous : Widget précédent
			 */
			inline void setPrevious(ClickableWidget* previous) {this->previous = previous;}

			/*!
			 * \brief Définit le widget suivant
			 * \param next : Widget suivant
			 */			
			inline void setNext(ClickableWidget* next) {this->next = next;}

			/*!
			 * \brief Sélectionne le widget précédent
			 *
			 * Cette méthode n'agit que si le widget est sélectionné
			 */
			void goPrevious();

			/*!
			 * \brief Sélectionne le widget suivant
			 *
			 * Cette méthode n'agit que si le widget est sélectionné
			 */
			void goNext();

		private:
			bool selected; /*!< Sélection du widget */

			ClickableWidget* previous; /*!< Widget précédent */
			ClickableWidget* next; /*!< Widget suivant */
	};
}

#endif




