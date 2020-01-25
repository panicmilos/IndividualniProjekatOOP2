//============================================================================
// Name         : Flight.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 19.01.2019.
// Description  : Definicija funkcija klase leta kao sto su konstruktori,
// geteri i funckije za rad sa ulazno/izlaznom jedinicom.
//============================================================================

#include "Flight.h"
#include "flight_stream.h"
#include <iomanip>

/**
 * Konstruktor sa parametrima.
 */
Flight::Flight(const std::string& flightNo, const std::string& destination,
	const std::string& departure, const std::string& gateNo) :
	m_flightNo(flightNo),
	m_destination(destination),
	m_departure(departure),
	m_gateNo(gateNo)
{
}

/**
 * Konstruktor kopije.
 */
Flight::Flight(const Flight& f) :
	m_flightNo(f.m_flightNo),
	m_destination(f.m_destination),
	m_departure(f.m_departure),
	m_gateNo(f.m_gateNo)
{
}

/**
 * Geter za broj leta.
 */
std::string Flight::getFlightNo() const
{
	return m_flightNo;
}

/**
 * Geter za destinaciju.
 */
std::string Flight::getDestination() const
{
	return m_destination;
}

/**
 * Geter za vreme polaska.
 */
std::string Flight::getDeparture() const
{
	return m_departure;
}

/**
 * Geter za broj kapije.
 */
std::string Flight::getGateNo() const
{
	return m_gateNo;
}

/**
 * Funkcija koja sve atribute leta smesta u vektor.
 *
 * @return vektor sa atributima.
 */
std::vector<std::string> Flight::toVector() const
{
	std::vector<std::string> data;

	data.push_back(m_flightNo);
	data.push_back(m_destination);
	data.push_back(m_departure);
	data.push_back(m_gateNo);

	return data;
}

/**
 * Preklapanje operatora >> za rad sa ulaznim tokovima.
 * Ucitava liniju sa ulaza i zatim uz pomoc
 * flight_stream unosi u atribute.
 *
 * @param in - ulazni tok sa kojeg se citaju podaci.
 * @param f - objekat u koji se upisuju informacije o letu.
 *
 * @return objekat ulaznog toka.
 */
std::istream& operator >>(std::istream& in, Flight& f)
{
	std::string line;
	getline(in, line);

	// Instanca klase flight_stream koja se ponasa kao
	// stringstream, parsira liniju i upisuje u dat string.
	flight_stream fs(line);

	// Upisivanje podataka iz ulaznog toka u argumente instance leta.
	fs >> f.m_destination >> f.m_departure >> f.m_flightNo >> f.m_gateNo;

	return in;
}

/**
 * Preklapanje operatora << za rad sa izlaznim tokovima.
 * Ispisuje sve podatke jednog leta na izlazni tok.
 *
 * @param out - izlazni tok na koji se ispisuju podaci.
 * @param f - objekat cije se informacije o letu ispisuju
 * u izlazni tok.
 *
 * @return objekat izlaznog toka.
 */
std::ostream& operator <<(std::ostream& out, const Flight& f)
{
	return out << std::left << std::setw(12) << f.m_destination
		<< "  " << ((f.m_departure.length() == 4) ? "0" : "") << f.m_departure
		<< "  " << f.m_flightNo << "  " << f.m_gateNo;
}