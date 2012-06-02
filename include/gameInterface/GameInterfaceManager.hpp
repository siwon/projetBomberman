#ifndef _GAMEINTERFACEMANAGER
#define _GAMEINTERFACEMANAGER

/*!
 * \file GameInterfaceManager.hpp
 * \brief Classe de gestion de l'interface du plateau de jeu
 * \author Maxime GUIHAL
 */

#include <vector>

#include <SFML/Graphics.hpp>

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
		friend class Singleton<GameInterfaceManager>; // Utilisation du singlaton

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
			~GameInterfaceManager() {}

			/*!
			 * \brief Méthode pour mettre à jour les informations du plateau de jeu
			 */
			void update();
			

			sf::Sprite background; /*!< Image de fond de la fenêtre et du plateau */

			std::vector<sf::Sprite> boxes; /*!< Sprites pour les caisses */
			std::vector<sf::Sprite> players; /*!< Sprites pour les personnages */
			std::vector<sf::Sprite> bonus; /*!< Sprites pour les bonus */
			std::vector<sf::Sprite> explosives; /*!< Sprites pour les bombes */
			std::vector<sf::Sprite> flames; /*!< Sprites pour les flammes */

			sf::Font font; /*!< Police utilisée pour le texte de fin */
			sf::Text finishText; /*! Texte de fin de partie */
	};
}

#endif

