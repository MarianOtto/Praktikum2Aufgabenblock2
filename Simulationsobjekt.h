/*
 * Simulationsobjekt.h
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

//#define DEBUG

#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <algorithm>

extern double dGlobaleZeit;
extern double dT;


class Simulationsobjekt
{
private:
	static int p_iMaxID;

protected:
	const int p_iID;
	std::string p_sName;
	double p_dGesamtZeit;
	double p_dZeit;

public:
	//Constructors etc.
	Simulationsobjekt();
	Simulationsobjekt(std::string sName);
	virtual ~Simulationsobjekt();
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	//Getters
	int iGetID() const;
	std::string sGetName() const;
	double dGetZeit() const;


	//Setters
	void setsName(std::string sName);

	//Operator Overload

	void operator=(const Simulationsobjekt& Simulationsobjekt);
	bool operator==(const Simulationsobjekt& Simulationsobjekt);

	//Other
	virtual void vKopf() const;
	virtual void vAusgeben() const;
	virtual void vSimulieren() = 0;
	bool EpsilonEquals(double dNum1, double dNum2);
};

std::ostream& operator << (std::ostream& ostr, const Simulationsobjekt& objekt );

#endif /* SIMULATIONSOBJEKT_H_ */
