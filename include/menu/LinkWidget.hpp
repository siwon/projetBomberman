#ifndef _LINKWIDGET
#define _LINKWIDGET

/*!
 * \file LinkWidget.hpp
 * \brief Classe du widget Lien
 * \author Maxime GUIHAL
 */

#include <SFML/Graphics/Text.hpp>

#include "PolyBomberException.hpp"
#include "menu/TextWidget.hpp"
#include "menu/EMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class TextWidget
	 * \brief Classe du widget Lien
	 */
	class LinkWidget : public TextWidget
	{
		public:
			/*!
			 * \brief Constructeur
			 * \param text : Texte à afficher
			 * \param y : Ordonnée du lien
			 * \param target : Cible du lien
			 */
			LinkWidget(std::string text, unsigned int y, EMenuScreen target) throw(PolyBomberException);

			/*!
			 * \brief Destructeur
			 */
			~LinkWidget();

			/*!
			 * \brief Constructeur de copie
			 */
			LinkWidget(const LinkWidget& obj) throw(PolyBomberException);

			/*!
			* \brief Opérateur d'affectation
			*/
			LinkWidget& operator=(const LinkWidget& obj) throw(PolyBomberException);

			/*!
			 * \brief Sélectionne ou désélectionne le lien
			 * \param selected : True si le lien est sélectionné
			 */
			void setSelected(bool selected);

			/*!
			 * \brief Récupère l'état de sélection du lien
			 * \return True si le lien est sélectionné
			 */
			inline bool getSelected() {return this->selected;}
			
			/*!
			 * \brief Définit le lien précédent
			 * \param previous : Lien précédent
			 */
			inline void setPrevious(LinkWidget* previous) {this->previous = previous;}

			/*!
			 * \brief Définit le lien suivant
			 * \param next : Lien suivant
			 */			
			inline void setNext(LinkWidget* next) {this->next = next;}

			/*!
			 * \brief Sélectionne le lien précédent
			 *
			 * Cette méthode n'agit que si le lien est sélectionné
			 */
			void goPrevious();

			/*!
			 * \brief Sélectionne le lien suivant
			 *
			 * Cette méthode n'agit que si le lien est sélectionné
			 */
			void goNext();

			/*!
			 * \brief Méthode qui active le lien
			 * \return La cible du lien
			 */
			inline EMenuScreen activate() {return this->target;}

		private:
			bool selected; /*!< Sélection du lien */

			LinkWidget* previous; /*!< Lien précédent */
			LinkWidget* next; /*!< Lien suivant */

			EMenuScreen target; /*!< Cible du lien */
	};
}

#endif




