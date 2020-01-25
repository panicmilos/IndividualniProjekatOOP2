//============================================================================
// Name         : io_utils.cpp
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija svih dodatnih funkcija za rad nad
// ulazno/izlazni tokovima.
//============================================================================

#include "io_utils.h"
#include <fstream>

/**
 * Funkcija koja proverava da li postoji fajl na zadatoj
 * putanji tako sto proba da ga otvori.
 *
 * @param path - putanja na kojoj se proverava da li
 * postoji fajl.
 *
 * @return true ako postoji ili false ako ne postoji.
 */
bool file_exists(const std::string& path)
{
	std::ifstream in(path);

	if (!in.is_open())
	{
		return false;
	}

	in.close();

	return true;
}