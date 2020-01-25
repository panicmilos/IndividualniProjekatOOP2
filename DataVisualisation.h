//============================================================================
// Name         : DataVisualisation.h
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 01.01.2020.
// Description  : Deklaracija klase koja predstavlja vizualizaciju
// podataka sortiranja sa svim funkcijama za racunanje kordinata,
// iscrtavanje tabela, teksta, kruzica, ...
//============================================================================

#pragma once

#include "Window.h"
#include "GUI.h"
#include "SortData.h"
#include "DataInfoDialog.h"

using namespace Graph_lib;

const int VISUAL_WINDOW_W = 1200;				// Duzina prozora
const int VISUAL_WINDOW_H = 600;				// Visina prozora

const int VISUAL_TABLE_W = 200;					// Duzina tabele
const int VISUAL_TABLE_H = 300;					// Visina tabele

const int VISUAL_FIRST_TABLE_W_OFFSET = 50;		// Rastojanje prve tabele od ivice po duzini
const int VISUAL_SECOND_TABLE_W_OFFSET = 950;	// Rastojanje druge tabele od ivice po duzini
const int VISUAL_TABLE_H_OFFSET = 200;			// Rastojanje tabela od ivise po visini

const int VISUAL_CIRCLE_AREA_W = 650;			// Duzina polja sa kruzicima

class DataVisualisation : public Window
{
public:
	// Konstruktor i destruktor
	DataVisualisation(const Point& xy, const int w, const int h,
		const string& title, const SortData& sd);
	~DataVisualisation();

	// Metoda za odrzavanje prozora zivim
	bool wait_for_button();
private:
	SortData m_sd;		// Podaci o sortiranju koji se prikazuju
	DataInfoDialog data_preview;	// Prozor u kojem se pokazuju podaci kroz iteracije
	unsigned int m_current_iter;	// Trenutna iteracija prikazana na prozoru
	unsigned int m_num_of_cities;	// Ukupan broj gradova koji su sortirani
	unsigned int m_num_of_iterations;	// Ukupan broj iteracija
	std::vector<int> m_horizontal_position;	// Horizontalana pozicija kruzica
	std::vector<int> m_vertical_position;	// Vertikalna pozicija kruzica
	std::vector<Shape*> m_dynamic_allocated;	// Vektor koji cuva sve dinamicki
	// instancirane objekte kako bi ih obrisao prilikom poziva destruktora

	// Dugme "dalje" i sve njegove potrebne funkcije
	Button next;
	bool buttonPushed;
	static void cb_nextButton(Address, Address);
	void nextButtonHandler();

	// Dugme "prikazi" i sve njegove potrebne funkcije
	Button preview;
	static void cb_previewButton(Address, Address);
	void previewButtonHandler();

	// Funkcija koja se aktivira klikom na X
	static void cb_quitButton(Fl_Widget* widget, void*);

	// Funkcija koja dodaje tabelu na prozor sa podacima
	// iz X iteracije na zeljenoj poziciji
	void add_table(const int iter, const Point& xy);

	// Funkcije za izracunavanje pozicija kruzica
	void calculate_horizontal_position_of_circles();
	void calculate_vertical_position_of_circles();
	void calculate_position_of_circles();

	// Funkcije za crtanje na ekranu
	void draw_init_data();
	void draw_iteration_data();
	void draw_final_data();
	void draw_column_of_circles(const int column_index);
	void draw_lines_between_iterations(const unsigned int first_iter_index,
		const unsigned int second_iter_index);

	// Funkcija za ispis texta iznad odredjene kolone kruzica
	void writeText(const int column_index, const std::string& text);
};
