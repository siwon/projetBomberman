
/*!
 * \file PolyBomberException.cpp
 * \brief Classe d'exception du programme
 * \author Maxime GUIHAL
 */

#include <iostream>
#include <sstream>
#include <exception>

#include "PolyBomberException.hpp"

namespace PolyBomber
{
	PolyBomberException::PolyBomberException(std::string msg)
	{
		std::ostringstream oss;
		oss << "Erreur : " << msg;
		this->msg = oss.str();
	}

	PolyBomberException::~PolyBomberException() throw()
	{}

	const char* PolyBomberException::what() const throw()
	{
		return this->msg.c_str();
	}
}



