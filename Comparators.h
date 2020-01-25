//============================================================================
// Name         : Comparators.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 30.12.2019.
// Description  : Deklaracija apstrakne klase Comparator koje nasledjuju
// druge klase, jedna za po svaki kriterijum sortiranja letova.
//============================================================================

#pragma once

#include "Flight.h"

class Comparator
{
public:
	// Konstruktor
	Comparator() = default;

	// Apstraktna funkcija za poredjenje dva leta
	virtual int compare(const Flight& f1, const Flight& f2) = 0;
};

class FlightNumComparator : public Comparator
{
public:
	// Konstruktor
	FlightNumComparator() = default;

	// Apstraktna funkcija za poredjenje dva leta
	int compare(const Flight& f1, const Flight& f2) override;
};

class DestinationComparator : public Comparator
{
public:
	// Konstruktor
	DestinationComparator() = default;

	// Apstraktna funkcija za poredjenje dva leta
	int compare(const Flight& f1, const Flight& f2) override;
};

class DepartureTimeComparator : public Comparator
{
public:
	// Konstruktor
	DepartureTimeComparator() = default;

	// Apstraktna funkcija za poredjenje dva leta
	int compare(const Flight& f1, const Flight& f2) override;
};

class GateNumComparator : public Comparator
{
public:
	// Konstruktor
	GateNumComparator() = default;

	// Apstraktna funkcija za poredjenje dva leta
	int compare(const Flight& f1, const Flight& f2) override;
};