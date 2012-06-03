#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include "Bonus.hpp"
#include "Location.hpp"
#include "EOrientation.hpp"

namespace PolyBomber {
	/*!
	 * \class Player
	 * \brief Classe Player
	 */
	class Player : public Location {
    protected:
		int id;				/*< Identifiant du joueur */
		int speed;			/*< Vitesse du joueur */
		int capacity;		/*< Nombre de bombes qu un joueur peut poser */
		EOrientation orientation;	/*< Orientation du joueur */
		bool alive;	/*< Statut du joueur */
		int step;			/*< Etat de la jambe du joueur */
		int lastMove; /*< Date du dernier mouvement (en millisecondes) */
		int lastActionSecond; /*< Date de la dernière action 2 (en secondes) */
		int range; /*< Portée du joueur */
		bool detonator; /*< Le joueur possède un détonateur */
		int saveCaracBeforeInfectionDilatation; /*< Permet une sauvegarde des caractéristiques avant l'infection dilatation */
		
		//Bonus du joueur
		std::vector<Bonus> bombBonus; /*< Vecteur des bonus attribués au joueur */
		int infection; /*< Type d'infection que le joueur a */
		
	private:
		void removeInfection();
		
	public:	
		/*!
		 * \brief Constructeur de la classe Player
		 * \param x : Abscisse du joueur en début de partie (en cran)
		 * \param y : Ordonné du joueur en début de partie (en cran)
		 * \param id : Identifiant du joueur
		 */
		Player(int, int, int);
		
		/*!
		 * \brief Constructeur par recopie de la classe Player
		 * \param pl : Objet à copier
		 */
		Player(const Player& pl);
		
		/*!
		 * \brief Destructeur de la classe Player
		 */
		~Player();

		 
		/*!
		 * \brief Retourne l'identifiant du joueur
		 * \return Identifiant du joueur
		 */
		inline int getId() const {return this->id;}
		
		/*!
		 * \brief Retourne la vitesse du joueur
		 * \return Vitesse du joueur
		 */
		inline int getSpeed() const {return this->speed;}
		
		/*!
		 * \brief Retourne le nombre de bombes que le joueur peut encore poser
		 * \return Nombre de bombes que le joueur peut encore poser
		 */
		inline int getCapacity() const {return this->capacity;}
		
		/*!
		 * \brief Retourne la direction vers laquelle regarde le joueur (pour l'affichage)
		 * \return Direction du joueur
		 */
		inline EOrientation getOrientation() const {return this->orientation;}
		
		/*!
		 * \brief Retourne si le joueur est encore en vie ou non
		 * \return TRUE si le joueur est encore en vie, FALSE sinon.
		 */
		inline bool getAlive() const {return this->alive;}
		
		/*!
		 * \brief Retourne le moment où le joueur a effectuer son dernier mouvement
		 * \return Date du dernier mouvement (en millisecondes)
		 */
		inline int getLastMove() const {return this->lastMove;}
		
		/*!
		 * \brief Retourne le moment où le joueur a effectuer sa dernière action 2
		 * \return Date de la dernière action 2 (en secondes)
		 */
		inline int getLastAction2() const {return this->lastActionSecond;}
		
		/*!
		 * \brief Retourne la pas du joueur (pour l'affichage)
		 * \return Pas du joueur
		 */
		inline int getStep() const {return this->step;}
		
		/*!
		 * \brief Retourne la portée des bombes du joueur
		 * \return Portée du joueur
		 */
		inline int getRange() const {return this->range;}
		
		/*!
		 * \brief Retourne si le joueur possède oui ou non un détonateur
		 * \return TRUE si le joueur possède un détonateur, FALSE sinon
		 */
		inline bool getDetonator() const {return this->detonator;}
		
		/*!
		 * \brief Retourne la liste des bonus de bombes dont bénéficie le joueur
		 * \return Vector de Bonus
		 */
		inline std::vector<Bonus> getBombBonus(){return this->bombBonus;}
		
		/*!
		 * \brief Retourne le premier bonus de bombe du joueur
		 * \return Bonus
		 */
		inline EGameBonus getFirstBombBonus(){return this->bombBonus[0].getType();}
		
		/*!
		 * \brief Retourne le nombre de bonus de bombes dont bénéficie le joueur
		 * \return Nombre de bonus de bombe
		 */
		inline unsigned int getBombBonusSize() {return this->bombBonus.size();}
		
		/*!
		 * \brief Retourne l'infection que le joueur subit
		 * \return Infection
		 */
		inline int getInfection() const {return this->infection;}
		

		/*!
		 * \brief Supprime le premier bonus de bombe du joueur dans la liste
		 */
		inline void eraseFirstBonus() {this->bombBonus.erase(this->bombBonus.begin());}
		
		/*!
		 * \brief Change le statut du joueur et le considérer comme mort
		 */
		inline void killPlayer() {this->alive=false;}
		
		/*!
		 * \brief Ajoute un bonus au joueur
		 */
		void addBonus(Bonus bonus);
		
		/*!
		 * \brief Déplace le joueur
		 * \param x : Nouvel abscisse du joueur (en cran)
		 * \param y : Nouvel ordonné du joueur (en cran)
		 */
		void move(int, int);
		
		/*!
		 * \brief Permet de centrer le joueur dans sa case sur l'axe horizontal
		 */
		void centrerPlayerSurAxeHorizontal();
		
		/*!
		 * \brief Permet de centrer le joueur dans sa case sur l'axe vertical
		 */
		void centrerPlayerSurAxeVertical();
		
		/*!
		 * \brief Incrémente la variable step du joueur
		 */
		inline void incrementStep() {this->step++;}
		
		/*!
		 * \brief Change l'orientation du joueur
		 * \param orient : Nouvelle orientation du joueur
		 */
		inline void setOrientation(EOrientation orient) {this->orientation=orient;}
		
		/*!
		 * \brief Incrémente le nombre de bombes posables par le joueur
		 * \param i : Nombre de bombes à ajouter
		 */
		inline void incrementCapacity(int i=1) {this->capacity+=i;}
		
		/*!
		 * \brief Décrémente le nombre de bombes posables par le joueur
		 * \param i : Nombre de bombes à supprimer
		 */
		inline void decrementCapacity(int i=1) {this->capacity-=i;}
		
		/*!
		 * \brief Met à jour la date du dernier mouvement
		 * \param date : Date du dernier mouvement (en millisecondes)
		 */
		inline void setLastMove(int date) {this->lastMove=date;}
		
		/*!
		 * \brief Met à jour la date de la dernière action 2
		 * \param date : Date de la dernière action 2 (en secondes)
		 */
		inline void setLastAction2(int date) {this->lastActionSecond=date;}
	};
}

#endif
