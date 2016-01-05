/**
* \file aghVector.h
* \author Kamil G. & Kamil K.
* \date 20.05.2015
* \brief Definicja szablonu klasy aghVector - struktury danych typu 'Vector'
*/
// -------------------------------------------------------------------------

#ifndef AGH_VECTOR
#define AGH_VECTOR
// --------------------------------------------------------------

#include "aghContainer.h"
#include "aghException.h"
// --------------------------------------------------------------

/**
* \class aghVector
* \author Kamil G. & Kamil K.
* \date 20.05.2015
* \brief Definicja szablonu klasy aghVector - struktury danych typu 'Vector'
*/
template<class T>
class aghVector : public aghContainer < T >
{
	T* tab;          ///< Tablica jednowymiarowa na elementy struktury
	int rozmiar;     ///< Przechowuje rozmiar tablicy (liczbę elementów)
public:
	/// \brief Konstruktor bezparametrowy - ustawia rozmiar tablicy na 0
	aghVector() : rozmiar(0) { }

	/// \brief Konstruktor kopiujący
	aghVector(aghContainer<T>&);

	/// \brief Destruktor - usuwa tablicę, ustawia rozmiar na 0
	virtual ~aghVector();

	/// \brief Metoda pomocnicza - zmienia rozmiar tablicy
	///
	/// \param n - nowy rozmiar
	/// \return nie zwraca wartości
	void resize(int n);

	/// \brief Metoda wirtualna - dodaje wartość na wskazanej pozycji
	///
	/// \param a - wartość, która ma zostać dopisana
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
	/// \return referencja na obiekt aghVector<T>
	aghVector& operator=(aghContainer<T> const& a);
};
// --------------------------------------------------------------

template<class T>
void aghVector<T>::resize(int x)
{
	if (x < 0)
		throw aghException(0, "Nowy rozmiar mniejszy od 0", __FILE__, __LINE__);
	T *tmp = new T[size()];
	if (size() > 0)
	{
		for (int i = 0; i < size(); i++)
		{
			tmp[i] = at(i);
		}
		delete[] tab;
	}
	tab = new T[x];
	if (x < size())
		rozmiar = x;
	if (size() > 0)
	{
		for (int i = 0; i < size(); i++)
		{
			tab[i] = tmp[i];
		}
	}
    delete[] tmp;
	rozmiar = x;
}
// --------------------------------------------------------------

template<class T>
aghVector<T>::aghVector(aghContainer<T> & a)
{
	rozmiar = 0;
	resize(a.size());
	for (int i = 0; i < size(); i++)
	{
		tab[i] = a.at(i);
	}
}
// --------------------------------------------------------------

template<class T>
aghVector<T>::~aghVector()
{
	delete[] tab;
	rozmiar = 0;
}
// --------------------------------------------------------------

template<class T>
T& aghVector<T>::at(int x) const
{
	if ((x < 0) || (x >= size()))
		throw aghException(0, "Indeks poza zasiêgiem", __FILE__, __LINE__);
	return tab[x];
}
// --------------------------------------------------------------

template<class T>
bool aghVector<T>::insert(int p, T const& a)
{
	if (p > size()) return false;
	resize(size() + 1);
	for (int i = size() - 1; i > p; i--)
	{
		tab[i] = tab[i - 1];
	}
	tab[p] = a;
	return true;
}
// --------------------------------------------------------------

template<class T>
bool aghVector<T>::remove(int x)
{
	if (x >= size()) return false;
	for (int i = x; i < size() - 1; i++)
	{
		tab[i] = tab[i + 1];
	}
	resize(size() - 1);
	return true;
}
// --------------------------------------------------------------

template<class T>
aghVector<T>& aghVector<T>::operator=(aghContainer<T> const& a)
{
	if (this == &a)
		return *this;
	resize(a.size());
	for (int i = 0; i < size(); i++)
		tab[i] = a.at(i);
	return *this;
}
// --------------------------------------------------------------

#endif // AGH_VECTOR
