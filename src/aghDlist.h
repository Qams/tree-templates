/**
* \file aghDlist.h
* \author Kamil G. & Kamil K.
* \date 25.05.2015
* \brief Definicja szablonu klasy aghDlist - struktury danych typu 'Lista podwójnie wiązana'
*/
// -------------------------------------------------------------------------

#ifndef AGH_DLIST
#define AGH_DlIST
// --------------------------------------------------------------

#include "aghContainer.h"
#include "aghException.h"
// --------------------------------------------------------------

/**
* \class aghDlist
* \author Kamil G. & Kamil K.
* \date 25.05.2015
* \brief Definicja szablonu klasy aghDlist - struktury danych typu 'Lista podwójnie wiązana'
*/
template<class T>
class aghDlist : public aghContainer < T >
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
        el<F> *p;       ///< Wskaźnik do poprzedniego obiektu na liście

        /// \brief Konstruktor parametrowy - ustawia wartość elementu, zeruje wskaźnik
        ///
        /// \param _w - wartość przypisywana do obiektu
        el(F _w): w(_w) { n = NULL; p = NULL; }
	};

	el<T> *head;            ///< Wskaźnik na pierwszy element struktury
	el<T> *tail;            ///< Wskaźnik na ostatni element struktury
	int rozmiar;            ///< Ilość elementów w strukturze

public:

    /// \brief Konstruktor bezparametrowy - ustawia rozmiar na 0
	aghDlist() : rozmiar(0) { head = NULL; tail = NULL; }

    /// \brief Konstruktor kopiujący
	aghDlist(const aghContainer<T>&);

    /// \brief Destruktor - usuwa elementy, ustawia rozmiar na 0
	virtual ~aghDlist();

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
	aghDlist& operator=(aghContainer<T> const& a);
};
// --------------------------------------------------------------

template<class T>
aghDlist<T>::aghDlist(const aghContainer<T> & a)
{
    rozmiar = 0;
    head = NULL;
    tail = NULL;
    for (int i = 0; i < a.size(); i++)
        aghContainer<T>::append(a[i]);
}
// --------------------------------------------------------------

template<class T>
aghDlist<T>::~aghDlist()
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
T& aghDlist<T>::at(int x) const
{
    if ((x < 0) || (x >= size()))
		throw aghException(0, "Indeks poza zasięgiem", __FILE__, __LINE__);
    el<T> *tym;
    if (((x + 1) * 2) <= size())
    {
        tym = head;
        for (int i = 0; i < x; i++)
            tym = tym->n;
    }
    else
    {
        tym = tail;
        for (int i = (size() - 1); i > x; i--)
            tym = tym->p;
    }
    return tym->w;
}
// --------------------------------------------------------------

template<class T>
bool aghDlist<T>::insert(int p, T const& a)
{
    if ((p > size()) || (p < 0)) return false;
    el<T> *tym2 = new el<T>(a);
    if (size() == 0)
    {
        head = tym2;
        head->p = NULL;
        head->n = NULL;
        tail = head;
    }
    else if (p == 0)
    {
        tym2->n = head;
        head = tym2;
        head->p = NULL;
        head->n->p = head;
    }
    else if (p == size())
    {
        tym2->p = tail;
        tail = tym2;
        tail->n = NULL;
        tail->p->n = tail;
    }
    else if (((p + 1) * 2) <= size())
    {
        el<T> *tym = head;
        for (int i = 0; i < (p - 1); i++)
            tym = tym->n;
        tym2->n = tym->n;
        tym->n = tym2;
        tym2->p = tym;
        if (tym2->n != NULL)
            tym2->n->p = tym2;
    }
    else
    {
        el<T> *tym = tail;
        for (int i = (size() - 1); i > p; i--)
            tym = tym->p;
        tym2->p = tym->p;
        tym->p = tym2;
        tym2->n = tym;
        if (tym2->p != NULL)
            tym2->p->n = tym2;
    }
    rozmiar++;
	return true;
}
// --------------------------------------------------------------

template<class T>
bool aghDlist<T>::remove(int x)
{
    if (x >= size()) return false;
    el<T> *tym = head;
	if (x == 0)
    {
        head = head->n;
        if (head != NULL)
            head->p = NULL;
    }
    else if (x == (size() - 1))
    {
        tym = tail;
        tail = tail->p;
        if (tail != NULL)
            tail->n = NULL;
    }
    else if (((x + 1) * 2) <= size())
    {
        for (int i = 0; i < x; i++)
            tym = tym->n;
        tym->p->n = tym->n;
        if (tym->n != NULL)
            tym->n->p = tym->p;
    }
    else
    {
        tym = tail;
        for (int i = (size() - 1); i > x; i--)
            tym = tym->p;
        tym->n->p = tym->p;
        if (tym->p != NULL)
            tym->p->n = tym->n;
    }
	rozmiar--;
    delete tym;
	return true;
}
// --------------------------------------------------------------

template<class T>
aghDlist<T>& aghDlist<T>::operator=(aghContainer<T> const& a)
{
    if (this == &a)
		return *this;
    aghContainer<T>::clear();
	for (int i = 0; i < a.size(); i++)
        aghContainer<T>::append(a[i]);
	return *this;
}
// --------------------------------------------------------------

#endif // AGH_DLIST
