//============================================================================
// Name         : Sort.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 18.01.2020.
// Description  : Definicija funkcija klasa naslednica za sortiranje i
// ostalih pomocnih funkcija.
//============================================================================

#include "Sort.h"
#include <algorithm>
#include "vector_utils.h"

/**
 * Funkcija koja izvrsava algoritam sortiranja nad vektorom podataka
 * sa predatim kriterijumom i informacije o iteraciji algoritma
 * smesta u instancu podataka o sortiranju.
 *
 * @param data - vektor podataka koji se sortira.
 * @param comp - kriterijum po kojem se elementi porede.
 * @param sd - instanca klase koja cuva podatke o iteraciji.
 */
void SelectionSort::do_sort_algorithm(std::vector<Flight>& data, Comparator* comp, SortData& sd)
{
	using flight_it = std::vector<Flight>::iterator;

	for (flight_it i = data.begin(); i != data.end(); ++i)
	{
		flight_it it_min = i;

		for (flight_it j = i + 1; j != data.end(); ++j)
		{
			if (comp->compare(*it_min, *j) > 0)
			{
				it_min = j;
			}
		}

		if (i != it_min)
		{
			std::swap(*i, *it_min);
		}

		sd.add_iteration(IterationData(i - data.begin() + 1, data.size() - (i - data.begin() + 1), (i != it_min) ? 2 : 0, data));
	}
}

/**
 * Funkcija koja sortira podatke uz pomoc zadatog kriterijuma i
 * vraca informacije o sortiranju kako bi se mogla uraditi
 * vizualizacija podataka.
 *
 * @param data - vektor podataka koji se sortira.
 * @param comp - kriterijum po kojem se elementi porede.
 *
 * @return instanca klase koja ima sve podatke o iteracijama sortiranja.
 */
SortData SelectionSort::sort(std::vector<Flight>& data, Comparator* comp)
{
	// Inicijalizacija objekta koji cuva podatke o iteracijama uz
	// postavku inicijalnih nesortiranih podataka kao nulta iteracija.
	SortData sd(data);

	// Sortiranje podataka i cuvanje informacija o iteracijama.
	do_sort_algorithm(data, comp, sd);

	// Dodavanje krajnjih sortiranih podataka.
	sd.add_iteration(IterationData(-1, -1, -1, data));

	return sd;
}

/**
 * Funckija koja uzima dva dela izdeljenog vektora i spaja ih tako da budu sortirana
 * dokle god se jedan od ta dva dela skroz ne isprazne. Zatim ostatak jednog od dva
 * vektora stavlja u temp i posle toga taj sortirani deo vraca u pocetan vektor.
 *
 * @param vec - vektor u koji se spajaju dva sortirana podvektora.
 * @param temp - pomocni vektor koji se koristi za spajanje dva vektora.
 * @param comp - kriterijum po kojem se elementi porede.
 * @param begin - pozicija prvog elementa u izdeljenom vektoru ili celom vektoru
 * @param middle - pozicija sredisnjeg elementa u izdeljenom vektoru ili celom vektoru
 * @param end - pozicija poslednjeg elementa u izdeljenom vektoru ili celom vektoru
 *
 * @return strukturu koja sadrzi informacije o broju poredjenja
 * i broju promene elemenata tokom izvrsavanja spajanja.
 */
MergeSort::MergeInfo MergeSort::merge(std::vector<Flight>& data, std::vector<Flight>& temp,
	Comparator* comp, const int begin, const int middle, const int end)
{
	int i = begin;
	int j = middle + 1;
	int k = begin;

	const auto condition = [](const Flight& f1, const Flight& f2) { return f1.getFlightNo().compare(f2.getFlightNo()) == 0; };

	while (i <= middle && j <= end)
	{
		temp[k++] = (comp->compare(data[i], data[j]) > 0) ? data[j++] : data[i++];
	}

	std::copy(data.begin() + i, data.begin() + middle + 1, temp.begin() + k);
	std::copy(data.begin() + j, data.begin() + end + 1, temp.begin() + k);

	std::vector<Flight>::iterator iter_end = temp.begin() + (k + (middle - i) + (end - j) + 1);
	const int num_of_changes = count_not_equal_if(temp.begin() + begin, iter_end + 1, data.begin() + begin, condition);
	std::copy(temp.begin() + begin, temp.begin() + end + 1, data.begin() + begin);

	return MergeInfo{ k - begin, num_of_changes };
}

/**
 * Funkcija koja izvrsava algoritam sortiranja nad vektorom podataka
 * sa predatim kriterijumom i informacije o iteraciji algoritma
 * smesta u instancu podataka o sortiranju.
 *
 * @param data - vektor podataka koji se sortira.
 * @param comp - kriterijum po kojem se elementi porede.
 * @param sd - instanca klase koja cuva podatke o iteraciji.
 */
void MergeSort::do_sort_algorithm(std::vector<Flight>& data, Comparator* comp, SortData& sd)
{
	std::vector<Flight> temp(data.size());

	int i = 1, iter_num = 1;
	// Iteracije 1, 2, 4, 8, 16, 2^n, ukupan broj elemenata.
	// zato sto se radi bottom up merge sort algoritam.
	while (i < data.size())
	{
		int j = 0, total_num_of_comparison = 0, total_num_of_changes = 0;
		// Prolaz kroz niz 1 po 1, 2 po 2, 4 pod 4, 8 po 8, ...
		while (j < data.size() - 1)
		{
			const int left = j;
			const int right = ((j + i - 1) >= data.size()) ? (data.size() - 1) : (j + i - 1);
			const int middle = (left + right) / 2;

			auto [num_of_comparison, num_of_changes] = merge(data, temp, comp, left, middle, right);

			total_num_of_comparison += num_of_comparison;
			total_num_of_changes += num_of_changes;
			j += i;
		}

		sd.add_iteration(IterationData(iter_num++, total_num_of_comparison, total_num_of_changes, data));

		i *= 2;
		// Spajanje dva dela vektora prilikom poslednje iteracije.
		if (i >= data.size()) {
			i = i / 2;

			auto [num_of_comparison, num_of_changes] = merge(data, temp, comp, 0, (i - 1), data.size() - 1);
			sd.add_iteration(IterationData(iter_num, num_of_comparison, num_of_changes, data));

			i = data.size();
		}
	}
}

/**
 * Funkcija koja sortira podatke uz pomoc zadatog kriterijuma i
 * vraca informacije o sortiranju kako bi se mogla uraditi
 * vizualizacija podataka.
 *
 * @param data - vektor podataka koji se sortira.
 * @param comp - kriterijum po kojem se elementi porede.
 *
 * @return instanca klase koja ima sve podatke o iteracijama sortiranja.
 */
SortData MergeSort::sort(std::vector<Flight>& data, Comparator* comp)
{
	// Inicijalizacija objekta koji cuva podatke o iteracijama uz
	// postavku inicijalnih nesortiranih podataka kao nulta iteracija.
	SortData sd(data);

	// Sortiranje podataka i cuvanje informacija o iteracijama.
	do_sort_algorithm(data, comp, sd);

	// Dodavanje krajnjih sortiranih podataka.
	sd.add_iteration(IterationData(-1, -1, -1, data));

	return sd;
}