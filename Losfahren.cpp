/*
 * Losfahren.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg)
:Fahrausnahme::Fahrausnahme(fahrzeug, weg)
{
	// TODO Auto-generated constructor stub

}

Losfahren::~Losfahren()
{
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten()
{
	std::cout << p_pFahrzeug.sGetName() << " auf " << p_pWeg.sGetName() << " ist losgefahren! \n";
}
