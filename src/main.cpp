/*!
 * \file main.cpp
 * \brief Démarrage du programme
 * \author Maxime GUIHAL
 */

#include "menu/MenuManager.hpp"

using namespace PolyBomber;

int main(int argc, char** argv)
{
	IMenuToMain* menu = MenuManager::getInstance();

	EScreenSignal signal = menu->run();

	MenuManager::kill();

	return signal;
}
