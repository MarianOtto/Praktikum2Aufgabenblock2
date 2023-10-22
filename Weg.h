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

class Kreuzung;
class Fahrzeug;

class Weg: public Simulationsobjekt
{
private:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	const std::weak_ptr<Kreuzung> p_pZielkreuzung;
	std::weak_ptr<Weg> p_pRueckWeg;

public:
	//Constructors etc.
	Weg();
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit, std::weak_ptr<Kreuzung> zielkreuzung);
	virtual ~Weg();

	//Getters
	double dGetTempolimit() const;
	double dGetLaenge() const;
	vertagt::VListe<std::unique_ptr<Fahrzeug>>& pGetFahrzeuge();
	std::shared_ptr<Kreuzung> pGetZielkreuzung();
	std::shared_ptr<Weg> pGetRueckweg();

	//Setters
	void setRueckweg(std::shared_ptr<Weg> rueckweg);


	//Other
	void vSimulieren();
	void vKopf() const override;
	void vAusgeben() const override;
	void vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug);
	void vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug, double Startzeit);
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);
	void vZeichneFahrzeuge() const;
};

#endif /* WEG_H_ */
