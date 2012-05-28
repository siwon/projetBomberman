#ifndef _GAMEINTERFACEMANAGER
#define _GAMEINTERFACEMANAGER

/*!
 * \file GameInterfaceManager.hpp
 * \brief Classe de gestion de l'interface du plateau de jeu
 * \author Maxime GUIHAL
 */

#include <vector>

#include "IGameInterfaceToMenu.hpp"
#include "TSingleton.hpp"

namespace PolyBomber
{
	/*!
	 * \class NetworkManager
	 * \brief Classe de gestion de l'interface du plateau de jeu
	 */
	class GameInterfaceManager : public IGameInterfaceToMenu,
						         public Singleton<GameInterfaceManager>
	{
		friend class Singleton<GameInterfaceManager>;

		public:
			/*!
			 * \see IGameInterfaceToMenu::run
			 */
			EScreenSignal run(sf::RenderWindow* window, unsigned int score[4], int& winner);

		private:
			/*!
			 * \brief Constructeur
			 */
			GameInterfaceManager();

			/*!
			 * \brief Destructeur
			 */
			~GameInterfaceManager();

			/*!
			 * \brief Méthode pour mettre à jour les informations du plateau de jeu
			 */
			void update();
			

			sf::Sprite background; /*!< Image de fond de la fenêtre et du plateau */

			std::vector<sf::Sprite> boxes; /*!< Sprites pour les caisses */
	};
}

#endif

