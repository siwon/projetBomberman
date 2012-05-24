#ifndef REMOTE_BOMB_HEADER
#define REMOTE_BOMB_HEADER

/*!
 * \file RemoteBomb.hpp
 * \brief Classe RemoteBomb
 * \author Simon ROUSSEAU
 */

#include "Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class RemoteBomb
	 * \brief Classe RemoteBomb
	 */
	class RemoteBomb : public Explosive {
	public:
		RemoteBomb(const Player&);
		RemoteBomb(const RemoteBomb&);
		RemoteBomb& operator=(RemoteBomb&);
		~RemoteBomb();
	};
}
#endif