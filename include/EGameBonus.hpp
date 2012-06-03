#ifndef _EGAMEBONUS
#define _EGAMEBONUS

/*!
 * \file EGameBonus.hpp
 * \brief Enumeration des bonus du jeu
 * \author Simon ROUSSEAU
 */

namespace PolyBomber
{ 
	/*!
	 * \enum EGameBonus
	 * \brief Liste des bonus du jeu
	 */
	enum EGameBonus
	{
		SPEEDUP=0,		/*!< Accélération du joueur */
		SPEEDDOWN,		/*!< Décélération du joueur */
		BOMBLINE,		/*!< le joueur pose des lignes de bombes */
		DETONATOR,		/*!< Le joueur possède un détonateur */
		BOMBUP,			/*!< Augmentation du nombre de bombe pour le joueur */
		BOMBDOWN,		/*!< Diminution du nombre de bombe pour le joueur */
		RANGEUP,		/*!< Augmentation de la portée du joueur */
		RANGEDOWN,		/*!< Diminution de la portée du joueur */
		RANGEUPMAX,		/*!< Augmentation de la portée du joueur au maximum */
		/*bonus de bombe*/
		MINE,			/*!< Mine pour le joueur */
		INFINITYBOMB,	/*!< Bombe inifinie */
		ATOMICBOMB,		/*!< Bombe atomique */
		/*infection*/
		CRANE,			/*!< Subit un infection au hasard */
		HELL,			/*!< Affecte une infection aléatoire à tous les joueurs */
		CONFUSION,		/*!< Touches du joueur inversée */
		SPASME,			/*!< Déplacement aléatoire du joueur toutes les X secondes */
		DILATATION,		/*!< Diminution au maximum de la vitesse du joueur */
		RAGE			/*!< Le joueur pose des bombes toutes les X secondes */
	};
}

#endif


