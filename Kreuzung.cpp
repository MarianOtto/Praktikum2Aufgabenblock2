/*
 * Kreuzung.cpp
 *
 *  Created on: Oct 20, 2023
 *      Author: marian
 */

#include "Kreuzung.h"
#include "Tempolimit.h"
#include "Weg.h"
#include "Fahrzeug.h"

Kreuzung::Kreuzung(std::string name, double tankinhalt)
:Simulationsobjekt::Simulationsobjekt(name),
 p_dTankstelle(tankinhalt)
{
}

Kreuzung::Kreuzung(std::string name)
:Simulationsobjekt::Simulationsobjekt(name),
 p_dTankstelle(0)
{
}

Kreuzung::~Kreuzung()
{
}

void Kreuzung::vVerbinde(
		std::string WegHin, std::string WegZur, double laenge, std::weak_ptr<Kreuzung> startKreuzung,
		std::weak_ptr<Kreuzung> zielKreuzung, const Tempolimit tempolimit, bool ueberholverbot)
{
	std::shared_ptr<Weg> wegHin = std::make_shared<Weg>(WegHin, laenge, tempolimit, zielKreuzung);
	std::shared_ptr<Weg> wegZur = std::make_shared<Weg>(WegZur, laenge, tempolimit, startKreuzung);

	wegHin.get()->setRueckweg(wegZur);
	wegZur.get()->setRueckweg(wegHin);


	startKreuzung.lock()->p_pWege.push_back(wegHin);
	zielKreuzung.lock()->p_pWege.push_back(wegZur);
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
	if(!bEquals(p_dTankstelle, 0))
	{
		double dMenge = fahrzeug.dTanken();
		p_dTankstelle -= dMenge;
		if(p_dTankstelle < 0)
		{
			p_dTankstelle = 0;
		}
	}
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit)
{
	vTanken(*fahrzeug);
	p_pWege.front()->vAnnahme(std::move(fahrzeug), startzeit);
}

void Kreuzung::vSimulieren()
{
	for(auto& weg : p_pWege)
	{
		weg->vSimulieren();
	}
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg)
{
	if(!(p_pWege.size() > 1))
	{
		std::shared_ptr<Weg> tempWeg = weg.pGetRueckweg();
		return tempWeg;
	}

	int rand = std::rand() %(p_pWege.size());
	auto begin = p_pWege.begin();
	auto next = std::next(begin, rand);
	if(next->get() == weg.pGetRueckweg().get())
	{
		*next = pZufaelligerWeg(weg);
	}
	return *next;
}
