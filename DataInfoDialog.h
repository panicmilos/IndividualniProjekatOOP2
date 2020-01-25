//============================================================================
// Name         : DataInfoDialog.h
// Author       : Milos Panic
// Date         : 29.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase koja predstavlja graficki dijalog u kojem
// se ispisuju svi podaci iz vektora u tabeli.
//============================================================================

#pragma once

#include "Window.h"
#include "GUI.h"
#include "Table.h"

using namespace Graph_lib;

const int DATA_WINDOW_W = 800;		// Duzina prozora
const int DATA_WINDOW_H = 520;		// Visina prozora

const int DATA_TABLE_W = 700;		// Duzina tabele
const int DATA_TABLE_H = 400;		// Visina tabele
const int DATA_TABLE_OFFSET = 50;	// Razmak izmedju coska prozora i table

const std::vector<std::string> DATA_INFO_HEADER =
{
	"Flight No.", "Destination", "Departure", "Gate No."	// Nazivi kolona
};

class DataInfoDialog : public Window
{
public:
	// Konstruktor i destruktor
	DataInfoDialog(const Point& xy, const int w, const int h, const string& title,
		const std::vector <std::string>& header_data,
		const std::vector < std::vector <std::string>>& table_data);
	~DataInfoDialog();

	// Metoda za odrzavanje prozora zivim
	bool wait_for_button();

	// Funkcija koja menja tekst u tabeli
	void change_text(const std::vector < std::vector <std::string>>& new_table_data);

private:
	Table t;				// Tabela
	std::string title;		// Naziv prozora (Cuva se zato sto se mora
	// svaki put setovati kada se uradi show() nakon hide()

	// Dugme i sve njegove potrebne funkcije
	Button next;
	bool buttonPushed;
	static void cb_nextButton(Address, Address);
	void nextButtonHandler();

	// Funkcija koja ispisuje tekst na prozoru
	void writeText();
};
