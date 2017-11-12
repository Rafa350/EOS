#include "eos.h"
#include "hal/halSYS.h"
#include "stm32746g_discovery_sdram.h"


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void InitializeHardware() {

	halSYSInitialize();

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);

}
