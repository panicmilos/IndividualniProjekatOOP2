//============================================================================
// Name         : Arguments.h
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 30.12.2019.
// Description  : Deklaracija strukture koja poseduje sve potrebne atribute
// koji su potrebni za cuvanje argumenata sa komandne linije/graficke sprege.
//============================================================================

#pragma once

#include <string>
struct Arguments
{
public:
	// Atributi
	std::string input_path;		// Cuva putanju ulazne datoteke
	std::string output_path;	// Cuva putanju izlazne datoteke
	int criterion;				// Cuva redni broj odabranog kriterijuma
	int sorter;					// Cuva redni broj odabrane metode za sortiranje

	// Konstruktori
	Arguments() = default;
	Arguments(const std::string& input_path, const std::string& output_path,
		const int criterion, const int sorter);
	Arguments(const Arguments& args);
};