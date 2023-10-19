/*
 * Losfahren.h
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"\

class Fahrzeug;
class Weg;

class Losfahren: public Fahrausnahme
{
public:
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Losfahren();
	void vBearbeiten();
};

#endif /* LOSFAHREN_H_ */
