#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include <SFML/Vector2.hpp>

namespace PolyBomber;

/*!
 * \class Player
 * \brief Classe Player
 */
class Player {
  protected :
    int id;			/*! Identifiant du joueur */
    int speed;			/*! Vitesse du joueur */
    //cpacity
    EOrientation orientation;	/*! Orientation du joueur */
    int step;			/*!  */
    sf::Vector2<int> location;	/*! Position du joueur */
    Board board;		/*! Plateau de jeu auquel appartient le joueur */
    
  public :
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
};

#endif