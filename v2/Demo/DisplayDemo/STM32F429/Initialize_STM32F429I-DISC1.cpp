#include "eos.h"
#include "hal/halGPIO.h"
#include "stm32f4xx.h"
#include "stm32f4xx_fmc.h"


// -----------------------------------------------------------------------
// Parametres del controlador de memoria SDRAM
// -----------------------------------------------------------------------

#define SDRAM_START_ADR             (uint32_t)0xD0000000        // Inici de la ram
#define SDRAM_MEMORY_SIZE           (uint32_t)0x800000          // Tamany de la ram 8MB
#define SDRAM_BANK                  FMC_Bank2_SDRAM             // Banc de memoria
#define SDRAM_COMMAND_TARGET_BANK   FMC_Command_Target_bank2    // Bank target command
#define SDRAM_REFRESH_COUNT         680                         // Refresh count
#define SDRAM_ROWBITS_NUMBER        FMC_RowBits_Number_12b      // Numero de fileres
#define SDRAM_MEMORY_WIDTH          FMC_SDMemory_Width_16b      // Amplada de dades
#define SDRAM_READ_BURST_STATE      FMC_Read_Burst_Disable      // Read burst
#define SDRAM_REG_VALUE             0x0231                      // Register value
#define SDRAM_TIMEOUT               ((uint32_t)0xFFFF)          // Initialization timeout

#define SDRAM_Write8(address, value)		(*(__IO uint8_t *) (SDRAM_START_ADR + (address)) = (value))
#define SDRAM_Read8(address)				(*(__IO uint8_t *) (SDRAM_START_ADR + (address)))



/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins.
///
static void InitializePins() {

	static GPIOInitializePortInfo gpioInitFMC[] = {
		{ HAL_GPIO_PORT_B,
		  HAL_GPIO_POS_5 | HAL_GPIO_POS_6,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC },
		{ HAL_GPIO_PORT_C,
		  HAL_GPIO_POS_0,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC },
		{ HAL_GPIO_PORT_D,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_8 | HAL_GPIO_POS_9 | HAL_GPIO_POS_10 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC },
		{ HAL_GPIO_PORT_E,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_7 | HAL_GPIO_POS_8 | HAL_GPIO_POS_9 | HAL_GPIO_POS_10 | HAL_GPIO_POS_11 | HAL_GPIO_POS_12 | HAL_GPIO_POS_13 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC },
		{ HAL_GPIO_PORT_F,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_2 | HAL_GPIO_POS_3 | HAL_GPIO_POS_4 | HAL_GPIO_POS_5 | HAL_GPIO_POS_11 | HAL_GPIO_POS_12 | HAL_GPIO_POS_13 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC },
		{ HAL_GPIO_PORT_G,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_4 | HAL_GPIO_POS_5 | HAL_GPIO_POS_8 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF_FMC }
	};

	// Inicialitza els pins associats al controlador FMC_SDRAM
	//
	halGPIOInitializePorts(gpioInitFMC, sizeof(gpioInitFMC) / sizeof(gpioInitFMC[0]));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador de memoria SDRAM
///
static void InitializeSDRAM() {

	FMC_SDRAMInitTypeDef FMC_SDRAMInitStructure;
	FMC_SDRAMTimingInitTypeDef FMC_SDRAMTimingInitStructure;
	FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;

	volatile uint32_t timeout = SDRAM_TIMEOUT;

	/* Enable FMC clock */
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;

	/* FMC SDRAM device initialization sequence --------------------------------*/
	/* Step 1 ----------------------------------------------------*/
	/* Timing configuration for 90 Mhz of SD clock frequency (180Mhz/2) */
	/* TMRD: 2 Clock cycles */
	/* 1 clock cycle = 1 / 90MHz = 11.1ns */
	FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay		= 2;
	/* TXSR: min=70ns (7x11.10ns) */
	FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay	= 7;
	/* TRAS: min=42ns (4x11.10ns) max=120k (ns) */
	FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime		= 4;
	/* TRC:  min=70 (7x11.10ns) */
	FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay			= 7;
	/* TWR:  min=1+ 7ns (1+1x11.10ns) */
	FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime		= 2;
	/* TRP:  20ns => 2x11.10ns */
	FMC_SDRAMTimingInitStructure.FMC_RPDelay				= 2;
	/* TRCD: 20ns => 2x11.10ns */
	FMC_SDRAMTimingInitStructure.FMC_RCDDelay				= 2;


	/* FMC SDRAM control configuration */
	FMC_SDRAMInitStructure.FMC_Bank 						= SDRAM_BANK;
	/* Row addressing: [7:0] */
	FMC_SDRAMInitStructure.FMC_ColumnBitsNumber 			= FMC_ColumnBits_Number_8b;
	/* Column addressing: [11:0] */
	FMC_SDRAMInitStructure.FMC_RowBitsNumber      			= SDRAM_ROWBITS_NUMBER;
	FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth  			= SDRAM_MEMORY_WIDTH;
	FMC_SDRAMInitStructure.FMC_InternalBankNumber 			= FMC_InternalBank_Number_4;
	/* CL: Cas Latency = 3 clock cycles */
	FMC_SDRAMInitStructure.FMC_CASLatency              	    = FMC_CAS_Latency_3;
	FMC_SDRAMInitStructure.FMC_WriteProtection 				= FMC_Write_Protection_Disable;
	FMC_SDRAMInitStructure.FMC_SDClockPeriod 				= FMC_SDClock_Period_2;
	FMC_SDRAMInitStructure.FMC_ReadBurst 					= SDRAM_READ_BURST_STATE;
	FMC_SDRAMInitStructure.FMC_ReadPipeDelay 				= FMC_ReadPipe_Delay_1;
	FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct 			= &FMC_SDRAMTimingInitStructure;

	/* FMC SDRAM bank initialization */
	FMC_SDRAMInit(&FMC_SDRAMInitStructure);

	/* SDRAM Init sequence */

	/* Configure a clock configuration enable command */
	FMC_SDRAMCommandStructure.FMC_CommandMode				= FMC_Command_Mode_CLK_Enabled;
	FMC_SDRAMCommandStructure.FMC_CommandTarget 			= SDRAM_COMMAND_TARGET_BANK;
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber 		= 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition 	= 0;

	/* Wait until the SDRAM controller is ready */
	timeout = SDRAM_TIMEOUT;
	while (FMC_GetFlagStatus(SDRAM_BANK, FMC_FLAG_Busy) != RESET && timeout) {
		timeout--;
	}

	/* Send the command */
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

	/* Little delay */
	timeout = SDRAM_TIMEOUT * 0x110;
	while (timeout--);

	/* Configure a PALL (precharge all) command */
	FMC_SDRAMCommandStructure.FMC_CommandMode          		= FMC_Command_Mode_PALL;
	FMC_SDRAMCommandStructure.FMC_CommandTarget          	= SDRAM_COMMAND_TARGET_BANK;
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber      	= 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition 	= 0;

	/* Wait until the SDRAM controller is ready */
	timeout = SDRAM_TIMEOUT;
	while (FMC_GetFlagStatus(SDRAM_BANK, FMC_FLAG_Busy) != RESET && timeout) {
		timeout--;
	}

	/* Send the command */
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

	/* Configure a Auto-Refresh command */
	FMC_SDRAMCommandStructure.FMC_CommandMode            	= FMC_Command_Mode_AutoRefresh;
	FMC_SDRAMCommandStructure.FMC_CommandTarget          	= SDRAM_COMMAND_TARGET_BANK;
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber      	= 8;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition 	= 0;

	/* Wait until the SDRAM controller is ready */
	timeout = SDRAM_TIMEOUT;
	while (FMC_GetFlagStatus(SDRAM_BANK, FMC_FLAG_Busy) != RESET && timeout) {
		timeout--;
	}

	/* Send the command */
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

	/* Configure a load Mode register command */
	FMC_SDRAMCommandStructure.FMC_CommandMode            	= FMC_Command_Mode_LoadMode;
	FMC_SDRAMCommandStructure.FMC_CommandTarget          	= SDRAM_COMMAND_TARGET_BANK;
	FMC_SDRAMCommandStructure.FMC_AutoRefreshNumber      	= 1;
	FMC_SDRAMCommandStructure.FMC_ModeRegisterDefinition 	= (uint32_t)SDRAM_REG_VALUE;

	/* Wait until the SDRAM controller is ready */
	timeout = SDRAM_TIMEOUT;
	while (FMC_GetFlagStatus(SDRAM_BANK, FMC_FLAG_Busy) != RESET && timeout) {
		timeout--;
	}

	/* Send the command */
	FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure);

	/* Set the refresh rate counter */
	/* (7.81 us x Freq) - 20 = (7.81 * 90MHz) - 20 = 683 */
	/* Set the device refresh counter */
	FMC_SetRefreshCount(SDRAM_REFRESH_COUNT);

	/* Wait until the SDRAM controller is ready */
	timeout = SDRAM_TIMEOUT;
	while (FMC_GetFlagStatus(SDRAM_BANK, FMC_FLAG_Busy) != RESET && timeout) {
		timeout--;
	}

	SDRAM_Write8(10, 0x55);
	if (SDRAM_Read8(10) == 0x55) {
		SDRAM_Write8(10, 0xAA);
		if (SDRAM_Read8(10) == 0xAA) {
		}
	}

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void InitializeHardware() {

	InitializePins();
	InitializeSDRAM();
}
