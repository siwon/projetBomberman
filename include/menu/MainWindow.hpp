#ifndef _MAINWINDOW
#define _MAINWINDOW

/*!
 * \file MainWindow.hpp
 * \brief Classe de la fenêtre du programme
 * \author Maxime GUIHAL
 */

#include <vector>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Event.hpp"

#include "menu/MainWindow.hpp"
#include "menu/IWidgetMenu.hpp"

namespace PolyBomber
{
	/*!
	 * \class MainWindow
	 * \brief Classe de la fenêtre du programme
	 */
	class MainWindow
	{
		public:
			/*!
			 * \brief Constructeur
			 */
			MainWindow();

			/*!
			 * \brief Destructeur
			 */
			~MainWindow();

			/*!
			 * \brief Constructeur de copie
			 */
			MainWindow(const MainWindow& obj);

			/*!
			* \brief Opérateur d'affectation
			*/
			MainWindow& operator=(const MainWindow& obj);

			/*!
			 * \brief Getter du style de la fenêtre
			 * \return Le style de la fenêtre
			 */
			unsigned int getStyle() const;

			/*!
			 * \brief Getter des paramètres de la fenêtre
			 * \return Les paramètres vidéo de la fenêtre
			 */
			sf::VideoMode getSettings() const;

			/*!
			 * \brief Méthode pour gérer la fermeture de la fenêtre
			 *  \return True si la fenêtre doit être fermée
			 */
			bool listenCloseButton(); 

			/*!
			 * \brief Méthode pour effacer la fenêtre
			 */
			void clear();

			/*!
			 * \brief Méthode pour afficher la fenêtre
			 * \param widgets : Elements à afficher
			 */
			void display(std::vector<IWidgetMenu*> widgets);

			void draw(sf::Sprite s);

		private:
			static sf::RenderWindow window; /*!< Fenetre du programme */
			unsigned int style; /*! Style de la fenêtre */
			sf::VideoMode settings; /*! Paramètres vidéo de la fenêtre */

			/*!
			 * \brief Méthode d'initialisation des paramètres de la fenêtre
			 * \param style : Style de la fenêtre (plein écran ou fenêtré)
			 * \param mode : Paramètres vidéo de la fenêtre
			 */
			void initVideoMode(unsigned int& style, sf::VideoMode& mode);

			/*!
			 * \brief Méthode d'initialisation de la fenêtre
			 * \param style : Style de la fenêtre (plein écran ou fenêtré)
			 * \param mode : Paramètres vidéo de la fenêtre
			 */
			void initWindow(unsigned int style, sf::VideoMode settings);
	};
}

#endif


