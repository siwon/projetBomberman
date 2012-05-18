#ifndef MINE_HEADER
#define MINE_HEADER

/*!
 * \file Mine.hpp
 * \brief Classe Mine
 * \author Simon ROUSSEAU
 */

#include "../../include/gameEngine/Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class Mine
	 * \brief Classe Mine
	 */
	class Mine : public Explosive {
	public:
		Mine(const Player& p);
		Mine(const Mine& mine);
		//opérateur d'affectation
		~Mine();
	};
}

#endif