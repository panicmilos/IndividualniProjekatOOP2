//============================================================================
// Name         : DataInfoDialog.cpp
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija konstruktora i funkcija klase DataInfoDialog
// za ispis texta u tabeli na grafickom dijalogu.
//============================================================================

#include "DataInfoDialog.h"
#include "MyText.h"
#include <FL/fl_ask.h>

/**
 * Konstruktor sa parametrima
 */
DataInfoDialog::DataInfoDialog(const Point& xy, const int w, const int h, const string& title,
	const std::vector <std::string>& header_data,
	const std::vector < std::vector <std::string>>& table_data) :
	Window(xy, w, h, title),
	t(Point(DATA_TABLE_OFFSET, DATA_TABLE_OFFSET), DATA_TABLE_W, DATA_TABLE_H, header_data, table_data),
	title(title),
	next(Point(360, 470), 80, 30, "Dalje", cb_nextButton),
	buttonPushed(false)
{
	writeText();

	attach(t);
	attach(next);

	// Onemogucavanje da se prozoru moze promeniti velicina ili maximizovati.
	size_range(DATA_WINDOW_W, DATA_WINDOW_H, DATA_WINDOW_W, DATA_WINDOW_H);

	// Onemogucavanje da se pristupa drugim prozorima dok se ne ugasi ovaj.
	set_modal();
}

/**
 * Destruktor
 */
DataInfoDialog::~DataInfoDialog()
{
}

bool DataInfoDialog::wait_for_button()
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
 * Funkcija koja se poziva pritiskom na dugme next. Sluzi
 * da zadovolji tip funkcije koji se moze postaviti kao poziv
 * i sluzi da pozove drugu funkciju koja se zaista izvrsava.
 */
void DataInfoDialog::cb_nextButton(Address, Address pw)
{
	reference_to<DataInfoDialog>(pw).nextButtonHandler();
}

/**
 * Funkcija koja sakriva ovaj prozor.
 */
void DataInfoDialog::nextButtonHandler()
{
	buttonPushed = true;
	hide();
}

/**
 * Funkcija koja ispisuje sav tekst na prozoru.
 */
void DataInfoDialog::writeText()
{
	static MyText title(Point(300, 35), "Podaci iz datoteke:");

	attach(title);
}

/**
 * Funkcija koja menja sadrzaj tabele.
 *
 * @param new_table_data - nov sadrzaj tabele
 */
void DataInfoDialog::change_text(const std::vector < std::vector <std::string>>& new_table_data)
{
	// Vracanje stanja dugmeta na false.
	buttonPushed = false;

	// Promena teksta uz pomoc funkcije iz tabele.
	t.change_text(new_table_data);

	// Ponovno postavljanje teksta zato sto se naziv prozora
	// promeni nakon ponovnog prikazivanja.
	set_label(title);

	// Ponovno iscrtavanje sadrzaja na prozoru kako bi se
	// promene prikazale.
	Fl::redraw();
}