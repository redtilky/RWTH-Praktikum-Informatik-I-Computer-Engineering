/**
 * @file Losfahren.h
 *
 * @brief Definition der Ausnahmeklasse Losfahren zur Behandlung eines Abfahr-/Start-Ereignisses.
 *
 * Diese Datei stellt die Klasse Losfahren bereit. Sie ist eine Spezialisierung von
 * Fahrausnahme und implementiert die konkrete Behandlung des zugehörigen Ereignisses
 * über vBearbeiten().
 */
#ifndef CORE_INC_LOSFAHREN_H_
#define CORE_INC_LOSFAHREN_H_

#include "../Inc/Fahrausnahme.h"
class Weg;
class Fahrzeug;

/**
 * @brief Spezialisierte Fahrausnahme zur Behandlung des Ereignisses „Losfahren“.
 *
 * Kapselt den Kontext (Fahrzeug und Weg) und definiert die entsprechende
 * Bearbeitungslogik in vBearbeiten().
 */
class Losfahren : public Fahrausnahme {
public:
    /**
     * @brief Konstruktor zur Initialisierung des Ausnahme-Kontexts.
     *
     * @param fahrzeug Referenz auf das betroffene Fahrzeug.
     * @param weg Referenz auf den zugehörigen Weg.
     */
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);

    /**
     * @brief Führt die ereignisspezifische Behandlung aus.
     */
	virtual void vBearbeiten() override;
};


#endif /* CORE_INC_LOSFAHREN_H_ */
