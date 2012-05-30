/*!
 * \file Board.cpp
 * \brief Implementation de la classe Board
 * \author Simon ROUSSEAU
 */


/** Includes **/
// Bibliotheques standards
#include <ctime>
#include <cstdlib>

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
	
	void Board::generateFlameHorizontal(int x, int y, int range, int date) {
		for (int i=1; i<range; i++) {
			if (x+i%2==0 && y%2==0) {
				flame.push_back(Flame(x+i,y,ORIENTATION_RIGHT,ORIGIN,date+DUREEFLAMME));
				flame.push_back(Flame(x-i,y,ORIENTATION_LEFT,ORIGIN,date+DUREEFLAMME));
			} else {
				flame.push_back(Flame(x+i,y,ORIENTATION_RIGHT,MIDDLE,date+DUREEFLAMME));
				flame.push_back(Flame(x-i,y,ORIENTATION_LEFT,MIDDLE,date+DUREEFLAMME));
			}
		}
		flame.push_back(Flame(x+range,y,ORIENTATION_RIGHT,END,date+DUREEFLAMME));
		flame.push_back(Flame(x-range,y,ORIENTATION_LEFT,END,date+DUREEFLAMME));
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
	
	void Board::actionToucheHaut(int player) {//TODO : faire la vérification si le déplacement se fait dans la meme case nécessaire ?
		Player pl = getPlayerById(player);
		int x = pl.getLocationX();//position en cran
		int y = pl.getLocationY();//position en cran
		int xCase = cranToCase(x);
		int yCase = cranToCase(y);
		EOrientation orient;
		if (pl.getInfection()==1) {
			//inversion des touches directionnelles
			if (caseIsFree(xCase,yCase+1)) {
				if (distanceDesAutresJoueursValide(player,x,y+pl.getSpeed())) {
					pl.move(x,y+pl.getSpeed());
					if (y+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeHorizontal();
					}
				}
			} else {
				if (y+pl.getSpeed()%5<=2) {
					pl.move(x,y+pl.getSpeed());
					if (y+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeHorizontal();
					}
				} else {
					pl.centrerPlayerSurAxeVertical();
				}
				
			}
			orient=ORIENTATION_DOWN;
		} else {
			//test si la case suivante est libre
			if (caseIsFree(xCase,yCase-1)) {
				if (distanceDesAutresJoueursValide(player,x,y-pl.getSpeed())) {
					pl.move(x,y-pl.getSpeed());
					if (y-pl.getSpeed()%5!=2) {//si on est pas centré sur la case, alors la position est corrigée
						pl.centrerPlayerSurAxeHorizontal();
					}
				}
			} else {
				if (y-pl.getSpeed()%5>=2) {
					pl.move(x,y-pl.getSpeed());
					if (y-pl.getSpeed()%5!=2) {//si on est pas centré sur la case, alors la position est corrigée
						pl.centrerPlayerSurAxeHorizontal();
					}
				} else {
					pl.centrerPlayerSurAxeVertical();
				}
			}
			orient=ORIENTATION_UP;
		}
		pl.incrementStep();
		pl.setOrientation(orient);
	}
	
	void Board::actionToucheBas(int player) {
		Player pl = getPlayerById(player);
		EOrientation orient;
		int x = pl.getLocationX();//position en cran
		int y = pl.getLocationY();//position en cran
		int xCase = cranToCase(x);
		int yCase = cranToCase(y);
		if (pl.getInfection()==1) {
			//inversion des touches directionnelles
			if (caseIsFree(xCase,yCase-1)) {
				if (distanceDesAutresJoueursValide(player,x,y-pl.getSpeed())) {
					pl.move(x,y-pl.getSpeed());
					if (y-pl.getSpeed()%5!=2) {//si on est pas centré sur la case, alors la position est corrigée
						pl.centrerPlayerSurAxeHorizontal();
					}
				}
			} else {
				if (y-pl.getSpeed()%5>=2) {
					pl.move(x,y-pl.getSpeed());
					if (y-pl.getSpeed()%5!=2) {//si on est pas centré sur la case, alors la position est corrigée
						pl.centrerPlayerSurAxeHorizontal();
					}
				} else {
					pl.centrerPlayerSurAxeVertical();
				}
			}
			orient=ORIENTATION_UP;
		} else {
			//test si la case suivante est libre
			if (caseIsFree(xCase,yCase+1)) {
				if (distanceDesAutresJoueursValide(player,x,y+pl.getSpeed())) {
					pl.move(x,y+pl.getSpeed());
					if (y+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeHorizontal();
					}
				}
			} else {
				if (y+pl.getSpeed()%5<=2) {
					pl.move(x,y+pl.getSpeed());
					if (y+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeHorizontal();
					}
				} else {
					pl.centrerPlayerSurAxeVertical();
				}
				
			}
			orient=ORIENTATION_DOWN;
		}
		pl.incrementStep();
		pl.setOrientation(orient);
	}
	
	void Board::actionToucheGauche(int player) {
		Player pl = getPlayerById(player);
		EOrientation orient;
		int x = pl.getLocationX();//position en cran
		int y = pl.getLocationY();//position en cran
		int xCase = cranToCase(x);
		int yCase = cranToCase(y);
		if (pl.getInfection()==1) {
			//inversion des touches directionnelles
			if (caseIsFree(xCase+1,yCase)) {
				if (distanceDesAutresJoueursValide(player,x+pl.getSpeed(),y)) {
					pl.move(x+pl.getSpeed(),y);
					if (x+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				}
			} else {
				if (x+pl.getSpeed()%5>=2) {
					pl.move(x+pl.getSpeed(),y);
					if (x+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				} else {
					pl.centrerPlayerSurAxeHorizontal();
				}
			}
			orient=ORIENTATION_RIGHT;
		} else {
			//test si la case suivante est libre
			if (caseIsFree(xCase-1,yCase)) {
				if (distanceDesAutresJoueursValide(player,x-pl.getSpeed(),y)) {
					pl.move(x-pl.getSpeed(),y);
					if (x-pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				}
			} else {
				if (x-pl.getSpeed()%5<=2) {
					pl.move(x-pl.getSpeed(),y);
					if (x-pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				} else {
					pl.centrerPlayerSurAxeHorizontal();
				}
			}
			orient=ORIENTATION_LEFT;
		}
		pl.incrementStep();
		pl.setOrientation(orient);
	}
	
	void Board::actionToucheDroite(int player) {
		Player pl = getPlayerById(player);
		EOrientation orient;
		int x = pl.getLocationX();//position en cran
		int y = pl.getLocationY();//position en cran
		int xCase = cranToCase(x);
		int yCase = cranToCase(y);
		if (pl.getInfection()==1) {
			//inversion des touches directionnelles
			if (caseIsFree(xCase-1,yCase)) {
				if (distanceDesAutresJoueursValide(player,x-pl.getSpeed(),y)) {
					pl.move(x-pl.getSpeed(),y);
					if (x-pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				}
			} else {
				if (x-pl.getSpeed()%5<=2) {
					pl.move(x-pl.getSpeed(),y);
					if (x-pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				} else {
					pl.centrerPlayerSurAxeHorizontal();
				}
			}
			orient=ORIENTATION_LEFT;
		} else {
			//test si la case suivante est libre
			if (caseIsFree(xCase+1,yCase)) {
				if (distanceDesAutresJoueursValide(player,x+pl.getSpeed(),y)) {
					pl.move(x+pl.getSpeed(),y);
					if (x+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				}
			} else {
				if (x+pl.getSpeed()%5>=2) {
					pl.move(x+pl.getSpeed(),y);
					if (x+pl.getSpeed()%5!=2) {
						pl.centrerPlayerSurAxeVertical();
					}
				} else {
					pl.centrerPlayerSurAxeHorizontal();
				}
			}
			orient=ORIENTATION_RIGHT;
		}
		pl.incrementStep();
		pl.setOrientation(orient);
	}
	
	void Board::actionToucheAction1(int player, int date) {
		Player pl = getPlayerById(player);
		if (pl.getCapacity()>0) {//le joueur peut poser une bombe
			bomb.push_back(Bomb(date,pl));
			pl.decrementCapacity();
		}
	}
	
	void Board::actionToucheAction2(int player, int date) {
		Player pl = getPlayerById(player);
		EGameBonus bon = pl.getFirstBombBonus();
		if (pl.getBombBonus().size()>0) {
			//utiliser le 1er bonus puis le supprimer de la liste
			if (bon==INFINITYBOMB) {
				bomb.push_back(Bomb(date,pl,1));
			} else if (bon==ATOMICBOMB) {
				bomb.push_back(Bomb(date,pl,2));
			} else { //bombline
				EOrientation orient = pl.getOrientation();
				int x=cranToCase(pl.getLocationX());
				int y=cranToCase(pl.getLocationY());
				switch (orient) {
					case ORIENTATION_UP:
						bomb.push_back(Bomb(date,pl,x,y));
						pl.decrementCapacity();
						y=y-1;
						while (pl.getCapacity()>0 && caseIsFree(x,y)) {
							bomb.push_back(Bomb(date,pl,x,y));
							pl.decrementCapacity();
							y=y-1;
						}
						break;
						
					case ORIENTATION_DOWN:
						bomb.push_back(Bomb(date,pl,x,y));
						pl.decrementCapacity();
						y=y+1;
						while (pl.getCapacity()>0 && caseIsFree(x,y)) {
							bomb.push_back(Bomb(date,pl,x,y));
							pl.decrementCapacity();
							y=y+1;
						}
						break;
						
					case ORIENTATION_LEFT:
						bomb.push_back(Bomb(date,pl,x,y));
						pl.decrementCapacity();
						x=x-1;
						while (pl.getCapacity()>0 && caseIsFree(x,y)) {
							bomb.push_back(Bomb(date,pl,x,y));
							pl.decrementCapacity();
							x=x-1;
						}
						break;
						
					case ORIENTATION_RIGHT:
						bomb.push_back(Bomb(date,pl,x,y));
						pl.decrementCapacity();
						x=x+1;
						while (pl.getCapacity()>0 && caseIsFree(x,y)) {
							bomb.push_back(Bomb(date,pl,x,y));
							pl.decrementCapacity();
							x=x+1;
						}
						break;
						
					default:
						break;
				}
			}
			bomb.erase(bomb.begin());
		} else {
			if (pl.getDetonator()) {
				bool remoteBombDejaPosee=false;
				int indiceRemoteBomb;
				for (unsigned int i=0;i<remoteBomb.size();i++) {
					if (remoteBomb[i].getPlayer()==player) {
						remoteBombDejaPosee=true;
						indiceRemoteBomb=i;
					}
				}
				if (remoteBombDejaPosee) {
					explodeRemoteBomb(indiceRemoteBomb, date);
				} else {
					remoteBomb.push_back(RemoteBomb(pl));
				}
			}
		}
	}
	
	void Board::removeBox(int i) {
		box.erase(box.begin()+i);
	}
	
	bool Board::caseIsFreeInitialisation(int x, int y) {
		bool toReturn = true;
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
		unsigned int i=0;
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
			if (x==cranToCase(player[i].getLocationX()) && y==cranToCase(player[i].getLocationY())) {
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
		int nbSurv = nbSurvivant();
		if (nbSurv==1) {
			toReturn=1;
			while (cpt< player.size() && !player[cpt].getAlive()) {
				cpt++;
				toReturn++;
			}
		} else if (nbSurv==0) {
			toReturn=-1;
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
		int type=bomb[indice].getType();
		if (type==0 || type==3) {//TODO : vérifier l'utilité de "type==3"
			generateFlame(bomb[indice].getLocationX(),bomb[indice].getLocationY(),bomb[indice].getRange(),bomb[indice].getTimeOfExplosion()+DUREEFLAMME);
			if (type==0) {
				int pl = bomb[indice].getPlayer();
				player[pl].incrementCapacity();
			}
		} else if (type==1) {
			generateFlameInfinityBomb(indice,bomb[indice].getTimeOfExplosion()+DUREEFLAMME);
		} else if (type==2) {
			generateFlameAtomicBomb(indice,bomb[indice].getTimeOfExplosion()+DUREEFLAMME);
		}
		bomb.erase(bomb.begin()+indice);
	}
	
	void Board::explodeRemoteBomb(unsigned int indice, int date) {
		generateFlame(remoteBomb[indice].getLocationX(),remoteBomb[indice].getLocationY(),remoteBomb[indice].getRange(),date+DUREEFLAMME);
		remoteBomb.erase(remoteBomb.begin()+indice);
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
		addFlame(Flame(origineX,origineY,ORIENTATION_UP,ORIGIN,date));
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
	
	void Board::generateFlameInfinityBomb(unsigned int indice, int date) {
		generateFlame(bomb[indice].getLocationX(),bomb[indice].getLocationY(),19,date);
	}
	
	void Board::generateFlameAtomicBomb(unsigned int indice, int date) {
		int x = bomb[indice].getLocationX();
		int y = bomb[indice].getLocationY();
		int range = bomb[indice].getRange();
		
		generateFlame(x,y,range,date);
		
		for (int i=1; i<range; i++) {//génération de toutes les flammes horizontales
			generateFlameHorizontal(x+i,y,range-i,date);
			generateFlameHorizontal(x-i,y,range-i,date);
		}
		
		bomb.erase(bomb.begin()+indice);
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
		//fait la vérification des joueurs (flammes, bonus)
		for (unsigned int i=0; i<player.size(); i++) {
			int x = cranToCase(player[i].getLocationX());
			int y = cranToCase(player[i].getLocationY());
			
			if (isAFlameInThisCase(x,y)) {
				player[i].killPlayer();
			}
			if (isABonusInThisCase(x,y)) {
				Bonus bon = getBonusByCoord(x,y);
				if (bon.getType()==HELL) {
					int alea=rand()%4;
					for (unsigned int j=0;j<player.size();j++) {
						switch(alea) {
							case 0 :
								player[j].addBonus(Bonus(player[j].getLocationX(),player[j].getLocationY(),CONFUSION,true));
								break;
								
							case 1 :
								player[j].addBonus(Bonus(player[j].getLocationX(),player[j].getLocationY(),SPASME,true));
								break;
								
							case 2 :
								player[j].addBonus(Bonus(player[j].getLocationX(),player[j].getLocationY(),DILATATION,true));
								break;
								
							case 3 :
								player[j].addBonus(Bonus(player[j].getLocationX(),player[j].getLocationY(),RAGE,true));
								break;
								
							default :
								break;
						}
					}
				} else if (bon.getType()==CRANE) {
					int alea=rand()%4;
					switch(alea) {
						case 0 :
							player[i].addBonus(Bonus(player[i].getLocationX(),player[i].getLocationY(),CONFUSION,true));
							break;
							
						case 1 :
							player[i].addBonus(Bonus(player[i].getLocationX(),player[i].getLocationY(),SPASME,true));
							break;
							
						case 2 :
							player[i].addBonus(Bonus(player[i].getLocationX(),player[i].getLocationY(),DILATATION,true));
							break;
							
						case 3 :
							player[i].addBonus(Bonus(player[i].getLocationX(),player[i].getLocationY(),RAGE,true));
							break;
							
						default :
							break;
					}
				} else {
					
				}
			}
			if (isAMineInThisCase(x,y)) {
				int indiceMine = getIndiceMineByCoord(x,y);
				//création de la flamme
				generateFlame(mine[indiceMine].getLocationX(),mine[indiceMine].getLocationY(),mine[indiceMine].getRange(),date+DUREEFLAMME);
				//suppression dans la liste des bombes
				mine.erase(mine.begin()+indiceMine);
			}
		}
		//fait la vérification des caisses (flammes)
		for (unsigned int i=0; i<box.size(); i++) {
			if (isAFlameInThisCase(box[i].getLocationX(),box[i].getLocationY())) {
				box.erase(box.begin()+i);
			}
		}
		//fait la vérification des bonus (flammes)
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (isAFlameInThisCase(bonus[i].getLocationX(),bonus[i].getLocationY())) {
				bonus[i].setVisible();
			}
		}
		//fait la vérification des bombes (flamme qui déclenche les autres)
		for (unsigned int i=0; i<bomb.size(); i++) {
			if (isAFlameInThisCase(bomb[i].getLocationX(),bomb[i].getLocationY())) {
				explodeBomb(bomb[i].getLocationX(),bomb[i].getLocationY());
			}
		}
	}
	
	void Board::makeInfectionAction(int date) {
		for (unsigned int i=0; i<player.size(); i++) {
			if (player[i].getInfection()==2) {// spasme : effectue un mouvement aléatoire
				bool movePossible=false;
				int random;
				int x, y;
				while (!movePossible) {
					random=rand()%8;
					switch (random) {
						case 0://en haut à gauche
							if (caseIsFree(cranToCase(x)-1,cranToCase(y)-1)) {
								x=x-1;
								y=y-1;
								movePossible=true;
							}
							break;
							
						case 1://en haut
							if (caseIsFree(cranToCase(x),cranToCase(y)-1)) {
								x=x;
								y=y-1;
								movePossible=true;
							}
							break;
							
						case 2://en haut à droite
							if (caseIsFree(cranToCase(x)+1,cranToCase(y)-1)) {
								x=x+1;
								y=y-1;
								movePossible=true;
							}
							break;
							
						case 3://a droite
							if (caseIsFree(cranToCase(x)+1,cranToCase(y))) {
								x=x+1;
								y=y;
								movePossible=true;
							}
							break;
							
						case 4://en bas à droite
							if (caseIsFree(cranToCase(x)+1,cranToCase(y)+1)) {
								x=x+1;
								y=y+1;
								movePossible=true;
							}
							break;
							
						case 5://en bas
							if (caseIsFree(cranToCase(x),cranToCase(y)+1)) {
								x=x;
								y=y+1;
								movePossible=true;
							}
							break;
							
						case 6://en bas à gauche
							if (caseIsFree(cranToCase(x)-1,cranToCase(y)+1)) {
								x=x-1;
								y=y+1;
								movePossible=true;
							}
							break;
							
						case 7://a gauche
							if (caseIsFree(cranToCase(x)-1,cranToCase(y))) {
								x=x-1;
								y=y;
								movePossible=true;
							}
							break;
							
						default:
							break;
					}
				}
				player[i].move(x,y);
			} else if (player[i].getInfection()==4) {//rage : pose des bombes
				bomb.push_back(Bomb(date,player[i]));
				player[i].decrementCapacity();
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
	
	bool Board::distanceDesAutresJoueursValide(unsigned int pl, int x, int y) {//x et y sont en crans
		bool toReturn = true;
		int x2;
		int y2;
		for (unsigned int i=0; i<player.size(); i++) {
			if (i!=pl) {
				x2=player[i].getLocationX();
				y2=player[i].getLocationY();
				if (x2<x) {
					if (y2<y) {
						if (x-x2<DISTANCEMINBETWEENTWOPLAYERS && y-y2<DISTANCEMINBETWEENTWOPLAYERS) {
							toReturn=false;
						}
					} else {
						if (x-x2<DISTANCEMINBETWEENTWOPLAYERS && y2-y<DISTANCEMINBETWEENTWOPLAYERS) {
							toReturn=false;
						}
					}
				} else {
					if (y2<y) {
						if (x2-x<DISTANCEMINBETWEENTWOPLAYERS && y-y2<DISTANCEMINBETWEENTWOPLAYERS) {
							toReturn=false;
						}
					} else {
						if (x2-x<DISTANCEMINBETWEENTWOPLAYERS && y2-y<DISTANCEMINBETWEENTWOPLAYERS) {
							toReturn=false;
						}
					}
				}
			}
		}
		return toReturn;
	}
	
	void Board::resetConfig() {
		bonus.clear();
		flame.clear();
		box.clear();
		player.clear();
		bomb.clear();
		remoteBomb.clear();
		mine.clear();
		wall.clear();
	}
}