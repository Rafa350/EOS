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
	orientation(TouchPadOrientation::normal) {

	// Wait at least 200ms after power up before accessing registers
	// Trsi timing (Time of starting to report point after resetting) from FT5336GQQ datasheet
	//
	//halTMRDelay(200);
    ioInit();
}


/// ----------------------------------------------------------------------
/// \brief selecciona l'oeirntacio del touch pad
/// \param orientation: La orientacio a seleccionar.
///
void FT5336_Driver::setOrientation(
	TouchPadOrientation orientation) {

	this->orientation = orientation;

	switch (orientation) {
		case TouchPadOrientation::normal:
		case TouchPadOrientation::rotate180:
			padWidth = FT5336_PAD_WIDTH;
			padHeight = FT5336_PAD_HEIGHT;
			break;

		case TouchPadOrientation::rotate90:
		case TouchPadOrientation::rotate270:
			padWidth = FT5336_PAD_HEIGHT;
			padHeight = FT5336_PAD_WIDTH;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief Obte l'estat del touchpad.
/// \param state: Buffer on deixar el resultat.
/// \return True si s'ha detectat contacte.
///
bool FT5336_Driver::getState(
	TouchPadState &state) {

	state.maxPoints = FT5336_MAX_DETECTABLE_TOUCH;
	state.numPoints = ioRead(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
	if (state.numPoints > state.maxPoints)
		state.numPoints = 0;

	for (uint8_t c = 0; c < state.numPoints; c++) {

		volatile uint8_t ucReadData = 0;
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
		ucReadData = ioRead(regAddressXLow);
		tempX = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio X [11:8] i estat [15:12]
		ucReadData = ioRead(regAddressXHigh);
		state.action[c] = (TouchPadAction) ((ucReadData & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT);
		tempX |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Posicio Y [7:0]
		ucReadData = ioRead(regAddressYLow);
		tempY = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio Y[11:8]
		ucReadData = ioRead(regAddressYHigh);
		tempY |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		switch (orientation) {
			case TouchPadOrientation::normal:
				state.x[c] = tempY;
				state.y[c] = tempX;
				break;

			case TouchPadOrientation::rotate90:
				state.x[c] = tempX;
				state.y[c] = tempY;
				break;

			case TouchPadOrientation::rotate180:
				state.x[c] = FT5336_PAD_HEIGHT - tempY;
				state.y[c] = FT5336_PAD_WIDTH - tempX;
				break;

			case TouchPadOrientation::rotate270:
				state.x[c] = tempX;
				state.y[c] = tempY;
				break;
		}
	}

	return state.numPoints != 0;
}


/// ----------------------------------------------------------------------
/// \brief Activa la generacio d'interrupcions pel pin INT
///
void FT5336_Driver::enableInt() {

}


/// ----------------------------------------------------------------------
/// \brief Desactiva la generacio d'interrupcions pel pin INT
///
void FT5336_Driver::disableInt() {

}


/// ----------------------------------------------------------------------
/// \brief Borra la intrrupcio generada
///
void FT5336_Driver::clearInt() {

}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la comunicacio amb el driver.
///
void FT5336_Driver::ioInit() {

	static const GPIOInitializePinInfo gpioInfo[] = {
#ifdef FT5336_INT_PORT
		{FT5336_INT_PORT, FT5336_INT_PIN, HAL_GPIO_MODE_IT_POS | HAL_GPIO_SPEED_FAST | HAL_GPIO_PULL_NONE, 0},
#endif
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

