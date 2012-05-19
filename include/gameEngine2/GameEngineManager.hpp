#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#include "gameEngine/Board.hpp"
#include "gameEngine/Bonus.hpp"
#include "gameEngine/Player.hpp"
#include "IGameEngineToNetwork.hpp"
#include "IGameEngineToGameInterface.hpp"
#include "INetworkToGameEngine.hpp"

namespace PolyBomber {
	/*!
	 * \class ControllerManager
	 * \brief Classe de gestion du moteur de jeu
	 */
	class GameEngineManager : public IGameEngineToNetwork, public IGameEngineToGameInterface, public INetworkToGameEngine {
		// TODO : faire en sorte que ce soit un singleton !!!
	protected:
		Board board; /*! Objet stockant le plateau de jeu */
		bool gameConfigIsSet;
    public:
		GameEngineManager();
		GameEngineManager(const GameEngineManager& b);
		//operateur d affectation
		~GameEngineManager();
		
		bool getGameConfigIsSet() const {return this->gameConfigIsSet;}
		
		void setGameConfigIsSet(bool b){this->gameConfigIsSet=b;}
		/*!
		 * \brief Applique un bonus a un joueur
		 * Cette methode permet d applique un bonus a un joueur.
		 * \param bonus : Bonus a appliquer
		 * \param player : Joueur sur lequel appliquer le bonus
		 */
		void applyBonus(Bonus bonus, Player player);
		
		/*!
		 * \brief Deplace le joueur sur le plateau de jeu
		 * 
		 * \param player : Joueur sur lequel appliquer le deplacement
		 * \param orientation : Direction du deplacement
		 */
		void movePlayer(Player player, EOrientation orientation);
		
		/*!
		 * \brief Declenche l explosion d une bombe
		 * 
		 * \param explosive : Bombe qui doit exploser
		 */
		void explode(Explosive explosive);
		
		/*!
		 * \brief Active le detonateur afin de faire exploser les bombes
		 * Cette methode est appelee lorsque le joueur active son detonateur.
		 * Elle provoque l explosion de toutes les bombes posees par le joueur pris en parametre.
		 * \param player : Joueur qui active le detonateur
		 */
		void activateDetonator(Player player);
		
		/*!
		 * \brief Pose une mine a l emplacement du joueur
		 * Cette methode est appelee lorsque le joueur demande a poser une mine.
		 * Dans le cas où le joueur peut poser une bombe, la bombe sera posee sous le joueur.
		 * \param player : Joueur qui pose la mine
		 */
		void putMine(Player player);
		
		/*!
		 * \brief Detruit une caisse
		 * Cette methode est appele lorsque la deflagration d une bombe touche une caisse.
		 * Elle provoque la destruction de la caisse ainsi que la probable liberation d un bonus.
		 * \param box : Caisse a exploser
		 */
		void breakBox(Box box);
		
		int isPaused();
		Board getTheBoard() const {return this->board;}
		SBoard getBoard();
		bool isFinished();
		void setGameConfig(SGameConfig gameConfig);
		SKeyPressed getKeysPressed();
		
		void run();
	};
}

#endif
