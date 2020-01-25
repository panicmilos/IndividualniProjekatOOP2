//============================================================================
// Name         : ComparatorFactory.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 09.12.2019.
// Description  : Definicija konstruktora, funkcija koje prave komparatore i
// funkcije koja vraca odgovarajuci komparator u zavisnosti od zadatog broja.
//============================================================================

#include "ComparatorFactory.h"
#include <functional>

/**
 * Podrazumevani konstruktor.
 * Za svaki od kriterijuma ubacuje referencu do funkcije
 * koja se koristi za kreiranje instance komparatora u mapu.
 */
ComparatorFactory::ComparatorFactory()
{
	creation_list[OPTIONS::FLIGHTNUM] = &ComparatorFactory::create_flnum_comparator;
	creation_list[OPTIONS::DESTINATION] = &ComparatorFactory::create_dstn_comparator;
	creation_list[OPTIONS::DEPARTURETIME] = &ComparatorFactory::create_dprt_comparator;
	creation_list[OPTIONS::GATENUM] = &ComparatorFactory::create_gtnum_comparator;
}

/**
 * Funkcija pravi instancu komparatora koji poredi
 * brojeve letova.
 *
 * @return instanca komparatora.
 */
Comparator* ComparatorFactory::create_flnum_comparator()
{
	return new FlightNumComparator;
}

/**
 * Funkcija pravi instancu komparatora koji poredi
 * destinacije letova.
 *
 * @return instanca komparatora.
 */
Comparator* ComparatorFactory::create_dstn_comparator()
{
	return new DestinationComparator;
}

/**
 * Funkcija pravi instancu komparatora koji poredi
 * vreme polaska letova.
 *
 * @return instanca komparatora.
 */
Comparator* ComparatorFactory::create_dprt_comparator()
{
	return new DepartureTimeComparator;
}

/**
 * Funkcija pravi instancu komparatora koji poredi
 * brojeve kapija letova.
 *
 * @return instanca komparatora.
 */
Comparator* ComparatorFactory::create_gtnum_comparator()
{
	return new GateNumComparator;
}

/**
 * Funkcija pravi instancu komparatora u zavisnosti
 * od zadatog broja kriterijuma.
 *
 * @param choice - broj kriterijuma.
 *
 * @return instanca komparatora.
 */
Comparator* ComparatorFactory::getComparator(const int choice)
{
	return std::invoke(creation_list[choice], this);	// poziva funkciju iz mape
}