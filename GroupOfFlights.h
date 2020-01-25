//============================================================================
// Name         : GroupOfFlights.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija funkcija klase grupe letova kao sto su
// konstruktori, geteri i funkcijame za rad sa ulazno/izlaznom jedinicom.
//============================================================================

#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include "Flight.h"

class GroupOfFlights
{
private:
	std::vector<Flight> m_flVec;	// Vektor koji cuva letove
public:
	// Konstruktori
	GroupOfFlights() = default;
	GroupOfFlights(const std::vector<Flight>& flVec);
	GroupOfFlights(const GroupOfFlights& gof);

	// Geteri
	std::vector<Flight>& getFlights();
	const std::vector<Flight>& getFlights() const;

	// Funkcije koje podatke stavlju u vektor za ispis u tabelu
	std::vector<std::vector<std::string>> toTableData() const;
	std::vector<std::vector<std::string>> toCitiesTable() const;

	// Funkcije za rad sa ulazno/izlaznom jedinicom
	friend std::istream& operator >>(std::istream& in, GroupOfFlights& gof);
	friend std::ostream& operator <<(std::ostream& out, const GroupOfFlights& gof);
};

// Deklaracija
std::istream& operator >>(std::istream& in, GroupOfFlights& gof);
std::ostream& operator <<(std::ostream& out, const GroupOfFlights& gof);