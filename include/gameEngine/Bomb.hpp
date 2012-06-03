#ifndef BOMB_HEADER
#define BOMB_HEADER

/*!
 * \file Bomb.hpp
 * \brief Classe Bomb
 * \author Simon ROUSSEAU
 */

#include "Explosive.hpp"

namespace PolyBomber {
	/*!
	 * \class Bomb
	 * \brief Classe Bomb
	 */
	class Bomb : public Explosive {
    protected:
		int timeOfExplosion; /*!< Date où doit exploser la bombe (en secondes) */
		int type; /*!< Type de bombe (0 => bombe normale, 1 => INFINITYBOMB, 2 => ATOMICBOMB, 3 => BOMBLINE */
	public:
		/*!
		 * \brief Constructeur de la classe Bomb
		 * \param date : Date à laquelle la bombe a été posée (en secondes)
		 * \param player : Player ayant posé la bombe
		 * \param type : Type de la bombe
		 */
		Bomb(int, const Player&, int type=0);
		
		/*!
		 * \brief Constructeur de la classe Bomb
		 * \param date : Date à laquelle la bombe a été posée (en secondes)
		 * \param pl : Player ayant posé la bombe
		 * \param x : Abscisse de la bombe (en case)
		 * \param y : Ordonné de la bombe (en case)
		 * \param type : Type de la bombe
		 */
		Bomb(int, const Player&, int, int, int type=0);
		
		/*!
		 * \brief Constructeur par recopie de la classe Bomb
		 * \param bombe : Objet à copier
		 */
		Bomb(const Bomb&);
		
		/*!
		 * \brief Destructeur de la classe Bomb
		 */
		~Bomb();
		
		
		/*!
		 * \brief Retourne la date à laquelle la bombe doit exploser
		 * \return Date à laquelle la bombe doit exploser (en secondes)
		 */
		inline int getTimeOfExplosion() const {return this->timeOfExplosion;}
		
		/*!
		 * \brief Retourne le type de bombe
		 * \return Type de la bombe
		 */
		inline int getType() const {return this->type;}
		
		
		/*!
		 * \brief Décale l'explosition de la bombe
		 * \param nbSecondes : Décalage à effectuer (en secondes)
		 */
		inline void decalerExplosion(int nbSecondes) {this->timeOfExplosion=this->timeOfExplosion+nbSecondes;}
	};
}

#endif