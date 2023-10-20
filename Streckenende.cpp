/*
 * Streckenende.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg)
:Fahrausnahme::Fahrausnahme(fahrzeug, weg)
{
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende()
{
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{
	p_pWeg.pAbgabe(p_pFahrzeug);
}
