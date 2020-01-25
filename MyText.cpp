//============================================================================
// Name         : MyText.cpp
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Definicija funkcija klase MyText kao sto su konstruktor
// i funkcija za ispis teksta na ekranu.
//============================================================================

#include "MyText.h"
/**
 * Konstruktor sa parametrima.
 * Ako se ne prosledi ugao podrazumevano ce biti
 * 0 sto znaci da ce tekst biti normalno ispisan.
 */
MyText::MyText(Point xy, const std::string& text, const int angle) :
	Text(xy, text),
	m_angle(angle)
{
	set_color(Color::black);
	set_font(Font::helvetica_bold);
	set_font_size(20);
}

/**
 * Funkcija koja ispisuje tekst na ekranu pod
 * odredjenim uglom.
 */
void MyText::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(m_angle, lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt, osz);
}