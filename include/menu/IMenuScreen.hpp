#ifndef _IMENUSCREEN
#define _IMENUSCREEN

/*!
 * \file IMenuScreen.hpp
 * \brief Interface des ecrans du menu
 * \author Maxime GUIHAL
 */

#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu/EMenuScreen.hpp"
#include "menu/MainWindow.hpp"

#include "EImage.hpp"
#include "EColorKey.hpp"

#include "menu/ImageWidget.hpp"

namespace PolyBomber
{
	/*!
	 * \class IMenuScreen
	 * \brief Interface des ecrans du menu
	 *
	 * Cette classe abstraite est la classe de base pour les menus,
	 * définissant les méthodes pour un appui sur une touche ainsi
	 * que la boucle d'exécution
	 */
	class IMenuScreen
	{
		public:
			/*!
			 * \brief Exécution du menu sélectionné
			 * \param window : Fenêtre du programme
			 * \param previous : Menu précédent
			 * \return Menu suivant
			 */
			virtual EMenuScreen run(MainWindow& window, EMenuScreen previous);

			/*!
			 * \brief Appui sur la touche Haut
			 */
			virtual void upPressed() {}

			/*!
			 * \brief Appui sur la touche Bas
			 */
			virtual void downPressed() {}

			/*!
			 * \brief Appui sur la touche Gauche
			 */
			virtual void leftPressed() {}

			/*!
			 * \brief Appui sur la touche Droite
			 */
			virtual void rightPressed() {}

			/*!
			 * \brief Exécution pendant la boucle d'affichage
			 * \param Menu suivant à afficher
			 */
			virtual void loopAction(EMenuScreen*) {}

			/*!
			 * \brief Appui sur la touche Valider
			 * \param Menu suivant à afficher
			 * \param Ecran suivant
			 */
			virtual void validPressed(EMenuScreen*) {}

			/*!
			 * \brief Appui sur la touche Retour
			 * \param Menu suivant à afficher
			 * \param Ecran suivant
			 */
			virtual void backPressed(EMenuScreen*) {}

			/*!
			 * \brief Constructeur général
			 */
			IMenuScreen();

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IMenuScreen() {}

		protected:
			std::vector<sf::Drawable*> widgets; /*!< Liste des widgets des écrans */

		private:
			ImageWidget background; /*!< Image de fond du menu */
	};
}

#endif




