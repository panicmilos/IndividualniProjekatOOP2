//============================================================================
// Name         : Table.cpp
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija funkcija klase sluzi da prikaze zeljene podatke
// u obliku tabele koja se moze postaviti u nekom grafickom prozoru/dijalogu.
//============================================================================

#include "Table.h"
#include <algorithm>
#include "MyText.h"

/**
 * Konstruktor sa parametrima
 *
 * @throws runtime_error u slucaju da se pravi tabela bez podataka.
 */
Table::Table(const Point& xy, const int w, const int h,
	const std::vector <std::string>& header_data,
	const std::vector < std::vector <std::string>>& table_data) :
	Rectangle(xy, w, h),
	header_data(header_data),
	table_data(table_data),
	vertical_lines(header_data.size()),
	horizontal_lines(table_data.size())
{
	if (header_data.size() == 0 || table_data.size() == 0)
	{
		error("Nije moguce napraviti praznu tabelu!");
	}

	set_color(Color::black);
	calculate_positions_of_lines();
}

/**
 * Funkcija racuna vertikalnu poziciju linija u tabeli
 * i smesta u atribut vertical_lines.
 */
void Table::calculate_position_of_vertical_lines()
{
	const int column_length = Rectangle::width() / header_data.size();
	const int start_at = point(0).x;

	int i = -1;
	const auto calculate_column_positions = [&i, start_at, column_length]()
	{
		return start_at + column_length * ++i;
	};

	std::generate(vertical_lines.begin(), vertical_lines.end(), calculate_column_positions);
}

/**
 * Funkcija racuna horizontalnu poziciju linija u tabeli
 * i smesta u atribut horizontal_lines.
 */
void Table::calculate_position_of_horizontal_lines()
{
	// Racuna se od donjeg dela tabele zato sto ima greske
	// prilikom zaokruzivanja visine reda i na ovaj nacin ce
	// se sva greska nalaziti u redu zaglavlja sto izgleda
	// bolje nego da je poslednji red veci od ostalih.
	const int row_height = Rectangle::height() / (table_data.size() + 1);
	const int end_at = point(0).y + Rectangle::height();

	int i = 0;
	const auto calculate_row_positions = [&i, end_at, row_height]()
	{
		return end_at - row_height * ++i;
	};

	std::generate(horizontal_lines.begin(), horizontal_lines.end(), calculate_row_positions);
}

/**
 * Funkcija koja racuna poziciju vertikalnih
 * i horizontalnih linija.
 */
void Table::calculate_positions_of_lines()
{
	calculate_position_of_vertical_lines();
	calculate_position_of_horizontal_lines();
}

/**
 * Funkcija koja iscrtava vertikalne linije na
 * ekranu koristeci pozicije iz vertical_lines.
 */
void Table::draw_vertical_lines() const
{
	const int from = point(0).y;
	const int to = from + Rectangle::height();

	const auto draw_vertical_line = [from, to](const int pos)
	{
		fl_line(pos, from, pos, to);
	};

	// Prva linija je gornja linija tabele koja se iscrtava kao pravougaonik
	// pa je nema potrebe iscrtati ponovo.
	std::for_each(vertical_lines.begin() + 1, vertical_lines.end(), draw_vertical_line);
}

/**
 * Funkcija koja iscrtava horizontalne linije na
 * ekranu koristeci pozicije iz horizontal_lines.
 */
void Table::draw_horizontal_lines() const
{
	const int from = point(0).x;
	const int to = from + Rectangle::width();

	const auto draw_horizontal_line = [from, to](const int pos)
	{
		fl_line(from, pos, to, pos);
	};

	std::for_each(horizontal_lines.begin(), horizontal_lines.end(), draw_horizontal_line);
}

/**
 * Funkcija koja iscrtava vertikalne i horizontalne
 * linije na ekranu praveci oblik tabele.
 */
void Table::draw_table_lines() const
{
	draw_vertical_lines();
	draw_horizontal_lines();
}

/**
 * Funkcija koja ispisuje tekst u redu zaglavlja
 * na ekranu iz header_data.
 */
void Table::write_header_text() const
{
	// Racunanje y pozicije teksta u redu zaglavlja kolone.
	const int pos = point(0).y + (Rectangle::height() / (table_data.size() + 1)) / 2 + 10;

	const std::vector <int>* vertical_lines_p = &vertical_lines;

	int i = -1;
	const auto write_text = [&i, pos, vertical_lines_p](const std::string& text)
	{
		MyText t(Point(vertical_lines_p->at(++i % vertical_lines_p->size()) + 10, pos), text);
		t.draw_lines();
	};

	std::for_each(header_data.begin(), header_data.end(), write_text);
}

/**
 * Funkcija koja ispisuje tekst u svakom redu
 * tabele po kolonama iz table_data.
 */
void Table::write_table_text() const
{
	// Racunanje razlike izmedju linije i mesta gde treba tekst da se ispise.
	const int offset = (Rectangle::height() / (table_data.size() + 1)) / 2 + 10;

	const std::vector <int>* horizontal_lines_p = &horizontal_lines;
	const std::vector <int>* vertical_lines_p = &vertical_lines;

	int i = -1;
	int iter = 0;
	const auto write_text = [&i, &iter, offset, horizontal_lines_p, vertical_lines_p](const std::string& text)
	{
		MyText t(Point(vertical_lines_p->at(++i % vertical_lines_p->size()) + 10,
			horizontal_lines_p->at(iter) + offset), text);
		t.draw_lines();
	};

	// Ispis se vrsi od nazad zato sto se u vektoru pozicija nalaze
	// kordinate od dole pa na gore.
	std::vector < std::vector <std::string>>::const_reverse_iterator it = table_data.crbegin();

	// Za svaki vektor iz vektora podataka
	while (it != table_data.crend())
	{
		// Ispisi svaki njegov string koji poseduje.
		std::for_each(it->cbegin(), it->cend(), write_text);
		++iter;
		++it;
	}
}

/**
 * Funkcija ispisuje tekst u zaglavlju i
 * svim redovima tebele.
 */
void Table::write_text() const
{
	write_header_text();
	write_table_text();
}

/**
 * Funkcija koja zamenjuje tekst iz tabele sa
 * zadatim tekstom i ponovo iscrtava tabelu.
 *
 * @param new_table_data - nov tekst.
 */
void Table::change_text(const std::vector < std::vector <std::string>> new_table_data)
{
	table_data = new_table_data;
	draw_lines();
}

/**
 * Funkcija koja iscrtava kompletnu tabelu na ekranu.
 */
void Table::draw_lines() const
{
	Rectangle::draw_lines();

	if (color().visibility())
	{
		draw_table_lines();
		write_text();
	}
}