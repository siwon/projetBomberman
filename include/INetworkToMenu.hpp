#ifndef _INETWORKTOMENU
#define _INETWORKTOMENU

/*!
 * \file INetworkToMenu.hpp
 * \brief Interface réseau - menu
 * \author Brice GUILLERMIC
 */
#include <string>
#include "SGameConfig.hpp"

namespace PolyBomber
{
	using namespace std;
	/*!
	 * \class INetworkToMenu
	 * \brief Interface Interface réseau - menu
	 */
	class INetworkToMenu
	{
		public:
			/*!
			 * \brief Enregistrer la connexion d'un ordinateur distant
			 * \return rien
			 */
			virtual void joinGame(string ip)=0;
			/*!
			 * \brief Nombre de place restant pour accueillir des joueurs
			 * \return Entier correspondant au nombre de joueurs
			 */
			virtual int getFreeSlots() = 0;
			/*!
			 * \brief Réservation des slots pour un nombre de joueur donné
			 * \return rien
			 */
			virtual void setBookedSlots(unsigned int nb) = 0;
			/*!
			 * \brief Enregistrement du nom des joueurs
			 * \return rien
			 */
			virtual void setPlayerName(string []) = 0;
			/*!
			 * \brief Obtention du score de chaque joueur
			 * \return Tableau de 4 entiers
			 */
			virtual int* getScores() =0;
			/*!
			 * \brief 
			 * \return VRAI si startGame() à déjà été déclanché
			 *	FAUX sinon
			 */
			virtual bool isStarted() = 0;
			/*!
			 * \brief Signal du début de partie
			 * \return rien
			 */
			virtual void startGame() =0;
			/*!
			 * \brief Obtenir l'adresse IP du poste
			 * \return Chaine de caractère correspondant à l'ip
			 */
			virtual string getIpAddress() =0;
			/*!
			 * \brief Enregistrer les configuration de jeu
			 * \return rien
			 */
			virtual void setGameConfig(SGameConfig gameConfig) =0;
	};
}

#endif
