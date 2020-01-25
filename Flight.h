//============================================================================
// Name         : Flight.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja predstavlja jedan let sa svojim
// konstruktorima, geterima i funkcijama za rad sa ulazno/izlaznom jedinicom.
//============================================================================
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Flight
{
private:
	std::string m_flightNo;			// Redni broj leta
	std::string m_destination;		// Destinacija
	std::string m_departure;		// Vreme polaska
	std::string m_gateNo;			// Broj kapije
public:
	// Konstruktori
	Flight() = default;
	Flight(const std::string& flightNo, const std::string& destination,
		const std::string& departure, const std::string& gateNo);
	Flight(const Flight& f);

	// Geteri za atribute
	std::string getFlightNo() const;
	std::string getDestination() const;
	std::string getDeparture() const;
	std::string getGateNo() const;

	// Funkcija koja atribute stavlja u vektor
	std::vector<std::string> toVector() const;

	// Funkcije za rad sa ulazno/izlaznom jedinicom
	friend std::istream& operator >>(std::istream& in, Flight& f);
	friend std::ostream& operator <<(std::ostream& out, const Flight& f);
};

// Deklaracija
std::istream& operator >>(std::istream& in, Flight& f);
std::ostream& operator <<(std::ostream& out, const Flight& f);