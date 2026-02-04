/**
 * @file Streckenende.h
 *
 * @brief Definition der Ausnahmeklasse Streckenende zur Behandlung des Wegendes.
 *
 * Diese Datei stellt die Klasse Streckenende bereit. Sie ist eine Spezialisierung von
 * Fahrausnahme und implementiert die Behandlung des Ereignisses, dass ein Fahrzeug
 * das Ende eines Weges erreicht bzw. überschritten hat.
 */
#ifndef CORE_INC_STRECKENENDE_H_
#define CORE_INC_STRECKENENDE_H_

#include "../Inc/Fahrausnahme.h"
class Weg;
class Fahrzeug;

/**
 * @brief Spezialisierte Fahrausnahme zur Behandlung des Ereignisses „Streckenende“.
 */
class Streckenende : public Fahrausnahme {
public:
	/**
	 * @brief Konstruktor zur Initialisierung des Ausnahme-Kontexts.
	 *
	 * @param fahrzeug Referenz auf das betroffene Fahrzeug.
	 * @param weg Referenz auf den zugehörigen Weg.
	 */
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);

	/**
	 * @brief Führt die ereignisspezifische Behandlung aus.
	 */
	virtual void vBearbeiten() override;
};


#endif /* CORE_INC_STRECKENENDE_H_ */
