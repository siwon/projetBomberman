#ifndef _SKEYSCONFIG
#define _SKEYSCONFIG

/*!
 * \file SKeysConfig.hpp
 * \brief Structure de configuration des touches d'un joueur
 * \author Maxime GUIHAL
 */

#include "EControllerType.hpp"

namespace PolyBomber
{ 
	/*!
	 * \struct SKeysConfig
	 * \brief Configuration des touches d'un joueur
	 *
	 * Le libellé de chaque touches est stockée dans la variable key.
	 * Si l'assignation choisie est déjà utilisée, la variable errors
	 * est renseignée du message d'erreur. L'index d'accès aux variables
	 * keys et errors se fait par l'énumération EGameKeys.
	 */
	struct SKeysConfig
	{
		EControllerType controllerType; /*!< Type du contrôleur */
		std::string keys[7]; /*!< Libellés des touches */
		std::string errors[7]; /*!< Libellé d'erreur */
	};
}

#endif


