/*
 * Streckenende.h
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"
class Fahrzeug;
class Weg;

class Streckenende: public Fahrausnahme
{
public:
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Streckenende();
	void vBearbeiten();
};

#endif /* STRECKENENDE_H_ */
