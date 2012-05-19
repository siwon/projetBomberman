#ifndef LOCATION_HEADER
#define LOCATION_HEADER

/*!
 * \file Location.hpp
 * \brief Classe Location
 * \author Simon Rousseau
 */
#include <SFML/System/Vector2.hpp>

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Location
	 * \brief Classe Location
	 */
	class Location {
    protected:
		sf::Vector2f location;
		
	public:
		Location(float x, float y);
		Location(const Location& loc);
		//operateur d affectation
		~Location();
		
		float getLocationX() const {return location.x;}
		float getLocationY() const {return location.y;}
		sf::Vector2f getLocation() const {return location;}
	};
}

#endif
