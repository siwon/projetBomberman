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
	private:
		bool active;
	public:
		Mine(const Player&);
		Mine(const Mine&);
		//Mine& operator=(Mine&);
		~Mine();
		
		inline bool isActive() {return this->active;}
		inline void activate() {this->active=true;}
		inline void desactivate() {this->active=false;}
	};
}

#endif
