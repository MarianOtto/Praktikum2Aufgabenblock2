/*
 * main.cpp
 *
 *  Created on: Sep 23, 2023
 *      Author: marian
 */

#include <iostream>
#include <memory>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"

double dGlobaleZeit = 0.0;
double dT = 0.001;

/*
 * Function to compare to floats for equality
 */


bool bEpsilonEquals(double dNum1, double dNum2)
{
	if(abs(dNum1 - dNum2) < std::pow(10,-25.0))
	{
		return true;
	}
	return false;
}

void vAufgabe_1()
{
	std::cout << "\n\n Aufgabe 1 \n\n";

	/* Testen von Ausgabe und Kopf*/
	Fahrzeug Auto("Auto");
	Fahrzeug Bus;
	Fahrzeug *Zug = new Fahrzeug("Zug");
	std::cout << "Test vAusgeben() und vKopf(): " << std::endl << std::endl;
	Zug->vKopf();
	std::cout << std::endl;
	Zug->vAusgeben();
	std::cout << std::endl << std::endl;

	/*Erstellen von smart pointer*/
	std::unique_ptr<Fahrzeug> unique1 = std::make_unique<Fahrzeug>("Unique1");
	std::unique_ptr<Fahrzeug> unique2 = std::make_unique<Fahrzeug>("Unique2");
	std::shared_ptr<Fahrzeug> shared1 = std::make_shared<Fahrzeug>("Shared1");
	std::shared_ptr<Fahrzeug> shared2 = std::make_shared<Fahrzeug>("Shared2");

	/*Ausgabe von Count*/
	std::cout << "Test von Count-Ausgabe" << std::endl;
	std::cout << "Zuvor: Count von shared2: " << shared2.use_count()
			<< std::endl;
	std::shared_ptr<Fahrzeug> shared2_1 = shared2;
	std::cout << "Danach: Count von shared2: " << shared2.use_count()
			<< std::endl;
	std::vector<std::unique_ptr<Fahrzeug>> vector_unique;

	/*Test pushback -> unique braucht std::move()*/
	vector_unique.push_back(std::move(unique1));
	vector_unique.push_back(std::move(unique2));
	vector_unique.clear();
	std::vector<std::shared_ptr<Fahrzeug>> vector_shared;
	vector_shared.push_back(shared1);
	vector_shared.push_back(shared2);
	vector_shared.push_back(std::move(shared2_1));
	std::cout << "Count after vector: " << shared2.use_count() << std::endl;
	vector_shared.clear();
}

void vAufgabe_1a()
{
	std::cout << "\n\n Aufgabe 1a \n\n";

	/*Kreiere Objekte und füge sie in Vector ein*/
	std::unique_ptr<Fahrzeug> Auto = std::make_unique<Fahrzeug>("Auto", 130);
	std::unique_ptr<Fahrzeug> Bus = std::make_unique<Fahrzeug>("Bus", 90);
	std::unique_ptr<Fahrzeug> Fahrrad = std::make_unique<Fahrzeug>("Fahrrad",
			25);
	std::vector<std::unique_ptr<Fahrzeug>> vector_Fahrzeuge;
	vector_Fahrzeuge.push_back(std::move(Auto));
	vector_Fahrzeuge.push_back(std::move(Bus));
	vector_Fahrzeuge.push_back(std::move(Fahrrad));

	/*Loop zum Simulieren*/
	for (int i = 0; i < 3; i++)
	{
		std::cout << std::endl << "Simulationsschritt: " << i << std::endl;
		std::cout << std::endl;
		vector_Fahrzeuge.at(1)->vKopf();
		std::cout << std::endl;
		double deltaT = rand() % 60;
		deltaT /= 60;
		dGlobaleZeit += deltaT;
		for (auto &vector : vector_Fahrzeuge)
		{
			vector->vSimulieren();
			vector->vAusgeben();
			std::cout << std::endl;
		}
	}
}

void vAufgabe_2()
{
	std::cout << "\n\n Aufgabe 2 \n\n";

	/*Anzahl einlesen und in Vector schreiben*/
	int iCountPKW;
	int iCountFahrrad;
	std::cout << "Bitte Anzahl an Autos eingeben: ";
	std::cin >> iCountPKW;
	std::cout << std::endl << "Bitte Anzahl an Fahrräder eingeben: ";
	std::cin >> iCountFahrrad;
	std::cout << std::endl;
	std::vector<std::unique_ptr<Fahrzeug>> vector_Fahrzeug;

	/*Kreieren von PKW und Fahrrad Objekte*/
	if (iCountPKW > 0)
	{
		for (int i = 1; i <= iCountPKW; i++)
		{
			std::string sName = "PKW" + std::to_string(i);
			std::unique_ptr<PKW> PKWs = std::make_unique<PKW>(sName,
					(double) (rand() % 5 * 20 + 20),
					(double) (rand() % 5 * 10 + 25), (double) (rand() % 5) + 1);
			vector_Fahrzeug.push_back(std::move(PKWs));
		}
	}

	if (iCountFahrrad > 0)
	{
		for (int i = 1; i <= iCountFahrrad; i++)
		{
			std::string sName = "Fahrrad" + std::to_string(i);
			std::unique_ptr<Fahrrad> Bikes = std::make_unique<Fahrrad>(sName,
					rand() % 5 * 5 + 5);
			vector_Fahrzeug.push_back(std::move(Bikes));
		}
	}

	/*Einlesen von Schritten*/
	int iSchritte;
	std::cout << "Bitte Anzahl Zeitschritte eingeben: ";
	std::cin >> iSchritte;
	std::cout << std::endl;

	/*Simulieren*/
	for (int i = 0; i <= iSchritte; i++)
	{
		double dDeltaT = rand() % 210;
		dDeltaT /= 60;
		dGlobaleZeit += dDeltaT;
		std::cout << std::endl << std::endl << "Simulationsschritt: " << i << std::endl << std::endl;
		vector_Fahrzeug.at(0)->vKopf();
		std::cout << std::endl;
		for (auto &Fahrzeug : vector_Fahrzeug)
		{
			if ((int) Fahrzeug->dGetZeit() / 3 < (int) dGlobaleZeit / 3)
			{
				Fahrzeug->dTanken();
				std::cout << std::endl;
			}
			Fahrzeug->vSimulieren();
			Fahrzeug->vAusgeben();
			std::cout << std::endl;
		}
	}
}

void vAufgabe_3()
{
	std::cout << "\n\n Aufgabe 3 \n\n";

	/*Objekte kreieren*/
	PKW PKW1("PKW1", 100, 50, 4.5);
	PKW PKW2("PKW2");
	Fahrzeug Fahrzeug("Fahrzeug", 100);
	Fahrrad Fahrrad("Fahrrad", 20);

	std::cout << "Ausgabe mit Operator Overload :" << std::endl << std::endl;
	PKW1.vKopf();
	std::cout << std::endl << PKW1 << std::endl << Fahrrad << std::endl << std::endl;

	std::cout << "Test Vergleichsopator:" << std::endl << std::endl;
	std::cout << "Vor Simulation: " << std::endl;
	PKW1.vKopf();
	std::cout << std::endl << PKW1 << std::endl << PKW2 << std::endl;
	if (PKW2 < PKW1)
	{
		std::cout << PKW1.sGetName() << " ist weiter gefahren";
	}
	else
	{
		std::cout << PKW2.sGetName() << " ist weiter (oder gleich weit) gefahren";
	}
	std::cout << std::endl << std::endl;

	dGlobaleZeit += 2;
	PKW1.vSimulieren();
	PKW2.vSimulieren();

	std::cout << "Nach Simulation: " << std::endl;
	PKW1.vKopf();
	std::cout << std::endl << PKW1 << std::endl << PKW2 << std::endl;
	if (PKW2 < PKW1)
	{
		std::cout << PKW1.sGetName() << " ist weiter gefahren";
	}
	else
	{
		std::cout << PKW2.sGetName() << " ist weiter gefahren";
	}
	std::cout << std::endl << std::endl;

	/*Test Zuweisung*/
	std::cout << "Teste Zuweisung:" << std::endl << std::endl;

	/*Fahrzeug = Fahrrad*/
	std::cout << "Fahrzeug = Fahrrad" << std::endl;
	std::cout << "Zuvor: \n\n";
	PKW1.vKopf();
	std::cout << std::endl << Fahrzeug << std::endl << Fahrrad << std::endl
			<< std::endl;
	Fahrzeug = Fahrrad;
	std::cout << "Danach: \n\n" << Fahrzeug << std::endl << Fahrrad << std::endl
			<< std::endl;

	/*Fahrzeug = PKW*/
	std::cout << "Fahrzeug = PKW1" << std::endl;
	std::cout << "Zuvor: \n\n";
	PKW1.vKopf();
	std::cout << std::endl << Fahrzeug << std::endl << PKW1 << std::endl
			<< std::endl;
	Fahrzeug = PKW1;
	std::cout << "Danach: \n\n" << Fahrzeug << std::endl << PKW1 << std::endl
			<< std::endl;

	/*PKW = Fahrzeug*/
	std::cout << "PKW2 = Fahrzeug" << std::endl;
	std::cout << "Zuvor: \n\n";
	PKW1.vKopf();
	std::cout << std::endl << PKW2 << std::endl << Fahrzeug << std::endl
			<< std::endl;
	PKW2 = Fahrrad;
	std::cout << "Danach: \n\n" << PKW2 << std::endl << Fahrzeug << std::endl
			<< std::endl;

	/*PKW = PKW*/
	std::cout << "PKW1 = PKW2" << std::endl;
	std::cout << "Zuvor: \n\n";
	PKW1.vKopf();
	std::cout << std::endl << PKW1 << std::endl << PKW2 << std::endl
			<< std::endl;
	PKW1 = PKW2;
	std::cout << "Danach: \n\n" << PKW1 << std::endl << PKW2 << std::endl
			<< std::endl;

}

void vAufgabe_4()
{
	std::cout << std::endl << std::endl << "Aufgabe 4" << std::endl << std::endl;

	Weg Weg("Weg", 10, Tempolimit::Innerorts);
	Weg.vKopf();
	std::cout << std::endl << Weg;
}


void vAufgabe_5()
{
	std::cout << std::endl << std::endl << "Aufgabe 5" << std::endl << std::endl;

	/*Kreiere Objekte*/
	dGlobaleZeit += 1;
	std::unique_ptr<Fahrzeug> Fahrzeug1 = std::make_unique<Fahrzeug>("Fahrzeug1", 120);
	std::unique_ptr<Fahrzeug> Fahrzeug2 = std::make_unique<Fahrzeug>("Fahrzeug2", 100);
	std::unique_ptr<Fahrzeug> Fahrzeug3 = std::make_unique<Fahrzeug>("Fahrzeug3", 50);
	Weg Weg("Weg1", 100, Tempolimit::Landstrasse);

	/*Füge Fahrzeuge zu Weg hinzu*/
	Weg.vAnnahme(std::move(Fahrzeug1));
	Weg.vAnnahme(std::move(Fahrzeug2));
	Weg.vAnnahme(std::move(Fahrzeug3), 0.8);

	/*Simuliere Weg und gebe Fahrzeug 1 aus*/
	Weg.vKopf();
	std::cout << std::endl << Weg << std::endl;
	Weg.pGetFahrzeuge().begin()->get()->vKopf();
	std::cout << std::endl << *(Weg.pGetFahrzeuge().begin()->get()) << std::endl << std::endl; //Fahrzeug 1 ausgeben
	Weg.vSimulieren();
	Weg.pGetFahrzeuge().begin()->get()->vKopf();
	std::cout << std::endl << *(Weg.pGetFahrzeuge().begin()->get()) << std::endl << std::endl;
}

void vAufgabe_6()
{
	bInitialisiereGrafik(1000, 1000);

	int koordinaten[] = {100, 100, 400, 500};
	Weg WegHin("WegHin", 500, Tempolimit::Autobahn);
	Weg WegZur("WegZur", 500, Tempolimit::Landstrasse);

	bZeichneStrasse(WegHin.sGetName(), WegZur.sGetName(), 500, 2, koordinaten);

	std::unique_ptr<Fahrzeug> Fahrzeug1 = std::make_unique<PKW>("Fahrzeug1", 110);
	std::unique_ptr<Fahrzeug> Fahrzeug2 = std::make_unique<PKW>("Fahrzeug2", 250);
	std::unique_ptr<Fahrzeug> Fahrzeug3 = std::make_unique<PKW>("Fahrzeug3", 120);
	std::unique_ptr<Fahrzeug> Fahrzeug4 = std::make_unique<PKW>("Fahrzeug4", 70);

	WegHin.vAnnahme(std::move(Fahrzeug1));
	WegHin.vAnnahme(std::move(Fahrzeug2));
	WegZur.vAnnahme(std::move(Fahrzeug3));
	WegZur.vAnnahme(std::move(Fahrzeug4), 1);

	for(int t = 0; t <= 50; t++)
	{
		dGlobaleZeit += 0.1;
		vSetzeZeit(dGlobaleZeit);

		WegHin.vSimulieren();
		WegZur.vSimulieren();

		WegHin.vZeichneFahrzeuge();
		WegZur.vZeichneFahrzeuge();
		vSleep(100);
	}
}

void vAufgabe_6a()
{
	//Liste erzeugen
	vertagt::VListe<int> Liste;
	for(int i = 0; i < 10; i++)
	{
		Liste.push_back(rand() % 10);
	}
	Liste.vAktualisieren();

	//Liste ausgeben
	std::cout << "Liste ausgeben: " << std::endl;
	for(auto elem : Liste)
	{
		std::cout << elem << " ";
	}

	//elem > 5 loeschen

	for(auto elem = Liste.begin(); elem != Liste.end(); elem++)
	{
		if(*elem > 5)
		{
			Liste.erase(elem);
		}
	}

	//Liste vor Aktualisieren ausgeben
	std::cout << std::endl << "Elemente > 5 loeschen: " <<  std::endl << "Liste ausgeben vor aktualisieren: " << std::endl;
	for(auto elem : Liste)
	{
		std::cout << elem << " ";
	}

	Liste.vAktualisieren();

	//Liste nach aktualisieren ausgeben
	std::cout << std::endl << "Liste ausgeben nach aktualisieren: " << std::endl;
	for(auto elem : Liste)
	{
		std::cout << elem << " ";
	}

	//Vorne und hinten Zahle hinzufuegen
	for(int i = 0; i < 2; i++)
	{
		Liste.push_front(rand() % 10);
	}

	for(int i = 0; i < 2; i++)
	{
		Liste.push_back(rand() % 10);
	}

	Liste.vAktualisieren();

	std::cout << std::endl << "Liste ausgeben nach Hinzufuegen: " << std::endl;
	for(auto elem : Liste)
	{
		std::cout << elem << " ";
	}
}

void vAufgabe_7()
{
	 Weg W12("W12", 40, Tempolimit::Innerorts);
	 Weg W21("W21", 40, Tempolimit::Innerorts);

	 Weg W23a("W23a", 115, Tempolimit::Autobahn);
	 Weg W32a("W32a", 115, Tempolimit::Autobahn);

	 Weg W23b("W23b", 40, Tempolimit::Innerorts);
	 Weg W32b("W32b", 40, Tempolimit::Innerorts);

	 Weg W24("W24", 55, Tempolimit::Innerorts);
	 Weg W42("W42", 55, Tempolimit::Innerorts);

	 Weg W34("W34", 85, Tempolimit::Autobahn);
	 Weg W43("W43", 85, Tempolimit::Autobahn);

	 Weg W44a("W44a", 130, Tempolimit::Landstrasse);
	 Weg W44b("W44b", 130, Tempolimit::Landstrasse);

	//Strasse 1
	int strasse1[] = {680, 40, 680, 300};
	int strasse2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	int strasse3[] = {680, 300, 680, 570};
	int strasse4[] = {680, 300, 320, 300};
	int strasse5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	int strasse6[] = {320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300};

    std::shared_ptr<Kreuzung> Kr1 = std::make_shared<Kreuzung>("Kr1");
    std::shared_ptr<Kreuzung> Kr2 = std::make_shared<Kreuzung>("Kr2", 10000);
    std::shared_ptr<Kreuzung> Kr3 = std::make_shared<Kreuzung>("Kr3");
    std::shared_ptr<Kreuzung> Kr4 = std::make_shared<Kreuzung> ("Kr4");

    Kr1->vVerbinde("W12", "W21", 40, Kr1, Kr2, Tempolimit::Innerorts, false);

    Kr2->vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Tempolimit::Autobahn, false);
    Kr2->vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Tempolimit::Innerorts, false);
    Kr2->vVerbinde("W24", "W42", 55, Kr2, Kr4, Tempolimit::Innerorts, false);

    Kr3->vVerbinde("W34", "W43", 85, Kr3, Kr4, Tempolimit::Autobahn, false);
    Kr4->vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Tempolimit::Landstrasse, false);

	bInitialisiereGrafik(1100, 1000);
	bZeichneKreuzung(680, 40);	 //Kr1
    bZeichneKreuzung(680, 300);	 //Kr2
	bZeichneKreuzung(680, 570);	 //Kr3
	bZeichneKreuzung(320, 300);  //Kr4
	bZeichneStrasse("W12", "W21", 40, 2, strasse1);
	bZeichneStrasse("W23a", "W32a", 115, 6, strasse2);
	bZeichneStrasse("W23b", "W32b", 40, 2, strasse3);
	bZeichneStrasse("W24", "W42", 55, 2, strasse4);
	bZeichneStrasse("W34", "W43", 85, 5, strasse5);
	bZeichneStrasse("W44a", "W44b", 130, 7, strasse6);

	std::unique_ptr<PKW> fahrzeug1 = std::make_unique<PKW>("PKW1", 75 , 45, 3.8);
	std::unique_ptr<PKW> fahrzeug2 = std::make_unique<PKW>("PKW2", 120, 50, 5);
	std::unique_ptr<Fahrrad> fahrzeug3 = std::make_unique<Fahrrad>("Fahrrad", 35);
	Kr1->vAnnahme(move(fahrzeug1), 0);
	Kr1->vAnnahme(move(fahrzeug2), 3);
	Kr1->vAnnahme(move(fahrzeug3), 8);



	 while(true)
	 {

		vSetzeZeit(dGlobaleZeit);

		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();

	 	 vSleep(100);

	     dGlobaleZeit+=0.1;
	 }
}


int main(void)
{
	std::srand(std::time(NULL));
	//vAufgabe_1();
	//vAufgabe_1a();
	//vAufgabe_2();
	//vAufgabe_3();
	//vAufgabe_4();
	//vAufgabe_5();
	//vAufgabe_6();
	std::srand(0);
	//vAufgabe_6a();
	//std::srand(std::time(NULL));
	vAufgabe_7();
}
