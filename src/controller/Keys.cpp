/*!
 * \file Keys.cpp
 * \brief Implémentation de la classe Keys
 * \author Alexandre BISIAUX
 */

#define DEBUG 0

/* Includes */

// Bibliothèques standarts 
#include <map>
#include <iostream>

// Bibliothèques SFML

// Bibliothèques externes

// Headers
#include "../../include/controller/Keys.hpp"

using namespace PolyBomber;

void Keys::init()
{
	/* Caractères alphabétiques */
	
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::A, new Keys::KeyValue('a')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::B, new Keys::KeyValue('b')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::C, new Keys::KeyValue('c')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::D, new Keys::KeyValue('d')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::E, new Keys::KeyValue('e')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::F, new Keys::KeyValue('f')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::G, new Keys::KeyValue('g')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::H, new Keys::KeyValue('h')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::I, new Keys::KeyValue('i')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::J, new Keys::KeyValue('j')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::K, new Keys::KeyValue('k')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::L, new Keys::KeyValue('l')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::M, new Keys::KeyValue('m')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::N, new Keys::KeyValue('n')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::O, new Keys::KeyValue('o')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::P, new Keys::KeyValue('p')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Q, new Keys::KeyValue('q')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::R, new Keys::KeyValue('r')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::S, new Keys::KeyValue('s')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::T, new Keys::KeyValue('t')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::U, new Keys::KeyValue('u')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::V, new Keys::KeyValue('v')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::W, new Keys::KeyValue('w')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::X, new Keys::KeyValue('x')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Y, new Keys::KeyValue('y')));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Z, new Keys::KeyValue('z')));
	
	/* Caractères numériques */
	
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num0, new Keys::KeyValue(0x30)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num1, new Keys::KeyValue(0x31)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num2, new Keys::KeyValue(0x32)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num3, new Keys::KeyValue(0x33)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num4, new Keys::KeyValue(0x34)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num5, new Keys::KeyValue(0x35)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num6, new Keys::KeyValue(0x36)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num7, new Keys::KeyValue(0x37)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num8, new Keys::KeyValue(0x38)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Num9, new Keys::KeyValue(0x39)));

	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad0, new Keys::KeyValue(0x30)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad1, new Keys::KeyValue(0x31)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad2, new Keys::KeyValue(0x32)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad3, new Keys::KeyValue(0x33)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad4, new Keys::KeyValue(0x34)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad5, new Keys::KeyValue(0x35)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad6, new Keys::KeyValue(0x36)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad7, new Keys::KeyValue(0x37)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad8, new Keys::KeyValue(0x38)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Numpad9, new Keys::KeyValue(0x39)));
	
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Back, new Keys::KeyValue(0x08, "retour arrière")));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Space, new Keys::KeyValue(0x13, "espace")));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::Slash, new Keys::KeyValue(0x2F)));
	keyMap.insert(std::pair<sf::Keyboard::Key, Keys::KeyValue*>(sf::Keyboard::BackSlash, new Keys::KeyValue(0x5C)));
}

Keys::KeyValue::KeyValue(int charCode, std::string label)
{
	this->charCode = charCode;
	this->label = label;
}

Keys::KeyValue::KeyValue(int charCode)
{
	this->charCode = charCode;
	this->label = (char)(charCode);
}

Keys::KeyValue::KeyValue(char charValue)
{
	this->charCode = (int)(charValue);
	this->label = (char)(charCode);
}

int Keys::KeyValue::getCharCode()
{
	return this->charCode;
}

std::string Keys::KeyValue::getLabel()
{
	return this->label;
}

char Keys::KeyValue::getCharValue()
{
	return (char)(this->charCode);
}

Keys::Keys()
{
	this->init();
}
/*
int main()
{
	Keys keys;
	std::map<sf::Keyboard::Key, Keys::KeyValue*> ::iterator it;
	for(it = keys.keyMap.begin(); it != keys.keyMap.end(); ++it)
	{
		std::cout << (*it).first << " = " << (*it).second->getLabel() << std::endl;
	}
	return 0;
}
*/