//============================================================================
// Name         : Sort.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 19.01.2020.
// Description  : Deklaracija apstraktne klase Sort koju nasledjuju
// druge klase koje predstavljaju razlicite algoritme sortiranja.
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>
#include "SortData.h"
#include "Comparators.h"

class Sort
{
public:
	// Konstruktor
	Sort() = default;

	// Apstraktna funkcija za sortiranje koja prima
	// podatke i kriterijum sortiranja
	virtual SortData sort(std::vector<Flight>& data, Comparator* comp) = 0;
};

class SelectionSort : public Sort
{
private:
	// Funkcija koja izvrsava algoritam za sortiranje
	void do_sort_algorithm(std::vector<Flight>& data, Comparator* comp, SortData& sd);

public:
	// Konstruktor
	SelectionSort() = default;

	// Funkcija za sortiranje koja vraca podatke o sortiranju
	SortData sort(std::vector<Flight>& data, Comparator* comp) override;
};

class MergeSort : public Sort
{
private:
	// Pomocna struktura u kojoj se cuvaju podaci tokom
	// spajanja delova vektora.
	struct MergeInfo
	{
		int num_of_comparison;
		int num_of_changes;
	};

	// Funkcija koja spaja dva dela vektora u jedan sortiran.
	MergeInfo merge(std::vector<Flight>& data, std::vector<Flight>& temp,
		Comparator* comp, const int begin, const int middle, const int end);

	// Funkcija koja izvrsava algoritam za sortiranje
	void do_sort_algorithm(std::vector<Flight>& data, Comparator* comp, SortData& sd);

public:
	// Konstruktor
	MergeSort() = default;

	// Funkcija za sortiranje koja vraca podatke o sortiranju
	SortData sort(std::vector<Flight>& data, Comparator* comp) override;
};