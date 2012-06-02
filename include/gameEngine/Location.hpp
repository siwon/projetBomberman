#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */
#include <SFML/System/Vector2.hpp>

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Location
	 * \brief Classe Location
	 */
	class Location {
    protected:
		sf::Vector2<int> location; /*< Vector2 de la SFML permettant de stocké deux entier correspondant à abscisse et ordonné */
		
	public:
		/*!
		 * \brief Constructeur de la classe Location
		 * \param x : Abscisse de l'objet Location
		 * \param y : Ordonné de l'objet Location
		 */
		Location(int, int);
		
		/*!
		 * \brief Constructeur par recopie de Location
		 * \param loc : Objet Location à copier
		 */
		Location(const Location&);
		
		/*!
		 * \brief Destructeur de la classe Location
		 */
		~Location();
		
		
		/*!
		 * \brief Retourne l'attribut x de l'attribut location de la classe Location
		 * \return Abscisse de l'objet location
		 */
		inline int getLocationX() const {return location.x;}
		
		/*!
		 * \brief Retourne l'attribut y de l'attribut location de la classe Location
		 * \return Ordonné de l'objet location
		 */
		inline int getLocationY() const {return location.y;}
		
		/*!
		 * \brief Retourne location de la classe Location
		 * \return Retourne l'attribut location
		 */
		inline sf::Vector2<int> getLocation() const {return location;}

		/*!
		 * \brief Permet de modifier les attributs x et y de l'attribut location
		 * \param x : Nouvel abscisse de l'attribut
		 * \param y : Nouvel ordonné de l'attribut
		 */
		void setLocation(int x, int y);
	};
}

#endif
