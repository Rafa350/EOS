#include "eos.h"
#include "HAL/halGPIO.h"


void NMI_Handler(void) {
}


void HardFault_Handler(void) {

	halGPIOSetPin(LEDS_LED1_PORT, LEDS_LED1_PIN);
#ifdef EXIST_LEDS_LED2
	halGPIOSetPin(LEDS_LED2_PORT, LEDS_LED2_PIN);
#endif
#ifdef EXIST_LEDS_LED3
	halGPIOSetPin(LEDS_LED3_PORT, LEDS_LED3_PIN);
#endif

	while (1) {
	}
}


void MemManage_Handler(void) {

	while (1) {
	}
}


void BusFault_Handler(void) {

	while (1) {
	}
}


void UsageFault_Handler(void) {

	while (1) {
	}
}


void DebugMon_Handler(void) {
}
