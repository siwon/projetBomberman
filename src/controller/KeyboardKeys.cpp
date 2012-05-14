/*!
 * \file KeyboardKeys.cpp
 * \brief Implémentation de la classe KeyboardKeys
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
#include "../../include/controller/KeyboardKeys.hpp"

using namespace PolyBomber;

void KeyboardKeys::init()
{
	/* Caractères alphabétiques */
	
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::A, new KeyboardKeys::KeyValue('a')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::B, new KeyboardKeys::KeyValue('b')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::C, new KeyboardKeys::KeyValue('c')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::D, new KeyboardKeys::KeyValue('d')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::E, new KeyboardKeys::KeyValue('e')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::F, new KeyboardKeys::KeyValue('f')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::G, new KeyboardKeys::KeyValue('g')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::H, new KeyboardKeys::KeyValue('h')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::I, new KeyboardKeys::KeyValue('i')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::J, new KeyboardKeys::KeyValue('j')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::K, new KeyboardKeys::KeyValue('k')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::L, new KeyboardKeys::KeyValue('l')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::M, new KeyboardKeys::KeyValue('m')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::N, new KeyboardKeys::KeyValue('n')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::O, new KeyboardKeys::KeyValue('o')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::P, new KeyboardKeys::KeyValue('p')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Q, new KeyboardKeys::KeyValue('q')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::R, new KeyboardKeys::KeyValue('r')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::S, new KeyboardKeys::KeyValue('s')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::T, new KeyboardKeys::KeyValue('t')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::U, new KeyboardKeys::KeyValue('u')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::V, new KeyboardKeys::KeyValue('v')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::W, new KeyboardKeys::KeyValue('w')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::X, new KeyboardKeys::KeyValue('x')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Y, new KeyboardKeys::KeyValue('y')));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Z, new KeyboardKeys::KeyValue('z')));
	
	/* Caractères numériques */
	
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num0, new KeyboardKeys::KeyValue(0x30)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num1, new KeyboardKeys::KeyValue(0x31)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num2, new KeyboardKeys::KeyValue(0x32)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num3, new KeyboardKeys::KeyValue(0x33)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num4, new KeyboardKeys::KeyValue(0x34)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num5, new KeyboardKeys::KeyValue(0x35)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num6, new KeyboardKeys::KeyValue(0x36)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num7, new KeyboardKeys::KeyValue(0x37)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num8, new KeyboardKeys::KeyValue(0x38)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Num9, new KeyboardKeys::KeyValue(0x39)));

	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad0, new KeyboardKeys::KeyValue(0x30)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad1, new KeyboardKeys::KeyValue(0x31)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad2, new KeyboardKeys::KeyValue(0x32)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad3, new KeyboardKeys::KeyValue(0x33)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad4, new KeyboardKeys::KeyValue(0x34)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad5, new KeyboardKeys::KeyValue(0x35)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad6, new KeyboardKeys::KeyValue(0x36)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad7, new KeyboardKeys::KeyValue(0x37)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad8, new KeyboardKeys::KeyValue(0x38)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Numpad9, new KeyboardKeys::KeyValue(0x39)));
	
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Back, new KeyboardKeys::KeyValue(0x08, "retour arrière")));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Space, new KeyboardKeys::KeyValue(0x13, "espace")));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::Slash, new KeyboardKeys::KeyValue(0x2F)));
	keyMap.insert(std::pair<sf::Keyboard::Key, KeyboardKeys::KeyValue*>(sf::Keyboard::BackSlash, new KeyboardKeys::KeyValue(0x5C)));
}

KeyboardKeys::KeyValue::KeyValue(int charCode, std::string label)
{
	this->charCode = charCode;
	this->label = label;
}

KeyboardKeys::KeyValue::KeyValue(int charCode)
{
	this->charCode = charCode;
	this->label = (char)(charCode);
}

KeyboardKeys::KeyValue::KeyValue(char charValue)
{
	this->charCode = (int)(charValue);
	this->label = (char)(charCode);
}

int KeyboardKeys::KeyValue::getCharCode()
{
	return this->charCode;
}

std::string KeyboardKeys::KeyValue::getLabel()
{
	return this->label;
}

char KeyboardKeys::KeyValue::getCharValue()
{
	return (char)(this->charCode);
}

KeyboardKeys::KeyboardKeys()
{
	this->init();
}

KeyboardKeys::~KeyboardKeys()
{
	std::map<sf::Keyboard::Key, KeyValue*>::const_iterator itr;

	for(itr = keyMap.begin(); itr != keyMap.end(); ++itr)
	{
		delete (*itr).second;
	}
}