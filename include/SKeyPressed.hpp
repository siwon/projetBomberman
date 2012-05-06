#ifndef _SKEYPRESSED
#define _SKEYPRESSED

/*!
 * \file SKeyPressed.hpp
 * \brief Structure des touches de jeu
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \struct SKeyPressed
	 * \brief Etat des touches de jeu
	 *
	 * Matrice de booléens dont la 1ère dimension correspond au numéro
	 * du joueur (de 0 à 3), et la 2ème dimesion correspond à la touche
	 * repérée par l'énumération EGameKeys. La matrice indique Vrai si
	 * la touche est actuellement enfoncée, Faux sinon.
	 */
	struct SKeyPressed
	{
		bool keys[4][7]; /*!< Matrice des touches */
	};
}

#endif

