/*
 * Parken.cpp
 *
 *  Created on: Oct 19, 2023
 *      Author: marian
 */

#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

Parken::Parken(Weg& WegPtr, double Startzeit)
:Verhalten::Verhalten(WegPtr),
 p_dStartzeit(Startzeit)
{
	// TODO Auto-generated constructor stub

}

Parken::~Parken()
{
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug* aFzg, double dZeitIntervall)
{
	for(int t = 1; t <= dZeitIntervall/dT; t++)
	{
		if(aFzg->bEquals(p_dStartzeit,0))
		{
			throw Losfahren(*aFzg, p_pWeg);
			goto exit;
		}
		p_dStartzeit -= dT;

	}
exit:
	return 0;
}

