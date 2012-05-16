/*!
 * \file MenuManager.cpp
 * \brief Gestionnaire du menu
 * \author Maxime GUIHAL
 */

#include "menu/MenuManager.hpp"

namespace PolyBomber
{
	MenuManager::MenuManager() : menuResources()
	{}

	MenuManager::~MenuManager()
	{}

	EScreenSignal MenuManager::run()
	{
		// TODO
		return EXITGAME;
	}

	
	EScreenSignal MenuManager::runPause(unsigned int player)
	{
		// TODO
		return EXITMENU;
	}
}
