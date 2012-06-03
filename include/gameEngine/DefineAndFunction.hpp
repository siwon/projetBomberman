#ifndef DEFINE_AND_FUNCTION_HEADER
#define DEFINE_AND_FUNCTION_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

#define VITESSEPARDEFAUT 60						/*!< Temps entre deux mouvements par défaut du joueur */
#define VITESSEMIN 100							/*!< Temps maximum entre deux mouvements */
#define VITESSEMAX 20							/*!< Temps minimum entre deux mouvements */
#define PASVITESSE 20							/*!< Seuil de modification du temps entre deux mouvements du joueur */
#define NOMBREBOMBEDEFAUT 2						/*!< Nombre de bombes que le joueur peut poser par défaut */
#define RANGEDEFAUT 1							/*!< Portée des bombes du joueur par défaut */
#define RANGEMIN 1								/*!< Portée minimum des bombes du joueur */
#define RANGEMAX 19								/*!< Portée maximale des bombes du joueur */
#define PASRANGE 1								/*!< Seuile de modification de la portée du joueur */
#define ORIENTATIONDEFAUT ORIENTATION_DOWN		/*!< Orientation par défaut de joueur */
#define BOMBTIMESTAMP 3							/*!< Durée de la mèche des bombes */
#define NOMBREBOX 150							/*!< Nombre de caisses sur le plateau */
#define DUREEFLAMME 1							/*!< Durée de la déflagration */

#define LARGEUR 35								/*!< Largeur d'une case en pixel */
#define DISTANCEMINBETWEENTWOPLAYERS 2			/*!< Distance minimum entre 2 joueurs (en cran) */
#define TEMPSENTREDEUXACTIONSINFECTION 1		/*!< Temps entre deux actions dûes aux infections */

#endif
