//============================================================================
// Name         : GroupOfFlights.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja grupise vise letova u jednu klasu
// sa svojim konstruktorima, geterima i funkcijama za rad sa ulazno/izlaznom
// jedinicom.
//============================================================================

#include "GroupOfFlights.h"
#include <algorithm>

/**
 * Konstruktor sa parametrima.
 */
GroupOfFlights::GroupOfFlights(const std::vector<Flight>& flVec) :
	m_flVec(flVec)
{
}

/**
 * Konstruktor kopije.
 */
GroupOfFlights::GroupOfFlights(const GroupOfFlights& gof) :
	m_flVec(gof.m_flVec)
{
}

/**
 * Geter za letove.
 */
std::vector<Flight>& GroupOfFlights::getFlights()
{
	return m_flVec;
}

/**
 * Geter za za letove po konstantnoj referenci.
 */
const std::vector<Flight>& GroupOfFlights::getFlights() const
{
	return m_flVec;
}

/**
 * Funkcija smesta podatke svakog od letova pretvara u vektor
 * koji potom takodje smesta u vektor koji sluzi sa ispis
 * podataka u tabeli.
 *
 * @return vektor sa vektorima podataka letova.
 */
std::vector<std::vector<std::string>> GroupOfFlights::toTableData() const
{
	std::vector<std::vector<std::string>> table_data;

	const auto add_to_data_vec = [&table_data](const Flight& f) { table_data.push_back(f.toVector()); };
	std::for_each(m_flVec.begin(), m_flVec.end(), add_to_data_vec);

	return table_data;
}

/**
 * Funkcija smesta ime destinacije svakog od letova u vektor
 * koji potom takodje smesta u vektor koji sluzi sa ispis
 * podataka u tabeli prilikom vizualizacije.
 *
 * @return vektor sa vektorima imena destinacija letova.
 */
std::vector<std::vector<std::string>> GroupOfFlights::toCitiesTable() const
{
	std::vector<std::vector<std::string>> table_data;

	const auto add_to_data_vec = [&table_data](const Flight& f)
	{
		std::vector<std::string> city;
		city.push_back(f.getDestination());
		table_data.push_back(city);
	};
	std::for_each(m_flVec.begin(), m_flVec.end(), add_to_data_vec);

	return table_data;
}

/**
 * Preklapanje operatora >> za rad sa ulaznim tokovima.
 * Ucitava let po let sa ulaza i zatim ih smesta u
 * vektor letova.
 *
 * @param in - ulazni tok sa kojeg se citaju podaci.
 * @param gof - objekat u kojem se cuvaju letovi.
 *
 * @return objekat ulaznog toka.
 */
std::istream& operator >>(std::istream& in, GroupOfFlights& gof)
{
	while (!in.eof())
	{
		Flight f;
		in >> f;
		gof.m_flVec.push_back(f);
	}

	return in;
}

/**
 * Preklapanje operatora << za rad sa izlaznim tokovima.
 * Ispisuje podatke svih letova na izlazni tok uz pomoc
 * iteratora izlaznog toka.
 *
 * @param out - izlazni tok na koji se ispisuju podaci.
 * @param f - objekat koji sadrzi sve letove koji se
 * ispisuju.
 *
 * @return objekat izlaznog toka.
 */
std::ostream& operator <<(std::ostream& out, const GroupOfFlights& gof)
{
	std::ostream_iterator<Flight> out_it(out, "\n");
	std::copy(gof.m_flVec.begin(), gof.m_flVec.end(), out_it);

	return out;
}