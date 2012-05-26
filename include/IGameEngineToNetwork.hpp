#ifndef I_GAME_ENGINE_TO_NETWORK_HEADER
#define I_GAME_ENGINE_TO_NETWORK_HEADER

/*!
 * \file IGameEngineToNetwork.hpp
 * \brief Interface en le moteur de jeu et le reseau
 * \author Simon Rousseau
 */

#include "SGameConfig.hpp"
#include "IGameEngineToGameInterface.hpp"

namespace PolyBomber {
	/*!
	 * \class IGameEngineToNetwork
	 * \brief Interface en le moteur de jeu et le reseau
	 */
	class IGameEngineToNetwork : public IGameEngineToGameInterface {
	public:
		/*!
		 * \brief Methode qui configure le jeu
		 * Cette methode permet de configurer le jeu.
		 */
		virtual void setGameConfig(SGameConfig gameConfig) =0;
		
		/*!
		 * \brief Méthode qui démarre le jeu
		 */
		virtual void run() =0;
		
		/*!
			* \brief Remise à zéro de la configuration du gameEngine en cas d'annulation
			*/
		virtual void resetConfig() =0;

		/*!
		 * \brief Destructeur virtuel
		 */
		virtual ~IGameEngineToNetwork() {};
		
		
	};
}

#endif
