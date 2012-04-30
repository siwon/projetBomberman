# Header Type

= Nom du fichier =
* EHeader.hpp : Enumération EHeader
* SHeader.hpp : Structure SHeader
* IHeader.hpp : Interface IHeader
* header.hpp  : Classe Header

## Unicité

Au début de chaque header, penser à écrire :

#ifndef _HEADER
#define _HEADER

...

#endif

# Commentaires

Chaque header doit être documenté selon la norme Doxygen (http://franckh.developpez.com/tutoriels/outils/doxygen/).
C'est à dire par exemple :

/*!
 * \file IMenuToMain.hpp
 * \brief Interface Entrée du programme - Menu
 * \author Maxime GUIHAL
 */

# Espace de nommage

Inclure tous les objets du programme dans le namespace PolyBomber :

namespace PolyBomber
{
	...
}

# Classe Type #

Toutes les classes devront respecter la forme de Coplien, et documentées en français.

/*!
 * \class Test
 * \brief Description courte
 *
 * Description longue
 */
class Test : public Father
{
	public:
		int run();

	protected:
		int a; /*!< Description courte de l'attribut */

	private:
		/*!
		 * \brief Description courte
		 *
		 * Description longue
		 *
		 * \param a : description du paramètre
		 * \param b : idem
		 * \return description du retour
		 */
		int func(int a, int b);
};

int Test::run()
{
	...
}

# Includes

Au début de chaque fichier .cpp, les #include doivent se faire dans l'ordre suivant :

- Bibliothèque standard (genre iostream, etc...)
- Ligne vide
- Bibliothèque SFML
- Ligne vide
- Autres bibliothèques externes
- Ligne vide
- Headers du projet

using namespace PolyBomber;

# Noms des objets

Les noms des objets doivent être écrits en anglais et en lowerCamelCase.

