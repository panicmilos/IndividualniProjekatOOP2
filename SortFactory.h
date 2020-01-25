//============================================================================
// Name         : SortFactory.h
// Author       : Milos Panic
// Date         : 01.01.2020.
// Last Modified: 01.01.2020.
// Description  : Deklaracija klase koja predstavlja "Factory" pattern a
// svrha je da vrati odgovarajuci sorter za zadati broj.
//============================================================================

#pragma once

#include <map>
#include "Sort.h"

class SortFactory
{
private:
	// Mapa u kojoj se cuvaju funkcije koje kreiraju sortere
	// Koristi se umesto switch case kao "Strategy" pattern
	typedef std::map < int, Sort * (SortFactory::*)() > pfmap_type;
	pfmap_type creation_list;

	// Funkcije koje sluze za kreiranje sortera
	Sort* create_selection_sort();
	Sort* create_merge_sort();

public:
	// Enumeracije sortera preko brojeva
	enum OPTIONS
	{
		SELECTION = 1,
		MERGE = 2
	};

	// Konstruktor
	SortFactory();

	// Geter za odgovarajuci sorter
	Sort* getSorter(const int choice);
};
