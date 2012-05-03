/*!
 * \file ControllerManager.cpp
 * \brief Implémentation de classe ControllerManager
 * \author Alexandre BISIAUX
 */

//#include <SFML/Graphics.hpp>

#include "../../include/controller/ControllerManager.hpp"


namespace PolyBomber
{
	EMenuKeys ControllerManager::getKeyPressed()
	{
		const sf::Input& Input = App.GetInput();

		/* Gestion des touches directionnelles */

		if(input.IsKeyDown(sf::Key::Left) || input.GetJoystickAxis(0, sf::Joy::AxisX) < 10 || input.GetJoystickAxis(1, sf::Joy::AxisX) < 10)
			return EMenuKeys.LEFT;

		if(input.IsKeyDown(sf::Key::Right) || input.GetJoystickAxis(0, sf::Joy::AxisX) > 10 || input.GetJoystickAxis(1, sf::Joy::AxisX) > 10)
			return EMenuKeys.RIGHT;
		
		if(input.IsKeyDown(sf::Key::Up) || input.GetJoystickAxis(0, sf::Joy::AxisY) > 10 || input.GetJoystickAxis(1, sf::Joy::AxisY) > 10)
			return EMenuKeys.UP;

		if(input.IsKeyDown(sf::Key::Down) || input.GetJoystickAxis(0, sf::Joy::AxisY) < 10 || input.GetJoystickAxis(1, sf::Joy::AxisY) < 10)
			return EMenuKeys.DOWN;	
		
		if(input.IsKeyDown(sf::Key::Return)|| input.IsJoystickButtonDown(0, 1) || input.IsJoystickButtonDown(1, 1))
			return EMenuKeys.VALID;
		
		if(input.IsKeyDown(sf::Key::Escape) || input.IsJoystickButtonDown(0, 2) || input.IsJoystickButtonDown(1, 2))
			return EMenuKeys.BACK;
		
		return EMenuKeys::NONE;
			
	}

	char ControllerManager::getCharPressed()
	{
	}

	SKeysConfig ControllerManager::getConfig(int player)
	{
	}


	SKeysConfig ControllerManager::setPlayerKey(int player, EGameKeys key)
	{
	}

	SKeysConfig ControllerManager::setPlayerController(int player, EControllerType type)
	{
	}


	void ControllerManager::save()
	{
	}

	void ControllerManager::reloadConfig()
	{
	}
}
