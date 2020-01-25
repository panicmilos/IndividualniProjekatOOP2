//============================================================================
// Name         : ComparatorFactory.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 30.12.2019.
// Description  : Deklaracija klase koja predstavlja "Factory" pattern a
// svrha je da vrati odgovarajuci komparator za zadati broj.
//============================================================================

#pragma once

#include <map>
#include "Comparators.h"

class ComparatorFactory
{
private:
	// Mapa u kojoj se cuvaju funkcije koje kreiraju komparatore
	// Koristi se umesto switch case kao "Strategy" pattern
	typedef std::map < int, Comparator * (ComparatorFactory::*)() > pfmap_type;
	pfmap_type creation_list;

	// Funkcije koje sluze za kreiranje komparatora
	Comparator* create_flnum_comparator();
	Comparator* create_dstn_comparator();
	Comparator* create_dprt_comparator();
	Comparator* create_gtnum_comparator();

public:
	// Enumeracije kriterijuma preko brojeva
	enum OPTIONS
	{
		FLIGHTNUM = 1,
		DESTINATION = 2,
		DEPARTURETIME = 3,
		GATENUM = 4
	};

	// Konstruktor
	ComparatorFactory();

	// Geter za odgovarajuci komparator
	Comparator* getComparator(const int choice);
};
