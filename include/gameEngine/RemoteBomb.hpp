#ifndef REMOTE_BOMB_HEADER
#define REMOTE_BOMB_HEADER

/*!
 * \file RemoteBomb.hpp
 * \brief Classe RemoteBomb
 * \author Simon ROUSSEAU
 */

namespace PolyBomber {
	/*!
	 * \class RemoteBomb
	 * \brief Classe RemoteBomb
	 */
	class RemoteBomb : public Explosive {
	public:
		RemoteBomb(Player player);
		RemoteBomb(RemoteBomb rb);
		//opérateur d'affectation
		~RemoteBomb();
	};
}
#endif