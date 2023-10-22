/*
 * PKW.h
 *
 *  Created on: Sep 27, 2023
 *      Author: marian
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include <limits>

class PKW: public Fahrzeug
{
private:
	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;

public:
	//Constructors etc.
	PKW();
	PKW(std::string sName);
	PKW(std::string sName, double maxGeschwindigkeit);
	PKW(std::string sName, double maxGeschwindigkeit, double Tankvolumen, double Verbrauch);
	virtual ~PKW();
	PKW(const PKW&) = delete;

	//Getters

	double dGetTankvolumen() const;
	double dGetVerbrauch() const;
	double dGetTankinhalt() const;

	//Operator Overload
	void operator=(const Fahrzeug& Fahrzeug);
	void operator=(const PKW& PKW);

	//Other
	void vKopf() const override;
	void vAusgeben() const override;
	void vSimulieren() override;
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	void vZeichnen(const Weg& weg);

};

#endif /* PKW_H_ */
