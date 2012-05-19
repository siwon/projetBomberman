#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include <vector>
#include "Bonus.hpp"
#include "Location.hpp"
#include "../EOrientation.hpp"

namespace PolyBomber {
	/*!
	 * \class Player
	 * \brief Classe Player
	 */
	class Player : public Location {
    protected:
		static int nbJoueur;
		
		int id;				/*! Identifiant du joueur */
		int speed;			/*! Vitesse du joueur */
		int capacity;		/*! Nombre de bombes qu un joueur peut poser */
		EOrientation orientation;	/*! Orientation du joueur */
		bool alive;	/*! Statut du joueur */
		int step;			/*! Etat de la jambe du joueur */
		int range;
		//Bonus du joueur
		std::vector<Bonus> bombBonus;
		std::vector<Bonus> infection;
		
		
    public:
		Player(int x, int y);
		Player(const Location& loc);
		Player(const Player& pl);
		//operateur d affectation
		~Player();
		
		/*!
		 * \brief Methode permettant de tuer le joueur
		 *
		 */
		void die();
		
		/*!
		 * \brief Methode permettant d appliquer un bonus au joueur
		 *
		 * \param bonus : Bonus a appliquer
		 */
		void applyBonus(Bonus bonus);
		
		/*!
		 * \brief Methode permettant de deplacer le joueur
		 *
		 * \param direction : Direction du deplacement
		 */
		void move(EOrientation direction);
		
		/*!
		 * \brief Methode renvoyant le nombre de bombe qu une joueur peut poser
		 *
		 * \return retourne le nombre de bombe que le joueur peut encore poser
		 */
		const int getCapacity() const {return this->capacity;}
		
		/*!
		 * \brief Methode qui augmente le nombre de bombes disponibles pour le joueur
		 * Declenchee lorsqu une bombe du joueur explose ou bien que le joueur prend un bonus augmentant le nombre de bombes que le joueut peut poser.
		 */
		void increaseCapacity(){this->capacity++;}
		
		/*!
		 * \brief Methode qui diminue le nombre de bombes disponibles pour le joueur
		 * Declenchee lorsque le joueur pose une bombe ou bien lorsque le joueur prend un bonus qui diminue le nombre de bombes que le joueur peut poser.
		 */
		void decreaseCapacity(){this->capacity--;}
		
		const int getId() const {return this->id;}
		const int getSpeed() const {return this->speed;}
		const EOrientation getOrientation() const {return this->orientation;}
		const bool getAlive() const {return this->alive;}
		const int getStep() const {return this->step;}
		const int getRange() const {return this->range;}
		//std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		//std::vector<Bonus> getInfection(){return this->infection;}
	};
}

#endif
