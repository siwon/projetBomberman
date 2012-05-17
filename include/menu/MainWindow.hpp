#ifndef _MAINWINDOW
#define _MAINWINDOW

/*!
 * \file MainWindow.hpp
 * \brief Classe de la fenêtre du programme
 * \author Maxime GUIHAL
 */

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "menu/MainWindow.hpp"

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

		private:
			sf::RenderWindow window; /*!< Fenetre du programme */
			unsigned int style; /*! Style de la fenêtre */
			sf::VideoMode settings; /*! Paramètres vidéo de la fenêtre */

			/*!
			 * \brief Méthode d'initialisation des paramètres de la fenêtre
			 * \param style : Style de la fenêtre (plein écran ou fenêtré)
			 * \param mode : Paramètres vidéo de la fenêtre
			 */
			void initVideoMode(unsigned int& style, sf::VideoMode& mode);
	};
}

#endif


