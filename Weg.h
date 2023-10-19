/*
 * Weg.h
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
class Fahrzeug;
#include "Tempolimit.h"

class Weg: public Simulationsobjekt
{

private:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
	std::list<std::unique_ptr<Fahrzeug>> Fahrzeuge;

public:
	//Constructors etc.
	Weg();
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);
	virtual ~Weg();

	//Getters
	double dGetTempolimit() const;
	double dGetLaenge() const;

	//Setters



	//Other
	void vSimulieren();
	void vKopf() const override;
	void vAusgeben() const override;
	void vAnnahme(std::unique_ptr<Fahrzeug> Fahrzeug);
};

#endif /* WEG_H_ */
