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
	std::cout << p_pFahrzeug.sGetName() << " auf " << p_pWeg.sGetName() << " hat das Streckenende erreicht! \n";
}
