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
		bool isLocal;
		unsigned int nbPlayers;
		std::string playersName[4];
		unsigned int nbBonus[17];
	};
}

#endif

