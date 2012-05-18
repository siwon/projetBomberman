#ifndef _POLYBOMBEREXCEPTION
#define _POLYBOMBEREXCEPTION

/*!
 * \file PolyBomberException.hpp
 * \brief Classe d'exception du programme
 * \author Maxime GUIHAL
 */

#include <exception>
#include <string>

namespace PolyBomber
{
	/*!
	 * \class PolyBomberException
	 * \brief Classe d'exception du programme
	 */
	class PolyBomberException : public std::exception
	{
		public:
			PolyBomberException(std::string msg);

			virtual ~PolyBomberException() throw();

			virtual const char* what() const throw();

		private:
			std::string msg;
	};
}

#endif

