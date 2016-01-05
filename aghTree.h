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
        F w;            ///< Przechowuje wartoœæ dla obiektu
        el<F> *p;       ///< WskaŸnik do nastêpnego mniejszego obiektu na liœcie
        el<F> *l;       ///< WskaŸnik do nastêpnego wiêkszego lub równego obiektu na liœcie
        el<F> *r;       ///< WskaŸnik do poprzedniego obiektu na liœcie

        /// \brief Konstruktor parametrowy - ustawia wartoœæ elementu, zeruje wskaŸnik
        ///
        /// \param _w - wartoœæ przypisywana do obiektu
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

	el<T> *head;            ///< WskaŸnik na pierwszy element struktury
	int rozmiar;            ///< Iloœæ elementów w strukturze

    /// \brief Metoda rekurencyjna - Zwraca drzewo do listy, w kolejnoœci In-Order
	///
	/// \param p - wskaŸnik na korzeñ
	/// \param tmp - wskaŸnik na listê, do której maj¹ byæ wpisane elementy
	/// \return nie zwraca wartoœci
	void wypisz(el<T> *p, aghSlist<T>* tmp) const;

    /// \brief Metoda rekurencyjna - Dopisuje element do drzewa
	///
	/// \param p - wskaŸnik na korzeñ, po którym nastêpuje przesuwanie
	/// \param a - wartoœæ nowego elementu
	/// \return nie zwraca wartoœci
    void dodaj(el<T> **p, T const& a) const;

    /// \brief Metoda rekurencyjna - Usuwa element ze wskazanej pozycji, dokonuje rotacji
	///
	/// \param poz - wskaŸnik na korzeñ
	/// \return nie zwraca wartoœci
    void usun(el<T> **poz) const;

public:

    /// \brief Konstruktor bezparametrowy - ustawia rozmiar na 0
	aghTree() : rozmiar(0) { head = NULL; }

    /// \brief Konstruktor kopiuj¹cy
	aghTree(const aghContainer<T>&);

    /// \brief Destruktor - usuwa elementy, ustawia rozmiar na 0
	virtual ~aghTree();

    /// \brief Metoda wirtualna - dodaje wartoœæ na wskazanej pozycji
	///
	/// \param e - wartoœæ, która ma zostaæ dopisana
	/// \param x - nr pozycji na której ma zostaæ wpisany element
	/// \return true jezeli operacja sie powiodla, false jeœli pozycja nie istnieje
	virtual bool insert(int x, T const& e);

    /// \brief Metoda wirtualna - zwraca iloœæ elementów w strukturze
	///
	/// \return iloœæ elementów
	virtual int size(void) const { return rozmiar; }

    /// \brief Metoda wirtualna - zwraca element z danej pozycji
	///
	/// \param x - pozycja elementu w strukturze
	/// \return wartoœæ elementu poprzez adres
	virtual T& at(int x) const;

    /// \brief Metoda wirtualna - usuwa element ze struktury
	///
	/// \param x - pozycja elementu w strukturze
	/// \return true jezeli operacja sie powiodla, false jeœli pozycja nie istnieje
	virtual bool remove(int x);

    /// \brief Operator= - zamienia wartoœæ struktury na now¹
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
		throw aghException(0, "Indeks poza zasiêgiem", __FILE__, __LINE__);
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
