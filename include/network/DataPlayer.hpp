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

		public:
			/*!
			 * \brief Constructeur
			 */
			DataPlayer(int, sf::IpAddress, std::string pName ="None");

			/*!
			 * \brief Destructeur
			 */
			~DataPlayer();
			DataPlayer(const DataPlayer &obj);
			DataPlayer& operator=(const DataPlayer &obj);

			inline sf::IpAddress getIp() const {return this->ip;}

			inline void setName(std::string pName) {this->name=pName;};
	};
}
#endif
