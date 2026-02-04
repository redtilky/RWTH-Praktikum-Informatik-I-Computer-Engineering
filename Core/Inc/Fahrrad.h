/**
 * @file Fahrrad.h
 *
 * @brief Spezialisierung der Basisklasse Fahrzeug zur Modellierung eines Fahrrads.
 */
#ifndef CORE_INC_FAHRRAD_H_
#define CORE_INC_FAHRRAD_H_

#include "../Inc/Fahrzeug.h"
#include <iostream>


/**
 * @brief Konkrete Fahrzeugklasse zur Simulation eines Fahrrads.
 *
 * Diese Klasse repräsentiert ein Fahrrad als spezielles Fahrzeug. Sie überschreibt
 * u. a. die Geschwindigkeitsberechnung (Ermüdungsmodell), die grafische Darstellung
 * sowie die Ausgabe in einen Ausgabestrom.
 */
class Fahrrad : public Fahrzeug {
public:
	/**
	 * @brief Konstruktor zur Initialisierung eines Fahrrads.
	 *
	 * @param name Name/Bezeichnung des Fahrrads.
	 * @param maxg Maximale Geschwindigkeit (z. B. in km/h oder m/s gemäß Projektkonvention).
	 */
	Fahrrad(std::string name, double maxg);

	/**
	 * @brief Liefert die aktuelle Geschwindigkeit des Fahrrads.
	 *
	 * Modelliert eine Ermüdung: Mit zunehmender Fahrzeit sinkt die effektiv verfügbare
	 * Leistung, wodurch die Geschwindigkeit reduziert wird.
	 *
	 * @return Aktuelle Geschwindigkeit des Fahrrads.
	 */
	virtual double dGeschwindigkeit() const override;

	/**
	 * @brief Grafische Darstellung des Fahrrads im Kontext eines Weges.
	 *
	 * @param weg Referenz auf den Weg, auf dem das Fahrrad dargestellt werden soll.
	 */
	virtual void vZeichnen(const Weg& weg) const override;

	/**
	 * @brief Fahrrad-spezifische Ausgabe in einen Ausgabestrom.
	 *
	 * @param os Ausgabestrom, in den die Objektinformationen geschrieben werden.
	 */
	virtual void vAusgeben(std::ostream& os) const override;
private:
};



#endif /* CORE_INC_FAHRRAD_H_ */
