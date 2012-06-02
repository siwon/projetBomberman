#ifndef BONUS_HEADER
#define BONUS_HEADER

/*!
 * \file Bonus.hpp
 * \brief Classe Bonus
 * \author Simon ROUSSEAU
 */

#include "EGameBonus.hpp"

#include "Location.hpp"

#include "DefineAndFunction.hpp"

namespace PolyBomber {
	/*!
	 * \class Bonus
	 * \brief Classe Bonus
	 */
	class Bonus : public Location {
	protected :
		EGameBonus type; /*< Définition du type de bonus */
		bool visible; /*< Détermine si le bonus est visible (pour envoyer une caisse ou un bonus à l'affichage) */
		
	public :
		/*!
		 * \brief Constructeur de la classe Bonus
		 * \param x : Abscisse du bonus (en cran)
		 * \param y : Ordonné du bonus (en cran)
		 * \param visible : Bonus visible ou non
		 */
		Bonus(int, int, EGameBonus, bool);
		
		/*!
		 * \brief Constructeur de la classe Bonus
		 * \param x : Abscisse du bonus (en cran)
		 */
		Bonus(const Bonus&);
		
		/*!
		 * \brief Destructeur de la classe Bonus
		 */
		~Bonus();
		
		/*!
		 * \brief Fonction qui renvoie le type de bonus
		 * \return Retourne le type de bonus
		 */
		inline EGameBonus getType() const {return this->type;}
		
		/*!
		 * \brief Fonction qui renvoie si le bonus est visible
		 * \return Retourne TRUE si le bonus est visible, FALSE sinon
		 */
		inline bool isVisible() const {return this->visible;}
		
		/*!
		 * \brief Rend un bonus visible
		 */
		inline void setVisible() {this->visible=true;}
	};
}

#endif