/*
 * Fahren.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Fahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& WegPtr)
:Verhalten::Verhalten(WegPtr)
{

}

Fahren::~Fahren()
{
}

double Fahren::dStrecke(Fahrzeug* aFzg, double dZeitIntervall)
{
	double dWeg = 0;
	double dGeschwindigkeit = p_pWeg.dGetTempolimit() > aFzg->dGetMaxGeschwindigkeit() ? aFzg->dGetMaxGeschwindigkeit() : p_pWeg.dGetTempolimit();
	for(int t = 1; t <= dZeitIntervall/dT; t++)
	{
		if(dWeg > p_pWeg.dGetLaenge())
		{
			throw Streckenende(*aFzg, p_pWeg);
			goto exit;
		}
		dWeg += dT * dGeschwindigkeit;
	}
exit:
	return dWeg;
}

