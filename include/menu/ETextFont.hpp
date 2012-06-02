#ifndef _ETEXTFONT
#define _ETEXTFONT

/*!
 * \file ETextFont.hpp
 * \brief Enumération des polices
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{ 
	/*!
	 * \enum ETextFont
	 * \brief Police utilisées
	 */
	enum ETextFont
	{
		TITLEFONT, /*!< Police pour les titres */
		TEXTFONT, /*!< Police pour le texte normal */
		LINKFONT, /*!< Police pour les liens */
		ERRORFONT /*!< Police pour les messages d'erreur */
	};
}

#endif



