//============================================================================
// Name         : SortData.cpp
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 10.01.2019.
// Description  : Definicija funkcija klase koja cuva sve iteracije jednog
// algoritma kao sto su konstruktor, geteri, funkcije za rad sa iteracijama
// i izlaznom jedinicom.
//============================================================================

#include "SortData.h"

/**
 * Konstruktor sa parametrima.
 * Zahteva vektor sa letovima koji predstavlja
 * pocetne nesortirane podatke.
 */
SortData::SortData(const std::vector<Flight>& initial_data)
{
	// Dodavanje pocetne iteracije sa nesortiranim podacima.
	m_iterations.push_back(IterationData(0, 0, 0, GroupOfFlights(initial_data)));
}

/**
 * Konstruktor sa parametrima.
 * Zahteva vektor sa svim iteracijama.
 */
SortData::SortData(const std::vector<IterationData>& iterations) :
	m_iterations(iterations)
{
}

/**
 * Konstruktor kopije.
 */
SortData::SortData(const SortData& sd) :
	m_iterations(sd.m_iterations)
{
}

/**
 * Geter za odredjenu iteraciju.
 *
 * @parat index - index zeljene iteracije iz vektora.
 *
 * @return zeljena iteracija po konstantnoj referenci.
 */
const IterationData& SortData::get_iteration(const int index) const
{
	return m_iterations.at(index);
}

/**
 * Funkcija koja dodaje iteraciju u vektor iteracija.
 *
 * @param iter_data - iteracija koja se dodaje.
 */
void SortData::add_iteration(const IterationData& iter_data)
{
	m_iterations.push_back(iter_data);
}

/**
 * Funkcija koja vraca broj iteracija koje se nalaze
 * u vektoru sa iteracijama.
 *
 * @return broj iteracija.
 */
size_t SortData::get_number_of_iterations() const
{
	return m_iterations.size();
}

/**
 * Preklapanje operatora << za rad sa izlaznim tokovima.
 * Ispisuje sve podatke iteracija algoritma za
 * sortiranje.
 *
 * @param out - izlazni tok na koji se ispisuju podaci.
 * @param sd - objekat cije se informacije
 * o iteracijama ispisuju na izlazni tok.
 *
 * @return objekat izlaznog toka.
 */
std::ostream& operator <<(std::ostream& out, const SortData& sd)
{
	// Ispisivanje nesortiranih podataka bez informacija o
	// iteraciji, poredjenju, ...
	out << "Unsorted flights: \n";
	out << sd.m_iterations[0].getGroupOfFlights() << '\n';

	// Ispis svih informacija o iteracijama bez prve i poslednje.
	std::ostream_iterator<IterationData> out_it(out);
	std::copy(sd.m_iterations.begin() + 1, sd.m_iterations.end() - 1, out_it);

	// Ispisivanje sortiranih podataka bez informacija o
	// iteraciji, poredjenju, ...
	out << "Sorted flights: \n";
	out << sd.m_iterations[sd.m_iterations.size() - 1].getGroupOfFlights() << '\n';

	return out;
}