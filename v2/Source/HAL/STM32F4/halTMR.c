#include "hal/halTMR.h"


/// ----------------------------------------------------------------------
/// \brief Retard en milisegons.
/// \param time: Temps en milisegons.
///
void halTMRDelay(
    uint32_t time) {

	while (time--) {
		for (int i = 1000; i; i--)
			continue;
	}

}