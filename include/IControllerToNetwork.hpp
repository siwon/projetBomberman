#ifndef _ICONTROLLERTONETWORK
#define _ICONTROLLERTONETWORK

/*!
 * \file IControllerToNetwork.hpp
 * \brief Interface entre le composant Contrôleur et Réseau
 * \author Maxime GUIHAL
 */

#include "SKeyPressed.hpp"

namespace PolyBomber
{
	/*!
	 * \class IControllerToNetwork
	 * \brief Interface Contrôleur - Réseau
	 */
	class IControllerToNetwork
	{
		public:
			/*!
			 * \brief Récupération des touches appuyées
			 *
			 * Méthode appelée en boucle par le composant Réseau pendant
			 * une partie.
			 * 
			 * \return La matrice des touches actuellement pressées pour
			 * chaque joueur.
			 */
			virtual SKeyPressed getKeysPressed() = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IControllerToNetwork() {};
	};
}

#endif

