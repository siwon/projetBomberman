/*!
 * \file main.cpp
 * \brief Démarrage du programme
 * \author Maxime GUIHAL
 */

 #include "menu/MenuManager.hpp"

int main(int argc, char** argv)
{
	IMenuToMain* menu = MenuManager::getInstance();

	EScreenSignal signal = menu->run();

	menu::kill();

	return signal;
}
