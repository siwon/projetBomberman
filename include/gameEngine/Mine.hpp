#ifndef MINE_HEADER
#define MINE_HEADER

/*!
 * \file Mine.hpp
 * \brief Classe Mine
 * \author Simon ROUSSEAU
 */

#include "Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class Mine
	 * \brief Classe Mine
	 */
	class Mine : public Explosive {
	private:
		bool active;	/*!< Détermine si la mine est active ou non */
	public:
		/*!
		 * \brief Constructeur de la classe Mine
		 * \param p : Player ayant posé la mine
		 */
		Mine(const Player&);
		
		/*!
		 * \brief Constructeur par recopie de la classe Mine
		 * \param mine : Objet à copier
		 */
		Mine(const Mine&);
		
		/*!
		 * \brief Destructeur de la classe Mine
		 */
		~Mine();
		
		
		/*!
		 * \brief Détermine si une mine est active ou pas
		 * \return TRUE si la mine est active, FALSE sinon
		 */
		inline bool isActive() {return this->active;}
		
		
		/*!
		 * \brief Active la mine
		 */
		inline void activate() {this->active=true;}
		
		/*!
		 * \brief Désactive la mine
		 */
		inline void desactivate() {this->active=false;}
	};
}

#endif
