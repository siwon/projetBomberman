#ifndef BOARD_HEADER
#define BOARD_HEADER

/*!
 * \file Board.hpp
 * \brief Classe Board
 * \author Simon Rousseau
 */

#include "Flame.hpp"
#include "Bonus.hpp"
#include "Box.hpp"
#include "RemoteBomb.hpp"
#include "Bomb.hpp"
#include "Mine.hpp"
#include "Player.hpp"
#include "Wall.hpp"

namespace PolyBomber {
	/*!
	 * \class Board
	 * \brief Classe Board
	 */
	class Board {
    protected:
		std::vector<Bonus> bonus; /*< Vecteur de Bonus */
		std::vector<Flame> flame; /*< Vecteur de Flame */
		std::vector<Box> box; /*< Vecteur de Box */
		std::vector<Player> player; /*< Vecteur de Player */
		std::vector<Bomb> bomb; /*< Vecteur de Bomb */
		std::vector<RemoteBomb> remoteBomb; /*< Vecteur de RemoteBomb */
		std::vector<Mine> mine; /*< Vecteur de Mine */
		std::vector<Wall> wall; /*< Vecteur de Wall */
		
		/*!
		 * \brief Retourne le joueur ayant pour identifiant id
		 * \param id : Identifiant du joueur
		 * \return Référence vers Player
		 */
		Player& getPlayerById(int);
		
		/*!
		 * \brief Génère une flamme horizontale
		 * \param x : Abscisse de la source (en case)
		 * \param y : Ordonné de la source (en case)
		 * \param range : Portée de la flamme
		 * \param date : Date courante du jeu
		 */
		void generateFlameHorizontal(int, int, int, int);
		
	public:
		/*!
		 * \brief Constructeur de la classe Board
		 */
		Board();
		
		/*!
		 * \brief Destructeur de la classe Board
		 */
		~Board();
		
		/*!
		 * \brief Calcule et retourne le nombre de joueurs encore en vie
		 * \return Nombre de joueurs encore en vie
		 */
		inline unsigned int getNbPlayer() {return this->player.size();}
		
		/*!
		 * \brief Génère le SBoard pour le renvoyer au GameEngineManager
		 * \return Une structure de type SBoard
		 */
		SBoard boardToSBoard();
		
		//gestion des touches
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche haut
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu
		 */
		void actionToucheHaut(int, int);
		
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche bas
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu
		 */
		void actionToucheBas(int, int);
		
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche gauche
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu
		 */
		void actionToucheGauche(int, int);
		
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche droite
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu
		 */
		void actionToucheDroite(int, int);
		
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche action 1
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu (en secondes)
		 * \param date2 : Date courante du jeu (en millisecondes)
		 */
		void actionToucheAction1(int, int, int);
		
		/*!
		 * \brief Effectue l'action lorsqu'un joueur appuie sur la touche action 2
		 * \param player : identifiant du joueur ayant pressé la touche
		 * \param date : Date courante du jeu (en secondes)
		 * \param date2 : Date courante du jeu (en millisecondes)
		 */
		void actionToucheAction2(int, int, int);
		
		
		/*!
		 * \brief Ajoute un joueur au vecteur de Player
		 * \param pl : Objet de type Player à ajouter
		 */
		inline void addPlayer(Player pl) {this->player.push_back(pl);}
		
		/*!
		 * \brief Ajoute un mur au vecteur de Wall
		 * \param wall : Objet de type Wall à ajouter
		 */
		inline void addWall(Wall wall) {this->wall.push_back(wall);}
		
		/*!
		 * \brief Ajoute un bonus au vecteur de Bonus
		 * \param b : Objet de type Bonus à ajouter
		 */
		inline void addBonus(Bonus b) {this->bonus.push_back(b);}
		
		/*!
		 * \brief Ajoute une caisse au vecteur de Box
		 * \param b : Objet de type Box à ajouter
		 */
		inline void addBox(Box b) {this->box.push_back(b);}
		
		/*!
		 * \brief Ajoute une flamme au vecteur de Flame
		 * \param f : Objet de type Flame à ajouter
		 */
		inline void addFlame(Flame f) {this->flame.push_back(f);}
		
		
		/*!
		 * \brief Supprimer une caisse du vecteur de Box
		 * \param i : Index de la caisse dans le vecteur
		 */
		void removeBox(int i);
		
		/*!
		 * \brief Supprimer un bonus du vecteur de Bonus
		 * \param x : Abscisse du bonus (en case)
		 * \param y : Ordonné du bonus (en case)
		 */
		void removeBonusByCoord(int x, int y);
		
		/*!
		 * \brief Détermine si une case est libre lors de l'initialisation
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE si elle est libre, FALSE sinon
		 */
		bool caseIsFreeInitialisation(int, int);
		
		/*!
		 * \brief Détermine si une case est libre lors du jeu
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE si elle est libre, FALSE sinon
		 */
		bool caseIsFree(int, int);
		
		/*!
		 * \brief Détermine si il y a un mur dans la case
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE en cas de présence, FALSE sinon
		 */
		bool isAWallInThisCase(int, int);
		
		/*!
		 * \brief Détermine si il y a une flamme dans la case
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE en cas de présence, FALSE sinon
		 */
		bool isAFlameInThisCase(int, int);
		
		/*!
		 * \brief Détermine si il y a un bonus dans la case
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE en cas de présence, FALSE sinon
		 */
		bool isABonusInThisCase(int, int);
		
		/*!
		 * \brief Détermine si il y a une mine dans la case
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE en cas de présence, FALSE sinon
		 */
		bool isAMineInThisCase(int, int);
		
		/*!
		 * \brief Détermine si il y a une bombe dans la case
		 * \param x : Abscisse de la case (en case)
		 * \param y : Ordonné de la case (en case)
		 * \return Retourne TRUE en cas de présence, FALSE sinon
		 */
		bool isABombInThisCase(int, int);
		
		
		/*!
		 * \brief Détermine le nombre de survivant
		 * \return Le nombre de survivants
		 */
		int nbSurvivant();
		
		/*!
		 * \brief Détermine l'identifiant de survivant si la partie est terminée
		 * \return 0 si la partie n'est pas encore terminée, -1 si la partie est terminée sans aucun survivants, l'identifiant du joueur plus 1 sinon.
		 */
		int getIdSurvivant();
		
		/*!
		 * \brief Effectue le décalage sur les coordonnées
		 * \param nbSecondes : Temps de décalage (en secondes)
		 */
		void effectuerDecalage(int);
		
		/*!
		 * \brief Applique un bonus à un joueur
		 * \param pl : Identifiant du joueur auquel appliquer le bonus
		 * \param b : Bonus à appliquer
		 */
		void applyBonus(int, Bonus);
		
		/*!
		 * \brief Fait exploser une bombe
		 * \param x : Abscisse de la bombe (en case)
		 * \param y : Ordonné de la bombe (en case)
		 */
		void explodeBomb(int, int);
		/*!
		 * \brief Fait exploser une bombe
		 * \param indice : Indice de la bombe dans le vecteur de Bomb
		 */
		void explodeBomb(unsigned int);
		
		/*!
		 * \brief Fait exploser une bombe télécommandée
		 * \param indice : Indice de la bombe dans le vecteur de Bomb
		 * \param date : Date courante du jeu (en secondes)
		 */
		void explodeRemoteBomb(unsigned int, int);
		
		/*!
		 * \brief Fait exploser une mine
		 * \param x : Abscisse de la mine (en case)
		 * \param y : Ordonné de la mine (en case)
		 * \param date : Date courante du jeu (en secondes)
		 */
		void explodeMine(int, int, int);
		
		/*!
		 * \brief Fait exploser une mine
		 * \param indice : Indice de la mine dans le vecteur de Mine
		 * \param date : Date courante du jeu (en secondes)
		 */
		void explodeMine(unsigned int, int);
		
		
		/*!
		 * \brief Génère les flammes d'un explosif
		 * \param origineX : Abscisse de la source de la flamme (en case)
		 * \param origineY : Ordonné de la source de la flamme (en case)
		 * \param range : Portée de la flamme
		 * \param date : Date courante du jeu (en secondes)
		 */
		void generateFlame(int, int, int, int);
		
		/*!
		 * \brief Génère les flammes d'une bombe infinie
		 * \param indice : Indice de la bombe dans le vecteur de Bomb
		 * \param date : Date courante du jeu (en secondes)
		 */
		void generateFlameInfinityBomb(unsigned int, int);
		
		/*!
		 * \brief Génère les flammes d'une bombe atomique
		 * \param indice : Indice de la bombe dans le vecteur de Bomb
		 * \param date : Date courante du jeu (en secondes)
		 */
		void generateFlameAtomicBomb(unsigned int, int);
		
		/*!
		 * \brief Récupère le Bonus par ses coordonnées
		 * \param x : Abscisse du bonus (en case)
		 * \param y : Ordonné du bonus (en case)
		 * \return Le bonus associé
		 */
		Bonus getBonusByCoord(int, int);
		
		/*!
		 * \brief Récupère le Bonus par son indice
		 * \param indice : Indice du bonus dans le vecteur de Bonus
		 * \return Le bonus associé
		 */
		inline Bonus getBonusByIndice(unsigned int indice){return this->bonus[indice];}
		
		/*!
		 * \brief Récupère l'indice d'un bonus par ses coordonées
		 * \param x : Abscisse du bonus (en case)
		 * \param y : Ordonné du bonus (en case)
		 * \return L'indice du bonus
		 */
		unsigned int getIndiceBonus(int, int);
		
		/*!
		 * \brief Récupère l'indice d'une mine par ses coordonées
		 * \param x : Abscisse de la mine (en case)
		 * \param y : Ordonné de la mine (en case)
		 * \return L'indice de la mine
		 */
		unsigned int getIndiceMineByCoord(int, int);
		
		
		/*!
		 * \brief Vérifie les superpositions d'objets entre eux sur la carte
		 * \param date : Date courante du jeu (en secondes)
		 */
		void checkPosition(int);
		
		/*!
		 * \brief Active les mines pas encore activées
		 * Lors de leur création, les mines ne sont pas activées, ce n'est que lorsque le joueur quitte la case aprèe l'avoir posée que celle-ci peut s'activer
		 */
		void activateAllMine();
		
		/*!
		 * \brief Effectue les actions récurentes dûes aux infections
		 * \param date : Date courante du jeu (en secondes)
		 */
		void makeInfectionAction(int);
		
		/*!
		 * \brief Supprime toutes les flammes qui sont trop vieilles
		 * \param date : Date courante du jeu (en secondes)
		 */
		void removeObseleteFlame(int);
		
		/*!
		 * \brief Explose toutes les bombes dont la date d'explosion est dépassée
		 * \param date : Date courante du jeu (en secondes)
		 */
		void explodeAllBomb(int);
		
		
		/*!
		 * \brief Effectue la conversion cran vers pixel pour la position des joueurs sur l'interface graphique
		 * \param i : Entier à convertir (en cran)
		 * \return Pixel correspondant (en pixel)
		 */
		static int cranToPixel(int i) {return (i-2)*7;}
		
		/*!
		 * \brief Effectue la conversion cran vers case pour la comparaison de la position des joueurs et des autres objets
		 * \param i : Entier à convertir (en cran)
		 * \return Case correspondante (en case)
		 */
		static int cranToCase(int i) {return (i-(i%5))/5;}
		
		/*!
		 * \brief Détermine si les joueurs sont à des distances suffisantes
		 * \param pl : Indice du joueur à partir duquel nous allons vérifier les distance suffisantes
		 * \param x : Abscisse du joueur (en cran)
		 * \param y : Ordonné du joueur (en cran)
		 * \return TRUE si les distances sont valides, FALSE sinon
		 */
		bool distanceDesAutresJoueursValide(unsigned int, int, int);
		
		/*!
		 * \brief Supprime tous les objets de tous les vecteurs (utile pour la fonction d'annulation du jeu)
		 */
		void resetConfig();
	};
}

#endif
