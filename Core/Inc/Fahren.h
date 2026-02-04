/**
 * @file Fahren.h
 *
 * @brief Spezialisierung der Basisklasse Verhalten für das Fahrverhalten.
 */
#ifndef CORE_INC_FAHREN_H_
#define CORE_INC_FAHREN_H_

#include "../Inc/Verhalten.h"
class Fahrzeug;
class Weg;


/**
 * @brief Konkrete Verhaltensklasse für das Fahren auf einem Weg.
 *
 * Modelliert die streckenbezogene Fortbewegung eines Fahrzeugs entlang eines Weges
 * und stellt die Berechnung der innerhalb eines Zeitintervalls zurücklegbaren
 * Strecke bereit.
 */
class Fahren : public Verhalten {
public:
	/**
	 * @brief Konstruktor zur Initialisierung des Fahrverhaltens auf einem Weg.
	 *
	 * @param weg Referenz auf den zugehörigen Weg.
	 */
	Fahren(Weg& weg);

	/**
	 * @brief Berechnet die innerhalb eines Zeitintervalls zurücklegbare Strecke.
	 *
	 * Ermittelt die Strecke, die ein Fahrzeug im angegebenen Zeitintervall
	 * zurücklegen kann, ohne das Ende des zugehörigen Weges zu überschreiten.
	 *
	 * @param aFzg Referenz auf das betrachtete Fahrzeug.
	 * @param dZeitIntervall Länge des Zeitintervalls.
	 * @return Zurücklegbare Strecke innerhalb des Zeitintervalls.
	 */
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};



#endif /* CORE_INC_FAHREN_H_ */
