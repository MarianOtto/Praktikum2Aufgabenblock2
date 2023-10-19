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



double Verhalten::dStrecke(Fahrzeug* aFzg, double dZeitIntervall)
{
	double dWeg = 0;
	double dGeschwindigkeit = p_pWeg.dGetTempolimit() > aFzg->dGetMaxGeschwindigkeit() ? aFzg->dGetMaxGeschwindigkeit() : p_pWeg.dGetTempolimit();
	for(int t = 1; t <= dZeitIntervall/dT; t++)
	{
		if(dWeg > p_pWeg.dGetLaenge())
		{
			std::cout <<std::endl << aFzg->sGetName() << " hat das Wegende erreicht." << std::endl;
			goto exit;
		}
		dWeg += dT * dGeschwindigkeit;
	}
exit:
	return dWeg;
}




