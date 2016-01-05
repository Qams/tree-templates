/**
* \file aghContainer.h
* \author Kamil G. & Kamil K.
* \date 19.05.2015
* \brief Definicja szablonu klasy abstrakcyjnej aghContainer - klasy bazowej dla szablonów struktur danych
*/
// -------------------------------------------------------------------------

#ifndef AGH_CONTAINER
#define AGH_CONTAINER
// --------------------------------------------------------------

#include <iostream>
// --------------------------------------------------------------

using namespace std;
// --------------------------------------------------------------

/**
* \class aghContainer
* \author Kamil G. & Kamil K.
* \date 19.05.2015
* \brief Definicja szablonu klasy abstrakcyjnej aghContainer - klasy bazowej dla szablonów struktur danych
*/
template<class T>
class aghContainer
{
public:
	/// \brief Konstruktor bezparametrowy
	aghContainer() { }

	/// \brief Destruktor
	virtual ~aghContainer() { }

	/// \brief Dodaje wartość na koniec struktury
	///
	/// \param e- wartość, która ma zostać dopisana
	/// \return nie zwraca wartości
	void append(T const& a);

	/// \brief Metoda abstrakcyjna - dodaje wartość na wskazanej pozycji
	///
	/// \param a - wartość, która ma zostać dopisana
	/// \param x - nr pozycji na której ma zostać wpisany element
	/// \return true jezeli operacja sie powiodla, false jeśli pozycja nie istnieje
	virtual bool insert(int x, T const& a) = 0;

	/// \brief Podmienia wartość na wskazanej pozycji
	///
	/// \param a - wartość, która ma zostać dopisana
	/// \param x - nr pozycji na której ma zostać zamieniony element
	/// \return true jezeli operacja sie powiodla, false jeżli pozycja nie istnieje
	bool replace(int x, T const& a);

	/// \brief Metoda abstrakcyjna - zwraca ilość elementów w strukturze
	///
	/// \return ilość elementów
	virtual int size(void) const = 0;

	/// \brief Metoda abstrakcyjna - zwraca element z danej pozycji
	///
	/// \param x - pozycja elementu w strukturze
	/// \return wartość elementu poprzez adres
	virtual T& at(int x) const = 0;

	/// \brief Metoda abstrakcyjna - usuwa element ze struktury
	///
	/// \param x - pozycja elementu w strukturze
	/// \return true jezeli operacja sie powiodla, false jeżeli pozycja nie istnieje
	virtual bool remove(int) = 0;

	/// \brief Usuwa wszystkie elementy ze struktury
	///
	/// \return nie zwraca wartości
	void clear(void);

	/// \brief Sprawdza czy w strukturze nie ma elementów
	///
	/// \return true, jeżeli struktura pusta, false jeżeli jest jakikolwiek element
	bool isEmpty(void);

	/// \brief Zwraca pozycję na której znajduje się element
	///
	/// \param _value - wartość szukanego elementu
	/// \param _from - pozycja, od której ma się rozpocząć wyszukiwanie
	/// \return nr pierwszej pozycji na której znaleziono element, lub -1 dla braku rezultatu
	int indexOf(T const& _value, int _from = 0) const;

	/// \brief Zwraca informacją czy w strukturze znajduje się element
	///
	/// \param _value - wartość szukanego elementu
	/// \param _from - pozycja, od której ma się rozpocząć wyszukiwanie
	/// \return true jeżeli znaleziono element, w przeciwnym wypadku false
	bool contains(T const& _value, int _from = 0) const;

	/// \brief Operator== - porównuje czy struktury są identyczne
	///
	/// \param right - struktura do przyrównania
	/// \return true jeżeli struktury są takie same, w przeciwnym wypadku false
	bool operator==(aghContainer<T> const& right);

	/// \brief Operator== - porównuje czy struktury są różne
	///
	/// \param right - struktura do przyrównania
	/// \return true jeżeli struktury są różne, w przeciwnym wypadku false
	bool operator!=(aghContainer<T> const& right);

	/// \brief Zwraca element z danej pozycji
	///
	/// \param n - pozycja elementu w strukturze
	/// \return wartość elementu poprzez adres
	T& operator[](int n) const;

	/// \brief Operator+= - dopisuje elementy do struktury
	///
	/// \param right - struktura z elementami do dopisania
	/// \return referencja na obiekt aghContainer<T>
	aghContainer<T>& operator+=(aghContainer<T> const& right);

	/// \brief Operator+= - dopisuje element do struktury
	///
	/// \param element - element do dopisania
	/// \return referencja na obiekt aghContainer<T>
	aghContainer<T>& operator+=(T const& element);

	/// \brief Operator<< - dopisuje elementy do struktury
	///
	/// \param right - struktura z elementami do dopisania
	/// \return referencja na obiekt aghContainer<T>
	aghContainer<T>& operator<<(aghContainer<T> const& right);

	/// \brief Operator<< - dopisuje element do struktury
	///
	/// \param element - element do dopisania
	/// \return referencja na obiekt aghContainer<T>
	aghContainer<T>& operator<<(T const& element);

	/// \brief Operator= - zamienia wartość struktury na nową
	///
	/// \param a - struktura do skopiowania
	/// \return referencja na obiekt aghContainer<T>
	aghContainer<T>& operator=(aghContainer<T>& a);

	/// \brief Funkcja zaprzyjaźniona - operator<< - wypisuje elementy struktury
	///
	/// \param out - referencja na strumień ostream, do którego nastąpi wpisanie wartości
	/// \param right - struktura do wypisania
	/// \return referencja na obiekt ostream
	template<class F>
	friend ostream& operator<<(ostream& out, aghContainer<F> const& right);
};
// --------------------------------------------------------------

template<class T>
void aghContainer<T>::append(T const& a)
{
	insert(size(), a);
}
// --------------------------------------------------------------

template<class T>
bool aghContainer<T>::replace(int x, T const& a)
{
	if (x < size()){
		remove(x);
		insert(x, a);
		return true;
	}
	return false;
}
// --------------------------------------------------------------

template<class T>
void aghContainer<T>::clear(void)
{
	while (size() > 0)
	{
		remove(0);
	}
}
// --------------------------------------------------------------

template<class T>
bool aghContainer<T>::isEmpty(void)
{
	if (size() == 0) return true;
	else return false;
}
// --------------------------------------------------------------

template<class T>
int aghContainer<T>::indexOf(T const& _value, int _from) const
{
	if (_from >= 0)
		for (int i = _from; i < size(); i++)
		{
			if (at(i) == _value) return i;
		}
	return (-1);
}
// --------------------------------------------------------------

template<class T>
bool aghContainer<T>::contains(T const& _value, int _from) const
{
	if (this->indexOf(_value, _from) >= 0)
        return true;
	return false;
}
// --------------------------------------------------------------

template<class T>
bool aghContainer<T>::operator==(aghContainer<T> const& right)
{
	if (size() != right.size()) return false;
	else
	{
		for (int i = 0; i < size(); i++)
		{
			if (at(i) != right.at(i)) return false;
		}
	}
	return true;
}
// --------------------------------------------------------------

template<class T>
bool aghContainer<T>::operator!=(aghContainer<T> const& right)
{
	return !(this->operator==(right));
}
// --------------------------------------------------------------

template<class T>
T& aghContainer<T>::operator[](int n) const
{
	return at(n);
}
// --------------------------------------------------------------

template<class T>
aghContainer<T>& aghContainer<T>::operator+=(aghContainer<T> const& right)
{
	for (int i = 0; i < right.size(); i++)
	{
		append(right.at(i));
	}
	return *this;
}
// --------------------------------------------------------------

template<class T>
aghContainer<T>& aghContainer<T>::operator+=(T const& element)
{
	append(element);
	return *this;
}
// --------------------------------------------------------------

template<class T>
aghContainer<T>& aghContainer<T>::operator<<(aghContainer<T> const& right)
{
	return this->operator+=(right);
}
// --------------------------------------------------------------

template<class T>
aghContainer<T>& aghContainer<T>::operator<<(T const& element)
{
	return this->operator+=(element);
}
// --------------------------------------------------------------

template<class T>
aghContainer<T>& aghContainer<T>::operator=(aghContainer<T>& a)
{
	if (this == &a)
		return *this;
	clear();
	for (int i = 0; i < a.size(); i++)
		append(a.at(i));
	return *this;
}
// --------------------------------------------------------------

template<class T>
ostream& operator<<(ostream& out, aghContainer<T> const& right)
{
	for (int i = 0; i < right.size(); i++)
	{
		out << right.at(i) << " ";
	}
	out << endl;
	return out;
}
// --------------------------------------------------------------

#endif // AGH_CONTAINER
