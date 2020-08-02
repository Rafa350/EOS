#include "eos.h"
#include "OSAL/osalKernel.h"


void NMI_Handler(void) {
}


void HardFault_Handler(void) {

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


/// ----------------------------------------------------------------------
// \brief     Handler de la interrupcio SysTick
///
void SysTick_Handler(void) {

	osalSysTickHandler();
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio ETH
///
void ETH_IRQHandler(void) {

	extern ETH_HandleTypeDef EthHandle;

	HAL_ETH_IRQHandler(&EthHandle);
}
