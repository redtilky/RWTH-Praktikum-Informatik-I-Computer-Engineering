/**
 * @file Verhalten.h
 *
 * @brief Definition der abstrakten Basisklasse Verhalten für fahrzeugspezifische Bewegungsmodelle.
 */
#ifndef CORE_INC_VERHALTEN_H_
#define CORE_INC_VERHALTEN_H_

class Weg;
class Fahrzeug;

/**
 * @brief Abstrakte Basisklasse zur Beschreibung des Verhaltens eines Fahrzeugs auf einem Weg.
 *
 * Eine Instanz von Verhalten kapselt die Logik zur Berechnung der in einem Zeitintervall
 * zurücklegbaren Strecke. Das konkrete Verhalten (z. B. Fahren, Parken) wird in
 * abgeleiteten Klassen implementiert.
 */
class Verhalten {
public:
	/**
	 * @brief Standardkonstruktor.
	 */
	Verhalten();

	/**
	 * @brief Konstruktor zur Initialisierung mit einem zugehörigen Weg.
	 *
	 * @param weg Referenz auf den zugehörigen Weg.
	 */
	Verhalten(Weg& weg);

	/**
	 * @brief Virtueller Destruktor.
	 */
	virtual ~Verhalten() = default;

	/**
	 * @brief Berechnet die innerhalb eines Zeitintervalls zurücklegbare Strecke.
	 *
	 * @param aFzg Referenz auf das betrachtete Fahrzeug.
	 * @param dZeitIntervall Länge des Zeitintervalls.
	 * @return Zurücklegbare Strecke innerhalb des Zeitintervalls.
	 */
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

	/**
	 * @brief Liefert den zugehörigen Weg.
	 *
	 * @return Zeiger auf den Weg (kann nullptr sein, falls nicht gesetzt).
	 */
	Weg* wGetWeg() const;
protected:
	/**
	 * @brief Zeiger auf den zugehörigen Weg.
	 */
	Weg* p_pWeg;
};



#endif /* CORE_INC_VERHALTEN_H_ */
