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
			 */
			DataPlayer(int, sf::IpAddress, std::string pName ="None");

			/*!
			 * \brief Destructeur
			 */
			~DataPlayer();
			
			/*!
			 * \brief Constructeur par recopie
			 */
			DataPlayer(const DataPlayer &obj);
			
			/*!
			 * \brief surcharge de l'opérateur d'affectation
			 */
			DataPlayer& operator=(const DataPlayer &obj);
			
			/*!
			 * \brief Constructeur
			 */
			inline sf::IpAddress getIp() const {return this->ip;}
			
			/*!
			 * \brief Constructeur
			 */
			inline void setName(std::string pName) {this->name=pName;}
			
			/*!
			 * \brief Constructeur
			 */
			inline void setConnected(bool a) {this->connected=a;}
			
			/*!
			 * \brief Constructeur
			 */
			inline std::string getName() {return this->name;}
			
			/*!
			 * \brief Constructeur
			 */
			inline bool isConnected() {return this->connected;}


	};
}
#endif
