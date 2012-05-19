#ifndef MINE_HEADER
#define MINE_HEADER

/*!
 * \file Mine.hpp
 * \brief Classe Mine
 * \author Simon ROUSSEAU
 */

#include "gameEngine/Explosive.hpp"

#include "gameEngine/DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Mine
	 * \brief Classe Mine
	 */
	class Mine : public Explosive {
	public:
		Mine(const Player& p);
		Mine(const Mine& mine);
		//operateur d affectation
		~Mine();
	};
}

#endif