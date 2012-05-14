#ifndef _TSINGLETON
#define _TSINGLETON

/*!
 * \file TSingleton.hpp
 * \brief Patron de conception Singleton
 * \author Maxime GUIHAL
 */

namespace PolyBomber
{
	/*!
	 * \class Singleton<T>
	 * \brief Patron de conception Singleton
	 *
	 * Ce patron de conception doit être utilisée par toutes les classes
	 * de type *Manager de chaque composant, pour lesquelles <<singleton>>
	 * est indiqué sur les diagrammes de classe, garantissant l'unicité de
	 * cette classe pendant toute l'exécution.
	 *
	 * Exemple d'utilisation :
	 *
	 * == TestManager.hpp ==
	 *
	 * #include "TSingleton.hpp"
	 * #include "ITestManager.hpp"
	 *
	 * class TestManager : public ITestManager, public Singleton<TestManager>
	 * {
	 *     friend class Singleton<TestManager>;
	 *
	 *     private:
	 *         string msg;
	 *
	 *         // Le constructeur doit être sans paramètres et privé
	 *         TestManager()
	 *         {
	 *             this->msg = "test";
	 *         }
	 * 
	 *     public:
	 *         inline void setMessage(string m) {this->msg = m;}
	 *         inline string getMessage() {return this->msg;}
	 * };
	 *
	 * == ClasseUtilisantTestManager.cpp ==
	 *
	 * int main()
	 * {
	 *     ITestManager* t = PolyBomber::getITestManager();
	 *
	 *     t->setMessage("Maxime");
	 *
	 *     cout << t->getMessage() << endl;
	 *
	 *     // Pas de désallocation du pointeur après utilisation
	 *
	 *     return 0;
	 * }
	 */
	template<class T>
	class Singleton
	{
		private:
			static T* instance; /*!< Instance unique de l'objet */

		protected:
			/*!
			 * \brief Constructeur par défaut redéfinissable
			 */
			Singleton()	{}

			/*!
			 * \brief Destructeur par défaut redéfinissable
			 */
			virtual ~Singleton() {}

		public:
			/*!
			 * \brief Méthode statique pour récupérer l'instance de l'objet
			 * \return L'instance unique de l'objet
			 */
			static T* getInstance()
			{
				if (Singleton::instance == NULL)
					Singleton::instance = new T;
								
				return Singleton::instance;
			}

			/*!
			 * \brief Méthode statique pour supprimer une instance de l'objet
			 *
			 * Cette méthode ne supprime l'objet que si plus aucun élément
			 * ne la référence.
			 */
			static void kill()
			{
				if (Singleton::instance != NULL)
				{
					delete Singleton::instance;
					Singleton::instance = NULL;
				}				
			}
	};

	/*!
	 * \brief Initialisation des variables statiques
	 */
	template <class T> T* Singleton<T>::instance = NULL;
}

#endif
