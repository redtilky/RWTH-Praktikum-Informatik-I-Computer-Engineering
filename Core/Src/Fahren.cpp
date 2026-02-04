#include "../Inc/Fahren.h"
#include "../Inc/Fahrzeug.h"
#include "../Inc/Weg.h"
#include "../Inc/Streckenende.h"

Fahren::Fahren(Weg& weg): Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
	double dGefahreneStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;
	double dRestStrecke = p_pWeg->getLaenge() - aFzg.getAbschnittStrecke();

	if (dRestStrecke <= 0.0) {
		throw Streckenende(aFzg, *p_pWeg);
	}

	if (dGefahreneStrecke <= dRestStrecke) {
		return dGefahreneStrecke;
	}

	return dRestStrecke;
}


