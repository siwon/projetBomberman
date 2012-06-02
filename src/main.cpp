/*!
 * \file main.cpp
 * \brief Démarrage du programme
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"

using namespace PolyBomber;

int main()
{
	int signal;
	
	try
	{
		PolyBomberApp* app = PolyBomberApp::getInstance();
		signal = app->run();

		PolyBomberApp::kill();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		signal = EXIT_FAILURE;
	}
	
	return signal;
}
