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
			/*!
			 * \brief Constructeur
			 * \param msg : Message d'erreur explicite
			 */
			PolyBomberException(std::string msg);

			/*!
			 * \brief Destructeur
			 */
			virtual ~PolyBomberException() throw();

			/*!
			 * \brief Méthode pour afficher l'erreur
			 * \return Message d'erreur explicite
			 */
			virtual const char* what() const throw();

		private:
			std::string msg; /*!< Message d'erreur */
	};
}

#endif

