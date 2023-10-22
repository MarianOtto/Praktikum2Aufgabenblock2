/*
 * Fahrzeug.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: marian
 */



#include "Fahrzeug.h"
#include "Weg.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

//BEGIN Constructors

Fahrzeug::Fahrzeug()
:Simulationsobjekt::Simulationsobjekt(),
 p_dMaxGeschwindigkeit(10),
 p_dGesamtStrecke(0),
 p_dGesamtVerbrauch(0),
 p_dGeschwindigkeit(p_dMaxGeschwindigkeit),
 p_dAbschnittStrecke(0)
{
#ifdef DEBUG
	std::cout <<
			"created | name: " 	<< this->	p_sName <<
			" | ID: " 			<< this-> 	p_iID <<
			" | MaxGeschw.: " 	<< this->	p_dMaxGeschwindigkeit <<
			std::endl;
#endif
}

Fahrzeug::Fahrzeug(std::string sName)
:Simulationsobjekt::Simulationsobjekt(sName),
 p_dMaxGeschwindigkeit(10),
 p_dGesamtStrecke(0),
 p_dGesamtVerbrauch(0),
 p_dGeschwindigkeit(p_dMaxGeschwindigkeit),
 p_dAbschnittStrecke(0)
{
#ifdef DEBUG
	std::cout <<
			"created | name: " 	<< this->	p_sName <<
			" | ID: " 			<< this-> 	p_iID <<
			" | MaxGeschw.: " 	<< this->	p_dMaxGeschwindigkeit <<
			std::endl;
#endif
}

Fahrzeug::Fahrzeug(std::string sName, double dmaxGeschwindigkeit)
:Simulationsobjekt::Simulationsobjekt(sName),
 p_dMaxGeschwindigkeit(dmaxGeschwindigkeit < 0 ? abs(dmaxGeschwindigkeit) : dmaxGeschwindigkeit),
 p_dGesamtStrecke(0),
 p_dGesamtVerbrauch(0),
 p_dGeschwindigkeit(p_dMaxGeschwindigkeit),
 p_dAbschnittStrecke(0)
{
#ifdef DEBUG
	std::cout <<
			"created | name: " 	<< this->	p_sName <<
			" | ID: " 			<< this-> 	p_iID <<
			" | MaxGeschw.: " 	<< this->	p_dMaxGeschwindigkeit <<
			std::endl;
#endif
}

Fahrzeug::~Fahrzeug()
{
}

//END Constructors etc.

//BEGIN Getters

double Fahrzeug::dGetGesamtStrecke() const
{
	return p_dGesamtStrecke;
}

double Fahrzeug::dGetMaxGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dGetAbschnittstrecke() const
{
	return p_dAbschnittStrecke;
}
//END Getters

//BEGIN Setters

void Fahrzeug::setMaxGeschwindigkeit(double MaxGeschwindigkeit)
{
	p_dMaxGeschwindigkeit = MaxGeschwindigkeit;
}

//END Setters
//BEGIN Operator Overload

bool Fahrzeug::operator<(const Fahrzeug& Fahrzeug2)
{
	if(p_dGesamtStrecke < Fahrzeug2.dGetGesamtStrecke())
	{
		return true;
	}
	return false;
}

void Fahrzeug::operator=(const Fahrzeug& Fahrzeug)
{
	Simulationsobjekt::operator=(Fahrzeug);
	p_dMaxGeschwindigkeit = Fahrzeug.dGetMaxGeschwindigkeit();
}

//END Operator Overload

//BEGIN Other

void Fahrzeug::vKopf() const
{
	Simulationsobjekt::vKopf();
	std::cout <<
		std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::fixed <<
		std::setw(20) << "MaxGeschwindigkeit" <<
		std::setw(20) << "Mom.Geschwindigkeit" <<
		std::setw(15) << "GesamtStrecke" <<
		std::setw(20) << "Abschnittstrecke";

}

void Fahrzeug::vAusgeben() const
{
	Simulationsobjekt::vAusgeben();
	std::cout <<
		std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) << std::fixed <<
		std::setw(20) << p_dMaxGeschwindigkeit <<
		std::setw(20) << p_dGeschwindigkeit <<
		std::setw(15) << p_dGesamtStrecke <<
		std::setw(20) << p_dAbschnittStrecke;
}

void Fahrzeug::vSimulieren()
{
	if(dGlobaleZeit != p_dZeit)
	{
		p_dGeschwindigkeit = dGeschwindigkeit();
		double deltaT = dGlobaleZeit - p_dZeit;
		double dWeg = p_pVerhalten->dStrecke(this, deltaT);
		p_dGesamtStrecke += dWeg;
		p_dAbschnittStrecke += dWeg;
		p_dZeit = dGlobaleZeit;
		p_dGesamtZeit = dGlobaleZeit;
	}
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0;
}

double Fahrzeug::dGeschwindigkeit()
{
	double dGeschwindigkeit = p_dMaxGeschwindigkeit;
	if(p_pVerhalten->pGetWeg().dGetTempolimit() < p_dMaxGeschwindigkeit)
		{
			dGeschwindigkeit = p_pVerhalten->pGetWeg().dGetTempolimit();
		}

	return dGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten = std::make_unique<Fahren>(weg);
	p_dAbschnittStrecke = 0;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double Startzeit)
{
	p_pVerhalten = std::make_unique<Parken>(weg, Startzeit);
	p_dAbschnittStrecke = 0;
}

void Fahrzeug::vZeichnen(const Weg& weg)
{

}

//END Other



