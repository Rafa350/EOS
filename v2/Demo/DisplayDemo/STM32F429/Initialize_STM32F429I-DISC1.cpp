#include "eos.h"
#include "hal/halSYS.h"
#include "stm32f429i_discovery_sdram.h"


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void InitializeHardware() {

	halSYSInitialize();

	BSP_SDRAM_Init();
	BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);

}
