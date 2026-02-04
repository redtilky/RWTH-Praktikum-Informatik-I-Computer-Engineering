/**
 * @file Weg.h
 *
 * @brief Definition der Klasse Weg zur Modellierung von Streckenabschnitten in der Simulation.
 *
 * Ein Weg ist ein Streckenabschnitt mit fester Länge und Tempolimit. Er verwaltet
 * die auf ihm befindlichen Fahrzeuge und stellt Schnittstellen zur Annahme, Abgabe
 * und Simulation dieser Fahrzeuge bereit. Optional können ein Rückweg sowie eine
 * Zielkreuzung referenziert werden.
 */
#ifndef CORE_INC_WEG_H_
#define CORE_INC_WEG_H_

class Fahrzeug;
class Kreuzung;
#include "../Inc/Simulationsobjekt.h"
#include "../Inc/Tempolimit.h"
#include "../Inc/vertagt_liste.h"
#include <string>
#include <memory>
#include <iosfwd>

/**
 * @brief Klasse zur Modellierung eines Weges (Streckenabschnitts) im Simulationsnetz.
 *
 * Die Klasse Weg erweitert Simulationsobjekt um streckenspezifische Parameter
 * (Länge, Tempolimit) und verwaltet Fahrzeuge, die sich aktuell auf diesem Weg
 * befinden. Die Fahrzeugverwaltung erfolgt über eine vertagte Liste, um
 * Modifikationen während einer Iteration sicher zu ermöglichen.
 *
 * Zusätzlich kann ein Rückweg (bidirektionale Verbindung) und eine Zielkreuzung
 * (z. B. für Netzübergänge) hinterlegt werden.
 */
class Weg : public Simulationsobjekt {
public:
	/**
	 * @brief Standardkonstruktor.
	 *
	 * Initialisiert einen Weg mit projektspezifischen Standardwerten.
	 */
	Weg();

	/**
	 * @brief Konstruktor zur Initialisierung eines Weges.
	 *
	 * @param name Name/Bezeichnung des Weges.
	 * @param laenge Länge des Weges.
	 * @param tempolimit Zulässiges Tempolimit (Default: Autobahn).
	 * @param ziel Optionaler Zeiger (shared_ptr) auf die Zielkreuzung (Default: nullptr).
	 */
	Weg(std::string name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn, std::shared_ptr<Kreuzung> ziel = nullptr);

	/**
	 * @brief Destruktor.
	 */
	~Weg();

	/**
	 * @brief Simuliert alle Fahrzeuge auf diesem Weg für den aktuellen Zeitschritt.
	 *
	 * Im Unterschied zur Simulation einzelner Fahrzeuge iteriert diese Methode
	 * über die interne Fahrzeugliste und ruft die jeweilige Fahrzeugsimulation auf.
	 */
	virtual void vSimulieren() override;

	/**
	 * @brief Gibt die Tabellenkopfzeile für die Wegausgabe aus.
	 */
	static void vKopf();

	/**
	 * @brief Schreibt wegspezifische Daten in einen Ausgabestrom.
	 *
	 * @param os Ausgabestrom.
	 */
	virtual void vAusgeben(std::ostream &os) const override;

	/**
	 * @brief Nimmt ein Fahrzeug auf dem Weg an.
	 *
	 * Das Fahrzeug wird in die interne Verwaltung übernommen (Ownership-Transfer).
	 *
	 * @param fahrzeug Besitzübertragendes Fahrzeugobjekt.
	 */
	virtual void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);

	/**
	 * @brief Nimmt ein Fahrzeug mit Startzeit (z. B. Parken) auf dem Weg an.
	 *
	 * @param fahrzeug Besitzübertragendes Fahrzeugobjekt.
	 * @param dStartZeit Startzeitpunkt für ein startzeitabhängiges Verhalten.
	 */
	virtual void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit);

	/**
	 * @brief Liefert das Tempolimit des Weges.
	 *
	 * @return Tempolimit des Weges (als numerischer Wert).
	 */
	double getTempolimit() const;

	/**
	 * @brief Liefert die Länge des Weges.
	 *
	 * @return Weglänge.
	 */
	double getLaenge() const;

	/**
	 * @brief Führt eine einmalige Initialaktualisierung durch.
	 *
	 * Typischer Einsatz: Initialisieren/Anpassen interner Zustände vor dem ersten
	 * Simulationsschritt (projektspezifische Semantik).
	 */
	void vErsteInnitAkt();

	/**
	 * @brief Gibt ein Fahrzeug aus der Verwaltung dieses Weges ab.
	 *
	 * Sucht das angegebene Fahrzeug in der internen Liste, entfernt es und gibt
	 * die Ownership als unique_ptr zurück.
	 *
	 * @param fahrzeug Referenz auf das abzugebende Fahrzeug.
	 * @return unique_ptr auf das abgegebene Fahrzeug; nullptr, falls nicht gefunden.
	 */
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);

	/**
	 * @brief Liefert den Rückweg (falls vorhanden).
	 *
	 * @return shared_ptr auf den Rückweg oder nullptr, falls nicht gesetzt/abgelaufen.
	 */
	std::shared_ptr<Weg> getRueckweg() const;

	/**
	 * @brief Liefert die Zielkreuzung (falls vorhanden).
	 *
	 * @return shared_ptr auf die Zielkreuzung oder nullptr, falls nicht gesetzt/abgelaufen.
	 */
	std::shared_ptr<Kreuzung> getZielkreuzung() const;

	/**
	 * @brief Setzt den Rückweg für diese Weginstanz.
	 *
	 * @param pRueckweg shared_ptr auf den Rückweg.
	 */
	void vSetRueckweg(const std::shared_ptr<Weg>& pRueckweg);

private:
	/**
	 * @brief Länge des Weges.
	 */
	double p_dLaenge;

	/**
	 * @brief Tempolimit des Wegs
	 */
	Tempolimit p_eTempolimit;

	/**
	 * @brief Verwaltung der Fahrzeuge auf diesem Weg.
	 *
	 * Vertagte Liste zur sicheren Modifikation (Einfügen/Löschen) während Iterationen.
	 */
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

	/**
	 * @brief Schwache Referenz auf den Rückweg.
	 *
	 * Wird als weak_ptr gespeichert, um zyklische Referenzen zu vermeiden.
	 */
	std::weak_ptr<Weg> p_pRueckweg;

	/**
	 * @brief Schwache Referenz auf die Zielkreuzung.
	 *
	 * Wird als weak_ptr gespeichert, um Besitzverhältnisse klar zu halten.
	 */
	const std::weak_ptr<Kreuzung> p_pZielKreuzung;
};




#endif /* CORE_INC_WEG_H_ */
