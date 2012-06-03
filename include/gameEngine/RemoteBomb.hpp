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
		/*!
		 * \brief Constructeur de la classe RemoteBomb
		 * \param player : Player qui pose la bombe télécommandée
		 */
		RemoteBomb(const Player&);
		
		/*!
		 * \brief Constructeur par recopie de la classe RemoteBomb
		 * \param rb : Objet à copier
		 */
		RemoteBomb(const RemoteBomb&);
		
		/*!
		 * \brief Destructeur de la classe RemoteBomb
		 */
		~RemoteBomb();
	};
}
#endif