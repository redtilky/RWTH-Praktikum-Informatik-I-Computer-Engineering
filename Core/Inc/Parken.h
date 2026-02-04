/**
 * @file Parken.h
 *
 * @brief Spezialisierung der Basisklasse Verhalten zur Modellierung eines Parkverhaltens.
 */
#ifndef CORE_INC_PARKEN_H_
#define CORE_INC_PARKEN_H_

#include "../Inc/Verhalten.h"
class Fahrzeug;
class Weg;



/**
 * @brief Konkrete Verhaltensklasse zur Modellierung des Parkens.
 *
 * Das Parkverhalten beschreibt, dass ein Fahrzeug bis zu einem definierten Startzeitpunkt
 * keine Strecke zurücklegt. Erst nach Erreichen dieser Startzeit wird im Rahmen der
 * Streckenberechnung wieder eine Bewegung zugelassen (gemäß Implementierung).
 */
class Parken : public Verhalten {
public:
	/**
	 * @brief Konstruktor zur Initialisierung des Parkverhaltens.
	 *
	 * @param weg Referenz auf den zugehörigen Weg.
	 * @param dStartzeit Zeitpunkt, ab dem das Fahrzeug die Fahrt aufnehmen darf.
	 */
	Parken(Weg& weg, double dStartzeit);

	/**
	 * @brief Berechnet die innerhalb eines Zeitintervalls zurücklegbare Strecke.
	 *
	 * Berücksichtigt dabei insbesondere den Startzeitpunkt des Parkverhaltens sowie
	 * die Begrenzung durch das Wegende.
	 *
	 * @param aFzg Referenz auf das betrachtete Fahrzeug.
	 * @param dZeitIntervall Länge des Zeitintervalls.
	 * @return Zurücklegbare Strecke innerhalb des Zeitintervalls.
	 */
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
	/**
	 * @brief Startzeitpunkt, ab dem die Fahrt begonnen werden darf.
	 */
	double p_dStartzeit;

};



#endif /* CORE_INC_PARKEN_H_ */
