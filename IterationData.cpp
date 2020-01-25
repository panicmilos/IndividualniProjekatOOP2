//============================================================================
// Name         : IterationData.cpp
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 19.01.2019.
// Description  : Definicija funkcija klase koja cuva sve podatke jedne iteracije
// sort algoritma kao sto su konstruktori, geteri i funkcije za rad sa
// ulazno/izlaznom jedinicom.
//============================================================================

#pragma once

#include "IterationData.h"

/**
 * Konstruktor sa parametrima.
 */
IterationData::IterationData(const unsigned int iter_num, const unsigned int num_of_comparison,
	const unsigned int num_of_changes, const GroupOfFlights& gof) :
	m_iter_num(iter_num),
	m_num_of_comparison(num_of_comparison),
	m_num_of_changes(num_of_changes),
	m_gof(gof)
{
}

/**
 * Geter za redni broj iteracije.
 */
unsigned int IterationData::getIterNum() const
{
	return m_iter_num;
}

/**
 * Geter za broj poredjenja.
 */
unsigned int IterationData::getNumOfComparison() const
{
	return m_num_of_comparison;
}

/**
 * Geter za redosled elemenata.
 */
unsigned int IterationData::getNumOfChanges() const
{
	return m_num_of_changes;
}

/**
 * Geter za broj zamena elemenata.
 */
const GroupOfFlights& IterationData::getGroupOfFlights() const
{
	return m_gof;
}

/**
 * Preklapanje operatora << za rad sa izlaznim tokovima.
 * Ispisuje sve podatke jedne iteracije algoritma za
 * sortiranje.
 *
 * @param out - izlazni tok na koji se ispisuju podaci.
 * @param iter_data - objekat cije se informacije
 * o iteraciji ispisuju na izlazni tok.
 *
 * @return objekat izlaznog toka.
 */
std::ostream& operator << (std::ostream& out, const IterationData& iter_data)
{
	out << "Iteration number: " << iter_data.m_iter_num << '\n';
	out << "Number of comparison: " << iter_data.m_num_of_comparison << '\n';
	out << "Number of changes: " << iter_data.m_num_of_changes << '\n';
	out << "Flights: \n";
	out << iter_data.m_gof << '\n';

	return out;
}