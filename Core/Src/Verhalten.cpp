#include "../Inc/Verhalten.h"
#include "../Inc/Weg.h"

Verhalten::Verhalten(Weg& weg):
	p_pWeg(&weg)
{};

Weg* Verhalten::wGetWeg() const {return p_pWeg;}
