#include "../Inc/Fahrausnahme.h"
#include "../Inc/Fahrzeug.h"
#include "../Inc/Weg.h"

Fahrausnahme::Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg): p_pFahrzeug(fahrzeug), p_pWeg(weg) {};
