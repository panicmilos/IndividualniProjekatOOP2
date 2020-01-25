//============================================================================
// Name         : Arguments.cpp
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 30.12.2019.
// Description  : Definicija konstruktora sa parametrima i kopije strukture
// Arguments.
//============================================================================

#include "Arguments.h"

/**
 * Konstruktor sa parametrima
 */
Arguments::Arguments(const std::string& input_path, const std::string& output_path,
	const int criterion, const int sorter) :
	input_path(input_path),
	output_path(output_path),
	criterion(criterion),
	sorter(sorter)
{
}

/**
 * Konstruktor kopije
 */
Arguments::Arguments(const Arguments& args) :
	input_path(args.input_path),
	output_path(args.output_path),
	criterion(args.criterion),
	sorter(args.sorter)
{
}