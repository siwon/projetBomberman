#ifndef _KEYBOARDKEYS
#define _KEYBOARDKEYS

/*!
 * \file KeyboardKeys.hpp
 * \brief Classe de correspondance pour les touches clavier
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
	/*!
	* \class KeyboardKeys
	* \brief Classe de correspondance pour les touches clavier
	*/
	class KeyboardKeys
	{
		public:
			class KeyValue
			{
				private :
					int charCode; /*!< Code ascii de la valeur */
					std::string label; /*!< Label de la valeur (ex : espace, entrée,...) */
				
				public :
					/**
					 * \brief Constructeur d'une KeyValue à partir d'un code ascii
					 * \param charCode : code ascii de la touche
					 */
					KeyValue(int charCode);
					
					/**
					 * \brief Constructeur d'une KeyValue à partir d'un carractère
					 * \param charValue : carractère
					 */
					KeyValue(char charValue);
					
					/**
					 * \brief Constructeur d'une KeyValue à partir d'un code ascii et d'un label
					 * \param charCode : code ascii de la touche
					 * \param label : label de la touche
					 */
					KeyValue(int charCode, std::string label);
					
					/**
					 * \brief Obtenir le code acsii d'une KeyValue
					 * \return code ascii correspondant
					 */
					int getCharCode();
					
					/**
					 * \brief Obtenir le caractère d'une KeyValue
					 * \return caractère correspondant
					 */
					char getCharValue();
					
					/**
					 * \brief Obtenir le label d'une touche
					 * \return label correspondant
					 */
					std::string getLabel();
			};
			
			std::map<sf::Keyboard::Key, KeyValue*> keyMap; /*!< Map de correspondance entre l'enum de la SFML et une structure KeyValue */
			
			/**
			 * \brief Constructeur par défaut de la classe KeyboardKeys
			 */
			KeyboardKeys();
			
			/**
			 * \brief Destructeur de la classe KeyboardKeys
			 */
			~KeyboardKeys();
		
		private : 
			
			/**
			 * \brief Initialisation de la map de correspondance
			 */
			void init();
	};
}

#endif

