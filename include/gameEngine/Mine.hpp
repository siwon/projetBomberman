#ifndef MINE_HEADER
#define MINE_HEADER

/*!
 * \file Mine.hpp
 * \brief Classe Mine
 * \author Simon ROUSSEAU
 */

#include "Explosive.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Mine
	 * \brief Classe Mine
	 */
	class Mine : public Explosive {
	public:
		Mine(const Player&);
		Mine(const Mine&);
		//Mine& operator=(Mine&);
		~Mine();
	};
}

#endif