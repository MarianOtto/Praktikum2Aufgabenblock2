/*
 * Fahren.h
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"
class Fahrzeug;
class Weg;

class Fahren: public Verhalten
{
public:
	Fahren(Weg& WegPtr);
	virtual ~Fahren();

	virtual double dStrecke(Fahrzeug* aFzg, double dZeitIntervall);
};

#endif /* FAHREN_H_ */
