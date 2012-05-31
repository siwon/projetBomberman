#ifndef _GAMEACTION
#define _GAMEACTION

/*!
 * \file GameAction.hpp
 * \brief Classe de gestion des actions de jeu
 * \author Alexandre BISIAUX
 */

namespace PolyBomber
{ 
	/*!
	 * \enum GameAction
	 * \brief Classe de gestion des actions de jeu
	 */
	class GameAction
	{
		public :
			bool actions[7]; /*!< Tableau de 7 booléens définissant si l'action indexé par EGameKeys est à effectuer */
		
			/*!
			 * \brief Initialise le tableau d'actions
			 */
			inline void init()
			{
				int i;
				for(i=0;i<7;i++)
					actions[i] = false;
			}
	};
}

#endif

