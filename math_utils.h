//============================================================================
// Name         : math_utils.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija svih dodatnih funkcija za rad sa
// odredjenom vrstom matematike ili logickih izraza.
//============================================================================

#pragma once

#include <string>

int time_to_minutes(const std::string& time);
bool is_in_range(const int number, const int lower, const int upper);