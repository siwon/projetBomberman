#ifndef REMOTE_BOMB_HEADER
#define REMOTE_BOMB_HEADER

/*!
 * \file RemoteBomb.hpp
 * \brief Classe RemoteBomb
 * \author Simon ROUSSEAU
 */

#include "../../include/gameEngine/Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class RemoteBomb
	 * \brief Classe RemoteBomb
	 */
	class RemoteBomb : public Explosive {
	public:
		RemoteBomb(const Player& player);
		RemoteBomb(const RemoteBomb& rb);
		//opérateur d'affectation
		~RemoteBomb();
	};
}
#endif