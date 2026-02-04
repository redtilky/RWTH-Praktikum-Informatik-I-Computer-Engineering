/**
 * @file Simulationsobjekt.h
 *
 * @brief Definition der abstrakten Basisklasse Simulationsobjekt sowie globaler Simulationsparameter.
 */
#ifndef CORE_INC_SIMULATIONSOBJEKT_H_
#define CORE_INC_SIMULATIONSOBJEKT_H_

#include <string>
#include <iosfwd>

/**
 * @brief Globale Simulationszeit.
 */
extern double dGlobaleZeit;

/**
 * @brief Zeitschrittweite (Takt) der Simulation.
 */
extern double dZeittakt;

/**
 * @brief Endzeitpunkt der Simulation.
 */
extern double dEndZeit;

/**
 * @brief Abstrakte Basisklasse für alle Objekte der Simulation.
 *
 * Jedes Simulationsobjekt besitzt einen Namen und eine eindeutige Identifikationsnummer (ID).
 * Die ID wird bei der Objekterzeugung automatisch vergeben und dient der eindeutigen Zuordnung
 * von Objekten innerhalb der Simulation.
 *
 * Die Klasse definiert die Schnittstellen für:
 * - Simulation eines Zeitschritts (vSimulieren)
 * - objektspezifische Ausgabe (vAusgeben)
 */
class Simulationsobjekt {
public:
	/**
	 * @brief Konstruktor zur Initialisierung des Simulationsobjekts.
	 *
	 * @param name Name/Bezeichnung des Objekts.
	 */
	Simulationsobjekt(std::string name);

	/**
	 * @brief Virtueller Destruktor.
	 */
	virtual ~Simulationsobjekt();

	/**
	 * @brief Kopierkonstruktor ist deaktiviert.
	 */
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	/**
	 * @brief Führt die Simulation des Objekts für den aktuellen Zeitschritt aus.
	 */
	virtual void vSimulieren() = 0;

	/**
	 * @brief Schreibt eine objektspezifische Darstellung in einen Ausgabestrom.
	 *
	 * @param os Ausgabestrom.
	 */
	virtual void vAusgeben(std::ostream &os) const = 0;

	/**
	 * @brief Liefert den Namen des Objekts.
	 *
	 * @return Name des Objekts.
	 */
	std::string sGetName() const;

	/**
	 * @brief Liefert die zuletzt verwendete Objektzeit.
	 *
	 * @return Zeitstempel des Objekts.
	 */
	double dGetZeit() const;

	/**
	 * @brief Zuweisungsoperator.
	 *
	 * Hinweis: Falls Kopiersemantik nicht vorgesehen ist, sollte auch dieser Operator
	 * gelöscht werden (analog zum Copy-Konstruktor).
	 */
	Simulationsobjekt& operator=(const Simulationsobjekt& simulationsobjekt);

	/**
	 * @brief Vergleich zweier Simulationsobjekte.
	 *
	 * @param other Vergleichsobjekt.
	 * @return true, falls beide Objekte als gleich definiert sind (z. B. über ID).
	 */
	bool operator==(const Simulationsobjekt& other) const;
protected:
	/**
	 * @brief Name des Simulationsobjekts.
	 */
	std::string p_sName = "";

	/**
	 * @brief Objektinterner Zeitstempel (letzter Simulationszeitpunkt).
	 */
	double p_dZeit = 0;

	/**
	 * @brief Eindeutige ID des Objekts.
	 */
	const int p_iID;
private:
	/**
	 * @brief Laufende Vergabequelle für Objekt-IDs.
	 *
	 * Wird bei jeder Objekterzeugung erhöht, um eindeutige IDs zu gewährleisten.
	 */
	static int p_iMaxID;
};


/**
 * @brief Stream-Ausgabeoperator für Simulationsobjekt.
 *
 * @param os Ausgabestrom.
 * @param simulationsobjekt Referenz auf das auszugebende Objekt.
 * @return Referenz auf den Ausgabestrom.
 */
std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& simulationsobjekt);

#endif /* CORE_INC_SIMULATIONSOBJEKT_H_ */
