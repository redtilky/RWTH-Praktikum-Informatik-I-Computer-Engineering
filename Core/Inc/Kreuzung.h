/**
 * @file Kreuzung.h
 *
 * @brief Definition der Klasse Kreuzung zur Modellierung von Knotenpunkten im Simulationsnetz.
 *
 * Diese Datei stellt die Klasse Kreuzung bereit. Eine Kreuzung verwaltet die von ihr
 * ausgehenden Wege, kann optional eine Tankstelle modellieren und bietet Funktionen
 * zum Verbinden von Kreuzungen sowie zur Annahme und Weiterleitung von Fahrzeugen.
 */
#ifndef CORE_INC_KREUZUNG_H_
#define CORE_INC_KREUZUNG_H_

class Fahrzeug;
class Weg;
#include "../Inc/Simulationsobjekt.h"
#include "../Inc/Tempolimit.h"
#include <string>
#include <list>
#include <memory>
#include <iosfwd>

/**
 * @class Kreuzung
 * @brief Knotenobjekt zur Modellierung einer Straßenkreuzung im Simulationsnetz.
 *
 * Ein Objekt der Klasse Kreuzung repräsentiert eine Kreuzung als Simulationsobjekt
 * und verwaltet die von der Kreuzung ausgehenden Wege. Zusätzlich kann optional
 * eine Tankstelle mit einem verfügbaren Tankvolumen modelliert werden.
 */
class Kreuzung : public Simulationsobjekt {
public:
    /**
     * @brief Standardkonstruktor.
     */
    Kreuzung() = default;

    /**
     * @brief Konstruktor zur Initialisierung von Name und Tankstellenkapazität.
     *
     * @param name Name der Kreuzung.
     * @param dTankstelle Verfügbares Tankvolumen der Tankstelle (Default: 0.0).
     */
    Kreuzung(const std::string& name, double dTankstelle = 0.0);

    /**
     * @brief Virtueller Destruktor.
     */
    virtual ~Kreuzung() = default;

    /**
     * @brief Erzeugt eine bidirektionale Verbindung zwischen zwei Kreuzungen.
     *
     * Legt zwei Wege (Hin- und Rückweg) mit der angegebenen Länge und dem Tempolimit
     * zwischen Start- und Zielkreuzung an.
     *
     * @param nameHin Name des Hinweges.
     * @param nameRueck Name des Rückweges.
     * @param laenge Länge der Wege.
     * @param krzstart Startkreuzung.
     * @param krzziel Zielkreuzung.
     * @param tempolimit Tempolimit der Verbindung.
     */
	static void vVerbinde(const std::string &nameHin,
			const std::string &nameRueck, double laenge,
			const std::shared_ptr<Kreuzung> &krzstart,
			const std::shared_ptr<Kreuzung> &krzziel, Tempolimit tempolimit);

    /**
     * @brief Nimmt ein Fahrzeug an der Kreuzung an und plant dessen Start.
     *
     * @param pFahrzeug Besitzübertragendes Fahrzeugobjekt.
     * @param dStartZeit Startzeitpunkt der Weiterfahrt.
     */
    void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartZeit);

    /**
     * @brief Führt die Simulation der Kreuzung für den aktuellen Zeitschritt aus.
     */
    virtual void vSimulieren() override;

    /**
     * @brief Schreibt Kreuzungsdaten in einen Ausgabestrom.
     *
     * @param os Ausgabestrom.
     */
    virtual void vAusgeben(std::ostream& os) const override;

    /**
     * @brief Betankt ein Fahrzeug (sofern Tankstellenvolumen vorhanden ist).
     *
     * @param fahrzeug Referenz auf das zu betankende Fahrzeug.
     */
    void vTanken(Fahrzeug& fahrzeug);

    /**
     * @brief Liefert einen zufälligen ausgehenden Weg (ohne den Ankunftsweg).
     *
     * @param ankunftsWeg Weg, über den das Fahrzeug angekommen ist.
     * @return Zufällig ausgewählter Weg (shared_ptr).
     */
    std::shared_ptr<Weg> pZufaelligerWeg(Weg& ankunftsWeg);

    /**
     * @brief Gibt das verfügbare Tankstellenvolumen zurück.
     *
     * @return Verfügbares Tankvolumen.
     */
    double dGetTankstelle() const;

private:
    /**
     * @brief Liste der von dieser Kreuzung ausgehenden Wege.
     */
    std::list<std::shared_ptr<Weg>> p_pWege;

    /**
     * @brief Verfügbares Tankstellenvolumen.
     */
    double p_dTankstelle = 0.0;
};



#endif /* CORE_INC_KREUZUNG_H_ */
