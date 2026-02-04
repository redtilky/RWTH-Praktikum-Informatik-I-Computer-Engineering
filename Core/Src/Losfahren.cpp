#include "../Inc/Fahrzeug.h"
#include "../Inc/Losfahren.h"
#include "../Inc/Weg.h"
#include <iostream>

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg) {};

void Losfahren::vBearbeiten() {
	std::cout << "Fahrzeug: " << p_pFahrzeug.sGetName()
			<< " Weg: " << p_pWeg.sGetName()
			<< " Mit Ausnahme Losfahren" << std::endl;

	std::unique_ptr<Fahrzeug> pFzg = p_pWeg.pAbgabe(p_pFahrzeug);

	if (pFzg) {
		p_pWeg.vAnnahme(std::move(pFzg));
	}
}
