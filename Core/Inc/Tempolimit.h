/**
 * @file Tempolimit.h
 *
 * @brief Definition des Enumerations-Typs Tempolimit zur Abbildung zulässiger Höchstgeschwindigkeiten.
 *
 * Die Enum-Werte repräsentieren typische Geschwindigkeitsbegrenzungen (in km/h).
 * Für Autobahn wird ein „praktisch unbegrenztes“ Limit über std::numeric_limits<int>::max() modelliert.
 */
#ifndef CORE_INC_TEMPOLIMIT_H_
#define CORE_INC_TEMPOLIMIT_H_

#include <limits>

enum class Tempolimit {
	/**
	 * @brief Innenorts = 50
	 */
	Innenorts = 50,

	/**
	 * @brief Landstraße = 100
	 */
	Landstraße = 100,

	/**
	 * @brief Autobahn = std::numeric_limits<int>::max()
	 */
	Autobahn = std::numeric_limits<int>::max()
};




#endif /* CORE_INC_TEMPOLIMIT_H_ */
