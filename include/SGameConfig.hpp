#ifndef _SGAMECONFIG
#define _SGAMECONFIG

/*!
 * \file SGameConfig.hpp
 * \brief Structure de configuration d une partie
 * \author Maxime GUIHAL
 */

#include <string>

namespace PolyBomber
{
	/*!
	* \struct SGameConfig
	* \brief Configuration d une partie
	*/
	struct SGameConfig
	{
		bool isLocal; /*!< Indique si la partie est locale ou en réseau */
		unsigned int nbPlayers; /*!< Indique le nombre de joueurs de la partie */
		std::string playersName[4]; /*!< Indique les noms des joueurs */
		unsigned int nbBonus[18]; /*!< Indique le nombre de bonus de la partie */
	};
}

#endif

