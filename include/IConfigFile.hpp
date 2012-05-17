#ifndef _ICONFIGFILE
#define _ICONFIGFILE

/*!
 * \file IConfigFile.hpp
 * \brief Interface du composant Configuration
 * \author Maxime GUIHAL
 */

#include <vector>

namespace PolyBomber
{
	/*!
	 * \class IConfigFile
	 * \brief Interface du composant Configuration
	 */
	class IConfigFile
	{
		public:
			/*!
			 * \brief Ecriture d'une chaine de caractère dans le fichier
			 *
			 * Si la clé est déjà présente, sa valeur est remplacée
			 * 
			 * \param key : Clé correspondante à la valeur
			 * \param value : Valeur à écrire
			 */
			virtual void setStringValue(std::string key, std::string value) = 0;

			/*!
			 * \brief Ecriture d'une valeur numérique dans le fichier
			 *
			 * Si la clé est déjà présente, sa valeur est remplacée
			 * 
			 * \param key : Clé correspondante à la valeur
			 * \param value : Nombre à écrire
			 */
			virtual void setIntValue(std::string key, int value) = 0;

			/*!
			 * \brief Récupération d'une chaine de caractère du fichier
			 *
			 * Si la clé n'est pas présente dans le fichier, la méthode
			 * lève une exception
			 * 
			 * \param key : Clé présente dans le fichier
			 * \return Chaine de caractère correspondante à la clé
			 */
			virtual std::string getStringValue(std::string key) = 0;

			/*!
			 * \brief Récupération d'un nombre dans le fichier
			 *
			 * Si la clé n'est pas présente dans le fichier, la méthode
			 * lève une exception
			 * 
			 * \param key : Clé présente dans le fichier
			 * \return Nombre correspondant à la clé
			 */
			virtual int getIntValue(std::string key) = 0;

			/*!
			 * \brief Récupération de toutes les clés du fichier
			 * \return La liste des clés du fichier
			 */
			//virtual std::vector<std::string> getKeys() = 0;

			/*!
			 * \brief Destructeur virtuel
			 */
			virtual ~IConfigFile() {};
	};
}

#endif

