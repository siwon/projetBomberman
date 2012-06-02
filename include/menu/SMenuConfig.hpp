#ifndef _SMENUCONFIG
#define _SMENUCONFIG

/*!
 * \file SMenuConfig.hpp
 * \brief Structure de configuration d'une partie dans le menu
 * \author Maxime GUIHAL
 */

#include "SGameConfig.hpp"

namespace PolyBomber
{
	/*!
	* \struct SMenuConfig
	* \brief Configuration d'une partie dans le menu
	*
	* Cette structure stocke toutes les informations nécessaires qui
	* doivent être partagées entre les différents menus
	*/
	struct SMenuConfig
	{
		bool isServer; /*!< Indique si l'ordinateur est serveur ou client */
		unsigned int nbLocalPlayers; /*!< Nombre de joueurs sur l'ordinateur courant */
		SGameConfig gameConfig; /*!< \see SGameConfig */
		unsigned int scores[4]; /*!< Score des joueurs */
		int winner; /*!< Gagnant de la dernière partie */
	};
}

#endif

