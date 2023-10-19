/*
 * Verhalten.cpp
 *
 *  Created on: Oct 18, 2023
 *      Author: marian
 */

#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"

Verhalten::Verhalten(Weg& WegPtr)
:p_pWeg(WegPtr)
{

}

Verhalten::~Verhalten()
{
	// TODO Auto-generated destructor stub
}

Weg& Verhalten::pGetWeg() const
{
	return p_pWeg;
}


