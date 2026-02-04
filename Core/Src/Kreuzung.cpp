#include "../Inc/Kreuzung.h"
#include "../Inc/Weg.h"
#include "../Inc/PKW.h"
#include <algorithm>
#include <random>
#include <iomanip>
#include <vector>


Kreuzung::Kreuzung(const std::string& name, double dTankstelle)
    : Simulationsobjekt(name), p_dTankstelle(dTankstelle)
{
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
    PKW* pkw = dynamic_cast<PKW*>(&fahrzeug);
    if (!pkw) return;

    if (p_dTankstelle <= 0.0) return;

    double getankt = pkw->dTanken(pkw->getTankvolumen());

    p_dTankstelle = std::max(0.0, p_dTankstelle - getankt);
}

void Kreuzung::vVerbinde(const std::string& nameHin, const std::string& nameRueck,
		double laenge, const std::shared_ptr<Kreuzung>& krzstart,
		const std::shared_ptr<Kreuzung>& krzziel, Tempolimit tempolimit) {

    auto pHin  = std::make_shared<Weg>(nameHin,  laenge, tempolimit, krzziel);
    auto pRueck = std::make_shared<Weg>(nameRueck, laenge, tempolimit, krzstart);

    pHin->vSetRueckweg(pRueck);
    pRueck->vSetRueckweg(pHin);

    krzstart->p_pWege.push_back(pHin);
    krzziel->p_pWege.push_back(pRueck);
}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartZeit) {
    if (!pFahrzeug) return;
    if (p_pWege.empty()) return;

    vTanken(*pFahrzeug);

    p_pWege.front()->vAnnahme(std::move(pFahrzeug), dStartZeit);
}

void Kreuzung::vSimulieren() {
    for (auto& pWeg : p_pWege) {
        if (pWeg) pWeg->vSimulieren();
    }
}

void Kreuzung::vAusgeben(std::ostream& os) const {
    Simulationsobjekt::vAusgeben(os);
    os << std::setw(20) << std::fixed << std::setprecision(2) << p_dTankstelle;
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& ankunftsWeg) {
	const auto pRueck = ankunftsWeg.getRueckweg();

	std::vector<std::shared_ptr<Weg>> kandidaten;
	kandidaten.reserve(p_pWege.size());

	for (const auto &pW : p_pWege) {
		if (!pW)
			continue;

		if (pRueck && pW == pRueck)
			continue;

		kandidaten.push_back(pW);
	}

	if (kandidaten.empty())
		return pRueck;

	static std::mt19937 device(0);
	std::uniform_int_distribution<std::size_t> dist(0, kandidaten.size() - 1);
	return kandidaten[dist(device)];
}

double Kreuzung::dGetTankstelle() const {return p_dTankstelle;}
