/*
 * Kreuzung.h
 *
 *  Created on: Oct 20, 2023
 *      Author: marian
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>

class Fahrzeug;
class Weg;

class Kreuzung: public Simulationsobjekt
{
private:
	std::list<std::shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;
public:
	Kreuzung(std::string name);
	Kreuzung(std::string name, double tankinhalt);
	virtual ~Kreuzung();

	static void vVerbinde(
			std::string WegHin, std::string WegZur, double laenge, std::weak_ptr<Kreuzung> startKreuzung,
			std::weak_ptr<Kreuzung> zielKreuzung, const Tempolimit tempolimit, bool ueberholverbot);
	void vTanken(Fahrzeug& fahrzeug);
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit);
	void vSimulieren();
	std::shared_ptr<Weg> pZufaelligerWeg(Weg& weg);
};

#endif /* KREUZUNG_H_ */
