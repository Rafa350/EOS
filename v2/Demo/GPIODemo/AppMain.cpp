#include "hal/halGPIO.h"


/// ----------------------------------------------------------------------
/// \brief Entrada a l'aplicacio
///
void AppMain() {

	halGPIOInitializePin(GPIO_PORT_G, GPIO_PIN_13, GPIO_DIRECTION_OUTPUT);
	halGPIOInitializePin(GPIO_PORT_G, GPIO_PIN_14, GPIO_DIRECTION_OUTPUT);

	halGPIOClearPin(GPIO_PORT_G, GPIO_PIN_13);
	halGPIOSetPin(GPIO_PORT_G, GPIO_PIN_14);

	while (true) {

		halGPIOTogglePin(GPIO_PORT_G, GPIO_PIN_13);
		halGPIOTogglePin(GPIO_PORT_G, GPIO_PIN_14);

		for (int i = 0; i < 100000; i++)
			continue;
	}
}
