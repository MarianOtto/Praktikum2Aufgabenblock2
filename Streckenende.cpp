/*
 * Streckenende.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"

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
	auto fahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);
	auto weg = p_pWeg.pGetZielkreuzung()->pZufaelligerWeg(p_pWeg);
	auto zielkreuzung = weg->pGetZielkreuzung();
	zielkreuzung->vTanken(*fahrzeug);
	weg->vAnnahme(std::move(fahrzeug));

	std::cout<<"[Zeit]               : " << dGlobaleZeit << "\n";
	std::cout<<"[Kreuzung]           : " << zielkreuzung->sGetName() << "\n";
	std::cout<<"[Wechsel]            : " << p_pWeg.sGetName() << " -> " << weg->sGetName() << "\n";
	std::cout<<"[Fahrzeug]           : " << p_pFahrzeug.sGetName() << "\n\n";
}
