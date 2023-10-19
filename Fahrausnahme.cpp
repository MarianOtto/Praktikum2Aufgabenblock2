/*
 * Fahrausnahme.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Fahrausnahme.h"

Fahrausnahme::Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg)
:p_pFahrzeug(fahrzeug),
 p_pWeg(weg)
{
}

Fahrausnahme::~Fahrausnahme()
{
	// TODO Auto-generated destructor stub
}

