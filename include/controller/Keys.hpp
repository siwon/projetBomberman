#ifndef _KEYS
#define _KEYS

/*!
 * \file Keys.hpp
 * \brief Classe de correspondance pour les touches
 * \author Alexandre BISIAUX
 */

/* Includes */

// Bibliothèques standarts 
#include <map>

// Bibliothèques SFML
#include <SFML/Graphics.hpp>

// Headers

namespace PolyBomber
{
	
	class Keys
	{
		public:
			class KeyValue
			{
				private :
					int charCode;
					std::string label;
				
				public :
					KeyValue(int charCode);
					KeyValue(char charValue);
					KeyValue(int charCode, std::string label);
					int getCharCode();
					char getCharValue();
					std::string getLabel();
			};
			
		public :
			std::map<sf::Keyboard::Key, KeyValue*> keyMap;
			Keys();
		
		private : 
			void init();
	};
}

#endif

