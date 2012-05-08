#ifndef PLAYER_HEADER
#define PLAYER_HEADER

/*!
 * \file Player.hpp
 * \brief Classe Player
 * \author Simon ROUSSEAU
 */

#include <SFML/System/Vector2.hpp>

namespace PolyBomber {
  /*!
  * \class Player
  * \brief Classe Player
  */
  class Player {
    protected :
      int id;			/*! Identifiant du joueur */
      int speed;			/*! Vitesse du joueur */
      int capacity;		/*! Nombre de bombes qu'un joueur peut poser */
      EOrientation orientation;	/*! Orientation du joueur */
      int step;			/*! Longueur d'un déplacement du joueur */
      sf::Vector2<int> location;	/*! Position du joueur */
      Board board;		/*! Plateau de jeu auquel appartient le joueur */
      Place place;		/*!  */
      Vector<Bonus> bonus;	/*! Listes des bonus du joueur */
      
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
      
      /*!
      * \brief Méthode renvoyant le nombre de bombe qu'une joueur peut poser
      *
      * \return retourne le nombre de bombe que le joueur peut encore poser
      */
      int getCapacity(){return this.capacity;}
      
      /*!
      * \brief Méthode qui augmente le nombre de bombes disponibles pour le joueur
      * Déclenchée lorsqu'une bombe du joueur explose ou bien que le joueur prend un bonus augmentant le nombre de bombes que le joueut peut poser.
      */
      void increaseCapacity(){this.capacity++;}
      
      /*!
      * \brief Méthode qui diminue le nombre de bombes disponibles pour le joueur
      * Déclenchée lorsque le joueur pose une bombe ou bien lorsque le joueur prend un bonus qui diminue le nombre de bombes que le joueur peut poser.
      */
      void decreaseCapacity(){this.capacity--;}
  };
}

#endif
