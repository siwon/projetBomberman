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
			 * \brief Méthode pour effacer la fenêtre
			 */
			void clear();

			/*!
			 * \brief Méthode pour afficher la fenêtre
			 * \param widgets : Elements à afficher
			 */
			void display(std::vector<sf::Drawable*> widgets);

			/*!
			 * \brief Accesseur vers la Fenêtre SFML
			 * \return La fenêtre SFML
			 */
			inline sf::RenderWindow* getWindow() {return &window;}

			/*!
			 * \brief Accesseur vers le style de la fenêtre
			 * \return True si la fenêtre est en plein écran
			 */
			inline bool getFullScreen() {return this->fullscreen;}

			/*!
			 * \brief Détermine si la fenêtre est en plein écran
			 * \param fullscreen : True si la fenêtre doit être en plein écran
			 */
			void setFullScreen(bool fullscreen);

			/*!
			 * \brief Détermine si la fenêtre peut se mettre en plein écran
			 * \return False si le plein ecran est impossible
			 */
			bool canFullScreen();

			/*!
			 * \brief Renvoie l'etat d'ouverture de la fenêtre
			 * \return True si la fenêtre est ouverte
			 */
			bool isOpen();

		private:
			static sf::RenderWindow window; /*!< Fenetre du programme */
			bool fullscreen; /*!< True si la fenêtre est en plein ecran */

			/*!
			 * \brief Méthode d'initialisation de la fenêtre
			 */
			void initWindow();
	};
}

#endif


