/*
 * Fahrausnahme.h
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <iostream>
class Fahrzeug;
class Weg;

class Fahrausnahme: public std::exception
{
public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);
	virtual ~Fahrausnahme();
	virtual void vBearbeiten() = 0;
protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
};

#endif /* FAHRAUSNAHME_H_ */
