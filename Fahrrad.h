/*
 * Fahrrad.h
 *
 *  Created on: Sep 27, 2023
 *      Author: marian
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad: public Fahrzeug
{
public:
	//Constructors etc.
	Fahrrad();
	Fahrrad(std::string sName);
	Fahrrad(std::string sName, double maxGeschwindigkeit);
	virtual ~Fahrrad();
	Fahrrad(const Fahrrad&) = delete;

	//Other
	void vKopf() const;
	void vAusgeben() const override;
	double dGeschwindigkeit() override;
};

#endif /* FAHRRAD_H_ */
