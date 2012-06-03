#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#include "Board.hpp"

namespace PolyBomber {
	/*!
	 * \class ControllerManager
	 * \brief Classe de gestion du moteur de jeu
	 */
	class GameEngineManager : public IGameEngineToNetwork, public Singleton<GameEngineManager> {

	friend class Singleton<GameEngineManager>; /* Utilisation du template singleton */
	private:
		sf::Mutex mutexBoard;
		sf::Mutex mutexRunnable;
		sf::Mutex mutexDisable;
	protected:
		INetworkToGameEngine* network; /*! Réseau assigné */
		Board board; /*! Objet stockant le plateau de jeu */
		bool gameConfigIsSet; /*! Détermine si le jeu est configuré ou pas */
		bool runnable; /*! Détermine si la partie doit tourner */
		sf::Clock horloge; /*! Stockage de l'horloge du jeu */
		int debutPause; /*! Date du début de la pause */
		int lastInfectionAction; /*! Date de la dernière action due à une infection */
		
	private:
		/*!
		 * \brief Constructeur de la classe GameEngineManager
		 */
		GameEngineManager();
		
		/*!
		 * \brief Destructeur de la classe GameEngineManager
		 */
		~GameEngineManager();

		//Fonction de génération de la map
		/*!
		 * \brief Génère les murs sur la carte
		 */
		void generateWall();
		
		/*!
		 * \brief Génère les joueurs sur la carte
		 * \param nbPlayer : Nombre de joueurs
		 */
		void generatePlayer(int);
		
		/*!
		 * \brief Génère les caisses
		 * \param nbBox : Nombre de caisses à générer
		 */
		void generateBox(int);
		
		/*!
		 * \brief Génère les flammes
		 * \param origineX : Abscisse de la source de la flamme (en case)
		 * \param origineY : Ordonné de la source de la flamme (en case)
		 * \param range : Portée de la flamme
		 * \param date : Date du jeu (en secondes)
		 */
		void generateFlame(int, int, int, int);
		
		//decalageHoraire
		/*!
		 * \brief Effectue un décalage de toutes les horloges en cas de pause
		 * \param secondes : Temps de décalage (en secondes)
		 */
		void decalageHoraire(int);

		/*!
		 * \brief Teste si le thread peut s'exécuter
		 */
		bool isRunnable();
			
    public:
		//IGameEngineToNetwork
		/*!
		 * \brief Génère les objets d'initialisation de la partie
		 * \param gameConfig : Structure contenant les informations de la partie
		 * Cette méthode fera appelle aux différentes fonctions privées de génération d'objets
		 */
		void setGameConfig(SGameConfig);
		
		/*!
		 * \brief Fonction générale permettant de jouer
		 */
		void run();
		
		/*!
		 * \brief Efface le contenu du board
		 */
		void resetConfig();
		
		//IGameEngineToGameInterface
		
		/*!
		 * \brief Génère une structure SBoard afin de l'envoyer au réseau
		 * \return Structure contenant les informations du SBoard
		 */
		SBoard getBoard();
		
		/*!
		 * \brief Détermine si la partie est terminée ou pas
		 * \return Retourne 0 si la partie n'est pas terminée, retourne -1 si il n'y a plus de survivants, retourne l'identifiant du joueur plus 1 si il n'y a plus qu'un survivant
		 */
		int isFinished();
	};
}

#endif
