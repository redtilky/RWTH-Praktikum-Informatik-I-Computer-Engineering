#include "../Inc/Simulationsobjekt.h"
#include "../Inc/Parken.h"
#include "../Inc/Losfahren.h"

Parken::Parken(Weg& weg, double dStartzeit): Verhalten(weg), p_dStartzeit(dStartzeit) {}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
	if (dGlobaleZeit < p_dStartzeit) {
		return 0.0;
	}
	throw Losfahren(aFzg, *p_pWeg);
}
