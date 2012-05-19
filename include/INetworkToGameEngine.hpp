#ifndef _INETWORKTOGAMEENGINE
#define _INETWORKTOGAMEENGINE

/*!
 * \file INetworkToGameEngine.hpp
 * \brief Interface reseau - moteur de jeu
 * \author Brice GUILLERMIC
 */

#include "SKeyPressed.hpp"

namespace PolyBomber
{
	/*!
	 * \class INetworkToGameEngine
	 * \brief Interface Interface reseau - moteur de jeu
	 */
	class INetworkToGameEngine
	{
	public:
		/*!
		 * \brief Obtenir les touches declenchees
		 * \return Matrice de booleens à VRAI si la touche est declanche
		 * FAUX si elle ne l est pas
		 */
		virtual SKeyPressed getKeysPressed() = 0;
		/*!
		 * \brief Demande si le jeu est en pause
		 * \return VRAI si le jeu est en pause
		 *	FAUX sinon
		 */
		virtual int isPaused() = 0;
		
		/*!
		 * \brief Destructeur virtuel
		 */
		virtual ~INetworkToGameEngine() {};
	};
}

#endif
