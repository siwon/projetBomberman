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
#include "gameEngine/Board.hpp"


namespace PolyBomber {
	
	Board::Board() {
		this->bonus=std::vector<Bonus>();
		this->flame=std::vector<Flame>();
		this->box=std::vector<Box>();
		this->player=std::vector<Player>();
		this->remoteBomb=std::vector<RemoteBomb>();
		this->bomb=std::vector<Bomb>();
		this->mine=std::vector<Mine>();
		this->wall=std::vector<Wall>();
	}
	
	Board::Board(const Board& b) {
		this->bonus=std::vector<Bonus>();
		this->flame=std::vector<Flame>();
		this->box=std::vector<Box>();
		this->player=std::vector<Player>();
		this->remoteBomb=std::vector<RemoteBomb>();
		this->bomb=std::vector<Bomb>();
		this->mine=std::vector<Mine>();
		this->wall=std::vector<Wall>();
	}
	
	Board::~Board() {
		unsigned int i;
		
		//suppression de tous les objets contenus
		for (i=0; i<this->bonus.size(); i++) {
			this->bonus[i].~Bonus();
		}
		for (i=0; i<this->flame.size(); i++) {
			this->flame[i].~Flame();
		}
		for (i=0; i<this->box.size(); i++) {
			this->box[i].~Box();
		}
		for (i=0; i<this->player.size(); i++) {
			this->player[i].~Player();
		}
		for (i=0; i<this->remoteBomb.size(); i++) {
			this->remoteBomb[i].~RemoteBomb();
		}
		for (i=0; i<this->bomb.size(); i++) {
			this->bomb[i].~Bomb();
		}
		for (i=0; i<this->mine.size(); i++) {
			this->mine[i].~Mine();
		}
		for (i=0; i<this->wall.size(); i++) {
			this->wall[i].~Wall();
		}
		
		//suppression de tous les conteneurs
		this->bonus.~vector();
		this->flame.~vector();
		this->box.~vector();
		this->player.~vector();
		this->remoteBomb.~vector();
		this->bomb.~vector();
		this->mine.~vector();
		this->wall.~vector();
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
		
		toReturn.boxes=std::vector<sf::Vector2<int> >();
		toReturn.bonus=std::vector<SBonus>();
		toReturn.explosives=std::vector<SExplosive>();
		toReturn.players=std::vector<SPlayer>();
		toReturn.flames=std::vector<SFlame>();
		
		for (unsigned int i=0; i<bonus.size(); i++) {//bonus
			if (bonus[i].isVisible()) {
				SBonus b;
				b.coords=sf::Vector2<int>(pixelToCase(bonus[i].getLocationX()),pixelToCase(bonus[i].getLocationY()));
				b.type=bonus[i].getType();
				toReturn.bonus.push_back(b);
			} else {
				toReturn.boxes.push_back(sf::Vector2<int>(pixelToCase(bonus[i].getLocationX()),pixelToCase(bonus[i].getLocationY())));
			}
		}
		
		for (unsigned int i=0; i<flame.size(); i++) {//flame
			SFlame f;
			f.coords=sf::Vector2<int>(pixelToCase(flame[i].getLocationX()),pixelToCase(flame[i].getLocationY()));
			f.orientation=flame[i].getOrientation();
			f.step=flame[i].getStep();
			toReturn.flames.push_back(f);
		}
		
		for (unsigned int i=0; i<box.size(); i++) {//box
			toReturn.boxes.push_back(sf::Vector2<int>(pixelToCase(box[i].getLocationX()),pixelToCase(box[i].getLocationY())));
		}
		
		for (unsigned int i=0; i<player.size(); i++) {//player
			SPlayer p;
			p.coords=sf::Vector2<int>(player[i].getLocationX(),player[i].getLocationY());
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
			e.coords=sf::Vector2<int>(pixelToCase(bomb[i].getLocationX()),pixelToCase(bomb[i].getLocationY()));
			e.type=EXPLOSIVE_BOMB;
			toReturn.explosives.push_back(e);
		}
		
		for (unsigned int i=0; i<bomb.size(); i++) {//remoteBomb
			SExplosive e;
			e.coords=sf::Vector2<int>(pixelToCase(bomb[i].getLocationX()),pixelToCase(bomb[i].getLocationY()));
			e.type=EXPLOSIVE_REMOTE;
			toReturn.explosives.push_back(e);
		}
		
		for (unsigned int i=0; i<mine.size(); i++) {//mine
			SExplosive e;
			e.coords=sf::Vector2<int>(pixelToCase(mine[i].getLocationX()),pixelToCase(mine[i].getLocationY()));
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
	
	bool Board::caseIsFreeInitialisation(float x, float y) {
		bool toReturn;
		//test si c'est une coordonnee reservee
		if ((x==caseToPixel(0)&&y==caseToPixel(1))||(x==caseToPixel(1)&&y==caseToPixel(0))||(x==caseToPixel(17)&&y==caseToPixel(0))||(x==caseToPixel(18)&&y==caseToPixel(1))||(x==caseToPixel(18)&&y==caseToPixel(11))||(x==caseToPixel(17)&&y==caseToPixel(12))||(x==caseToPixel(0)&&y==caseToPixel(11))||(x==caseToPixel(1)&&y==caseToPixel(12))||(x==caseToPixel(8)&&y==caseToPixel(11))||(x==caseToPixel(8)&&y==caseToPixel(12))||(x==caseToPixel(10)&&y==caseToPixel(12))||(x==caseToPixel(10)&&y==caseToPixel(11))) {
			toReturn=false;
		} else {
			toReturn=caseIsFree(x,y);
		}
		return toReturn;
	}
	
	bool Board::caseIsFree(float x, float y) {
		bool toReturn = true;
		unsigned int i=0;;
		while (toReturn && i<bonus.size()) {//bonus
			if (pixelToCase(x)==pixelToCase(bonus[i].getLocationX()) && pixelToCase(y)==pixelToCase(bonus[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<flame.size()) {//flame
			if (pixelToCase(x)==pixelToCase(flame[i].getLocationX()) && pixelToCase(y)==pixelToCase(flame[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<box.size()) {//box
			if (pixelToCase(x)==pixelToCase(box[i].getLocationX()) && pixelToCase(y)==pixelToCase(box[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<player.size()) {//player
			if (pixelToCase(x)==pixelToCase(player[i].getLocationX()) && pixelToCase(y)==pixelToCase(player[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<bomb.size()) {//bomb
			if (pixelToCase(x)==pixelToCase(bomb[i].getLocationX()) && pixelToCase(y)==pixelToCase(bomb[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<remoteBomb.size()) {//remote
			if (pixelToCase(x)==pixelToCase(remoteBomb[i].getLocationX()) && pixelToCase(y)==pixelToCase(remoteBomb[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		i=0;
		while (toReturn && i<wall.size()) {//wall
			if (pixelToCase(x)==pixelToCase(wall[i].getLocationX()) && pixelToCase(y)==pixelToCase(wall[i].getLocationY())) {
				toReturn=false;
			}
			i++;
		}
		return toReturn;
	}
	
	bool Board::isAWallInThisCase(int x, int y) {
		bool toReturn=false;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<wall.size(); i++) {
			if (wall[i].getLocationX()==xPixel && wall[i].getLocationY()==yPixel) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isAFlameInThisCase(int x, int y) {
		bool toReturn=false;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<flame.size(); i++) {
			if (flame[i].getLocationX()==xPixel && flame[i].getLocationY()==yPixel) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isABonusInThisCase(int x, int y) {
		bool toReturn=false;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (bonus[i].getLocationX()==xPixel && bonus[i].getLocationY()==yPixel) {
				toReturn=true;
			}
		}
		return toReturn;
	}
	
	bool Board::isAMineInThisCase(int x, int y) {
		bool toReturn=false;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==xPixel && mine[i].getLocationY()==yPixel) {
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
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<bomb.size(); i++) {
			if (bomb[i].getLocationX()==xPixel && bomb[i].getLocationY()==yPixel) {
				explodeBomb(i);
			}
		}
	}
	
	void Board::explodeBomb(unsigned int indice) {
		generateFlame(pixelToCase(bomb[indice].getLocationX()),pixelToCase(bomb[indice].getLocationY()),bomb[indice].getRange(),bomb[indice].getTimeOfExplosion()+DUREEFLAMME);
		//bomb[indice].~Bomb();
		bomb.erase(bomb.begin()+indice);
	}
	
	void Board::explodeMine(int x, int y, int date) {
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==xPixel && mine[i].getLocationY()==yPixel) {
				explodeMine(i,date);
			}
		}
	}
	
	void Board::explodeMine(unsigned int indice, int date) {
		generateFlame(pixelToCase(mine[indice].getLocationX()),pixelToCase(mine[indice].getLocationY()),mine[indice].getRange(),date+DUREEFLAMME);
		//mine[indice].~Mine();
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
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_RIGHT,MIDDLE,date));
			x=x+1;
		}
		if (x==origineX+range && !isAWallInThisCase(x,y) && x<18) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_RIGHT,END,date));
		}
		
		//propagation vers la gauche
		x=origineX-1;
		y=origineY;
		while (!isAWallInThisCase(x,y) && origineX-x<range && x>0) { 
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_LEFT,MIDDLE,date));
			x=x-1;
		}
		if (x==origineX-range && !isAWallInThisCase(x,y) && x>0) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_LEFT,END,date));
		}
		
		//propagation vers le haut
		x=origineX;
		y=origineY-1;
		while (!isAWallInThisCase(x,y) && origineY-y<range && y>0) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_UP,MIDDLE,date));
			y=y-1;
		}
		if (y==origineY-range && !isAWallInThisCase(x,y) && y>0) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_UP,END,date));
		}
		
		//propagation vers le bas
		x=origineX;
		y=origineY+1;
		while (!isAWallInThisCase(x,y) && y-origineY<range && y<13) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_DOWN,MIDDLE,date));
			y=y+1;
		}
		if (y==origineY+range && !isAWallInThisCase(x,y) && y<13) {
			addFlame(Flame(caseToPixel(x),caseToPixel(y),ORIENTATION_DOWN,END,date));
		}
	}
	
	Bonus Board::getBonusByCoord(int x, int y) {//on suppose que le bonus existe
		return bonus[getIndiceBonus(x,y)];
	}
	
	unsigned int Board::getIndiceBonus(int x, int y) {
		unsigned int toReturn;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (bonus[i].getLocationX()==xPixel && bonus[i].getLocationY()==yPixel) {
				toReturn=i;
			}
		}
		return toReturn;
	}
	
	unsigned int Board::getIndiceMineByCoord(int x, int y) {
		unsigned int toReturn;
		float xPixel = Board::caseToPixel(x);
		float yPixel = Board::caseToPixel(y);
		for (unsigned int i=0; i<mine.size(); i++) {
			if (mine[i].getLocationX()==xPixel && mine[i].getLocationY()==yPixel) {
				toReturn=i;
			}
		}
		return toReturn;
	}
	
	void Board::checkPosition(int date) {
		//faire la vérification des toutes les positions
		//faire la vérification des joueurs (flammes, bonus)
		for (unsigned int i=0; i<player.size(); i++) {
			if (isAFlameInThisCase(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY()))) {
				player[i].killPlayer();
			}
			if (isABonusInThisCase(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY()))) {
				//ajout du bonus au joueur
				player[i].addBonus(getBonusByCoord(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY())));
				//suppression du bonus sur la carte
				bonus.erase(bonus.begin()+getIndiceBonus(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY())));
			}
			if (isAMineInThisCase(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY()))) {
				int indiceMine = getIndiceMineByCoord(Board::pixelToCase(player[i].getLocationX()),Board::pixelToCase(player[i].getLocationY()));
				//création de la flamme
				generateFlame(Board::pixelToCase(mine[indiceMine].getLocationX()),Board::pixelToCase(mine[indiceMine].getLocationY()),mine[indiceMine].getRange(),date+DUREEFLAMME);
				//suppression dans la liste des bombes
				//mine[indiceMine].~Mine();
				mine.erase(mine.begin()+indiceMine);
			}
		}
		//faire la vérification des caisses (flammes)
		for (unsigned int i=0; i<box.size(); i++) {
			if (isAFlameInThisCase(Board::pixelToCase(box[i].getLocationX()),Board::pixelToCase(box[i].getLocationY()))) {
				//box[i].~Box();
				box.erase(box.begin()+i);
			}
		}
		//faire la vérification des bonus (flammes)
		for (unsigned int i=0; i<bonus.size(); i++) {
			if (isAFlameInThisCase(Board::pixelToCase(bonus[i].getLocationX()),Board::pixelToCase(bonus[i].getLocationY()))) {
				bonus[i].setVisible();
			}
		}
		//faire la vérification des bombes (flamme qui déclenche les autres)
		for (unsigned int i=0; i<bomb.size(); i++) {
			if (isAFlameInThisCase(Board::pixelToCase(bomb[i].getLocationX()),Board::pixelToCase(bomb[i].getLocationY()))) {
				explodeBomb(Board::pixelToCase(bomb[i].getLocationX()),Board::pixelToCase(bomb[i].getLocationY()));
			}
		}
	}
	
	void Board::removeObseleteFlame(int date) {
		for (unsigned int i=0; i<flame.size(); i++) {
			if (flame[i].getDateDebutFlame()+DUREEFLAMME<date) {
				//flame[i].~Flame();
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
	
	static EGameBonus intToEGameBonus(int i) {
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
	}
	
}