//============================================================================
// Name         : str_utils.cpp
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija svih dodatnih funkcija za rad nad
// stringovima.
//============================================================================

#include "str_utils.h"
#include <algorithm>

/**
 * Funkcija koja proverava da li string sadrzi
 * samo numericke karaktere.
 *
 * @param text - string koji se proverava.
 *
 * @return true ako sadrzi samo numericke karaktere
 * a u suprotnom vraca false.
 */
bool is_numeric(const std::string& text)
{
	if (text.length() == 0)
	{
		return false;
	}

	const auto condition = [](char c) { return '0' <= c && c <= '9'; };

	return std::all_of(text.cbegin(), text.cend(), condition);
}
/**
 * Funkcija koja string u obliku HH:mm parsira i
 * smesta u instance strukture Time.
 *
 * @param time - string koji se parsira.
 *
 * @return instanca strukture Time koji sadrzi
 * sate i minute.
 */
Time get_hours_and_minutes_from_string(const std::string& time)
{
	const std::string::const_iterator delimeter = std::find(time.cbegin(), time.cend(), ':');

	if (delimeter == time.cend())
	{
		return Time{ -1, -1 };
	}

	const std::string hours(time.begin(), delimeter);
	const std::string minutes(delimeter + 1, time.end());

	return Time{ std::stoi(hours), std::stoi(minutes) };
}