/*
 * Weg.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#include "Weg.h"
#include "Fahrzeug.h"

//BEGIN Constructors ec=tc.
Weg::Weg()
:Simulationsobjekt::Simulationsobjekt(),
 p_dLaenge(10),
 p_eTempolimit(Tempolimit::Autobahn)
{
#ifdef DEBUG
	std::cout <<
			"created | name: " 	<< p_sName <<
			" | ID: " 			<< p_iID <<
			" | Tempolimit: " 	<< this->getTempolimit() <<
			std::endl;
#endif
}

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit)
:Simulationsobjekt::Simulationsobjekt(sName),
 p_dLaenge(dLaenge),
 p_eTempolimit(eTempolimit)
{
#ifdef DEBUG
	std::cout <<
			"created | name: " 	<< this->	p_sName <<
			" | ID: " 			<< this-> 	p_iID <<
			" | Tempolimit: " 	<< this->getTempolimit() <<
			std::endl;
#endif
}

Weg::~Weg()
{
	// TODO Auto-generated destructor stub
}

//END Constructors etc.

//BEGINN Getters

double Weg::dGetTempolimit() const
{
	return (double) p_eTempolimit;
}

double Weg::dGetLaenge() const
{
	return p_dLaenge;
}
//END Getters

//BEGINN Setters

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug)
{	Fahrzeug->vNeueStrecke(*this);
	Fahrzeuge.push_back(std::move(Fahrzeug));
}

//END Setters

//BEGINN Other

void Weg::vSimulieren()
{
	for(auto &Fahrzeug : Fahrzeuge)
	{
		Fahrzeug->vSimulieren();
	}
}

void Weg::vKopf() const
{
	Simulationsobjekt::vKopf();
	std::cout <<
		std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::fixed <<
		std::setw(10) << "Laenge" <<
		std::setw(20) << "Tempolimit " <<
		std::setw(15) << " Fahrzeuge";
}

void Weg::vAusgeben() const
{
	Simulationsobjekt::vAusgeben();
	std::cout <<
		std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::fixed <<
		std::setw(10) << p_dLaenge <<
		std::setw(20) << ((dGetTempolimit() < (double)Tempolimit::Autobahn) ? std::to_string(dGetTempolimit()) : "Unbegrenzt") <<
		std::setw(3)<< " (";
	for(auto &Fahrzeug : Fahrzeuge)
	{
		std::cout << Fahrzeug->sGetName() << " | ";
	}
	std::cout << ")";
}

//END Other
