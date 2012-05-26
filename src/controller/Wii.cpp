/*!
 * \file Wii.cpp
 * \brief Implémentation de la classe Wii
 * \author Alexandre BISIAUX
 */
 
#define DEBUG 1

/* Includes */

// Bibliothèques standards 
#include <iostream>
#include <sstream>
#include <map>

// Bibliothèques externes

// Headers
#include "../../include/EMenuKeys.hpp"
#include "../../include/EGameKeys.hpp"
#include "../../include/SKeysConfig.hpp"
#include "../../include/EControllerType.hpp"
#include "../../include/controller/Wii.hpp"
#include "../../include/PolyBomberException.hpp"
#include "../../include/controller/Wiicpp.hpp"

using namespace PolyBomber;

int Wii::nbWiimotes = 0;
int Wii::LED_MAP[4] = {CWiimote::LED_1, CWiimote::LED_2, CWiimote::LED_3, CWiimote::LED_4};


std::string Wii::getLabel(int key)
{
	return keysLabel[(CButtons::ButtonDefs)(key)];
}


Wii::Wii()
{
	this->wii = new CWii();
	this->nbWiimotes = 0;
	
	cout << "Recherche des périphériques wiimotes....... Allumez les !" << endl;
	this->numFound = wii->Find(3);
	
	wiimotes = wii->Connect();

	this->setupWiimotes();

	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_TWO,"Bouton 2"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_ONE,"Bouton 1"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_B,"Bouton B"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_A,"Bouton A"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_MINUS,"Bouton -"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_HOME,"Bouton Home"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_LEFT,"Gauche"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_RIGHT,"Droite"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_DOWN,"Bas"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_UP,"Haut"));
	keysLabel.insert(std::pair<CButtons::ButtonDefs,std::string>(CButtons::BUTTON_PLUS,"Bouton +"));
}

Wii::~Wii()
{
	delete wii;
}


EMenuKeys Wii::getMenuKey(sf::RenderWindow* window)
{
	std::vector<CWiimote>::iterator i;
	if(wii->Poll())
	{
		for(i = wiimotes.begin(); i != wiimotes.end(); ++i)
		{
			CWiimote & wiimote = *i;
			switch(wiimote.GetEvent())
			{
			case CWiimote::EVENT_EVENT :
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_LEFT))
				{
					#if DEBUG
						std::cout << "LEFT on Wiimote" << std::endl;
					#endif
					return MENU_LEFT;
				}
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_RIGHT))
				{
					#if DEBUG
						std::cout << "RIGHT on Wiimote" << std::endl;
					#endif
					return MENU_RIGHT;
				}

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_UP))
				{
					#if DEBUG
						std::cout << "UP on Wiimote" << std::endl;
					#endif
					return MENU_UP;
				}

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_DOWN))
				{
					#if DEBUG
						std::cout << "DOWN on Wiimote" << std::endl;
					#endif
					return MENU_DOWN;
				}

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_A))
				{
					#if DEBUG
						std::cout << "VALID on Wiimote" << std::endl;
					#endif
					return MENU_VALID;
				}

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_B))
				{
					wiimote.SetRumbleMode(CWiimote::ON);
					usleep(50000);
					wiimote.SetRumbleMode(CWiimote::OFF);
					#if DEBUG
						std::cout << "BACK on Wiimote" << std::endl;
					#endif
					return MENU_BACK;
				}
				break;
			default :
				break;
			}
		}
	}
	return MENU_NONE;
		
}


EControllerType Wii::getControllerType()
{
	return WII;
}

char Wii::getCharPressed(sf::RenderWindow* window)
{
	return '\0';
}

int Wii::getKeyPressed(int player,sf::RenderWindow* window)
{
	if(wii->Poll())
	{
		CWiimote & wiimote =  *wiimotesAssignation[player];
			
		switch(wiimote.GetEvent())
		{
			case CWiimote::EVENT_EVENT :
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_LEFT))
					return CButtons::BUTTON_LEFT;

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_RIGHT))
					return CButtons::BUTTON_RIGHT;

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_UP))
					return CButtons::BUTTON_UP;

				if(wiimote.Buttons.isPressed(CButtons::BUTTON_DOWN))
					return CButtons::BUTTON_DOWN;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_TWO))
					return CButtons::BUTTON_TWO;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_ONE))
					return CButtons::BUTTON_ONE;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_HOME))
					return CButtons::BUTTON_HOME;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_MINUS))
					return CButtons::BUTTON_MINUS;
				
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_PLUS))
					return CButtons::BUTTON_PLUS;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_A))
					return CButtons::BUTTON_A;
			
				if(wiimote.Buttons.isPressed(CButtons::BUTTON_B))
					return CButtons::BUTTON_B;
				break;
			default :
				return -1;
				break;
		}				
	}
	return -1;
}

void Wii::setupWiimotes()
{
	std::vector<CWiimote>::iterator i;
	int index;
	for(index = 0, i = wiimotes.begin(); i != wiimotes.end(); ++i, ++index)
	{
		CWiimote & wiimote = *i;

		wiimote.SetLEDs(LED_MAP[index]);

		wiimote.SetRumbleMode(CWiimote::ON);
		usleep(200000);
		wiimote.SetRumbleMode(CWiimote::OFF);
	}
}

void Wii::reload()
{
     wiimotes = wii->GetWiimotes();
}

void Wii::add(int player)
{
	if(numFound > nbWiimotes)
	{		
		wiimotesAssignation.insert(std::pair<int,CWiimote*>(player,&wiimotes[nbWiimotes]));
		nbWiimotes++;
	}
	else
	{
		this->reload();
		//this->setupWiimotes();
		if(numFound > nbWiimotes)
		{
			wiimotesAssignation.insert(std::pair<int,CWiimote*>(player,&wiimotes[nbWiimotes]));
			nbWiimotes++;
		}
		else
		{
			throw new PolyBomberException("Aucune wiimotes disponible.\n");
		}
	}
}

void Wii::disconnect(int player)
{
	wiimotesAssignation[player]->SetRumbleMode(CWiimote::ON);
	usleep(100000);
	wiimotesAssignation[player]->SetRumbleMode(CWiimote::OFF);
	
	wiimotesAssignation[player]->Disconnect();
	wiimotesAssignation.erase(player);
	nbWiimotes--;
}
