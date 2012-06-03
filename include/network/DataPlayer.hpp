#ifndef _DATAPLAYER
#define _DATAPLAYER

/*!
 * \file DataPlayer.hpp
 * \brief information sur un joueur
 * \author Brice GUILLERMIC
 */

#include <string>

#include <SFML/Network.hpp>

namespace PolyBomber
{
	/*!
	 * \class DataPlayer
	 * \brief information sur un joueur
	 */
	class DataPlayer
	{
		private:
			int id;
			sf::IpAddress ip;
			std::string name;
			bool connected;

		public:
			/*!
			 * \brief Constructeur
			 * \param identifient du joueur
			 * \param adresse ip du joueur
			 * \param nom du joueur, par defaut None
			 */
			DataPlayer(int, sf::IpAddress, std::string pName ="None");

			/*!
			 * \brief Destructeur
			 */
			~DataPlayer();
			
			/*!
			 * \brief Constructeur par recopie
			 * \param obj : Objet à copier
			 */
			DataPlayer(const DataPlayer &obj);
			
			/*!
			 * \brief surcharge de l'opérateur d'affectation
			 * \param obj : Objet à copier
			 */
			DataPlayer& operator=(const DataPlayer &obj);
			
			/*!
			 * \brief permet de récupérer l'adresse ip du joueur
			 * \return l'adresse ip du joueur
			 */
			inline sf::IpAddress getIp() const {return this->ip;}
			
			/*!
			 * \brief enregistre un nom pour le joueur
			 * \param pName : le nom du joueur
			 */
			inline void setName(std::string pName) {this->name=pName;}
			
			/*!
			 * \brief enregistre l'état du joueur
			 * \param a : état du joueur
			 */
			inline void setConnected(bool a) {this->connected=a;}
			
			/*!
			 * \brief accesseur sur le nom du joueur;
			 */
			inline std::string getName() {return this->name;}
			
			/*!
			 * \brief accesseur sur l'etat du joueur;
			 */
			inline bool isConnected() {return this->connected;}


	};
}
#endif
