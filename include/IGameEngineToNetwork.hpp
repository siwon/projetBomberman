#ifndef I_GAME_ENGINE_TO_NETWORK_HEADER
#define I_GAME_ENGINE_TO_NETWORK_HEADER

/*!
 * \file IGameEngineToNetwork.hpp
 * \brief Interface en le moteur de jeu et le réseau
 * \author Simon Rousseau
 */

#include "./IGameEngineToGameInterface.hpp"
#include "./SGameConfig.hpp"

namespace PolyBomber;

/*!
 * \class IGameEngineToNetwork
 * \brief Interface en le moteur de jeu et le réseau
 */
class IGameEngineToNetwork : public IGameEngineToGameInterface {
  public :
    /*!
     * \brief Méthode qui configure le jeu
     * Cette méthode permet de configurer le jeu.
     * \return void
     */
    virtual void setGameConfig(SGameConfig gameConfig);
}

#endif