#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "../IGameEngineToNetwork.hpp"
#include "../IGameEngineToGameInterface.hpp"
#include "../INetworkToGameEngine.hpp"
#include "../TSingleton.hpp"

#include "Board.hpp"

#include "DefineAndFunction.hpp"


namespace PolyBomber {
	/*!
	 * \class ControllerManager
	 * \brief Classe de gestion du moteur de jeu
	 */
	class GameEngineManager : public IGameEngineToNetwork, public Singleton<GameEngineManager> {

	friend class Singleton<GameEngineManager>; 

	protected:
		INetworkToGameEngine* network;
		Board board; /*! Objet stockant le plateau de jeu */
		bool gameConfigIsSet;
		bool runnable;
		sf::Clock horloge;
		int debutPause;
		int lastInfectionAction;
		
	private:
		GameEngineManager();
		~GameEngineManager();

		//generation de la map
		void generateWall();
		void generatePlayer(int);
		void generateBox(int);
		void generateFlame(int, int, int, int);
		
		//decalageHoraire
		void decalageHoraire(int);
			
    public:
		//IGameEngineToNetwork
		void setGameConfig(SGameConfig);
		void run();
		void resetConfig();
		
		//IGameEngineToGameInterface
		SBoard getBoard();
		int isFinished();
		/*
		 * -1 : pas de gagnant et partie terminée
		 * 0 : partie non terminée
		 * 1-4 : renvoie l'id du joueur +1
		 */
		
		//INetworkToGameEngine
		/*SKeyPressed getKeysPressed();
		int isPaused();*/
		
	};
}

#endif
