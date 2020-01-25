//============================================================================
// Name         : math_utils.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija svih dodatnih funkcija za rad sa
// odredjenom vrstom matematike ili logickih izraza.
//============================================================================

#include "math_utils.h"
#include "str_utils.h"

/**
 * Funkcija koja string u obliku HH:mm pretvara u minute.
 *
 * @param time - string koji se pretvara u minute.
 *
 * @return broj minuta.
 */
int time_to_minutes(const std::string& time)
{
	auto [hours, minutes] = get_hours_and_minutes_from_string(time);	// structured bindings

	return hours * 60 + minutes;
}

/**
 * Funkcija koja proverava da li je broj u zadatom intervalu.
 *
 * @param number - broj koji se proverava.
 * @param lower - broj koji predstavlja donju granicu.
 * @param upper - broj koji predstavlja gornju granicu.
 *
 * @return true u slucaju da jeste ili false ako nije.
 */
bool is_in_range(const int number, const int lower, const int upper)
{
	return lower <= number && number <= upper;
}