/*
 * Verhalten.h
 *
 *  Created on: Oct 18, 2023
 *      Author: marian
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include <list>

extern double dT;

class Fahrzeug;
class Weg;

class Verhalten
{
private:
	Weg& p_pWeg;
public:
	Verhalten(Weg& WegPtr);
	virtual ~Verhalten();

	double dStrecke(Fahrzeug* aFzg, double dZeitIntervall);
};

#endif /* VERHALTEN_H_ */
