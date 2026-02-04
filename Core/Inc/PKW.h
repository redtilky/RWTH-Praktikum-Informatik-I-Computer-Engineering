/**
 * @file PKW.h
 *
 * @brief Spezialisierung der Basisklasse Fahrzeug zur Modellierung eines PKW.
 */
#ifndef CORE_INC_PKW_H_
#define CORE_INC_PKW_H_

#include "../Inc/Fahrzeug.h"
#include <iosfwd>
#include <string>
#include <limits>


/**
 * @brief Konkrete Fahrzeugklasse zur Simulation eines Personenkraftwagens (PKW).
 *
 * Diese Klasse erweitert Fahrzeug um kraftstoffbezogene Eigenschaften wie Verbrauch,
 * Tankvolumen und aktuellen Tankinhalt. Sie überschreibt u. a. die Simulation,
 * die Ausgabe sowie die Betankungslogik.
 */
class PKW : public Fahrzeug {
public:
	/**
	 * @brief Konstruktor zur Initialisierung eines PKW.
	 *
	 * @param name Name/Bezeichnung des PKW.
	 * @param maxg Maximale Geschwindigkeit.
	 * @param verbrauch Kraftstoffverbrauch in Liter pro 100 km.
	 * @param tankvolumen Tankvolumen in Liter (Default: 55).
	 */
	PKW(std::string name, double maxg, double verbrauch, double tankvolumen = 55);

	/**
	 * @brief Betankt den PKW um die angegebene Menge (begrenzt durch Tankvolumen).
	 *
	 * @param dMenge Gewünschte Betankungsmenge (Default: unendlich).
	 * @return Tatsächlich getankte Menge.
	 */
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;

	/**
	 * @brief Führt einen Simulationsschritt unter Berücksichtigung des Kraftstoffverbrauchs aus.
	 */
	virtual void vSimulieren() override;

	/**
	 * @brief Schreibt PKW-spezifische Daten (z. B. Verbrauch und Tankinhalt) in einen Ausgabestrom.
	 *
	 * @param os Ausgabestrom.
	 */
	virtual void vAusgeben(std::ostream& os) const override;

	/**
	 * @brief Liefert die aktuelle Geschwindigkeit des PKW.
	 *
	 * @return Aktuelle Geschwindigkeit.
	 */
	virtual double dGeschwindigkeit() const override;

	/**
	 * @brief Grafische Darstellung des PKW im Kontext eines Weges.
	 *
	 * @param weg Referenz auf den Weg.
	 */
	virtual void vZeichnen(const Weg& weg) const override;

	/**
	 * @brief Gibt das Tankvolumen zurück.
	 *
	 * @return Tankvolumen in Liter.
	 */
	double getTankvolumen() const;
private:
	/**
	 * @brief Kraftstoffverbrauch (Liter pro 100 km).
	 */
	const double p_dVerbrauch;

	/**
	 * @brief Tankvolumen (Liter).
	 */
	const double p_dTankvolumen;

	/**
	 * @brief Aktueller Tankinhalt (Liter).
	 */
	double p_dTankinhalt;
};

#endif /* CORE_INC_PKW_H_ */
