#ifndef _INETWORKTOGAMEENGINE
#define _INETWORKTOGAMEENGINE

/*!
 * \file INetworkToGameEngine.hpp
 * \brief Interface r�seau - moteur de jeu
 * \author Brice GUILLERMIC
 */

#include "SKeyPressed.hpp"

namespace PolyBomber
{
	/*!
	 * \class INetworkToGameEngine
	 * \brief Interface Interface r�seau - moteur de jeu
	 */
	class INetworkToGameEngine
	{
		public:
			/*!
			 * \brief Obtenir les touches d�clench�es
			 * \return Matrice de bool�ens � VRAI si la touche est d�clanch�
			 *	� FAUX si elle ne l'est pas
			 */
			virtual SKeyPressed getKeysPressed() = 0;
			/*!
			 * \brief Demande si le jeu est en pause
			 * \return VRAI si le jeu est en pause
			 *	FAUX sinon
			 */
			virtual int isPaused() = 0;
};

#endif
