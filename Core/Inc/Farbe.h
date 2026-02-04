/**
 * @file Farbe.h
 *
 * @brief Escape codes für die Färbung
 */
#ifndef CORE_INC_FARBE_H_
#define CORE_INC_FARBE_H_

/**
 * @namepsace Farbe
 *
 * @brief ANSI Farbe escape codes für die Ausgabe
 */
namespace Farbe {
	/**
	 * @brief Zurücksetzen die Farbe
	 */
    inline const char* reset   = "\033[0m";

    /**
     * @brief Schwarz
     */
    inline const char* black   = "\033[30m";

    /**
     * @brief Rot
     */
    inline const char* red     = "\033[31m";

    /**
     * @brief Grün
     */
    inline const char* green   = "\033[32m";

    /**
     * @brief Gelb
     */
    inline const char* yellow  = "\033[33m";

    /**
     * @brief Blau
     */
    inline const char* blue    = "\033[34m";

    /**
     * @brief Weiß
     */
    inline const char* white   = "\033[37m";

    /**
     * @brief Bold
     */
    inline const char* bold      = "\033[1m";

    /**
     * @brief Italic
     */
    inline const char* italic    = "\033[3m";
}

#endif /* CORE_INC_FARBE_H_ */
