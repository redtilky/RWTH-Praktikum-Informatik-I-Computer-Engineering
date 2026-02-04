#include "../Inc/PKW.h"
#include "../Inc/Verhalten.h"
#include "../Inc/Weg.h"
#include "../Inc/SimuClient.h"
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

PKW::PKW(string name, double maxg, double verbrauch, double tankvolumen):
	Fahrzeug(name, maxg),
	p_dVerbrauch(verbrauch < 0 ? -verbrauch : verbrauch),
	p_dTankvolumen(tankvolumen <= 0 ? 55 : tankvolumen),
	p_dTankinhalt(tankvolumen/2)
{}

double PKW::dTanken(double dMenge) {
	double dGetankteMenge = std::min(dMenge, p_dTankvolumen - p_dTankinhalt);
	p_dTankinhalt += dGetankteMenge;

	return dGetankteMenge;
}

void PKW::vSimulieren() {
	switch(p_dTankinhalt > 0) {
	case true:
	{
		double dAlteStrecke = p_dGesamtStrecke;
		Fahrzeug::vSimulieren();
		double dNeueStrecke = p_dGesamtStrecke;
		double dVerbrauchte = (dNeueStrecke - dAlteStrecke) * p_dVerbrauch / 100;

		p_dTankinhalt = ((p_dTankinhalt - dVerbrauchte) < 0) ? 0 : p_dTankinhalt - dVerbrauchte;
		break;
	}
	case false:
		//std::cout << p_sName << " muss getankt werden" << std::endl;
		break;
	}
}

void PKW::vAusgeben(ostream& os) const {
	double dGesamtverbrauch = p_dGesamtStrecke * p_dVerbrauch / 100.0;

	Fahrzeug::vAusgeben(os);
	os << std::setw(21) << std::left << std::fixed << std::setprecision(2) << dGesamtverbrauch
			<< std::setw(15) << std::left << std::fixed << std::setprecision(2) << p_dTankinhalt
			<< std::left << std::fixed << std::setprecision(2) << dGeschwindigkeit();
}

double PKW::dGeschwindigkeit() const {
	if (p_pVerhalten && p_pVerhalten->wGetWeg()) {
		Weg* weg = p_pVerhalten->wGetWeg();
		double dLimit = weg->getTempolimit();
		return std::min(p_dMaxGeschwindigkeit, dLimit);
	}
	return p_dMaxGeschwindigkeit;
}

void PKW::vZeichnen(const Weg& weg) const {
	double dWegLaenge = weg.getLaenge();
	bZeichnePKW(p_sName, weg.sGetName(), p_dAbschnittStrecke / dWegLaenge, dGeschwindigkeit(), p_dTankinhalt);
}

double PKW::getTankvolumen() const {return p_dTankvolumen;};
