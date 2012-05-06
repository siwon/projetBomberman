#ifndef GAME_ENGINE_MANAGER_HEADER
#define GAME_ENGINE_MANAGER_HEADER

/*!
 * \file GameEngineManager.hpp
 * \brief Classe de gestion du moteur de jeu
 * \author Simon Rousseau
 */

namespace PolyBomber;

/*!
 * \class ControllerManager
 * \brief Classe de gestion du moteur de jeu
 */
class GameEngineManager : public IGameEngineToNetwork {
  protected :
    Board board; /*! Objet stockant le plateau de jeu */
  public :
    
    /*!
      * \brief Applique un bonus à un joueur
      * Cette méthode permet d'applique un bonus à un joueur.
      * \param bonus : Bonus à appliquer
      * \param player : Joueur sur lequel appliquer le bonus
      */
    void applyBonus(Bonus bonus, Player player);
    
    /*!
      * \brief Déplace le joueur sur le plateau de jeu
      * 
      * \param player : Joueur sur lequel appliquer le déplacement
      */
    void movePlayer(Player player);
    
    /*!
      * \brief Déclenche l'explosion d'une bombe
      * 
      * \param explosive : Bombe qui doit exploser
      */
    void explode(Explosive explosive);
    
    /*!
      * \brief Active le détonateur afin de faire exploser les bombes
      * Cette méthode est appelée lorsque le joueur active son détonateur.
      * Elle provoque l'explosion de toutes les bombes posées par le joueur pris en paramètre.
      * \param player : Joueur qui active le détonateur
      */
    void activateDetonator(Player player);
    
    /*!
      * \brief Pose une mine à l'emplacement du joueur
      * Cette méthode est appelée lorsque le joueur demande à poser une mine.
      * Dans le cas où le joueur peut poser une bombe, la bombe sera posée sous le joueur.
      * \param player : Joueur qui pose la mine
      */
    void putMine(Player player);
    
    /*!
      * \brief Détruit une caisse
      * Cette méthode est appelé lorsque la déflagration d'une bombe touche une caisse.
      * Elle provoque la destruction de la caisse ainsi que la probable libération d'un bonus.
      * \param box : Caisse à exploser
      */
    void breakBox(Box box);
};

#endif