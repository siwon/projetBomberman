#ifndef I_GAME_ENGINE_TO_NETWORK_HEADER
#define I_GAME_ENGINE_TO_NETWORK_HEADER

/*!
 * \file IGameEngineToGameInterface.hpp
 * \brief Interface en le moteur de jeu et le réseau
 * \author Simon Rousseau
 */

namespace PolyBomber;

/*!
 * \class IGameEngineToGameInterface
 * \brief Interface en le moteur de jeu et le réseau
 */
class IGameEngineToNetwork {
  public :
    /*!
     * \brief Méthode permettant de retourner le plateau de jeu
     *
     * \return Retourne le plateau de jeu.
     */
    virtual SBoard getBoard();
    
    /*!
     * \brief Méthode qui signal si le jeu est terminé ou pas
     * Cette méthode permet de déterminer si le jeu est terminé ou pas.
     * \return Renvoie 1 si le jeu est terminé, renvoie 0 sinon.
     */
    virtual int isFinished();
};

#endif