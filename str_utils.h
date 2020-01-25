//============================================================================
// Name         : str_utils.h
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija svih dodatnih funkcija za rad nad
// stringovima.
//============================================================================

#pragma once

#include <string>
#include "Time.h"

bool is_numeric(const std::string& text);
Time get_hours_and_minutes_from_string(const std::string& time);