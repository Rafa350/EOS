#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "HAL/halTMR.h"
#include "hal/halI2C.h"
#include "hal/halGPIO.h"


using namespace eos;


ITouchPadDriver *FT5336_Driver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
ITouchPadDriver *FT5336_Driver::getInstance() {

	if (instance == nullptr)
		instance = new FT5336_Driver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
FT5336_Driver::FT5336_Driver():

	addr(FT5336_I2C_ADDR),
	padWidth(FT5336_PAD_WIDTH),
	padHeight(FT5336_PAD_HEIGHT),
	currActiveTouchNb(0) {

	// Wait at least 200ms after power up before accessing registers
	// Trsi timing (Time of starting to report point after resetting) from FT5336GQQ datasheet
	//
	//halTMRDelay(200);
    ioInit();
}


void FT5336_Driver::queryState() {

	ReadID();
}


/**
  * @brief  Read the ft5336 device ID, pre initialize I2C in case of need to be
  *         able to read the FT5336 device ID, and verify this is a FT5336.
  * @param  DeviceAddr: I2C FT5336 Slave address.
  * @retval The Device ID (two bytes).
  */
uint16_t FT5336_Driver::ReadID() {

	volatile uint8_t ucReadId = 0;
	uint8_t nbReadAttempts = 0;
	uint8_t bFoundDevice = 0; // Device not found by default

	// At maximum 4 attempts to read ID : exit at first finding of the searched device ID
	for (nbReadAttempts = 0; ((nbReadAttempts < 3) && !(bFoundDevice)); nbReadAttempts++) {
		/* Read register FT5336_CHIP_ID_REG as DeviceID detection */
		ucReadId = ioRead(FT5336_CHIP_ID_REG);

		/* Found the searched device ID ? */
		if(ucReadId == FT5336_ID_VALUE) {

			// Set device as found */
			bFoundDevice = 1;
		}
	}

	return ucReadId;
}

/**
  * @brief  Configures the touch Screen IC device to start detecting touches
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address).
  * @retval None.
  */
void FT5336_Driver::Start() {

	// By default set FT5336 IC in Polling mode : no INT generation on FT5336 for new touch available
	// Note TS_INT is active low
	DisableIT();
}


/// ----------------------------------------------------------------------
/// \brief Obte en numero de tocs des de l'ultima crida.
/// \return El numero de tocs.
///
uint8_t FT5336_Driver::getTouches() {

	volatile uint8_t nbTouch = 0;

	// Read register FT5336_TD_STAT_REG to check number of touches detection
	nbTouch = ioRead(FT5336_TD_STAT_REG);
	nbTouch &= FT5336_TD_STAT_MASK;

	if (nbTouch > FT5336_MAX_DETECTABLE_TOUCH) {
		// If invalid number of touch detected, set it to zero
		nbTouch = 0;
	}

	// Update ft5336 driver internal global : current number of active touches
	currActiveTouchNb = nbTouch;

	// Reset current active touch index on which to work on
	currActiveTouchIdx = 0;

	return nbTouch;
}


/// ----------------------------------------------------------------------
/// \brief Obte les coordinades del toc.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
///
void FT5336_Driver::GetXY(uint16_t &x, uint16_t &y) {

	volatile uint8_t ucReadData = 0;
	static uint16_t coord;
	uint8_t regAddressXLow = 0;
	uint8_t regAddressXHigh = 0;
	uint8_t regAddressYLow = 0;
	uint8_t regAddressYHigh = 0;

	if (currActiveTouchIdx < currActiveTouchNb) {
		switch(currActiveTouchIdx) {
			case 0 :
				regAddressXLow  = FT5336_P1_XL_REG;
				regAddressXHigh = FT5336_P1_XH_REG;
				regAddressYLow  = FT5336_P1_YL_REG;
				regAddressYHigh = FT5336_P1_YH_REG;
				break;

			case 1 :
				regAddressXLow  = FT5336_P2_XL_REG;
				regAddressXHigh = FT5336_P2_XH_REG;
				regAddressYLow  = FT5336_P2_YL_REG;
				regAddressYHigh = FT5336_P2_YH_REG;
				break;

			case 2 :
				regAddressXLow  = FT5336_P3_XL_REG;
				regAddressXHigh = FT5336_P3_XH_REG;
				regAddressYLow  = FT5336_P3_YL_REG;
				regAddressYHigh = FT5336_P3_YH_REG;
				break;

			case 3 :
				regAddressXLow  = FT5336_P4_XL_REG;
				regAddressXHigh = FT5336_P4_XH_REG;
				regAddressYLow  = FT5336_P4_YL_REG;
				regAddressYHigh = FT5336_P4_YH_REG;
				break;

			case 4 :
				regAddressXLow  = FT5336_P5_XL_REG;
				regAddressXHigh = FT5336_P5_XH_REG;
				regAddressYLow  = FT5336_P5_YL_REG;
				regAddressYHigh = FT5336_P5_YH_REG;
				break;

			case 5 :
				regAddressXLow  = FT5336_P6_XL_REG;
				regAddressXHigh = FT5336_P6_XH_REG;
				regAddressYLow  = FT5336_P6_YL_REG;
				regAddressYHigh = FT5336_P6_YH_REG;
				break;

			case 6 :
				regAddressXLow  = FT5336_P7_XL_REG;
				regAddressXHigh = FT5336_P7_XH_REG;
				regAddressYLow  = FT5336_P7_YL_REG;
				regAddressYHigh = FT5336_P7_YH_REG;
				break;

			case 7 :
				regAddressXLow  = FT5336_P8_XL_REG;
				regAddressXHigh = FT5336_P8_XH_REG;
				regAddressYLow  = FT5336_P8_YL_REG;
				regAddressYHigh = FT5336_P8_YH_REG;
				break;

			case 8 :
				regAddressXLow  = FT5336_P9_XL_REG;
				regAddressXHigh = FT5336_P9_XH_REG;
				regAddressYLow  = FT5336_P9_YL_REG;
				regAddressYHigh = FT5336_P9_YH_REG;
				break;

			case 9 :
				regAddressXLow  = FT5336_P10_XL_REG;
				regAddressXHigh = FT5336_P10_XH_REG;
				regAddressYLow  = FT5336_P10_YL_REG;
				regAddressYHigh = FT5336_P10_YH_REG;
				break;
		}

		// Read low part of X position
		ucReadData = ioRead(regAddressXLow);
		coord = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Read high part of X position
		ucReadData = ioRead(regAddressXHigh);
		coord |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Send back ready X position to caller
		x = coord;

		// Read low part of Y position
		ucReadData = ioRead(regAddressYLow);
		coord = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Read high part of Y position
		ucReadData = ioRead(regAddressYHigh);
		coord |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Send back ready Y position to caller
		y = coord;

		currActiveTouchIdx++;
	}
}

/**
  * @brief  Configure the FT5336 device to generate IT on given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of FT5336).
  * @retval None
  */
void FT5336_Driver::EnableIT() {

	uint8_t regValue = 0;
	regValue = (FT5336_G_MODE_INTERRUPT_TRIGGER & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

	/* Set interrupt trigger mode in FT5336_GMODE_REG */
	ioWrite(FT5336_GMODE_REG, regValue);
}


/**
  * @brief  Configure the FT5336 device to stop generating IT on the given INT pin
  *         connected to MCU as EXTI.
  * @param  DeviceAddr: Device address on communication Bus (Slave I2C address of FT5336).
  * @retval None
  */
void FT5336_Driver::DisableIT() {

	uint8_t regValue = 0;
	regValue = (FT5336_G_MODE_INTERRUPT_POLLING & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

	/* Set interrupt polling mode in FT5336_GMODE_REG */
	ioWrite(FT5336_GMODE_REG, regValue);
}


/**
  * @brief  Get IT status from FT5336 interrupt status registers
  *         Should be called Following an EXTI coming to the MCU to know the detailed
  *         reason of the interrupt.
  *         @note : This feature is not applicable to FT5336.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT5336).
  * @retval TS interrupts status : always return 0 here
  */
uint8_t FT5336_Driver::ITStatus() {

	// Always return 0 as feature not applicable to FT5336
	return 0;
}

/**
  * @brief  Clear IT status in FT5336 interrupt status clear registers
  *         Should be called Following an EXTI coming to the MCU.
  *         @note : This feature is not applicable to FT5336.
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT5336).
  * @retval None
  */
void FT5336_Driver::ClearIT()
{
  /* Nothing to be done here for FT5336 */
}

/**** NEW FEATURES enabled when Multi-touch support is enabled ****/

#if (TS_MULTI_TOUCH_SUPPORTED == 1)

/**
  * @brief  Get the last touch gesture identification (zoom, move up/down...).
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT5336).
  * @param  pGestureId : Pointer to get last touch gesture Identification.
  * @retval None.
  */
void FT5336_Driver::GetGestureID(uint32_t * pGestureId)
{
  volatile uint8_t ucReadData = 0;

  ucReadData = ioRead(FT5336_GEST_ID_REG);

  * pGestureId = ucReadData;
}

/**
  * @brief  Get the touch detailed informations on touch number 'touchIdx' (0..1)
  *         This touch detailed information contains :
  *         - weight that was applied to this touch
  *         - sub-area of the touch in the touch panel
  *         - event of linked to the touch (press down, lift up, ...)
  * @param  DeviceAddr: Device address on communication Bus (I2C slave address of FT5336).
  * @param  touchIdx : Passed index of the touch (0..1) on which we want to get the
  *                    detailed information.
  * @param  pWeight : Pointer to to get the weight information of 'touchIdx'.
  * @param  pArea   : Pointer to to get the sub-area information of 'touchIdx'.
  * @param  pEvent  : Pointer to to get the event information of 'touchIdx'.

  * @retval None.
  */
void FT5336_Driver::GetTouchInfo(
	uint32_t   touchIdx,
	uint32_t * pWeight,
	uint32_t * pArea,
	uint32_t * pEvent) {

	volatile uint8_t ucReadData = 0;
	uint8_t regAddressXHigh = 0;
	uint8_t regAddressPWeight = 0;
	uint8_t regAddressPMisc = 0;

	if (touchIdx < currActiveTouchNb) {
		switch (touchIdx) {
			case 0 :
				regAddressXHigh   = FT5336_P1_XH_REG;
				regAddressPWeight = FT5336_P1_WEIGHT_REG;
				regAddressPMisc   = FT5336_P1_MISC_REG;
				break;

			case 1 :
				regAddressXHigh   = FT5336_P2_XH_REG;
				regAddressPWeight = FT5336_P2_WEIGHT_REG;
				regAddressPMisc   = FT5336_P2_MISC_REG;
				break;

			case 2 :
				regAddressXHigh   = FT5336_P3_XH_REG;
				regAddressPWeight = FT5336_P3_WEIGHT_REG;
				regAddressPMisc   = FT5336_P3_MISC_REG;
				break;

			case 3 :
				regAddressXHigh   = FT5336_P4_XH_REG;
				regAddressPWeight = FT5336_P4_WEIGHT_REG;
				regAddressPMisc   = FT5336_P4_MISC_REG;
				break;

			case 4 :
				regAddressXHigh   = FT5336_P5_XH_REG;
				regAddressPWeight = FT5336_P5_WEIGHT_REG;
				regAddressPMisc   = FT5336_P5_MISC_REG;
				break;

			case 5 :
				regAddressXHigh   = FT5336_P6_XH_REG;
				regAddressPWeight = FT5336_P6_WEIGHT_REG;
				regAddressPMisc   = FT5336_P6_MISC_REG;
				break;

			case 6 :
				regAddressXHigh   = FT5336_P7_XH_REG;
				regAddressPWeight = FT5336_P7_WEIGHT_REG;
			  	regAddressPMisc   = FT5336_P7_MISC_REG;
			  break;

			case 7 :
				regAddressXHigh   = FT5336_P8_XH_REG;
				regAddressPWeight = FT5336_P8_WEIGHT_REG;
				regAddressPMisc   = FT5336_P8_MISC_REG;
				break;

			case 8 :
				regAddressXHigh   = FT5336_P9_XH_REG;
				regAddressPWeight = FT5336_P9_WEIGHT_REG;
				regAddressPMisc   = FT5336_P9_MISC_REG;
				break;

			case 9 :
				regAddressXHigh   = FT5336_P10_XH_REG;
				regAddressPWeight = FT5336_P10_WEIGHT_REG;
				regAddressPMisc   = FT5336_P10_MISC_REG;
				break;

			default :
				break;

		}

		/* Read Event Id of touch index */
		ucReadData = ioRead(regAddressXHigh);
		* pEvent = (ucReadData & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT;

		/* Read weight of touch index */
		ucReadData = ioRead(regAddressPWeight);
		* pWeight = (ucReadData & FT5336_TOUCH_WEIGHT_MASK) >> FT5336_TOUCH_WEIGHT_SHIFT;

		/* Read area of touch index */
		ucReadData = ioRead(regAddressPMisc);
		* pArea = (ucReadData & FT5336_TOUCH_AREA_MASK) >> FT5336_TOUCH_AREA_SHIFT;
	}
}
#endif


/// ----------------------------------------------------------------------
/// \brief Inicialitza la comunicacio amb el driver.
///
void FT5336_Driver::ioInit() {

	static const GPIOInitializePinInfo gpioInfo[2] = {
		{FT5336_SCL_PORT, FT5336_SCL_PIN, HAL_GPIO_MODE_ALT_OD | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_NONE, FT5336_SCL_AF},
		{FT5336_SDA_PORT, FT5336_SDA_PIN, HAL_GPIO_MODE_ALT_OD | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_NONE, FT5336_SCL_AF}
	};

	halGPIOInitializePins(gpioInfo, sizeof(gpioInfo) / sizeof(gpioInfo[0]));

	I2CInitializeInfo i2cInfo;
	i2cInfo.id = FT5336_I2C_MODULE;
	halI2CInitialize(&i2cInfo);
}


/// ----------------------------------------------------------------------
/// \brief Esciu en un registre del driver.
/// \param addr: Adressa I2C.
/// \param reg: Numero de registre.
/// \param value: El valor a escriure.
///
void FT5336_Driver::ioWrite(
	uint8_t reg,
	uint8_t value) {

	halI2CWriteMultiple(FT5336_I2C_MODULE, addr, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT,(uint8_t*)&value, 1);
}


/// ----------------------------------------------------------------------
/// \brief llegeix un valor d'un registre del driver.
/// \param addr: L'adressa I2C.
/// \param reg: Numero del registre.
/// \return El valor del registre.
///
uint8_t FT5336_Driver::ioRead(
	uint8_t reg) {

	uint8_t value = 0;

	halI2CReadMultiple(FT5336_I2C_MODULE, addr, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&value, 1);

	return value;
}
