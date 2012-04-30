#ifndef _ISKIN
#define _ISKIN

/*!
 * \file ISkin.hpp
 * \brief Interface de sortie du composant Skin
 * \author Maxime GUIHAL
 */

#include <vector>

#include <SFML/Color.hpp>
#include <SFML/Image.hpp>

#include "EImage.hpp"
#include "EColorKey.hpp"

namespace PolyBomber
{
	/*!
	 * \class ISkin
	 * \brief Interface de sortie du composant Skin
	 *
	 * Cette interface permet de charger les images et couleurs du jeu
	 * en fonction du skin choisi.
	 */
	class ISkin
	{
		public:
			/*!
			 * \brief Liste des skins disponibles
			 *
			 * Si aucun skin n'est disponible, la méthode lance une
			 * exception
			 * 
			 * \return Tableau des noms des skins
			 */
			virtual std::vector<std::string> getSkinsList() = 0;

			/*!
			 * \brief Chargement d'une image donnée
			 *
			 * Si la clé est incorrecte, la méthode lance une exception
			 * 
			 * \param name Clé correspondante à l'image
			 * \return Image du skin
			 */
			virtual sf::Image loadImage(EImage name) = 0;

			/*!
			 * \brief Chargement d'une couleur donnée
			 *
			 * Si la clé est incorrecte, la méthode lance une exception
			 * 
			 * \param key Clé correspondante à la couleur
			 * \return Couleur sélectionnée
			 */
			virtual sf::Color getColor(EColorKey key) = 0;

			/*!
			 * \brief Assignation du skin
			 *
			 * Si le nom est incorrect, la méthode lance une exception
			 * 
			 * \param name Nom du skin
			 */
			virtual void setSkin(std::string name) = 0;

			/*!
			 * \brief Récupération du nom du skin courant
			 * \return Nom du skin
			 */
			virtual std::string getSkin() = 0;

			/*!
			 * \brief Sauvegarde de la configuration
			 *
			 * Ecriture du choix du skin actuel dans le fichier de
			 * configuration
			 */
			virtual void saveConfig() = 0;

			/*!
			 * \brief Rechargement de la configuration
			 *
			 * En cas d'annulation des changements effectués,
			 * rechargement entier du skin
			 */
			virtual void reloadConfig() = 0;
	};
}

#endif

