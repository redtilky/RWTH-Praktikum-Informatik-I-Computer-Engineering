#include "../Inc/Weg.h"
#include "../Inc/Fahrzeug.h"
#include "../Inc/Farbe.h"
#include "../Inc/Fahrausnahme.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <utility>
#include <iterator>
using namespace Farbe;
using namespace std;

Weg::Weg(string name, double laenge, Tempolimit tempolimit, std::shared_ptr<Kreuzung> ziel):
	Simulationsobjekt(name),
	p_dLaenge(laenge),
	p_eTempolimit(tempolimit),
	p_pZielKreuzung(ziel)
{}

Weg::~Weg()
{}

double Weg::getTempolimit() const {
	switch(p_eTempolimit) {
		case Tempolimit::Innenorts: return 50.0;
		case Tempolimit::Landstraße: return 100.0;
		case Tempolimit::Autobahn: return std::numeric_limits<int>::max();
	}

	return 0.0;
}

void Weg::vSimulieren() {
	p_pFahrzeuge.vAktualisieren();

	for (auto iterator = p_pFahrzeuge.begin(); iterator != p_pFahrzeuge.end(); ) {

		auto iteratorNext = std::next(iterator);
		if (!*iterator) { iterator = iteratorNext; continue; }

		try {
			(*iterator)->vSimulieren();
			std::cout << *(*iterator) << std::endl;
		} catch (Fahrausnahme& exception) {
			exception.vBearbeiten();
		}

		iterator = iteratorNext;
	}

	p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug) {
	fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartZeit) {
	fahrzeug->vNeueStrecke(*this, dStartZeit);
	p_pFahrzeuge.push_front(std::move(fahrzeug));
}

void Weg::vKopf() {
	std::cout << red << bold << italic << std::left << std::setw(7) << "|Zeit"
			<< std::setw(5) << "|ID"
			<< std::setw(14) << "|Name"
			<< std::setw(25) << "|Länge"
			<< std::setw(20) << "|Fahrzeuge" << std::endl
			<< yellow << "-------------------------------------------------------------" << reset << std::endl;
}

void Weg::vAusgeben(ostream &os) const {
	Simulationsobjekt::vAusgeben(os);
	os << std::setw(24) << std::fixed << std::setprecision(2)
			<< p_dLaenge << std::setw(1) << std::fixed
			<< std::setprecision(2) << "( " << green << italic;

	for (const auto& fahrzeugPtr : p_pFahrzeuge) {
		os << fahrzeugPtr->sGetName() << " | ";
	}

	os << reset << ")";
}

double Weg::getLaenge() const {
	return p_dLaenge;
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
	for(auto iterator = p_pFahrzeuge.begin(); iterator != p_pFahrzeuge.end(); iterator++) {
		if (!(*iterator)) continue;

		if(*(*iterator) == fahrzeug) {
			std::unique_ptr<Fahrzeug> ausGezogene = std::move(*iterator);
			p_pFahrzeuge.erase(iterator);
			return ausGezogene;
		}
	}

	return nullptr;
}

void Weg::vErsteInnitAkt() {
	p_pFahrzeuge.vAktualisieren();
}

std::shared_ptr<Weg> Weg::getRueckweg() const {
    return p_pRueckweg.lock();
}

std::shared_ptr<Kreuzung> Weg::getZielkreuzung() const {
    return p_pZielKreuzung.lock();
}

void Weg::vSetRueckweg(const std::shared_ptr<Weg>& pRueckweg) {
    p_pRueckweg = pRueckweg;
}
