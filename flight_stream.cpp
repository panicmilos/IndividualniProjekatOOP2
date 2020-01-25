//============================================================================
// Name         : flight_stream.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Implementation of the Flight class
//============================================================================

#include "flight_stream.h"

/**
 * Konstruktor sa parametrima.
 */
flight_stream::flight_stream(const std::string& line) :
	m_line(line),
	str_it(m_line.begin()),
	m_eof(0)
{
};

/**
 * Geter za kraj.
 */
bool flight_stream::eof() const
{
	return m_eof;
}

/**
 * Preklapanje operatora >> za rad sa flight tokom.
 * Parsira liniju od mesta iteratora do sledeceg ';' ili
 * kraja linije i smesta u predat string.
 *
 * @param attribute - string u koji se smesta parsirani deo.
 *
 * @return objekat flight toka.
 */
flight_stream& flight_stream::operator >> (std::string& attribute)
{
	// Trazenje pozicije ';'.
	std::string::iterator char_found_it = std::find(str_it, m_line.end(), ';');

	// Smestanje dela od iteratora do iteratora iz std::find u atribut.
	attribute.assign(str_it, char_found_it);

	// Pomeranje iteratora na poziciju sledece reci ili na kraj iteratora.
	str_it = (char_found_it != m_line.end() - 1) ? char_found_it + 2 : m_line.end();

	// Postavljanje indikatora kraja.
	m_eof = (str_it == m_line.end()) ? 1 : 0;

	return *this;
}