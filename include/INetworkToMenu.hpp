#ifndef _INETWORKTOMENU
#define _INETWORKTOMENU

/*!
 * \file INetworkToMenu.hpp
 * \brief Interface réseau - menu
 * \author Brice GUILLERMIC
 */

#include "SGameConfig.hpp"

namespace PolyBomber
{
	/*!
	 * \class INetworkToMenu
	 * \brief Interface Interface réseau - menu
	 */
	class INetworkToMenu
	{
		public:
			/*!
			 * \brief Enregistrer la connexion d'un ordinateur distant
			 * \param ip : Adresse IP du serveur
			 */
			virtual void joinGame(std::string ip) =0;
			
			/*!
			 * \brief Nombre de place restant pour accueillir des joueurs
			 * \return Entier correspondant au nombre de joueurs
			 */
			virtual int getFreeSlots() = 0;
			
			/*!
			 * \brief Réservation des slots pour un nombre de joueur donné
			 * \param nb : Nombre de places réservées (0-4)
			 */
			virtual void setBookedSlots(unsigned int nb) = 0;
			
			/*!
			 * \brief Enregistrement du nom des joueurs
			 * \param Noms des joueurs
			 */
			virtual void setPlayerName(std::string []) = 0;
			
			/*!
			 * \brief Teste si la partie est lancée
			 * \return VRAI si startGame() à déjà été déclanché
			 *	FAUX sinon
			 */
			virtual bool isStarted() = 0;
			
			/*!
			 * \brief Signal du début de partie
			 */
			virtual void startGame() =0;
			
			/*!
			 * \brief Obtenir l'adresse IP du poste
			 * \return Chaine de caractère correspondant à l'ip
			 */
			virtual std::string getIpAddress() =0;
			
			/*!
			 * \brief Enregistrer les configuration de jeu
			 * \param gameConfig : Structure de configuration du jeu
			 */
			virtual void setGameConfig(SGameConfig& gameConfig) =0;
			
			/*!
			 * \brief annulation de la config de jeu en cours
			 */
			virtual void cancel() =0;
			
			/*!
			 * \brief remplit le tableau de noms des joueurs
			 * \param names : Noms des joueurs
			 */
			virtual void getPlayersName(std::string names[4]) =0;
			
			/*!
			 * \brief Obtenir le joueur qui a mis le jeu en pause
			 * \return Numéro du joueur
			 */
			virtual int isPaused() =0;
			
			/*!
			 * \brief Reprendre la partie après une pause
			 */
			virtual void resume() = 0;
			
			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~INetworkToMenu() {};
	};
}

#endif
