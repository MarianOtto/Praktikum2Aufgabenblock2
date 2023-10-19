/*
 * Fahrzeug.h
 *
 *  Created on: Sep 23, 2023
 *      Author: marian
 */
#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"
class Verhalten;
class Fahren;
//class Parken;
class Weg;


class Fahrzeug: public Simulationsobjekt
{
private:
	static int p_iMaxID; //

protected:
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtVerbrauch;
	double p_dGeschwindigkeit;
	std::unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke;


public:
	//Constructor etc.
	Fahrzeug();
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double maxGeschwindigkeit);
	virtual ~Fahrzeug();

	//Getter
	double dGetGesamtStrecke() const;
	double dGetMaxGeschwindigkeit() const;
	double dGetAbschnittstrecke() const;

	//Setters
	void setdMaxGeschwindigkeit(double MaxGeschwindigkeit);

	//Operator Overload
	virtual bool operator<(const Fahrzeug& Fahrzeug);
	void operator=(const Fahrzeug& Fahrzeug);

	//Other
	virtual void vKopf() const;
	virtual void vAusgeben() const;
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit();
	virtual void vNeueStrecke(Weg& weg);
	virtual void vNeueStrecke(Weg& weg, double Startzeit);
	virtual void vZeichnen(const Weg& weg);
};



#endif /* FAHRZEUG_H_ */
