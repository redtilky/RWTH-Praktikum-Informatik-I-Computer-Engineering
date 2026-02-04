/**
 * @file Fahrausnahme.h
 *
 * @brief Abstrakte Basisklasse zur Behandlung fahrbezogener Ausnahmen.
 */
#ifndef CORE_INC_FAHRAUSNAHME_H_
#define CORE_INC_FAHRAUSNAHME_H_

#include <exception>
class Weg;
class Fahrzeug;

/**
 * @brief Abstrakte Ausnahme-Klasse für fahrzeugspezifische Ereignisse auf einem Weg.
 *
 * Diese Klasse kapselt den Kontext einer Ausnahme, bestehend aus Referenzen auf
 * das betroffene Fahrzeug und den zugehörigen Weg. Die konkrete Behandlung wird
 * in abgeleiteten Klassen implementiert.
 */
class Fahrausnahme : public std::exception {
public:
	/**
	 * @brief Konstruktor zur Initialisierung des Ausnahme-Kontexts.
	 *
	 * Initialisiert die Ausnahme mit Referenzen auf das betroffene Fahrzeug sowie
	 * den zugehörigen Weg.
	 *
	 * @param fahrzeug Referenz auf das betroffene Fahrzeugobjekt.
	 * @param weg Referenz auf das zugehörige Wegobjekt.
	 */
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

	/**
	 * @brief Virtueller Destruktor.
	 *
	 * Ermöglicht das korrekte Freigeben von Ressourcen bei polymorpher Nutzung.
	 */
	virtual ~Fahrausnahme() = default;

	/**
	 * @brief Abstrakte Schnittstelle zur Ausnahmebehandlung.
	 *
	 * Führt die spezifische Behandlung der Ausnahme aus. Die konkrete Semantik
	 * wird durch abgeleitete Klassen definiert.
	 */
	virtual void vBearbeiten() = 0;
protected:
	/**
	 * @brief Referenz auf das betroffene Fahrzeug.
	 */
	Fahrzeug& p_pFahrzeug;

	/**
	 * @brief Referenz auf den zugehörigen Weg.
	 */
	Weg& p_pWeg;
};



#endif /* CORE_INC_FAHRAUSNAHME_H_ */
