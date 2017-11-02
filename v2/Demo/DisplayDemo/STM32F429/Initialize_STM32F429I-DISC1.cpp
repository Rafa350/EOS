#include "eos.h"
#include "hal/halGPIO.h"
#include "hal/halSYS.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_sdram.h"


#define SDRAM_DEVICE_ADDR         ((uint32_t)0xD0000000)
#define SDRAM_DEVICE_SIZE         ((uint32_t)0x800000)  /* SDRAM device size in MBytes */

/**
  * @brief  FMC SDRAM Memory Width
  */
/* #define SDRAM_MEMORY_WIDTH   FMC_SDRAM_MEM_BUS_WIDTH_8 */
#define SDRAM_MEMORY_WIDTH      FMC_SDRAM_MEM_BUS_WIDTH_16

/**
  * @brief  FMC SDRAM CAS Latency
  */
/* #define SDRAM_CAS_LATENCY    FMC_SDRAM_CAS_LATENCY_2 */
#define SDRAM_CAS_LATENCY       FMC_SDRAM_CAS_LATENCY_3

/**
  * @brief  FMC SDRAM Memory clock period
  */
#define SDCLOCK_PERIOD          FMC_SDRAM_CLOCK_PERIOD_2    /* Default configuration used with LCD */
/* #define SDCLOCK_PERIOD       FMC_SDRAM_CLOCK_PERIOD_3 */

/**
  * @brief  FMC SDRAM Memory Read Burst feature
  */
#define SDRAM_READBURST         FMC_SDRAM_RBURST_DISABLE    /* Default configuration used with LCD */
/* #define SDRAM_READBURST      FMC_SDRAM_RBURST_ENABLE */

/**
  * @brief  FMC SDRAM Bank Remap
  */
/* #define SDRAM_BANK_REMAP */

/* Set the refresh rate counter */
/* (15.62 us x Freq) - 20 */
#define REFRESH_COUNT           ((uint32_t)1386)   /* SDRAM refresh counter */
#define SDRAM_TIMEOUT           ((uint32_t)0xFFFF)

/* DMA definitions for SDRAM DMA transfer */
#define __DMAx_CLK_ENABLE       __DMA2_CLK_ENABLE
#define SDRAM_DMAx_CHANNEL      DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM       DMA2_Stream0
#define SDRAM_DMAx_IRQn         DMA2_Stream0_IRQn
#define SDRAM_DMAx_IRQHandler   DMA2_Stream0_IRQHandler

/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


static SDRAM_HandleTypeDef sdramHandle;
static FMC_SDRAM_TimingTypeDef timing;
static FMC_SDRAM_CommandTypeDef command;
static DMA_HandleTypeDef dmaHandle;


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins.
///
static void InitializePins() {

	static GPIOInitializePortInfo gpioInitFMC[] = {
		{ HAL_GPIO_PORT_B,
		  HAL_GPIO_POS_5 | HAL_GPIO_POS_6,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC },
		{ HAL_GPIO_PORT_C,
		  HAL_GPIO_POS_0,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC },
		{ HAL_GPIO_PORT_D,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_8 | HAL_GPIO_POS_9 | HAL_GPIO_POS_10 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC },
		{ HAL_GPIO_PORT_E,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_7 | HAL_GPIO_POS_8 | HAL_GPIO_POS_9 | HAL_GPIO_POS_10 | HAL_GPIO_POS_11 | HAL_GPIO_POS_12 | HAL_GPIO_POS_13 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC },
		{ HAL_GPIO_PORT_F,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_2 | HAL_GPIO_POS_3 | HAL_GPIO_POS_4 | HAL_GPIO_POS_5 | HAL_GPIO_POS_11 | HAL_GPIO_POS_12 | HAL_GPIO_POS_13 | HAL_GPIO_POS_14 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC },
		{ HAL_GPIO_PORT_G,
		  HAL_GPIO_POS_0 | HAL_GPIO_POS_1 | HAL_GPIO_POS_4 | HAL_GPIO_POS_5 | HAL_GPIO_POS_8 | HAL_GPIO_POS_15,
		  HAL_GPIO_OPENDRAIN_DISABLED | HAL_GPIO_PULL_NONE | HAL_GPIO_SPEED_HIGH | HAL_GPIO_MODE_FUNCTION, HAL_GPIO_AF12_FMC }
	};

	// Inicialitza els pins associats al controlador FMC_SDRAM
	//
	halGPIOInitializePorts(gpioInitFMC, sizeof(gpioInitFMC) / sizeof(gpioInitFMC[0]));
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el controlador de memoria SDRAM
///
static void InitializeSDRAM() {

	sdramHandle.Instance = FMC_SDRAM_DEVICE;

	/* FMC Configuration -------------------------------------------------------*/
	/* FMC SDRAM Bank configuration */
	/* Timing configuration for 90 Mhz of SD clock frequency (180Mhz/2) */
	/* TMRD: 2 Clock cycles */
	timing.LoadToActiveDelay    = 2;
	/* TXSR: min=70ns (7x11.11ns) */
	timing.ExitSelfRefreshDelay = 7;
	/* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
	timing.SelfRefreshTime      = 4;
	/* TRC:  min=70 (7x11.11ns) */
	timing.RowCycleDelay        = 7;
	/* TWR:  min=1+ 7ns (1+1x11.11ns) */
	timing.WriteRecoveryTime    = 2;
	/* TRP:  20ns => 2x11.11ns*/
	timing.RPDelay              = 2;
	/* TRCD: 20ns => 2x11.11ns */
	timing.RCDDelay             = 2;

	/* FMC SDRAM control configuration */
	sdramHandle.Init.SDBank             = FMC_SDRAM_BANK2;
	/* Row addressing: [7:0] */
	sdramHandle.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
	/* Column addressing: [11:0] */
	sdramHandle.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
	sdramHandle.Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
	sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	sdramHandle.Init.CASLatency         = SDRAM_CAS_LATENCY;
	sdramHandle.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	sdramHandle.Init.SDClockPeriod      = SDCLOCK_PERIOD;
	sdramHandle.Init.ReadBurst          = SDRAM_READBURST;
	sdramHandle.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;

	// -------------------------------------------------------------------
	// Inicialitza el controlador
	// -------------------------------------------------------------------

	__FMC_CLK_ENABLE();
	__DMAx_CLK_ENABLE();

	// Configure common DMA parameters
	dmaHandle.Init.Channel             = SDRAM_DMAx_CHANNEL;
	dmaHandle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
	dmaHandle.Init.PeriphInc           = DMA_PINC_ENABLE;
	dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
	dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
	dmaHandle.Init.Mode                = DMA_NORMAL;
	dmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
	dmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
	dmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	dmaHandle.Init.MemBurst            = DMA_MBURST_SINGLE;
	dmaHandle.Init.PeriphBurst         = DMA_PBURST_SINGLE;

	dmaHandle.Instance = SDRAM_DMAx_STREAM;

	// Associate the DMA handle
	__HAL_LINKDMA(&sdramHandle, hdma, dmaHandle);

	// Deinitialize the stream for new transfer
	HAL_DMA_DeInit(&dmaHandle);

	// Configure the DMA stream
	HAL_DMA_Init(&dmaHandle);

	// NVIC configuration for DMA transfer complete interrupt
	HAL_NVIC_SetPriority(SDRAM_DMAx_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SDRAM_DMAx_IRQn);

	/* SDRAM controller initialization */
	HAL_SDRAM_Init(&sdramHandle, &timing);

	// -------------------------------------------------------------------
	// SDRAM initialization sequence
	// -------------------------------------------------------------------

	__IO uint32_t tmpmrd = 0;

	/* Step 1:  Configure a clock configuration enable command */
	command.CommandMode             = FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber       = 1;
	command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdramHandle, &command, SDRAM_TIMEOUT);

	/* Step 2: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	HAL_Delay(1);

	/* Step 3: Configure a PALL (precharge all) command */
	command.CommandMode             = FMC_SDRAM_CMD_PALL;
	command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber       = 1;
	command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdramHandle, &command, SDRAM_TIMEOUT);

	/* Step 4: Configure an Auto Refresh command */
	command.CommandMode             = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber       = 4;
	command.ModeRegisterDefinition  = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdramHandle, &command, SDRAM_TIMEOUT);

	/* Step 5: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_3           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	command.CommandMode             = FMC_SDRAM_CMD_LOAD_MODE;
	command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber       = 1;
	command.ModeRegisterDefinition  = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdramHandle, &command, SDRAM_TIMEOUT);

	/* Step 6: Set the refresh rate counter */
	/* Set the device refresh rate */
	HAL_SDRAM_ProgramRefreshRate(&sdramHandle, REFRESH_COUNT);
}


void BSP_SDRAM_DMA_IRQHandler(void) {

	HAL_DMA_IRQHandler(sdramHandle.hdma);
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el hardware del sistema.
///
void InitializeHardware() {

	halSYSInitialize();

	InitializePins();
	InitializeSDRAM();
}
