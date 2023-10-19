/*
 * Parken.h
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"
class Fahrzeug;

class Parken: public Verhalten
{
private:
	double p_dStartzeit;
public:
	Parken(Weg& WegPtr, double Startzeit);
	virtual ~Parken();

	virtual double dStrecke(Fahrzeug* aFzg, double dZeitIntervall);
};

#endif /* PARKEN_H_ */
