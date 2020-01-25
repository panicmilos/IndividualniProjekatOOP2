//============================================================================
// Name         : MyText.h
// Author       : Milos Panic
// Date         : 28.12.2019.
// Last Modified: 31.12.2019.
// Description  : Deklaracija klase MyText koja nasledjuje Text iz Graph.h
// i ima za cilj da ispise tekst sa definisanim fontom i velicinom i ima
// mogucnost da bude ispisa sa odredjenim uglom. Ova klasa se koristi za
// ispis svih tekstova u mom programu.
//============================================================================

#pragma once

#include "GUI.h"
#include <string>
#include <iostream>

using namespace Graph_lib;

class MyText : public Text
{
public:
	int m_angle;	// Ugao pod kojim ce tekst biti ispisan.
public:
	// Konstruktor
	MyText(Point xy, const std::string& text, const int angle = 0);

	// Funkcija za ispis teksta na ekranu.
	void draw_lines() const;
};
