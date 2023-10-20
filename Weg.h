/*
 * Weg.h
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;

class Weg: public Simulationsobjekt
{
private:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> Fahrzeuge;

public:
	//Constructors etc.
	Weg();
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);
	virtual ~Weg();

	//Getters
	double dGetTempolimit() const;
	double dGetLaenge() const;
	vertagt::VListe<std::unique_ptr<Fahrzeug>>& lGetFahrzeuge();

	//Setters



	//Other
	void vSimulieren();
	void vKopf() const override;
	void vAusgeben() const override;
	void vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug);
	void vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug, double Startzeit);
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);
	void vZeichneFahrzeuge();
};

#endif /* WEG_H_ */
