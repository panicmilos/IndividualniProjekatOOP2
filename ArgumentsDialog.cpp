//============================================================================
// Name         : ArgumentsDialog.cpp
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 11.01.2020.
// Description  : Definicija konstruktora i funkcija klase ArgumentsDialog
// za ispis texta na ekranu i cuvanje argumenata prilikom pritiska na dugme.
//============================================================================

#include "ArgumentsDialog.h"
#include "MyText.h"
#include <FL/fl_ask.h>
#include "validations.h"

/**
 * Konstruktor sa parametrima
 */
ArgumentsDialog::ArgumentsDialog(const Point& xy, const int w, const int h, const string& title) :
	Window(xy, w, h, title),
	input_path(Point(50, 40), 500, 30, ""),
	output_path(Point(50, 120), 500, 30, ""),
	criterion_choice(Point(50, 330), 200, 30, ""),
	sorter_choice(Point(350, 330), 200, 30, ""),
	next(Point(260, 380), 80, 30, "Dalje", cb_nextButton),
	buttonPushed(false)
{
	writeTexts();

	attach(input_path);
	attach(output_path);
	attach(criterion_choice);
	attach(sorter_choice);
	attach(next);

	size_range(w, h, w, h);

	// Postavljanje funckije koja ce se desiti
	// kada korisnik pritisne na dugme X
	callback(cb_quitButton);
}

/**
 * Destruktor
 */
ArgumentsDialog::~ArgumentsDialog()
{
}

bool ArgumentsDialog::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
	show();
	buttonPushed = false;
	#if 1
	// Simpler handler
	while (!buttonPushed) Fl::wait();
	Fl::redraw();
	#else
	// To handle the case where the user presses the X button in the window frame
	// to kill the application, change the condition to 0 to enable this branch.
	Fl::run();
	#endif
	return buttonPushed;
}

/**
 * Geter za prikupljene argumente u instanci strukture Arguments
 */
Arguments& ArgumentsDialog::getArguments()
{
	return args;
}

/**
 * Funkcija koja se poziva pritiskom na dugme next. Sluzi
 * da zadovolji tip funkcije koji se moze postaviti kao poziv
 * i sluzi da pozove drugu funkciju koja se zaista izvrsava.
 */
void ArgumentsDialog::cb_nextButton(Address, Address pw)
{
	reference_to<ArgumentsDialog>(pw).nextButtonHandler();
}

/**
 * Funkcija koja prikuplja sve unesene argumente iz ulaznih
 * polja i zatim proverava da li su ispravni i gasi prozor.
 * Ako su ispravni smesta ih u args a ako nisu ispisuje
 * poruku da nisu ispravni.
 */
void ArgumentsDialog::nextButtonHandler()
{
	const std::string input = input_path.get_string();
	const std::string output = output_path.get_string();
	const std::string criterion = criterion_choice.get_string();
	const std::string sorter = sorter_choice.get_string();

	// Provera da li su argumenti ispravni
	if (!validate_arguments(input, output, criterion, sorter))
	{
		// Pravi mali obavestajni dijalog sa porukom.
		fl_alert("Argumenti nisu ispravni!");
		return;
	}

	args = Arguments(input, output, std::stoi(criterion), std::stoi(sorter));
	buttonPushed = true;
	hide();
}

/**
 * Funkcija koja se poziva kada korisnik klikne X. Tada se
 * pojavljuje forma za proveru da li je korisnik siguran i
 * ako jeste program prestaje sa radom a ako nije ne desava
 * nista.
 */
void ArgumentsDialog::cb_quitButton(Fl_Widget* widget, void*)
{
	if (!fl_ask("Da li zelite da izadjete iz programa?"))
	{
		return;
	}

	exit(0);
}

/**
 * Funkcija koja ispisuje sve potrebne tekstove na prozoru.
 */
void ArgumentsDialog::writeTexts()
{
	writePathTexts();
	writeCriteionTexts();
	writeSortTexts();
}

/**
 * Funkcija koja ispisuje tekst vezan za ulaznu i izlaznu
 * putanju na prozoru.
 */
void ArgumentsDialog::writePathTexts()
{
	static MyText input_path_text(Point(150, 30), "Uneti putanju ulazne datoteke:");
	static MyText output_path_text(Point(150, 110), "Uneti putanju izlazne datoteke:");

	attach(input_path_text);
	attach(output_path_text);
}

/**
 * Funkcija koja ispisuje tekst vezan za kriterijume po kojima
 * se mogu podaci sortirati.
 */
void ArgumentsDialog::writeCriteionTexts()
{
	static MyText select_criterion(Point(50, 190), "Odaberite kriterijum:");
	static MyText by_flnum_text(Point(50, 230), "1. Po broju leta");
	static MyText by_dstn_text(Point(50, 260), "2. Po odredistu");
	static MyText by_dprt_text(Point(50, 290), "3. Po vremenu polaska");
	static MyText by_gtnum_text(Point(50, 320), "4. Po broju kapije");

	attach(select_criterion);
	attach(by_flnum_text);
	attach(by_dstn_text);
	attach(by_dprt_text);
	attach(by_gtnum_text);
}

/**
 * Funkcija koja ispisuje tekst vezan za metode uz pomoc kojih
 * se podaci mogu sortirati.
 */
void ArgumentsDialog::writeSortTexts()
{
	static MyText select_sorter(Point(350, 190), "Odaberite sorter:");
	static MyText selection_sort_text(Point(350, 230), "1. Selection sort");
	static MyText merge_sort_text(Point(350, 260), "2. Merge sort");

	attach(select_sorter);
	attach(selection_sort_text);
	attach(merge_sort_text);
}