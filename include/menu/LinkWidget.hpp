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
#include "menu/ClickableWidget.hpp"
#include "menu/EMenuScreen.hpp"

namespace PolyBomber
{
	/*!
	 * \class LinkWidget
	 * \brief Classe du widget Lien
	 */
	class LinkWidget : public TextWidget, public ClickableWidget
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
			 * \param obj : Objet à copier
			 */
			LinkWidget(const LinkWidget& obj) throw(PolyBomberException);

			/*!
			* \brief Opérateur d'affectation
			* \param obj : Objet à copier
			*/
			LinkWidget& operator=(const LinkWidget& obj) throw(PolyBomberException);

			/*!
			 * \brief Sélectionne ou désélectionne le lien
			 * \param selected : True si le lien est sélectionné
			 */
			void setSelected(bool selected);

			/*!
			 * \brief Méthode qui active le lien
			 * \return La cible du lien
			 */
			EMenuScreen activate();

			/*!
			 * \brief Méthode pour déterminer la cible du lien
			 * \param target : La cible du lien
			 */
			inline void setTarget(EMenuScreen target) {this->target = target;}

		private:
			EMenuScreen target; /*!< Cible du lien */
	};
}

#endif




