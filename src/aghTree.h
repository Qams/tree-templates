/**
* \file aghTree.h
* \author Kamil G. & Kamil K.
* \date 05.06.2015
* \brief Definicja szablonu klasy aghTree - struktury danych typu 'Drzewo binarne'
*/
// -------------------------------------------------------------------------

#ifndef AGH_TREE
#define AGH_TREE
// --------------------------------------------------------------

#include "aghContainer.h"
#include "aghException.h"
#include "aghSlist.h"
// --------------------------------------------------------------

/**
* \class aghTree
* \author Kamil G. & Kamil K.
* \date 05.06.2015
* \brief Definicja szablonu klasy aghTree - struktury danych typu 'Drzewo binarne'
*/
template<class T>
class aghTree : public aghContainer < T >
{
    template<class F>
	class el
	{
    public:
        F w;            ///< Przechowuje warto�� dla obiektu
        el<F> *p;       ///< Wska�nik do nast�pnego mniejszego obiektu na li�cie
        el<F> *l;       ///< Wska�nik do nast�pnego wi�kszego lub r�wnego obiektu na li�cie
        el<F> *r;       ///< Wska�nik do poprzedniego obiektu na li�cie

        /// \brief Konstruktor parametrowy - ustawia warto�� elementu, zeruje wska�nik
        ///
        /// \param _w - warto�� przypisywana do obiektu
        el() { p = NULL; l = NULL; r = NULL; }
        el(F _w): w(_w) { p = NULL; l = NULL; r = NULL; }
        ~el()
        {
            if(l!=NULL)
                delete l;
            if(r!=NULL)
                delete r;
            l = NULL;
            r = NULL;
            p = NULL;
        };
	};

	el<T> *head;            ///< Wska�nik na pierwszy element struktury
	int rozmiar;            ///< Ilo�� element�w w strukturze

    /// \brief Metoda rekurencyjna - Zwraca drzewo do listy, w kolejno�ci In-Order
	///
	/// \param p - wska�nik na korze�
	/// \param tmp - wska�nik na list�, do kt�rej maj� by� wpisane elementy
	/// \return nie zwraca warto�ci
	void wypisz(el<T> *p, aghSlist<T>* tmp) const;

    /// \brief Metoda rekurencyjna - Dopisuje element do drzewa
	///
	/// \param p - wska�nik na korze�, po kt�rym nast�puje przesuwanie
	/// \param a - warto�� nowego elementu
	/// \return nie zwraca warto�ci
    void dodaj(el<T> **p, T const& a) const;

    /// \brief Metoda rekurencyjna - Usuwa element ze wskazanej pozycji, dokonuje rotacji
	///
	/// \param poz - wska�nik na korze�
	/// \return nie zwraca warto�ci
    void usun(el<T> **poz) const;

public:

    /// \brief Konstruktor bezparametrowy - ustawia rozmiar na 0
	aghTree() : rozmiar(0) { head = NULL; }

    /// \brief Konstruktor kopiuj�cy
	aghTree(const aghContainer<T>&);

    /// \brief Destruktor - usuwa elementy, ustawia rozmiar na 0
	virtual ~aghTree();

    /// \brief Metoda wirtualna - dodaje warto�� na wskazanej pozycji
	///
	/// \param e - warto��, kt�ra ma zosta� dopisana
	/// \param x - nr pozycji na kt�rej ma zosta� wpisany element
	/// \return true jezeli operacja sie powiodla, false je�li pozycja nie istnieje
	virtual bool insert(int x, T const& e);

    /// \brief Metoda wirtualna - zwraca ilo�� element�w w strukturze
	///
	/// \return ilo�� element�w
	virtual int size(void) const { return rozmiar; }

    /// \brief Metoda wirtualna - zwraca element z danej pozycji
	///
	/// \param x - pozycja elementu w strukturze
	/// \return warto�� elementu poprzez adres
	virtual T& at(int x) const;

    /// \brief Metoda wirtualna - usuwa element ze struktury
	///
	/// \param x - pozycja elementu w strukturze
	/// \return true jezeli operacja sie powiodla, false je�li pozycja nie istnieje
	virtual bool remove(int x);

    /// \brief Operator= - zamienia warto�� struktury na now�
	///
	/// \param a - struktura typu bazowego (aghContainer) do skopiowania
	/// \return referencja na obiekt aghSlist<T>
	aghTree& operator=(aghContainer<T> const& a);
};
// --------------------------------------------------------------

template<class T>
void aghTree<T>::wypisz(el<T> *p, aghSlist<T>* tmp) const
{
    if (p != NULL)
    {
        wypisz(p->l, tmp);
        tmp->append(p->w);
        wypisz(p->r, tmp);
    }
}
template<class T>
void aghTree<T>::dodaj(el<T> **p, T const& a) const
{
    if (a < (*p)->w)
    {
        if ((*p)->l != NULL)
            dodaj(&((*p)->l), a);
        else
        {
            el<T> *tym = new el<T>(a);
            tym->p = (*p);
            (*p)->l = tym;
        }
    }
    else
    {
        if ((*p)->r != NULL)
            dodaj(&((*p)->r), a);
        else
        {
            el<T> *tym = new el<T>(a);
            tym->p = (*p);
            (*p)->r = tym;
        }
    }
}

template<class T>
void aghTree<T>::usun(el<T> **poz) const
    {
        el<T> *p = (*poz);
        bool rek = true;
        if ((p->l == NULL) && (p->r == NULL))
        {
            rek = false;
            if (p->p != NULL)
            {
                if (p->p->w > p->w)
                    p->p->l = NULL;
                else
                    p->p->r = NULL;
            }
            delete p;
            p = NULL;
        }
        else if ((p->l == NULL) && (p->r != NULL))
        {
            if ((p->r->l == NULL) && (p->r->r == NULL))
            {
                rek = false;
                p->w = p->r->w;
                delete p->r;
                p->r = NULL;
            }
        }
        else if ((p->r == NULL) && (p->l != NULL))
        {
            if ((p->l->l == NULL) && (p->l->r == NULL))
            {
                rek = false;
                p->w = p->l->w;
                delete p->l;
                p->l = NULL;
            }
        }
        if (rek)
        {
            aghSlist<T> *tmp = new aghSlist<T>();
            if((*poz)->r != NULL)
            {
                wypisz((*poz)->r, tmp);
                T mini = tmp->at(0);
                for(int i = 1; i < tmp->size(); i++)
                    if (tmp->at(i) < mini)
                        mini = tmp->at(i);
                el<T> *minimum = (*poz)->r;
                while (minimum->w != mini)
                {
                    minimum = minimum->l;
                }
                (*poz)->w = minimum->w;
                delete tmp;
                usun(&minimum);
            }
            else
            {
                wypisz((*poz)->l, tmp);
                T maxi = tmp->at(0);
                for(int i = 1; i < tmp->size(); i++)
                    if (tmp->at(i) > maxi)
                        maxi = tmp->at(i);
                el<T> *maksimum = (*poz)->l;
                while (maksimum->w != maxi)
                {
                    maksimum = maksimum->r;
                }
                (*poz)->w = maksimum->w;
                cout << "MAM " << (*poz)->w << " SZUKAM: " << maxi;
                delete tmp;
                usun(&maksimum);
            }
        }
    }

template<class T>
aghTree<T>::aghTree(const aghContainer<T> & a)
{
    rozmiar = 0;
    head = NULL;
    for (int i = 0; i < a.size(); i++)
        aghContainer<T>::append(a[i]);
}
// --------------------------------------------------------------

template<class T>
aghTree<T>::~aghTree()
{
    delete head;
    rozmiar = 0;
}

// --------------------------------------------------------------

template<class T>
T& aghTree<T>::at(int x) const
{
    if ((x < 0) || (x >= size()))
		throw aghException(0, "Indeks poza zasi�giem", __FILE__, __LINE__);
    aghSlist<T> *tmp = new aghSlist<T>();
    wypisz(head, tmp);
    T wynik = tmp->at(x);
    el<T> *p = head;
    while (p->w != wynik)
    {
        if (wynik < p->w)
            p = p->l;
        else
            p = p->r;
    }
    delete tmp;
    return p->w;
}
// --------------------------------------------------------------

template<class T>
bool aghTree<T>::insert(int p, T const& a)
{
   // if ((p > size()) || (p < 0)) return false;
    if (size() == 0)
        head = new el<T>(a);
    else dodaj(&head, a);
    rozmiar++;
	return true;
}
// --------------------------------------------------------------

template<class T>
bool aghTree<T>::remove(int x)
{
    if ((x < 0) || (x > size()))
		return false;
    T wartosc = at(x);
    el<T> *p = head;
    while (p->w != wartosc)
    {
        if (wartosc < p->w)
            p = p->l;
        else
            p = p->r;
    }
    usun(&p);
    rozmiar--;
    return true;
}
// --------------------------------------------------------------

template<class T>
aghTree<T>& aghTree<T>::operator=(aghContainer<T> const& a)
{
    if (this == &a)
		return *this;
    this->clear();
	for (int i = 0; i < a.size(); i++)
        this->append(a[i]);
	return *this;
}
// --------------------------------------------------------------

#endif // AGH_TREE
