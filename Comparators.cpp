//============================================================================
// Name         : Comparators.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 30.12.2019.
// Description  : Definicija compare funkcija za svaku klasu
// koja nasledjuje Comparator klasu.
//============================================================================

#include "Comparators.h"
#include "math_utils.h"

/**
 * Funkcija koja poredi dva leta po njihovom broju leta.
 *
 * @param f1 - prvi let.
 * @param f2 - drugi let.
 *
 * @return 0 ako su jednaki ili brojevna razlika izmedju
 * dva stringa.
 */
int FlightNumComparator::compare(const Flight& f1, const Flight& f2)
{
	return f1.getFlightNo().compare(f2.getFlightNo());
}

/**
 * Funkcija koja poredi dva leta po njihovoj destinaciji.
 *
 * @param f1 - prvi let.
 * @param f2 - drugi let.
 *
 * @return 0 ako su jednaki ili brojevna razlika izmedju
 * dva stringa.
 */
int DestinationComparator::compare(const Flight& f1, const Flight& f2)
{
	return f1.getDestination().compare(f2.getDestination());
}

/**
 * Funkcija koja poredi dva leta po njihovom vremenu poletanja.
 *
 * @param f1 - prvi let.
 * @param f2 - drugi let.
 *
 * @return 0 ako su jednaki ili brojevna razlika izmedju
 * dva vremena.
 */
int DepartureTimeComparator::compare(const Flight& f1, const Flight& f2)
{
	return time_to_minutes(f1.getDeparture()) - time_to_minutes(f2.getDeparture());
}

/**
 * Funkcija koja poredi dva leta po njihovom broju kapija.
 *
 * @param f1 - prvi let.
 * @param f2 - drugi let.
 *
 * @return 0 ako su jednaki ili brojevna razlika izmedju
 * dva stringa.
 */
int GateNumComparator::compare(const Flight& f1, const Flight& f2)
{
	return f1.getGateNo().compare(f2.getGateNo());
}