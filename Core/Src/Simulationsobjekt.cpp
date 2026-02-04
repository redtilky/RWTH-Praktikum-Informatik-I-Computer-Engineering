#include "../Inc/Simulationsobjekt.h"
#include "../Inc/Farbe.h"
#include <iostream>
#include <iomanip>
using namespace Farbe;
using namespace std;

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(string name):
		p_sName(name),
		p_iID(p_iMaxID++)
{}

Simulationsobjekt::~Simulationsobjekt() {
	std::cout << "Objekt " << bold << red << p_sName << reset << " with ID #" << bold << red << p_iID << reset << " wurde gelöscht!" << std::endl;
}

void Simulationsobjekt::vAusgeben(ostream& os) const {
	os << bold << italic << red << std::left << std::setw(7) << std::fixed << std::setprecision(2) << dGlobaleZeit
			<< std::setw(5) << p_iID << reset
			<< std::setw(15) << p_sName;
};

Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& simulationsobjekt) {
    if (this != &simulationsobjekt) {
        p_sName = simulationsobjekt.p_sName;
    }
    return *this;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& other) const {
	if (this->p_iID == other.p_iID) {return true;}
	return false;
}

ostream& operator<<(ostream& os, const Simulationsobjekt& simulationsobjekt) {
	simulationsobjekt.vAusgeben(os);
	return os;
}

string Simulationsobjekt::sGetName() const {
	return p_sName;
}

double Simulationsobjekt::dGetZeit() const {
	return p_dZeit;
}
