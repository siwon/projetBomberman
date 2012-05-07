/*!
 * \file main.cpp
 * \brief Démarrage du programme
 * \author Maxime GUIHAL
 */

#include "PolyBomberApp.hpp"

using namespace PolyBomber;

int main(int argc, char** argv)
{
	PolyBomberApp* app = PolyBomberApp::getInstance();

	int signal = app->run();

	PolyBomberApp::kill();

	return signal;
}
