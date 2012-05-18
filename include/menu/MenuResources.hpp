#ifndef _MENURESOURCES
#define _MENURESOURCES

/*!
 * \file MenuResources.hpp
 * \brief Classe de gestion des ressources du menu
 * \author Maxime GUIHAL
 */

#include "IGameInterfaceToMenu.hpp"
#include "INetworkToMenu.hpp"
#include "ISkin.hpp"
#include "ISound.hpp"

#include "menu/MainWindow.hpp"

namespace PolyBomber
{
	/*!
	 * \class MenuResources
	 * \brief Classe de gestion des ressources du menu
	 */
	class MenuResources
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			MenuResources();

			/*!
			 * \brief Destructeur
			 */
			~MenuResources();

			/*!
			 * \brief Constructeur par recopie
			 */
			MenuResources(const MenuResources& obj);

			/*!
			 * \brief Opérateur d'affectation
			 */
			MenuResources& operator=(const MenuResources& obj);

			/*!
			 * \brief Méthode de récupération de la fenêtre
			 */
			MainWindow* getWindow();

			/*!
			 * \brief Méthode de récupération de l'interface de jeu
			 * \return Interface IGameInterfaceToMenu
			 */
			IGameInterfaceToMenu* getGameInterfaceToMenu();

			/*!
			 * \brief Méthode de récupération du composant Réseau
			 * \return Interface NetworkToMenu
			 */
			INetworkToMenu* getNetworkToMenu();

			/*!
			 * \brief Méthode de récupération du Skin
			 * \return Interface ISkin
			 */
			ISkin* getSkin();

			/*!
			 * \brief Méthode de récupération du module Son
			 * \return Interface ISound
			 */
			ISound* getSound();			

		private:
			IGameInterfaceToMenu* gameInterfaceToMenu; /*!< Interface vers le plateau de jeu */
			INetworkToMenu* networkToMenu; /*!< Interface vers le composant Réseau */
			ISkin* skin; /*!< Interface vers le composant Skin */
			ISound* sound; /*!< Interface vers le composant Son */

			MainWindow window; /*!< Fenêtre du programme */

			/*!
			 * \brief Initialisation des interfaces
			 */
			void initInterfaces();
	};
}

#endif

