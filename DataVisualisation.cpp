//============================================================================
// Name         : DataVisualisation.cpp
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 10.01.2020.
// Description  : Definicije funkcija klase koja predstavlja vizualizaciju
// podataka sortiranja kao sto su funkcije za racunanje kordinata,
// iscrtavanje tabela, teksta, kruzica, ...
//============================================================================

#include "DataVisualisation.h"
#include "MyText.h"
#include <FL/fl_ask.h>
#include "Table.h"
#include <algorithm>

/**
 * Konstruktor sa parametrima
 */
DataVisualisation::DataVisualisation(const Point& xy, const int w, const int h,
	const string& title, const SortData& sd) :
	Window(xy, w, h, title),
	m_sd(sd),
	// Instanciranje prozora sa nesortiranim podacima.
	data_preview(Point(0, 0), DATA_WINDOW_W, DATA_WINDOW_H,
		"Pregled informacija", DATA_INFO_HEADER,
		m_sd.get_iteration(0).getGroupOfFlights().toTableData()),
	m_current_iter(0),
	m_num_of_cities(sd.get_iteration(0).getGroupOfFlights().toCitiesTable().size()),
	m_num_of_iterations(sd.get_number_of_iterations()),
	m_horizontal_position(m_num_of_cities),
	m_vertical_position(m_num_of_iterations),
	next(Point(620, 550), 80, 30, "Dalje", cb_nextButton),
	preview(Point(500, 550), 80, 30, "Pregled", cb_previewButton),
	buttonPushed(false)
{
	// Sakrivanje prozora koji prikazuje informacije jer se
	// automatski prikazuje prilikom instanciranja.
	data_preview.hide();

	calculate_position_of_circles();

	draw_init_data();

	attach(next);
	attach(preview);

	size_range(w, h, w, h);

	// Postavljanje funckije koja ce se desiti
	// kada korisnik pritisne na dugme X
	callback(cb_quitButton);
}

/**
 * Destruktor.
 * Oslobadja svu dinamicko zauzetu memoriju.
 */
DataVisualisation::~DataVisualisation()
{
	const auto action = [](const Shape* s) { delete s; };

	std::for_each(m_dynamic_allocated.begin(), m_dynamic_allocated.end(), action);
}

bool DataVisualisation::wait_for_button()
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
void DataVisualisation::cb_nextButton(Address, Address pw)
{
	reference_to<DataVisualisation>(pw).nextButtonHandler();
}

/**
 * Funkcija koja iscrtava sledecu iteraciju tj kruzice,
 * linije i text dokle god ne dodje do kraja, a na poslednjoj
 * iteraciji i tabelu. Nakon toga ako se pritisne dugme next
 * prozor ce se zatvoriti.
 */
void DataVisualisation::nextButtonHandler()
{
	if (++m_current_iter + 1 < m_num_of_iterations)
	{
		draw_iteration_data();
		return;
	}

	if (m_current_iter + 1 == m_num_of_iterations)
	{
		draw_final_data();
		return;
	}

	buttonPushed = true;
	hide();
}

/**
 * Funkcija koja se poziva pritiskom na dugme prikaz. Sluzi
 * da zadovolji tip funkcije koji se moze postaviti kao poziv
 * i sluzi da pozove drugu funkciju koja se zaista izvrsava.
 */
void DataVisualisation::cb_previewButton(Address, Address pw)
{
	reference_to<DataVisualisation>(pw).previewButtonHandler();
}

/**
 * Funkcija menja tekst prozora za prikaz teksta u tabeli na
 * podatke iz trenutne iteracije i prikazuje prozor.
 */
void DataVisualisation::previewButtonHandler()
{
	data_preview.change_text(m_sd.get_iteration(m_current_iter).getGroupOfFlights().toTableData());
	data_preview.show();
}

/**
 * Funkcija koja se poziva kada korisnik klikne X. Tada se
 * pojavljuje forma za proveru da li je korisnik siguran i
 * ako jeste program prestaje sa radom a ako nije ne desava
 * nista.
 */
void DataVisualisation::cb_quitButton(Fl_Widget* widget, void*)
{
	if (!fl_ask("Da li zelite da izadjete iz programa?"))
	{
		return;
	}

	exit(0);
}

/**
 * Funkcija koja pravi novu instancu tabele sa podacima iz
 * zeljene iteracije i postavlja na zadato mesto.
 *
 * @param iter - zeljena iteracije.
 * @param xy - pozicija tabele na ekranu.
 */
void DataVisualisation::add_table(const int iter, const Point& xy)
{
	const std::vector<std::string> header_data = { "Country" };
	const std::vector<std::vector<std::string>> cities_data = m_sd.get_iteration(iter).getGroupOfFlights().toCitiesTable();

	Table* t = new Table(xy, VISUAL_TABLE_W, VISUAL_TABLE_H, header_data, cities_data);
	m_dynamic_allocated.push_back(t);

	attach(*t);
}

/**
 * Funkcija koja racuna horizontalnu i vertikalnu poziciju
 * kruzica na ekranu i smesta u odgovarajuci vektor.
 */
void DataVisualisation::calculate_position_of_circles()
{
	calculate_horizontal_position_of_circles();
	calculate_vertical_position_of_circles();
}

/**
 * Funkcija racuna horizontalnu poziciju kruzica na ekranu
 * i smesta ih u m_horizontal_position.
 */
void DataVisualisation::calculate_horizontal_position_of_circles()
{
	// Racunica je ista kao i racunica za horizontalne linije tabele.
	const int distance_between_two_circles = VISUAL_TABLE_H / (m_num_of_cities + 1);
	const int offset = (VISUAL_TABLE_H / (m_num_of_cities + 1)) / 2;
	const int end_at = VISUAL_TABLE_H + VISUAL_TABLE_H_OFFSET;

	int i = 0;
	const auto calculate_circle_positions = [&i, end_at, distance_between_two_circles, offset]()
	{
		return end_at - distance_between_two_circles * ++i + offset;
	};

	std::generate(m_horizontal_position.begin(),
		m_horizontal_position.end(),
		calculate_circle_positions);
}

/**
 * Funkcija racuna vertikalnu poziciju kruzica na ekranu
 * i smesta ih u m_vertical_position.
 */
void DataVisualisation::calculate_vertical_position_of_circles()
{
	// Racunica je ista kao i racunica za vertikalne linije tabele.
	const int distance_between_two_circles = VISUAL_CIRCLE_AREA_W / (m_num_of_iterations - 1);
	const int start_at = VISUAL_FIRST_TABLE_W_OFFSET + VISUAL_TABLE_W + 25;

	int i = -1;
	const auto calculate_circle_positions = [&i, start_at, distance_between_two_circles]()
	{
		return start_at + distance_between_two_circles * ++i;
	};

	std::generate(m_vertical_position.begin(),
		m_vertical_position.end(),
		calculate_circle_positions);
}

/**
 * Funkcija crta pocetne delove ekrana prilikom prvog prikazivanja
 * tj tabelu sa nesortiranim podacima, kruzice i tekst iznad njih.
 */
void DataVisualisation::draw_init_data()
{
	// Iscrtavanje tabele sa nesortiranim podacima.
	add_table(0, Point(VISUAL_FIRST_TABLE_W_OFFSET, VISUAL_TABLE_H_OFFSET));

	writeText(0, "Unsorted data");
	draw_column_of_circles(m_current_iter);
}

/*
 * Funkcija iscrtava trenutnu iteraciju tj kruzice u odredjenoj koloni,
 * povezuje ih sa prethodnim i ispisuje tekst sa brojem iteracije iznad.
 */
void DataVisualisation::draw_iteration_data()
{
	draw_lines_between_iterations(m_current_iter - 1, m_current_iter);
	writeText(m_current_iter, std::string("Iteration" + std::to_string(m_current_iter)));
	draw_column_of_circles(m_current_iter);
}

/**
 * Funkcija koja iscrtava poslednju iteraciju tj kada su svi podaci
 * sortirani, povezuje ih sa prethodnom iteracijom i ispisujhe tekst
 * iznad njih.
 */
void DataVisualisation::draw_final_data()
{
	// Iscrtavanje tabele sa sortiranim podacima.
	add_table(m_current_iter, Point(VISUAL_SECOND_TABLE_W_OFFSET, VISUAL_TABLE_H_OFFSET));

	draw_lines_between_iterations(m_current_iter - 1, m_current_iter);

	writeText(m_current_iter, "Sorted data");
	draw_column_of_circles(m_current_iter);
}

/**
 * Funkcija koja iscrtava kolonu sa kruzicima na osnovu
 * informacija iz vektora sa pozicijama i trenutnoj
 * iteraciji.
 *
 * @param column_index - broj kolone koji se iscrtava.
 */
void DataVisualisation::draw_column_of_circles(const int column_index)
{
	int i = -1;

	std::vector<int>::iterator it = m_horizontal_position.begin();

	while (it != m_horizontal_position.end())
	{
		Circle* c = new Circle(Point(m_vertical_position.at(column_index), m_horizontal_position.at(++i)), 7);
		c->set_color(Color::black);
		c->set_fill_color(Color::black);
		m_dynamic_allocated.push_back(c);

		attach(*c);
		++it;
	}

	Fl::redraw();
}

/**
 * Funkcija koja iscrtava linije izmedju dve iteracije. Ona u prethodnoj
 * iteraciji trazi kruzic u sledecoj koji joj odgovara po broju leta
 * a nakon toga ih povezuje uz pomoc pozicija iz vektora koji cuvaju pozicije.
 *
 * @param first_iter_index - broj prve iteracije iz podataka o iteracijama.
 * @param second_iter_index - broj druge iteracije iz podataka o iteracijama.
 */
void DataVisualisation::draw_lines_between_iterations(const unsigned int first_iter_index,
	const unsigned int second_iter_index)
{
	// Dobijanje informacija o letovima iz iteracija.
	const std::vector<Flight> first_iter_data = m_sd.get_iteration(first_iter_index).getGroupOfFlights().getFlights();
	const std::vector<Flight> second_iter_data = m_sd.get_iteration(second_iter_index).getGroupOfFlights().getFlights();

	std::vector<Flight>::const_iterator it = first_iter_data.cbegin();

	const auto condition = [&it](const Flight& f) { return it->getFlightNo().compare(f.getFlightNo()) == 0; };

	int iter_num = 0;
	while (it != first_iter_data.end())
	{
		// Trazenje odgovarajucih kruzica.
		const std::vector<Flight>::const_iterator it_found = std::find_if(second_iter_data.cbegin(), second_iter_data.cend(), condition);

		// Racunanje indeksa kruzica druge iteracije.
		const int index_found = it_found - second_iter_data.cbegin();

		// Povezivanje kruzica.
		Line* l = new Line(Point(m_vertical_position.at(first_iter_index),
			m_horizontal_position.at(m_num_of_cities - 1 - iter_num)),
			Point(m_vertical_position.at(second_iter_index),
				m_horizontal_position.at(m_num_of_cities - 1 - index_found)));
		l->set_color(Color::black);
		m_dynamic_allocated.push_back(l);

		attach(*l);
		++iter_num;
		++it;
	}
}

/**
 * Funkcija koja ispisuje zeljeni tekst iznad zeljene
 * kolone sa kruzicima pod uglom od -90 stepeni.
 *
 * @param column_index - broj kolone iznad koje se iscrtava.
 * @param text - tekst koji se ispisuje.
 */
void DataVisualisation::writeText(const int column_index, const std::string& text)
{
	MyText* t = new MyText(Point(m_vertical_position.at(column_index), 50), text, -90);
	m_dynamic_allocated.push_back(t);

	attach(*t);
}