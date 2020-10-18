#include "eos.h"
#if defined(USE_TOUCHPAD) && defined(TOUCHPAD_DRV_FT5336)

#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "HAL/halTMR.h"
#include "hal/halI2C.h"
#include "hal/halGPIO.h"
#ifdef TOUCHPAD_INT_PORT
#include "HAL/STM32/halEXTI.h"
#include "HAL/STM32/halINT.h"
#endif
#include "System/eosMath.h"


using namespace eos;


ITouchPadDriver *FT5336Driver::instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief Obte una instancia unica del driver.
/// \return La instancia del driver.
///
ITouchPadDriver *FT5336Driver::getInstance() {

	if (instance == nullptr)
		instance = new FT5336Driver();
	return instance;
}


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
FT5336Driver::FT5336Driver():

	addr(TOUCHPAD_I2C_ADDR),
	padWidth(TOUCHPAD_PAD_WIDTH),
	padHeight(TOUCHPAD_PAD_HEIGHT),
	orientation(TouchPadOrientation::normal) {
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el driver.
///
void FT5336Driver::initialize() {

	// Wait at least 200ms after power up before accessing registers
	// Trsi timing (Time of starting to report point after resetting) from FT5336GQQ datasheet
	//
	halTMRDelay(200);
    ioInit();

#ifdef TOUCHPAD_INT_PORT
    enableInt();
#endif
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el driver.
///
void FT5336Driver::shutdown() {

#ifdef TOUCHPAD_INT_PORT
	disableInt();
#endif
}


/// ----------------------------------------------------------------------
/// \brief selecciona l'oeirntacio del touch pad
/// \param orientation: La orientacio a seleccionar.
///
void FT5336Driver::setOrientation(
	TouchPadOrientation orientation) {

	this->orientation = orientation;

	switch (orientation) {
		case TouchPadOrientation::normal:
		case TouchPadOrientation::rotate180:
			padWidth = TOUCHPAD_PAD_WIDTH;
			padHeight = TOUCHPAD_PAD_HEIGHT;
			break;

		case TouchPadOrientation::rotate90:
		case TouchPadOrientation::rotate270:
			padWidth = TOUCHPAD_PAD_HEIGHT;
			padHeight = TOUCHPAD_PAD_WIDTH;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Comprova si hi ha accio.
/// \return True si hi ha accio en el touchpad.
///
int FT5336Driver::getTouchCount() {

	int8_t numPoints = ioRead(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
    if (numPoints > FT5336_MAX_DETECTABLE_TOUCH)
    	numPoints = 0;
    return numPoints;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat del touchpad.
/// \param state: Buffer on deixar el resultat.
/// \return True si s'ha detectat contacte.
///
bool FT5336Driver::getState(
	TouchPadState &state) {

	state.maxPoints = FT5336_MAX_DETECTABLE_TOUCH;
	state.numPoints = ioRead(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
	if (state.numPoints > state.maxPoints)
		state.numPoints = 0;

	uint8_t cMax = Math::min((uint8_t) TOUCHPAD_MAX_POINTS, state.numPoints);
	for (uint8_t c = 0; c < cMax; c++) {

		volatile uint8_t readData = 0;
		uint8_t regAddressXLow = 0;
		uint8_t regAddressXHigh = 0;
		uint8_t regAddressYLow = 0;
		uint8_t regAddressYHigh = 0;
		int16_t tempX;
		int16_t tempY;

		switch(c) {
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

		// Posicio X [7:0]
		//
		readData = ioRead(regAddressXLow);
		tempX = (readData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio X [11:8] i estat [15:12]
		//
		readData = ioRead(regAddressXHigh);
		state.action[c] = (TouchPadAction) ((readData & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT);
		tempX |= ((readData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Posicio YLow [7:0]
		//
		readData = ioRead(regAddressYLow);
		tempY = (readData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio YHigh [11:8]
		//
		readData = ioRead(regAddressYHigh);
		tempY |= ((readData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Ajusta les coordinades a la orientacio
		//
		switch (orientation) {
			case TouchPadOrientation::normal:
				state.x[c] = tempX;
				state.y[c] = tempY;
				break;

			case TouchPadOrientation::rotate90:
				state.x[c] = tempY;
				state.y[c] = tempX;
				break;

			case TouchPadOrientation::rotate180:
				state.x[c] = padWidth - tempX;
				state.y[c] = padHeight - tempY;
				break;

			case TouchPadOrientation::rotate270:
				state.x[c] = padWidth - tempY;
				state.y[c] = padHeight - tempX;
				break;
		}
	}

	return state.numPoints != 0;
}


/// ----------------------------------------------------------------------
/// \brief Activa la generacio d'interrupcions pel pin INT
///
void FT5336Driver::enableInt() {

   uint8_t regValue = 0;
   regValue = (FT5336_G_MODE_INTERRUPT_TRIGGER & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

   // Set interrupt trigger mode in FT5336_GMODE_REG
   //
   ioWrite(FT5336_GMODE_REG, regValue);
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la generacio d'interrupcions pel pin INT
///
void FT5336Driver::disableInt() {

	uint8_t regValue = 0;
	regValue = (FT5336_G_MODE_INTERRUPT_POLLING & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

	// Set interrupt polling mode in FT5336_GMODE_REG
	//
	ioWrite(FT5336_GMODE_REG, regValue);
}


/// ----------------------------------------------------------------------
/// \brief Borra la interrupcio generada
///
void FT5336Driver::clearInt() {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la comunicacio amb el driver.
///
void FT5336Driver::ioInit() {

	static GPIOInitializePinInfo const gpioInfo[] = {
#ifdef TOUCHPAD_INT_PORT
		{TOUCHPAD_INT_PORT, TOUCHPAD_INT_PIN, HAL_GPIO_MODE_INPUT | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_UP, 0},
#endif
		{TOUCHPAD_SCL_PORT, TOUCHPAD_SCL_PIN, HAL_GPIO_MODE_ALT_OD | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_UP, TOUCHPAD_SCL_AF},
		{TOUCHPAD_SDA_PORT, TOUCHPAD_SDA_PIN, HAL_GPIO_MODE_ALT_OD | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_UP, TOUCHPAD_SCL_AF}
	};

#ifdef TOUCHPAD_INT_PORT
	static EXTIInitializePinInfo const extiInfo[] = {
		{TOUCHPAD_INT_EXTI_LINE, HAL_EXTI_MODE_INT | HAL_EXTI_TRIGGER_RISING | TOUCHPAD_INT_EXTI_PORT, nullptr, nullptr}
	};
#endif

	halGPIOInitializePins(gpioInfo, sizeof(gpioInfo) / sizeof(gpioInfo[0]));

#ifdef TOUCHPAD_INT_PORT
	halEXTIInitializePins(extiInfo, sizeof(extiInfo) / sizeof(extiInfo[0]));
	halINTSetInterruptVectorPriority(TOUCHPAD_INT_IRQ, TOUCHPAD_INT_PRIORITY, TOUCHPAD_INT_SUBPRIORITY);
	halINTEnableInterruptVector(TOUCHPAD_INT_IRQ);
#endif

	I2CMasterInitializeInfo i2cInfo;
	i2cInfo.channel = TOUCHPAD_I2C_CHANNEL;
	hI2C = halI2CMasterInitialize(&i2cData, &i2cInfo);
}


/// ----------------------------------------------------------------------
/// \brief Esciu en un registre del driver.
/// \param addr: Adressa I2C.
/// \param reg: Numero de registre.
/// \param value: El valor a escriure.
///
void FT5336Driver::ioWrite(
	uint8_t reg,
	uint8_t value) {

	uint8_t buffer[1];

	buffer[0] = value;
	halI2CMasterWriteMultiple(hI2C, addr, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer));
}


/// ----------------------------------------------------------------------
/// \brief llegeix un valor d'un registre del driver.
/// \param addr: L'adressa I2C.
/// \param reg: Numero del registre.
/// \return El valor del registre.
///
uint8_t FT5336Driver::ioRead(
	uint8_t reg) {

	uint8_t buffer[1];

	halI2CMasterReadMultiple(hI2C, addr, reg, I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer));

	return buffer[0];
}


#endif // defined(USE_TOUCHPAD) && defined(TOUCHPAD_DRV_FT5336)

