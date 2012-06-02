#ifndef _INETWORKTOMENU
#define _INETWORKTOMENU

/*!
 * \file INetworkToMenu.hpp
 * \brief Interface r�seau - menu
 * \author Brice GUILLERMIC
 */

#include "SGameConfig.hpp"

namespace PolyBomber
{
	/*!
	 * \class INetworkToMenu
	 * \brief Interface Interface r�seau - menu
	 */
	class INetworkToMenu
	{
		public:
			/*!
			 * \brief Enregistrer la connexion d'un ordinateur distant
			 * \return rien
			 */
			virtual void joinGame(std::string ip) =0;
			/*!
			 * \brief Nombre de place restant pour accueillir des joueurs
			 * \return Entier correspondant au nombre de joueurs
			 */
			virtual int getFreeSlots() = 0;
			/*!
			 * \brief R�servation des slots pour un nombre de joueur donn�
			 */
			virtual void setBookedSlots(unsigned int nb) = 0;
			/*!
			 * \brief Enregistrement du nom des joueurs
			 */
			virtual void setPlayerName(std::string []) = 0;
			/*!
			 * \brief 
			 * \return VRAI si startGame() � d�j� �t� d�clanch�
			 *	FAUX sinon
			 */
			virtual bool isStarted() = 0;
			/*!
			 * \brief Signal du d�but de partie
			 */
			virtual void startGame() =0;
			/*!
			 * \brief Obtenir l'adresse IP du poste
			 * \return Chaine de caract�re correspondant � l'ip
			 */
			virtual std::string getIpAddress() =0;
			/*!
			 * \brief Enregistrer les configuration de jeu
			 */
			virtual void setGameConfig(SGameConfig& gameConfig) =0;
			/*!
			 * \brief annulation de la config de jeu en cours
			 */
			virtual void cancel() =0;
			/*!
			 * \brief remplit le tableau de noms des joueurs
			 */
			virtual void getPlayersName(std::string names[4]) =0;
			/*!
			 * \brief Obtenir le joueur qui a mis le jeu en pause
			 * \return Num�ro du joueur
			 */
			virtual int isPaused() =0;
			/*!
			 * \brief Reprendre la partie apr�s une pause
			 */
			virtual void resume() = 0;
			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~INetworkToMenu() {};
	};
}

#endif
