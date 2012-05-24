/*!
 * \file Board.cpp
 * \brief Implementation de la classe Board
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards


// Bibliotheques SFML


// Bibliotheques externes


// Headers
#include "../../include/gameEngine/Board.hpp"


namespace PolyBomber {
	
	Board::Board() {

	}
	
	Board::~Board() {
		
	}
	
	Player Board::getPlayerById(int id) {
		unsigned int indice=0;
		while (indice<player.size() && player[indice].getId()!=id) {
			indice++;
		}
		return player[indice];
	}
	
	SBoard Board::boardToSBoard() {
		SBoard toReturn;
		/* enregitrer les bonus*/
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (bonus[i].isVisible()) {
				SBonus b;
				b.coords=sf::Vector2<int>(bonus[i].getLocationX(),bonus[i].getLocationY());
				b.type=bonus[i].getType();
				toReturn.bonus.push_back(b);
			} else {
				toReturn.boxes.push_back(sf::Vector2<int>(bonus[i].getLocationX(),bonus[i].getLocationY()));
			}
		}
		
		/*les flames*/
		for (unsigned int i=0; i<flame.size(); i++) {
			SFlame f;
			f.coords=sf::Vector2<int>(flame[i].getLocationX(),flame[i].getLocationY());
			f.orientation=flame[i].getOrientation();
			f.step=flame[i].getStep();
			toReturn.flames.push_back(f);
		}
		
		/*les boxes*/
		for (unsigned int i=0; i<box.size(); i++) {
			toReturn.boxes.push_back(sf::Vector2<int>(box[i].getLocationX(),box[i].getLocationY()));
		}
		
		/*les joueurs*/
		for (unsigned int i=0; i<player.size(); i++) {
			SPlayer p;
			p.coords=sf::Vector2<int>(cranToPixel(player[i].getLocationX()),cranToPixel(player[i].getLocationY()));
			p.orientation=player[i].getOrientation();
			p.number=player[i].getId();
			if (player[i].getAlive()) {
				p.state=ALIVE;
			} else {
				p.state=DEAD;
			}
			p.step=player[i].getStep();
			toReturn.players.push_back(p);
		}
		
		for (unsigned int i=0; i<bomb.size(); i++) {//bomb
			SExplosive e;
			e.coords=sf::Vector2<int>(bomb[i].getLocationX(),bomb[i].getLocationY());
			e.type=EXPLOSIVE_BOMB;
			toReturn.explosives.push_back(e);
		}
		
		for (unsigned int i=0; i<bomb.size(); i++) {//remoteBomb
			SExplosive e;
			e.coords=sf::Vector2<int>(bomb[i].getLocationX(),bomb[i].getLocationY());
			e.type=EXPLOSIVE_REMOTE;
			toReturn.explosives.push_back(e);
		}
		
		for (unsigned int i=0; i<mine.size(); i++) {//mine
			SExplosive e;
			e.coords=sf::Vector2<int>(mine[i].getLocationX(),mine[i].getLocationY());
			e.type=EXPLOSIVE_MINE;
			toReturn.explosives.push_back(e);
		}
		
		return toReturn;
	}
	
	void Board::actionToucheHaut(int player) {
		// TODO : a faire
		//tester si il y a une maladie
		//tester si le mouvement est possible
	}
	
	void Board::actionToucheBas(int player) {
		// TODO : a faire
	}
	
	void Board::actionToucheGauche(int player) {
		// TODO : a faire
	}
	
	void Board::actionToucheDroite(int player) {
		// TODO : a faire
	}
	
	void Board::actionToucheAction1(int player) {
		// TODO : a faire
	}
	
	void Board::actionToucheAction2(int player) {
		// TODO : a faire
	}
	
	void Board::removeBox(int i) {
		//box[i].~Box();
		box.erase(box.begin()+i);
	}
	
	bool Board::caseIsFreeInitialisation(int x, int y) {
		bool toReturn;
		//test si c'est une coordonnee reservee
		if ((x==0&&y==1)||(x==1&&y==0)||(x==17&&y==0)||(x==18&&y==1)||(x==18&&y==11)||(x==17&&y==12)||(x==0&&y==11)||(x==1&&y==12)||(x==8&&y==11)||(x==8&&y==12)||(x==10&&y==12)||(x==10&&y==11)) {
			toReturn=false;
		} else {
			toReturn=caseIsFree(x,y);
		}
		return toReturn;
	}
	
	bool Board::caseIsFree(int x, int y) {
		bool toReturn = true;
		unsigned int i=0;;
		while (toReturn && i<bonus.size()) {//bonus
			if (x==bonus[i].getLocationX() && y==bonus[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<flame.size()) {//flame
			if (x==flame[i].getLocationX() && y==flame[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<box.size()) {//box
			if (x==box[i].getLocationX() && y==box[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<player.size()) {//player
			if (x==player[i].getLocationX() && y==player[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<bomb.size()) {//bomb
			if (x==bomb[i].getLocationX() && y==bomb[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<remoteBomb.size()) {//remote
			if (x==remoteBomb[i].getLocationX() && y==remoteBomb[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<wall.size()) {//wall
			if (x==wall[i].getLocationX() && y==wall[i].getLocationY()) {
				toReturn=false;
			}
			i++;
		}
		return toReturn;
	}
	
	bool Board::isAWallInThisCase(int x, int y) {
		bool toReturn=false;
		for (unsigned int i=0; i<wall.size(); i++) {
			if (wall[i].getLocationX()==x && wall[i].getLocationY()==y) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isAFlameInThisCase(int x, int y) {
		bool toReturn=false;
		for (unsigned int i=0; i<flame.size(); i++) {
			if (flame[i].getLocationX()==x && flame[i].getLocationY()==y) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isABonusInThisCase(int x, int y) {
		bool toReturn=false;
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (bonus[i].getLocationX()==x && bonus[i].getLocationY()==y) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isAMineInThisCase(int x, int y) {
		bool toReturn=false;
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==x && mine[i].getLocationY()==y) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	int Board::nbSurvivant() {
		int toReturn=0;
		for (unsigned int i=0; i<player.size(); i++) {
			if (player[i].getAlive()) {
				toReturn++;
			}
		}
		return toReturn;
	}
	
	int Board::getIdSurvivant() {
		int toReturn;
		unsigned int cpt;
		if (nbSurvivant()==1) {
			toReturn=1;
			while (cpt< player.size() && !player[cpt].getAlive()) {
				cpt++;
				toReturn++;
			}
		} else {
			toReturn=0;
		}
		return toReturn;
	}
	
	void Board::applyBonus(int pl, Bonus b) {
		player[pl].addBonus(b);
	}
	
	void Board::effectuerDecalage(int nbSecondes) {
		for (unsigned int i=0; i<this->flame.size(); i++) {
			this->flame[i].decalerDebutFlame(nbSecondes);
		}
		for (unsigned int i=0; i<this->bomb.size(); i++) {
			this->bomb[i].decalerExplosion(nbSecondes);
		}
	}
	
	void Board::explodeBomb(int x, int y) {
		for (unsigned int i=0; i<bomb.size(); i++) {
			if (bomb[i].getLocationX()==x && bomb[i].getLocationY()==y) {
				explodeBomb(i);
			}
		}
	}
	
	void Board::explodeBomb(unsigned int indice) {
		generateFlame(bomb[indice].getLocationX(),bomb[indice].getLocationY(),bomb[indice].getRange(),bomb[indice].getTimeOfExplosion()+DUREEFLAMME);
		bomb.erase(bomb.begin()+indice);
	}
	
	void Board::explodeMine(int x, int y, int date) {
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==x && mine[i].getLocationY()==y) {
				explodeMine(i,date);
			}
		}
	}
	
	void Board::explodeMine(unsigned int indice, int date) {
		generateFlame(mine[indice].getLocationX(),mine[indice].getLocationY(),mine[indice].getRange(),date+DUREEFLAMME);
		mine.erase(mine.begin()+indice);
	}
	
	void Board::generateFlame(int origineX, int origineY, int range, int date) {
		addFlame(Flame(Board::caseToPixel(origineX),Board::caseToPixel(origineY),ORIENTATION_UP,ORIGIN,date));
		int x;
		int y;
		
		//propagation vers la droite
		x=origineX+1;
		y=origineY;
		while (!isAWallInThisCase(x,y) && x-origineX<range && x<18) { 
			addFlame(Flame(x,y,ORIENTATION_RIGHT,MIDDLE,date));
			x=x+1;
		}
		if (x==origineX+range && !isAWallInThisCase(x,y) && x<18) {
			addFlame(Flame(x,y,ORIENTATION_RIGHT,END,date));
		}
		
		//propagation vers la gauche
		x=origineX-1;
		y=origineY;
		while (!isAWallInThisCase(x,y) && origineX-x<range && x>0) { 
			addFlame(Flame(x,y,ORIENTATION_LEFT,MIDDLE,date));
			x=x-1;
		}
		if (x==origineX-range && !isAWallInThisCase(x,y) && x>0) {
			addFlame(Flame(x,y,ORIENTATION_LEFT,END,date));
		}
		
		//propagation vers le haut
		x=origineX;
		y=origineY-1;
		while (!isAWallInThisCase(x,y) && origineY-y<range && y>0) {
			addFlame(Flame(x,y,ORIENTATION_UP,MIDDLE,date));
			y=y-1;
		}
		if (y==origineY-range && !isAWallInThisCase(x,y) && y>0) {
			addFlame(Flame(x,y,ORIENTATION_UP,END,date));
		}
		
		//propagation vers le bas
		x=origineX;
		y=origineY+1;
		while (!isAWallInThisCase(x,y) && y-origineY<range && y<13) {
			addFlame(Flame(x,y,ORIENTATION_DOWN,MIDDLE,date));
			y=y+1;
		}
		if (y==origineY+range && !isAWallInThisCase(x,y) && y<13) {
			addFlame(Flame(x,y,ORIENTATION_DOWN,END,date));
		}
	}
	
	Bonus Board::getBonusByCoord(int x, int y) {//on suppose que le bonus existe
		return bonus[getIndiceBonus(x,y)];
	}
	
	unsigned int Board::getIndiceBonus(int x, int y) {
		unsigned int toReturn;
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (bonus[i].getLocationX()==x && bonus[i].getLocationY()==y) {
				toReturn=i;
			}
		}
		return toReturn;
	}
	
	unsigned int Board::getIndiceMineByCoord(int x, int y) {
		unsigned int toReturn;
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==x && mine[i].getLocationY()==y) {
				toReturn=i;
			}
		}
		return toReturn;
	}
	
	void Board::checkPosition(int date) {
		//faire la vérification des toutes les positions
		//faire la vérification des joueurs (flammes, bonus)
		for (unsigned int i=0; i<player.size(); i++) {
			int x = cranToCase(player[i].getLocationX());
			int y = cranToCase(player[i].getLocationY());

			if (isAFlameInThisCase(x,y)) {
				player[i].killPlayer();
			}
			if (isABonusInThisCase(x,y)) {
				//ajout du bonus au joueur
				player[i].addBonus(getBonusByCoord(x,y));
				//suppression du bonus sur la carte
				bonus.erase(bonus.begin()+getIndiceBonus(x,y));
			}
			if (isAMineInThisCase(x,y)) {
				int indiceMine = getIndiceMineByCoord(x,y);
				//création de la flamme
				generateFlame(mine[indiceMine].getLocationX(),mine[indiceMine].getLocationY(),mine[indiceMine].getRange(),date+DUREEFLAMME);
				//suppression dans la liste des bombes
				mine.erase(mine.begin()+indiceMine);
			}
		}
		//faire la vérification des caisses (flammes)
		for (unsigned int i=0; i<box.size(); i++) {
			if (isAFlameInThisCase(box[i].getLocationX(),box[i].getLocationY())) {
				box.erase(box.begin()+i);
			}
		}
		//faire la vérification des bonus (flammes)
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (isAFlameInThisCase(bonus[i].getLocationX(),bonus[i].getLocationY())) {
				bonus[i].setVisible();
			}
		}
		//faire la vérification des bombes (flamme qui déclenche les autres)
		for (unsigned int i=0; i<bomb.size(); i++) {
			if (isAFlameInThisCase(bomb[i].getLocationX(),bomb[i].getLocationY())) {
				explodeBomb(bomb[i].getLocationX(),bomb[i].getLocationY());
			}
		}
	}
	
	void Board::removeObseleteFlame(int date) {
		for (unsigned int i=0; i<flame.size(); i++) {
			if (flame[i].getDateDebutFlame()+DUREEFLAMME<date) {
				flame.erase(flame.begin()+i);
			}
		}
	}
	
	void Board::explodeAllBomb(int date) {
		for (unsigned int i =0; i<bomb.size(); i++) {
			if (bomb[i].getTimeOfExplosion()>date) {
				explodeBomb(i);
			}
		}
	}
	
	/*static EGameBonus intToEGameBonus(int i) {
		EGameBonus toReturn;
		switch (i) {
			case 0:
				toReturn=SPEEDUP;
				break;
				
			case 1:
				toReturn=SPEEDDOWN;
				break;
				
			case 2:
				toReturn=BOMBLINE;
				break;
				
			case 3:
				toReturn=DETONATOR;
				break;
				
			case 4:
				toReturn=BOMBUP;
				break;
				
			case 5:
				toReturn=BOMBDOWN;
				break;
				
			case 6:
				toReturn=RANGEUP;
				break;
				
			case 7:
				toReturn=RANGEDOWN;
				break;
				
			case 8:
				toReturn=RANGEUPMAX;
				break;
				
			case 9:
				toReturn=MINE;
				break;
				
			case 10:
				toReturn=INFINITYBOMB;
				break;
				
			case 11:
				toReturn=ATOMICBOMB;
				break;
				
			case 12:
				toReturn=CRANE;
				break;
				
			case 13:
				toReturn=HELL;
				break;
				
			case 14:
				toReturn=CONFUSION;
				break;
				
			case 15:
				toReturn=SPASME;
				break;
				
			case 16:
				toReturn=DILATATION;
				break;
				
			case 17:
				toReturn=RAGE;
				break;
				
			default:
				//erreur
				break;
		}
	}*/
	
}