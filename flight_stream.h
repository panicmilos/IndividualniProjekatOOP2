//============================================================================
// Name         : flight_stream.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja se ponasa kao string_stream, parsira
// liniju po pravilu da se svaki deo linije zavrsava sa ';' i uz pomoc
// operatora ulaznog toka smesta u neki dat string.
//============================================================================

#pragma once

#include <string>

class flight_stream
{
private:
	std::string m_line;					// Linija koja se parsira
	std::string::iterator str_it;		// Iterator kroz string koji pamti poziciju ';'
	bool m_eof;							// Indikator kraja linije
public:
	// Konstruktor
	flight_stream(const std::string& line);

	// Geter za kraj
	bool eof() const;

	// Funkcija za rad sa ulaznim operatorom
	flight_stream& operator >> (std::string& attribute);
};