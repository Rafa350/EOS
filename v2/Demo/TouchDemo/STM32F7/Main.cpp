#include "cmsis_os.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"


extern void AppMain();
extern void InitializeHardware();


static void LED_Thread1(void const *argument) {

	uint32_t PreviousWakeTime = osKernelSysTick();

	while (true) {
		osDelayUntil (&PreviousWakeTime, 200);
		BSP_LED_Toggle(LED1);
	}
}


void demo() {

	static osThreadId LED1_ThreadId;

	/* Initialize LEDs */
	BSP_LED_Init(LED1);

	/* Thread 1 definition */
	osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

	/* Start thread 1 */
	LED1_ThreadId = osThreadCreate(osThread(LED1), NULL);

	/* Start scheduler */
	osKernelStart();

	  /* We should never get here as control is now taken by the scheduler */
	while (true)
		continue;
}



/// ----------------------------------------------------------------------
/// \brief Punt d'entrada a l'aplicacio.
///
int main() {

	// Inicialitzacio del hardware
	//
	InitializeHardware();

	// Inicia l'aplicacio EOS
	//
	AppMain();
	//demo();

	return 0;
}
