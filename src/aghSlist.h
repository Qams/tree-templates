/**
* \file aghSlist.h
* \author Kamil G. & Kamil K.
* \date 25.05.2015
* \brief Definicja szablonu klasy aghSlist - struktury danych typu 'Lista pojedyńczo wiązana'
*/
// -------------------------------------------------------------------------

#ifndef AGH_SLIST
#define AGH_SLIST
// --------------------------------------------------------------

#include "aghContainer.h"
#include "aghException.h"
// --------------------------------------------------------------

/**
* \class aghSlist
* \author Kamil G. & Kamil K.
* \date 25.05.2015
* \brief Definicja szablonu klasy aghSlist - struktury danych typu 'Lista pojedyńczo wiązana'
*/
template<class T>
class aghSlist : public aghContainer < T >
{
    /**
    * \class el
    * \author Kamil G. & Kamil K.
    * \date 25.05.2015
    * \brief Definicja szablonu klasy lokalnej el - obiekty tej klasy stanowią pojedyncze elementy listy
    */
    template<class F>
	class el
	{
    public:
        F w;            ///< Przechowuje wartość dla obiektu
        el<F> *n;       ///< Wskaźnik do następnego obiektu na liście

        /// \brief Konstruktor parametrowy - ustawia wartość elementu, zeruje wskaźnik
        ///
        /// \param _w - wartość przypisywana do obiektu
        el(F _w): w(_w) { n = NULL; }
	};

	el<T> *head;            ///< Wskaźnik na pierwszy element struktury
	int rozmiar;            ///< Ilość elementów w strukturze

public:

    /// \brief Konstruktor bezparametrowy - ustawia rozmiar na 0
	aghSlist() : rozmiar(0) { head = NULL; }

	/// \brief Konstruktor kopiujący
	aghSlist(const aghContainer<T>&);

    /// \brief Destruktor - usuwa elementy, ustawia rozmiar na 0
	virtual ~aghSlist();

    /// \brief Metoda wirtualna - dodaje wartość na wskazanej pozycji
	///
	/// \param e - wartość, która ma zostać dopisana
	/// \param x - nr pozycji na której ma zostać wpisany element
	/// \return true jezeli operacja sie powiodla, false jeśli pozycja nie istnieje
	virtual bool insert(int x, T const& e);

    /// \brief Metoda wirtualna - zwraca ilość elementów w strukturze
	///
	/// \return ilość elementów
	virtual int size(void) const { return rozmiar; }

    /// \brief Metoda wirtualna - zwraca element z danej pozycji
	///
	/// \param x - pozycja elementu w strukturze
	/// \return wartość elementu poprzez adres
	virtual T& at(int x) const;

    /// \brief Metoda wirtualna - usuwa element ze struktury
	///
	/// \param x - pozycja elementu w strukturze
	/// \return true jezeli operacja sie powiodla, false jeśli pozycja nie istnieje
	virtual bool remove(int x);

    /// \brief Operator= - zamienia wartość struktury na nową
	///
	/// \param a - struktura typu bazowego (aghContainer) do skopiowania
	/// \return referencja na obiekt aghSlist<T>
	aghSlist& operator=(aghContainer<T> const& a);
};
// --------------------------------------------------------------

template<class T>
aghSlist<T>::aghSlist(const aghContainer<T> & a)
{
    rozmiar = 0;
    head = NULL;
    for (int i = 0; i < a.size(); i++)
        aghContainer<T>::append(a[i]);
}
// --------------------------------------------------------------

template<class T>
aghSlist<T>::~aghSlist()
{
    el<T>* tmp = head;
    while(tmp!=NULL)
    {
         el<T>* tmp2 = tmp;
         tmp=tmp->n;
         delete tmp2;
    }
    rozmiar = 0;
}
// --------------------------------------------------------------

template<class T>
T& aghSlist<T>::at(int x) const
{
    if ((x < 0) || (x >= size()))
		throw aghException(0, "Indeks poza zasięgiem", __FILE__, __LINE__);
    el<T> *tym = head;
	for (int i = 0; i < x; i++)
        tym = tym->n;
    return tym->w;
}
// --------------------------------------------------------------

template<class T>
bool aghSlist<T>::insert(int p, T const& a)
{
    if ((p > size()) || (p < 0)) return false;
    el<T> *tym = head;
    el<T> *tym2 = new el<T>(a);
    if (p == 0)
    {
        tym2->n = head;
        head = tym2;
    }
    else
    {
        for (int i = 0; i < (p - 1); i++)
            tym = tym->n;
        tym2->n = tym->n;
        tym->n = tym2;
    }
    rozmiar++;
	return true;
}
// --------------------------------------------------------------

template<class T>
bool aghSlist<T>::remove(int x)
{
    if (x >= size()) return false;
    el<T> *tym = head;
	if (x == 0)
    {
        head = head->n;
        delete tym;
    }
    else
    {
        for (int i = 0; i < (x - 1); i++)
            tym = tym->n;
        el<T> *tym2 = tym->n;
        tym->n = tym2->n;
        delete tym2;
    }
	rozmiar--;
	return true;
}
// --------------------------------------------------------------

template<class T>
aghSlist<T>& aghSlist<T>::operator=(aghContainer<T> const& a)
{
    if (this == &a)
		return *this;
    aghContainer<T>::clear();
	for (int i = 0; i < a.size(); i++)
        aghContainer<T>::append(a[i]);
	return *this;
}
// --------------------------------------------------------------

#endif // AGH_SLIST
