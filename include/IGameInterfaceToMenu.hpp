#ifndef _IGAMEINTERFACETOMENU
#define _IGAMEINTERFACETOMENU

/*!
 * \file IGameInterfaceToMenu.hpp
 * \brief Interface entre le composant Interface de jeu et Menu
 * \author Maxime GUIHAL
 */

#include <SFML/Graphics/RenderWindow.hpp>

#include "EScreenSignal.hpp"

namespace PolyBomber
{
	/*!
	 * \class IGameInterfaceToMenu
	 * \brief Interface Plateau de jeu - Menu
	 */
	class IGameInterfaceToMenu
	{
		public:
			/*!
			 * \brief Affichage du plateau de jeu
			 *
			 * Méthode appelée par le menu au début d'une partie pour
			 * afficher le plateau de jeu
			 *
			 * \param window : Fenêtre du programme
			 * \param score : Score des joueurs avant le début de la partie
			 * \param winner : Référence vers le numéro du joueur qui gagnera
			 * \return Signal de retour
			 * 
			 */
			virtual EScreenSignal run(sf::RenderWindow window, unsigned int score[4], int& winner) = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IGameInterfaceToMenu() {};
	};
}

#endif


