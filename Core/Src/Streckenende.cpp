#include "../Inc/Streckenende.h"
#include "../Inc/Fahrzeug.h"
#include "../Inc/Weg.h"
#include "../Inc/Kreuzung.h"
#include <iomanip>
#include <iostream>

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg) {};

void Streckenende::vBearbeiten() {
	auto pZielKreuzung = p_pWeg.getZielkreuzung();

	std::unique_ptr<Fahrzeug> pFzg = p_pWeg.pAbgabe(p_pFahrzeug);

	if (!pZielKreuzung || !pFzg)
		return;

	auto pNeuerWeg = pZielKreuzung->pZufaelligerWeg(p_pWeg);
	if (!pNeuerWeg)
		return;

	pZielKreuzung->vTanken(*pFzg);

	// ZEIT : [Zeitpunkt der Umsetzung]
	std::cout << "ZEIT      : " << std::fixed << std::setprecision(2)
			<< dGlobaleZeit << "\n";

	// KREUZUNG : [Name der Kreuzung] [Inhalt der Tankstelle]
	std::cout << "KREUZUNG  : " << pZielKreuzung->sGetName() << " ["
			<< std::fixed << std::setprecision(2)
			<< pZielKreuzung->dGetTankstelle() << "]\n";

	// WECHSEL : [Name alter Weg -> Name neuer Weg]
	std::cout << "WECHSEL   : " << p_pWeg.sGetName() << " -> "
			<< pNeuerWeg->sGetName() << "\n";

	// FAHRZEUG : [Daten des Fahrzeugs]
	std::cout << "FAHRZEUG  : " << pFzg->sGetName() << "\n";

	pNeuerWeg->vAnnahme(std::move(pFzg));
}
