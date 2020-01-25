//============================================================================
// Name         : Table.h
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja nasledjuje Rectangle iz Graph.h
// i sluzi da prikaze zeljene podatke u obliku tabele koja se moze postaviti
// u nekom grafickom prozoru/dijalogu.
//============================================================================

#pragma once

#include "Graph.h"

using namespace Graph_lib;

class Table : public Rectangle
{
private:
	std::vector <std::string> header_data;					// Vektor koji cuva nazive kolona
	std::vector < std::vector <std::string>> table_data;	// Vektor koji cuva podatke tabele
	std::vector <int> vertical_lines;			// Vektor koji cuva kordinate vertikalnih linija
	std::vector <int> horizontal_lines;			// Vektor koji cuva kordinate horizontalnih linija

	// Funkcije za racunanje kordinata linija
	void calculate_position_of_vertical_lines();
	void calculate_position_of_horizontal_lines();
	void calculate_positions_of_lines();

	// Funkcije za crtanje linija
	void draw_vertical_lines() const;
	void draw_horizontal_lines() const;
	void draw_table_lines() const;

	// Funkcije za ispisivanje teksta
	void write_header_text() const;
	void write_table_text() const;
	void write_text() const;

public:
	// Konstruktor
	Table(const Point& xy, const int w, const int h,
		const std::vector <std::string>& header_data,
		const std::vector < std::vector <std::string>>& table_data);

	// Funkcija koja menja tekst u tabeli
	void change_text(const std::vector < std::vector <std::string>> new_table_data);

	// Funkcija koja iscrtava sadrzaj na ekranu
	void draw_lines() const;
};
