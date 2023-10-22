/*
 * Weg.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"

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

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, std::weak_ptr<Kreuzung> zielkreuzung)
:Simulationsobjekt::Simulationsobjekt(sName),
 p_dLaenge(dLaenge),
 p_eTempolimit(eTempolimit),
 p_pZielkreuzung(zielkreuzung)
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

vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::pGetFahrzeuge()
{
	return p_pFahrzeuge;
}

std::shared_ptr<Kreuzung> Weg::pGetZielkreuzung()
{
	std::shared_ptr<Kreuzung> tempPtr = p_pZielkreuzung.lock();
	return tempPtr;
}


std::shared_ptr<Weg> Weg::pGetRueckweg()
{
	std::shared_ptr<Weg> tempPtr = p_pRueckWeg.lock();
	return tempPtr;
}

//END Getters

//BEGINN Setters


void Weg::setRueckweg(std::shared_ptr<Weg> rueckweg)
{
	std::weak_ptr<Weg> tempRueckweg = rueckweg;
	p_pRueckWeg = tempRueckweg;
}

//END Setters

//BEGINN Other

void Weg::vSimulieren()
{
	for(auto &Fahrzeug : p_pFahrzeuge)
	{
		try
		{
			vZeichneFahrzeuge();
			Fahrzeug->vSimulieren();
		}
		catch (Fahrausnahme& ausnahme)
		{
			ausnahme.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
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
	for(auto &Fahrzeug : p_pFahrzeuge)
	{
		std::cout << Fahrzeug->sGetName() << " | ";
	}
	std::cout << ")";
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug)
{
	Fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(Fahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug, double Startzeit)
{
	Fahrzeug->vNeueStrecke(*this, Startzeit);
	p_pFahrzeuge.push_front(std::move(Fahrzeug));
	p_pFahrzeuge.vAktualisieren();
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug)
{
	auto it = std::find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), [&](std::unique_ptr<Fahrzeug>& Fzg) {return Fzg.get() == &fahrzeug; });
	std::unique_ptr<Fahrzeug> lokal = std::move(*it);
	if (it != p_pFahrzeuge.end())
	{
		p_pFahrzeuge.erase(it);
		return lokal;
	}
	else
	{
		return std::make_unique<Fahrzeug>(nullptr);
	}

}

void Weg::vZeichneFahrzeuge() const
{
	for(auto &Fahrzeug : p_pFahrzeuge)
	{
		Fahrzeug->vZeichnen(*this);
	}
}
//END Other
