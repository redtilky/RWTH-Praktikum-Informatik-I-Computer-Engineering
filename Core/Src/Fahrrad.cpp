#include "../Inc/Fahrrad.h"
#include "../Inc/Weg.h"
#include "../Inc/Farbe.h"
#include "../Inc/SimuClient.h"
#include <iomanip>
using namespace Farbe;
using namespace std;

Fahrrad::Fahrrad(string name, double maxg):
		Fahrzeug(name, maxg)
{}

double Fahrrad::dGeschwindigkeit() const {
	if (p_dMaxGeschwindigkeit < 12.0) {return p_dMaxGeschwindigkeit;}
	int iStrecke = int(p_dGesamtStrecke / 20);
	double dGes = p_dMaxGeschwindigkeit;

	for (int i = 1; i <= iStrecke; i++) {
		dGes -= dGes * 0.1;
	}

	return dGes < 12.0 ? 12.0 : dGes;
}

void Fahrrad::vAusgeben(ostream& os) const {
	Fahrzeug::vAusgeben(os);
		std::cout << red << bold << italic << std::setw(21) << std::left << std::fixed << std::setprecision(2) << "N/A"
				<< std::setw(15) << std::left << std::fixed << std::setprecision(2) << "N/A" << reset
				<< bold << blue << std::left << std::fixed << std::setprecision(2) << dGeschwindigkeit() << reset;
}

void Fahrrad::vZeichnen(const Weg& weg) const {
	double dWegLaenge = weg.getLaenge();
	bZeichneFahrrad(p_sName, weg.sGetName() , p_dAbschnittStrecke / dWegLaenge, dGeschwindigkeit());
}
