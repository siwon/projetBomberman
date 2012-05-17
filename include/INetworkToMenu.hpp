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
			 * \return rien
			 */
			virtual void setBookedSlots(unsigned int nb) = 0;
			/*!
			 * \brief Enregistrement du nom des joueurs
			 * \return rien
			 */
			virtual void setPlayerName(std::string []) = 0;
			/*!
			 * \brief Obtention du score de chaque joueur
			 * \return Tableau de 4 entiers
			 */
			virtual int* getScores() =0;
			/*!
			 * \brief 
			 * \return VRAI si startGame() � d�j� �t� d�clanch�
			 *	FAUX sinon
			 */
			virtual bool isStarted() = 0;
			/*!
			 * \brief Signal du d�but de partie
			 * \return rien
			 */
			virtual void startGame() =0;
			/*!
			 * \brief Obtenir l'adresse IP du poste
			 * \return Chaine de caract�re correspondant � l'ip
			 */
			virtual std::string getIpAddress() =0;
			/*!
			 * \brief Enregistrer les configuration de jeu
			 * \return rien
			 */

			virtual void setGameConfig(SGameConfig& gameConfig) =0;
			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~INetworkToMenu() {};
	};
}

#endif
