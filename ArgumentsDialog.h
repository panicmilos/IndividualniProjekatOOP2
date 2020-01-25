//============================================================================
// Name         : ArgumentsDialog.h
// Author       : Milos Panic
// Date         : 27.12.2019.
// Last Modified: 30.12.2019.
// Description  : Deklaracija klase koja predstavlja graficki prozor u kojem
// korisnik unosi sve potrebne argumente i cuva ih kao atribut.
//============================================================================

#pragma once

#include "Window.h"
#include "GUI.h"
#include "Arguments.h"

using namespace Graph_lib;

const int ARG_WINDOW_W = 600;	// Duzina prozora
const int ARG_WINDOW_H = 430;	// Visina prozora

class ArgumentsDialog : public Window
{
public:
	// Konstruktor i destruktor
	ArgumentsDialog(const Point& xy, const int w, const int h, const string& title);
	~ArgumentsDialog();

	// Metoda za odrzavanje prozora zivim
	bool wait_for_button();

	// Geter uz pomoc kojeg se dobijaju uneseni argumenti
	Arguments& getArguments();

private:
	Arguments args;				// Ovde se cuvaju uneseni argumenti

	// Ulazna polja
	In_box input_path;
	In_box output_path;
	In_box criterion_choice;
	In_box sorter_choice;

	// Dugme i sve njegove potrebne funkcije
	Button next;
	bool buttonPushed;
	static void cb_nextButton(Address, Address);
	void nextButtonHandler();

	// Funkcija koja se aktivira klikom na X
	static void cb_quitButton(Fl_Widget* widget, void*);

	// Funkcije koje ispisuju tekst na prozoru
	void writeTexts();
	void writePathTexts();
	void writeCriteionTexts();
	void writeSortTexts();
};
