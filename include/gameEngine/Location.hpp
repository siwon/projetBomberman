#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */

namespace PolyBomber {
	/*!
	 * \class Location
	 * \brief Classe Location
	 */
	class Location {
    protected:
		Board board ;	/*! Plateau de jeu */
		sf::Vector2<int> location;
		
		Location(sf::Vector2<int> location);
		Location(int x, int y);
		Location(Location loc);
		//opérateur d'affectation
		~Location();
		
	public:
		sf::Vector2<int> getLocation(){return this->location;}
	};
}

#endif