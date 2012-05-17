#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#define VITESSEPARDEFAUT 150
#define VITESSEMIN 100
#define VITESSEMAX 400
#define PASVITESSE 50
#define NOMBREBOMBEDEFAUT 2
#define RANGEDEFAUT 3
#define RANGEMIN 3
#define RANGEMAX 19
#define PASRANGE 2
#define ORIENTATIONDEFAUT EOrientation.RIGHT
#define BOMBTIMESTAMP 3

//TODO : mettre tous les define dans un fichier séparé

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
		int capacity;		/*! Nombre de bombes qu'un joueur peut poser */
		EOrientation orientation;	/*! Orientation du joueur */
		bool alive;	/*! Statut du joueur */
		int step;			/*! Etat de la jambe du joueur */
		int range;
		//Bonus du joueur
		sl::vector<Bonus> bombBonus;
		sl::vector<Bonus> infection;
		
		
    public:
		Player();
		Player(Player pl);
		//opérateur d'affectation
		~Player();
		
		/*!
		 * \brief Méthode permettant de tuer le joueur
		 *
		 */
		void die();
		
		/*!
		 * \brief Méthode permettant d'appliquer un bonus au joueur
		 *
		 * \param bonus : Bonus à appliquer
		 */
		void applyBonus(Bonus bonus);
		
		/*!
		 * \brief Méthode permettant de déplacer le joueur
		 *
		 * \param direction : Direction du déplacement
		 */
		void move(EOrientation direction);
		
		/*!
		 * \brief Méthode renvoyant le nombre de bombe qu'une joueur peut poser
		 *
		 * \return retourne le nombre de bombe que le joueur peut encore poser
		 */
		int getCapacity(){return this->capacity;}
		
		/*!
		 * \brief Méthode qui augmente le nombre de bombes disponibles pour le joueur
		 * Déclenchée lorsqu'une bombe du joueur explose ou bien que le joueur prend un bonus augmentant le nombre de bombes que le joueut peut poser.
		 */
		void increaseCapacity(){this->capacity++;}
		
		/*!
		 * \brief Méthode qui diminue le nombre de bombes disponibles pour le joueur
		 * Déclenchée lorsque le joueur pose une bombe ou bien lorsque le joueur prend un bonus qui diminue le nombre de bombes que le joueur peut poser.
		 */
		void decreaseCapacity(){this->capacity--;}
		
		int getId(){return this->id;}
		int getSpeed(){return this->speed;}
		EOrientation getOrientation(){return this->orientation;}
		bool getAlive(){return this->alive;}
		int getStep(){return this->step;}
		int getRange(){return this->range;}
		vector<Bonus> getBombBonus(){return this->bombBonus;}
		vector<Bonus> getInfection(){return this->infection;}
	};
}

#endif
