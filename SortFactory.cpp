//============================================================================
// Name         : SortFactory.cpp
// Author       : Milos Panic
// Date         : 01.01.2020
// Last Modified: 09.01.2020
// Description  : Definicija konstruktora, funkcija koje prave sortere i
// funkcije koja vraca odgovarajuci sorter u zavisnosti od zadatog broja.
//============================================================================

#include "SortFactory.h"
#include <functional>

/**
 * Podrazumevani konstruktor.
 * Za svaki od sortera ubacuje referencu do funkcije
 * koja se koristi za kreiranje instance sortera u mapu.
 */
SortFactory::SortFactory()
{
	creation_list[OPTIONS::SELECTION] = &SortFactory::create_selection_sort;
	creation_list[OPTIONS::MERGE] = &SortFactory::create_merge_sort;
}

/**
 * Funkcija pravi instancu selection sorta.
 *
 * @return instanca sortera.
 */
Sort* SortFactory::create_selection_sort()
{
	return new SelectionSort;
}

/**
 * Funkcija pravi instancu merge sorta.
 *
 * @return instanca sortera.
 */
Sort* SortFactory::create_merge_sort()
{
	return new MergeSort;
}

/**
 * Funkcija pravi instancu sortera u zavisnosti
 * od zadatog broja algoritma za sortiranje.
 *
 * @param choice - broj algoritma za sortiranje.
 *
 * @return instanca sortera.
 */
Sort* SortFactory::getSorter(const int choice)
{
	return std::invoke(creation_list[choice], this);	// poziva funkciju iz mape
}