#ifndef _GAMEPADKEYS
#define _GAMEPADKEYS

/*!
 * \file GamepadKeys.hpp
 * \brief Classe de correspondance pour les boutons des joystick
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
	
	class GamepadKeys
	{
		public:
			class KeyValue
			{
				private :
					std::string label;
				
				public :
					KeyValue(std::string label);
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

