#ifndef _ICONTROLLERTOMENU
#define _ICONTROLLERTOMENU

/*!
 * \file IControllerToMenu.hpp
 * \brief Interface entre le composant Contrôleur et Menu
 * \author Alexandre BISIAUX
 */

#include "EMenuKeys.hpp"
#include "EGameKeys.hpp"

namespace PolyBomber
{
	/*!
	 * \class IControllerToMenu
	 * \brief Interface Contrôleur - Menu
	 */
	class IControllerToMenu
	{
		


		public:
			/*!
			 * \brief Récupération de la touche appuyée
			 *
			 * Méthode appelée en boucle par le contrôleur menu pour
			 * récupérer les actions à effectuer sur le menu
			 * 
			 * \return L'action à effectuer sur le menu
			 */
			virtual EMenuKeys getKeyPressed() = 0;

			/*!
			 * \brief Récupération du caractère appuyé
			 *
			 * Méthode appelée en boucle par le contrôleur menu pour
			 * récupérer les caractères appuyés sur le clavier
			 * 
			 * \return Le caractère appuyé sur le clavier
			 */
			virtual char getCharPressed() = 0;

			/*!
			 * \brief Récupération de la configuration des touches d'un joueur donné
			 *
			 * Méthode appelée par le contrôleur menu pour
			 * récuperer la configuration des touches d'un joueur
			 * 
			 * \param Player : Joueur dont on veut récupérer la configuration des touches
			 *
			 * \return La structure de configuration des touches d'un joueur
			 */
			virtual SKeysConfig getConfig(int player) = 0;
			
			/*!
			 * \brief Assignation d'une touche à un joueur
			 *
			 * Méthode appelée par le contrôleur menu pour
			 * assigner une touche à un joueur
			 * 
			 * \param Player : Joueur à configurer
			 * 
			 * \param key : Action à configurer
			 *
			 * \return La nouvelle structure de configuration des touches du joueur
			 */
			virtual SKeysConfig setPlayerKey(int player, EGameKeys key) = 0;

			/*!
			 * \brief Assignation d'un type de contrôleur à un joueur
			 *
			 * Méthode appelée par le contrôleur menu pour
			 * assigner un contrôleur de jeu disponible à un joueur
			 * 
			 * \param Player : Joueur à configurer
			 * 
			 * \param type : Le type de contôleur à assigner
			 *
			 * \return La nouvelle structure de configuration des touches du joueur
			 */
			virtual SKeysConfig setPlayerController(int player, EControllerType type) = 0;

			/*!
			 * \brief Sauvegarde de la configuration actuelle des joueurs dans le fichier de configuration
			 *
			 * Méthode appelée par le contrôleur menu pour
			 * sauvegarder la configuration des joueurs
			 * 
			 */
			virtual void save() = 0;

			/*!
			 * \brief Chargement de la configuration des joueurs à partir du fichier de configuration
			 *
			 * Méthode appelée par le contrôleur menu pour
			 * recharger la configuration des joueurs
			 * 
			 */
			virtual void reloadConfig() = 0;

			/*!
			 * \brief Méthode pour récupérer la fenêtre de rendu
			 * \param window : Fenêtre de rendu
			 */
			virtual void setWindow(sf::RenderWindow* window) = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IControllerToMenu() {};
	};
}

#endif

