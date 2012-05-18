#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */
#include <SFML/System/Vector2.hpp>
//#include "Board.hpp"

namespace PolyBomber {
	/*!
	 * \class Location
	 * \brief Classe Location
	 */
	class Location {
    protected:
		//Board board;	/*! Plateau de jeu */
		sf::Vector2<int> location;
		
	public:
		Location(const sf::Vector2<int>& location);
		Location(int x, int y);
		Location(const Location& loc);
		//opérateur d'affectation
		~Location();
		const int getLocationX() const {return location.x;}
		const int getLocationY() const {return location.y;}
		const sf::Vector2<int> getLocation() const {return location;}
	};
}

#endif