//============================================================================
// Name         : SortData.h
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 01.01.2020.
// Description  : Deklaracija klase koja predstavlja grupu iteracija jednog
// sortiranja algoritma. Ima konstrutkor koji zahteva inicijalne podatke,
// funkcija za rad sa iteracijama i funkciju za rad sa izlaznom jedinicom.
// Klasa je osmisljena tako da su prva iteracija nesortirani podaci a
// poslednja sortirani sto znaci da ima 2 + broj iteracija algoritma.
//============================================================================

#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include "IterationData.h"

class SortData
{
private:
	std::vector<IterationData> m_iterations;	// Vektor koji cuva iteracije
public:
	// Konstruktori
	SortData(const std::vector<Flight>& initial_data);
	SortData(const std::vector<IterationData>& iterations);
	SortData(const SortData& sd);

	// Geter za odredjenu iteraciju
	const IterationData& get_iteration(const int index) const;

	// Funkcija za dodavanje iteracija
	void add_iteration(const IterationData& iter_data);

	// Funkcija koja vraca broj iteracija
	size_t get_number_of_iterations() const;

	// Funkcija za rad sa izlaznom jedinicom
	friend std::ostream& operator <<(std::ostream& out, const SortData& sd);
};

// Deklaracija
std::ostream& operator <<(std::ostream& out, const SortData& sd);