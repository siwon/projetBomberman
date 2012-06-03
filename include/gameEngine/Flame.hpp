#ifndef FLAME_HEADER
#define FLAME_HEADER

/*!
 * \file Flame.hpp
 * \brief Classe Flame
 * \author Simon ROUSSEAU
 */

#include "Location.hpp"

#include "EOrientation.hpp"
#include "EFlameLocation.hpp"

namespace PolyBomber {
	/*!
	 * \class Flame
	 * \brief Classe Flame
	 */
	
	class Flame : public Location {
	private:
		EOrientation orientation;		/*< Orientation de la flamme (haut, bas, gauche, droite) */
		EFlameLocation flameLocation;	/*< Position de la flamme dans la déflégration pour l'affichage (source, milieu, fin) */
		int dateDebutFlame;				/*< Date du début de la flamme (en secondes) */
		
	public:
		/*!
		 * \brief Constructeur de la classe Flame
		 * \param x : Abscisse de la flamme (en case)
		 * \param y : Ordonné de la flamme (en case)
		 * \param orientation : Orientation de la flamme
		 * \param flameLocation : Position de la flamme dans la déflagration
		 * \param date : Date du début de la flamme (en secondes)
		 */
		Flame(int, int, EOrientation, EFlameLocation, int);
		
		/*!
		 * \brief Constructeur par recopie de la classe Flame
		 * \param flamme : Objet à copier
		 */
		Flame(const Flame&);
		
		/*!
		 * \brief Destructeur de la classe Flame
		 */
		~Flame();
		
		/*!
		 * \brief Retourne l'orientation de la flamme
		 * \return Orientation de la flamme (ORIENTATION_UP, ORIENTATION_DOWN, ORIENTATION_LEFT, ORIENTATION_RIGHT)
		 */
		inline EOrientation getOrientation() const {return this->orientation;}
		
		/*!
		 * \brief Retourne la position de la flamme dans la déflagration
		 * \return Position de la flamme dans la déflagration (ORIGIN, MIDDLE, END)
		 */
		inline EFlameLocation getFlameLocation() const {return this->flameLocation;}
		
		/*!
		 * \brief Retourne la date de début de la flamme
		 * \return Date de début de la flamme (en secondes)
		 */
		inline int getDateDebutFlame() const {return this->dateDebutFlame;}
		
		/*!
		 * \brief Décale la date de début de la flamme
		 * \param nbSecondes : Durée du décalage (en secondes)
		 */
		inline void decalerDebutFlame(int nbSecondes) {this->dateDebutFlame=this->dateDebutFlame+nbSecondes;}
	};
}

#endif