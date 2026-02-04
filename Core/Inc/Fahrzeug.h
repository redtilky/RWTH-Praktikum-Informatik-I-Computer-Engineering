/**
 * @file Fahrzeug.h
 *
 * @brief Abstrakte Basisklasse zur Modellierung von Fahrzeugen in der Simulation.
 */
#ifndef CORE_INC_FAHRZEUG_H_
#define CORE_INC_FAHRZEUG_H_

#include "../Inc/Simulationsobjekt.h"
class Weg;
class Verhalten;
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <memory>



/**
 * @brief Allgemeine Basisklasse für Fahrzeuge.
 *
 * Die Klasse Fahrzeug bildet die Grundlage für alle konkreten Fahrzeugtypen in der
 * Simulation. Sie verwaltet zentrale Zustandsgrößen wie maximale Geschwindigkeit,
 * zurückgelegte Strecken sowie die bisherige Simulationszeit.
 *
 * Darüber hinaus stellt sie Schnittstellen zur Ausgabe von Fahrzeugdaten, zur
 * Simulation der Bewegung sowie zur Zuordnung eines Fahrverhaltens auf einem Weg
 * bereit. Die grafische Darstellung ist als rein virtuelle Funktion definiert und
 * muss in abgeleiteten Klassen implementiert werden.
 */
class Fahrzeug : public Simulationsobjekt {
public:
	/**
	 * @brief Konstruktor zur Initialisierung von Name und maximaler Geschwindigkeit.
	 *
	 * @param name Bezeichnung des Fahrzeugs.
	 * @param maxg Maximale Geschwindigkeit des Fahrzeugs.
	 */
	Fahrzeug(std::string name, double maxg);

	/**
	 * @brief Virtueller Destruktor.
	 */
	virtual ~Fahrzeug();

	/**
	 * @brief Gibt die Tabellenkopfzeile für die Fahrzeugausgabe aus.
	 */
	static void vKopf();

	/**
	 * @brief Gibt eine Kurzrepräsentation (z. B. Name und ID) des Fahrzeugs aus.
	 *
	 * Diese Methode ist const, da sie den Objektzustand nicht verändert.
	 */
	void Ausgabe() const;

	/**
	 * @brief Schreibt fahrzeugspezifische Daten in einen Ausgabestrom.
	 *
	 * @param os Ausgabestrom, in den die Informationen geschrieben werden.
	 */
	virtual void vAusgeben(std::ostream& os) const override;

	/**
	 * @brief Führt einen Simulationsschritt basierend auf der globalen Simulationszeit aus.
	 */
	virtual void vSimulieren() override;

	/**
	 * @brief Betankungsfunktion (Standardimplementierung).
	 *
	 * Standardmäßig wird keine Betankung durchgeführt; abgeleitete Klassen können
	 * dieses Verhalten überschreiben.
	 *
	 * @param dMenge Zu betankende Menge (Default: unendlich).
	 * @return Tatsächlich betankte Menge (Default-Implementierung typischerweise 0).
	 */
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	/**
	 * @brief Liefert die aktuell verwendete Geschwindigkeit des Fahrzeugs.
	 *
	 * Diese Funktion ist als virtuelle Schnittstelle ausgelegt, damit abgeleitete
	 * Klassen (z. B. Fahrrad) eine spezifische Geschwindigkeitsberechnung implementieren können.
	 *
	 * @return Aktuelle Geschwindigkeit des Fahrzeugs.
	 */
	virtual double dGeschwindigkeit() const;

	/**
	 * @brief Weist dem Fahrzeug einen neuen Weg zu und setzt das zugehörige Verhalten.
	 *
	 * @param weg Referenz auf den neuen Weg.
	 */
	void vNeueStrecke(Weg& weg);

	/**
	 * @brief Weist dem Fahrzeug einen neuen Weg zu und initialisiert ein Startzeit-abhängiges Verhalten.
	 *
	 * Typischer Anwendungsfall: Parkverhalten mit vorgegebenem Startzeitpunkt.
	 *
	 * @param weg Referenz auf den neuen Weg.
	 * @param dStartZeit Startzeitpunkt für das (z. B. Parken-)Verhalten.
	 */
	void vNeueStrecke(Weg &weg, double dStartZeit);

	/**
	 * @brief Liefert die auf dem aktuellen Wegabschnitt zurückgelegte Strecke.
	 *
	 * @return Abschnittsstrecke auf dem aktuellen Weg.
	 */
	virtual double getAbschnittStrecke() const;


	/**
	 * @brief Grafische Darstellung des Fahrzeugs im Kontext eines Weges.
	 *
	 * Muss von abgeleiteten Klassen implementiert werden.
	 *
	 * @param weg Referenz auf den Weg, auf dem das Fahrzeug dargestellt wird.
	 */
	virtual void vZeichnen(const Weg& weg) const = 0;

	/**
	 * @brief Vergleichsoperator basierend auf der zurückgelegten Gesamtstrecke.
	 *
	 * @param fahrzeug Referenz auf das Vergleichsfahrzeug.
	 * @return true, falls die Gesamtstrecke dieses Fahrzeugs kleiner ist als die des Vergleichsfahrzeugs.
	 */
	bool operator<(const Fahrzeug& fahrzeug) const;
protected:
	/**
	 * @brief Maximale Geschwindigkeit des Fahrzeugs.
	 *
	 * Konstante Obergrenze der Geschwindigkeit; wird im Konstruktor initialisiert.
	 */
	const double p_dMaxGeschwindigkeit = 0;

	/**
	 * @brief Insgesamt zurückgelegte Strecke.
	 */
	double p_dGesamtStrecke = 0;

	/**
	 * @brief Insgesamt verstrichene Fahr-/Simulationszeit.
	 */
	double p_dGesamtZeit = 0;

	/**
	 * @brief Aktuell zugeordnetes Verhalten des Fahrzeugs.
	 */
	std::unique_ptr<Verhalten> p_pVerhalten;

	/**
	 * @brief Auf dem aktuellen Wegabschnitt zurückgelegte Strecke.
	 */
	double p_dAbschnittStrecke = 0;
};

#endif /* CORE_INC_FAHRZEUG_H_ */
