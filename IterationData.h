//============================================================================
// Name         : IterationData.h
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja cuva sve podatke jedne iteracije
// sort algoritma sa konstruktorima, geterima i funkciju za rad sa
// izlaznom jedinicom.
//============================================================================

#pragma once

#include <iostream>
#include <vector>
#include "GroupOfFlights.h"

class IterationData
{
private:
	unsigned int m_iter_num;			// Redni broj iteracije
	unsigned int m_num_of_comparison;	// Broj poredjenja
	unsigned int m_num_of_changes;		// Broj zamena elemenata
	GroupOfFlights m_gof;				// Redosled elemenata
public:
	// Konstruktori
	IterationData(const unsigned int iter_num, const unsigned int num_of_comparison,
		const unsigned int num_of_changes, const GroupOfFlights& gof);

	// Geteri za atribute
	unsigned int getIterNum() const;
	unsigned int getNumOfComparison() const;
	unsigned int getNumOfChanges() const;
	const GroupOfFlights& getGroupOfFlights() const;

	// Funkcija za rad sa izlaznom jedinicom
	friend std::ostream& operator << (std::ostream& out, const IterationData& iter_data);
};

// Deklaracija
std::ostream& operator << (std::ostream& out, const IterationData& iter_data);
