//============================================================================
// Name          : main.cpp
// Author	     : Milos Panic
// Date          : 27.12.2019.
// Last Modified : 09.01.2020.
// Description   : Glavna funkcija programa gde se instanciraju svi bitni
// objekti i povezuju u jednu celinu.
//============================================================================

#include <iostream>
#include <fstream>
#include "GroupOfFlights.h"
#include "ArgumentsDialog.h"
#include "DataVisualisation.h"
#include "ComparatorFactory.h"
#include "SortFactory.h"

int main()
{
	try
	{
		// Prikupljanje argumenata uz pomoc ArgumentsDialog
		ArgumentsDialog win(Point(0, 0), ARG_WINDOW_W, ARG_WINDOW_H, "Odabir argumenata");
		win.wait_for_button();
		Arguments args = win.getArguments();

		// Citanje podataka iz datoteke.
		std::ifstream in_file(args.input_path);
		in_file.ignore(256, '\n'); // Preskakanje zaglavlja
		GroupOfFlights gof;
		in_file >> gof;
		in_file.close();

		// Pravljenje komparatora i algoritma za sortiranje uz pomocu argumenata.
		ComparatorFactory cf;
		std::unique_ptr<Comparator> comp(cf.getComparator(args.criterion));

		SortFactory sf;
		std::unique_ptr<Sort> sorter(sf.getSorter(args.sorter));

		// Sortiranje podataka
		SortData sd = sorter->sort(gof.getFlights(), &*comp);

		// Ispis informacija o sortiranju u izlaznu datoteku.
		std::ofstream out_file(args.output_path);
		if (!out_file.is_open())
		{
			error("output path is not valid!");
		}
		out_file << sd;
		out_file.close();

		// Vizualizacija podataka.
		DataVisualisation dv(Point(0, 0), VISUAL_WINDOW_W, VISUAL_WINDOW_H, "Pregled sortiranja", sd);
		dv.wait_for_button();
	}
	catch (std::exception & e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}