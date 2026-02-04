#include "../Inc/Fahrzeug.h"
#include "../Inc/Verhalten.h"
#include "../Inc/Fahren.h"
#include "../Inc/Parken.h"
#include "../Inc/Farbe.h"

#include <iostream>
#include <iomanip>
#include <memory>
using namespace Farbe;
using namespace std;

Fahrzeug::Fahrzeug(string name,  double maxg):
		Simulationsobjekt(name),
		p_dMaxGeschwindigkeit(maxg)
{Ausgabe();};

Fahrzeug::~Fahrzeug()
{Ausgabe();};

void Fahrzeug::Ausgabe() const {
/*	std::cout << "---------------------------" << std::endl
			<< "Fahrzeug Name: " << p_sName << std::endl
			<< "Fahrzeug ID: " << p_iID << std::endl;	*/
}

void Fahrzeug::vKopf() {
	std::cout << red << bold << italic << std::left << std::setw(7) << "|Zeit"
			<< std::setw(5) << "|ID"
			<< std::setw(15) << "|Name"
			<< std::setw(25) << "|MaxGeschwindigkeit"
			<< std::setw(20) << "|GesamtStrecke"
			<< std::setw(20) << "|AbschnittStrecke"
			<< std::setw(21) << "|Gesamtverbrauch"
			<< std::setw(15) << "|Tankinhalt"
			<< "|AktGeschwindigkeit" << std::endl
			<< yellow << "----------------------------------------------------------------------------------------------------------------------------------------------------" << reset << std::endl;
}

void Fahrzeug::vAusgeben(ostream& os) const {
	Simulationsobjekt::vAusgeben(os);
	os << std::setw(25) << std::fixed << std::setprecision(2) << p_dMaxGeschwindigkeit
			<< std::setw(20) << std::fixed << std::setprecision(2) << p_dGesamtStrecke
			<< std::setw(20) << std::fixed << std::setprecision(2) << p_dAbschnittStrecke;
}

void Fahrzeug::vSimulieren() {

	double dDeltaZeit = dGlobaleZeit - p_dZeit;

	if (dDeltaZeit <= 0) return;
	if (!p_pVerhalten) return;

	double dGefahren = p_pVerhalten->dStrecke(*this, dDeltaZeit);

	p_dAbschnittStrecke += dGefahren;
	p_dGesamtStrecke += dGefahren;
	p_dGesamtZeit += dDeltaZeit;

	p_dZeit = dGlobaleZeit;

	/*
	if (dGefahren == 0) {
		std::cout << red << p_sName << reset << " hat das Ende des Weges erreicht!" << std::endl;
	}
	*/
	//std::cout << *(p_pVerhalten->wGetWeg())->sGetName() << std::endl;
	vZeichnen(*(p_pVerhalten->wGetWeg()));
}

double Fahrzeug::dTanken(double dMenge) {
	return 0;
}

double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
	p_pVerhalten = make_unique<Fahren>(weg);
	p_dAbschnittStrecke = 0;
	std::cout << "Start des Weges" << std::endl;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartZeit) {
	p_pVerhalten = make_unique<Parken>(weg, dStartZeit);
	p_dAbschnittStrecke = 0;
	std::cout << "Start des Weges" << std::endl;
}

bool Fahrzeug::operator<(const Fahrzeug& fahrzeug) const {
    return p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke;
}

double Fahrzeug::getAbschnittStrecke() const {
	return p_dAbschnittStrecke;
};
