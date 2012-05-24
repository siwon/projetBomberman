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
		sf::Vector2<int> location;
		
	public:
		Location(int, int);
		Location(const Location&);
		Location& operator=(Location&);
		~Location();
		
		inline int getLocationX() const {return location.x;}
		inline int getLocationY() const {return location.y;}
		inline sf::Vector2<int> getLocation() const {return location;}

		void setLocation(int x, int y);
	};
}

#endif
