#ifndef _POLYBOMBERAPP
#define _POLYBOMBERAPP

/*!
 * \file PolyBomberApp.hpp
 * \brief Classe contenant le programme
 * \author Maxime GUIHAL
 */

class MenuManager;
class ControllerManager;
class NetworkManager;
/*class GameEngineManager;
class GameInterfaceManager;*/
class SoundManager;
class SkinManager;

#include "TSingleton.hpp"

#include "controller/ControllerManager.hpp"
#include "sound/SoundManager.hpp"
#include "skin/SkinManager.hpp"
#include "menu/MenuManager.hpp"
#include "network/NetworkManager.hpp"
//#include "gameEngine/GameEngineManager.hpp"
//#include "gameInterface/GameInterfaceManager.hpp"

namespace PolyBomber
{
	/*!
	 * \class PolyBomberApp
	 * \brief Classe contenant le programme
	 */
	class PolyBomberApp : public Singleton<PolyBomberApp>
	{
		friend class Singleton<PolyBomberApp>;

		public:
			/*!
			 * \brief Méthode d'exécution du programme
			 * \return Valeur de retour du programme
			 */
			int run();

			/*!
			 * \brief Retourne l'interface IControllerToMenu
			 * \return l'interface IControllerToMenu
			 */
			static IControllerToMenu* getIControllerToMenu();

			/*!
			 * \brief Retourne l'interface IControllerToNetwork
			 * \return l'interface IControllerToNetwork
			 */
			static IControllerToNetwork* getIControllerToNetwork();

			/*!
			 * \brief Retourne l'interface IGameEngineToNetwork
			 * \return l'interface IGameEngineToNetwork
			 */
			//static IGameEngineToNetwork* getIGameEngineToNetwork();

			/*!
			 * \brief Retourne l'interface INetworkToGameEngine
			 * \return l'interface INetworkToGameEngine
			 */			
			//static INetworkToGameEngine* getINetworkToGameEngine();

			/*!
			 * \brief Retourne l'interface INetworkToGameInterface
			 * \return l'interface INetworkToGameInterface
			 */
			//static INetworkToGameInterface* getINetworkToGameInterface();

			/*!
			 * \brief Retourne l'interface INetworkToMenu
			 * \return l'interface INetworkToMenu
			 */
			//static INetworkToMenu* getINetworkToMenu();

			/*!
			 * \brief Retourne l'interface IMenuToGameInterface
			 * \return l'interface IMenuToGameInterface
			 */			
			static IMenuToGameInterface* getIMenuToGameInterface();

			/*!
			 * \brief Retourne l'interface IMenuToMain
			 * \return l'interface IMenuToMain
			 */			
			static IMenuToMain* getIMenuToMain();

			/*!
			 * \brief Retourne l'interface IGameInterfaceToMenu
			 * \return l'interface IGameInterfaceToMenu
			 */			
			//static IGameInterfaceToMenu* getIGameInterfaceToMenu();

			/*!
			 * \brief Retourne l'interface ISkin
			 * \return l'interface ISkin
			 */			
			static ISkin* getISkin();

			/*!
			 * \brief Retourne l'interface ISound
			 * \return l'interface ISound
			 */			
			static ISound* getISound();

		private:
			/*!
			 * \brief Constructeur privé
			 */
			PolyBomberApp();

			/*!
			 * \brief Destructeur privé
			 */
			~PolyBomberApp();

			static MenuManager* menuManager; /*!< Instance du composant Menu */
			//static GameInterfaceManager* gameInterfaceManager; /*!< Instance du composant Interface de jeu */
			//static NetworkManager* networkManager; /*!< Instance du composant Réseau */
			//static GameEngineManager* gameEngineManager; /*!< Instance du composant Moteur de jeu */
			static ControllerManager* controllerManager; /*!< Instance du composant Contrôleur */
			static SoundManager* soundManager; /*!< Instance du composant Son */
			static SkinManager* skinManager; /*!< Instance du composant Skin */
	};
}

#endif
