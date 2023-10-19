/*
 * Simulationsobjekt.cpp
 *
 *  Created on: Oct 17, 2023
 *      Author: marian
 */

#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

//BEGIN Constructors etc.
Simulationsobjekt::Simulationsobjekt()
:p_iID(++Simulationsobjekt::p_iMaxID),
 p_sName("0"),
 p_dGesamtZeit(0),
 p_dZeit(0)
{
}

Simulationsobjekt::Simulationsobjekt(std::string sName)
:p_iID(++Simulationsobjekt::p_iMaxID),
 p_sName(sName),
 p_dGesamtZeit(0),
 p_dZeit(0)
{
}

Simulationsobjekt::~Simulationsobjekt()
{
	#ifdef DEBUG
		std::cout << std::endl <<
				"Destroyed | name: " 	<< this-> p_sName <<
				" | ID: "				<< this-> p_iID <<
				std::endl;
	#endif
}
//END COnstructors etc.

//BEGIN Getters

int Simulationsobjekt::iGetID() const
{
	return p_iID;
}

std::string Simulationsobjekt::sGetName() const
{
	return p_sName;
}

double Simulationsobjekt::dGetZeit() const
{
	return p_dZeit;
}



//END Getters

//BEGIN Setters
void Simulationsobjekt::setsName(std::string sName)
{
	p_sName = sName;
}

//END Setters

//BEGIN Operator Overload


void Simulationsobjekt::operator=(const Simulationsobjekt& Simulationsobjekt)
{
	p_sName = Simulationsobjekt.sGetName();
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& Simulationsobjekt)
{
	if(this->p_iID == Simulationsobjekt.iGetID())
	{
		return true;
	}
	return false;
}
//END Operator Overload

//BEGIN Other
void Simulationsobjekt::vKopf() const
{
	std::cout <<
		std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) <<
		std::setw( 4) << "ID" << " " <<
		std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) <<
		std::setw(15) << "Name";
}
void Simulationsobjekt::vAusgeben() const
{
	std::cout.precision(2);
	std::cout <<
		std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right) <<
		std::setw( 4) << p_iID << " " <<
		std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) <<
		std::setw(15) << p_sName;
}

bool Simulationsobjekt::EpsilonEquals(double dNum1, double dNum2)
{
	if(abs(dNum1 - dNum2) < std::pow(10,-25.0))
	{
		return true;
	}
	return false;
}

//END Other
