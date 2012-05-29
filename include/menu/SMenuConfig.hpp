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
	*/
	struct SMenuConfig
	{
		bool isServer;
		unsigned int nbLocalPlayers;
		SGameConfig gameConfig;
	};
}

#endif

