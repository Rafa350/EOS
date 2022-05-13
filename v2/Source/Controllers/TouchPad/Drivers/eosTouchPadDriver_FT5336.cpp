#include "eos.h"
#if defined(USE_TOUCHPAD) && defined(TOUCHPAD_DRV_FT5336)

#include "Controllers/TouchPad/Drivers/eosTouchPadDriver_FT5336.h"
#include "HAL/halTMR.h"
#include "hal/halGPIO.h"
#ifdef TOUCHPAD_INT_PORT
#include "HAL/STM32/halEXTI.h"
#include "HAL/STM32/halEXTITpl.h"
#include "HAL/STM32/halINTTpl.h"
#endif
#include "System/eosMath.h"


using namespace eos;


ITouchPadDriver *TouchPadDriver_FT5336::_instance = nullptr;


/// ----------------------------------------------------------------------
/// \brief    Obte una instancia unica del driver.
/// \return   La instancia del driver.
///
ITouchPadDriver* TouchPadDriver_FT5336::getInstance() {

	if (_instance == nullptr)
		_instance = new TouchPadDriver_FT5336();
	return _instance;
}


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
TouchPadDriver_FT5336::TouchPadDriver_FT5336():
	_addr(TOUCHPAD_I2C_ADDR),
	_padWidth(TOUCHPAD_PAD_WIDTH),
	_padHeight(TOUCHPAD_PAD_HEIGHT),
	_orientation(TouchPadOrientation::normal) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void TouchPadDriver_FT5336::initialize() {

	// Wait at least 200ms after power up before accessing registers
	// Trsi timing (Time of starting to report point after resetting) from FT5336GQQ datasheet
	//
	halTMRDelay(200);
    initializeInterface();

#ifdef TOUCHPAD_INT_PORT
    enableInt();
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el driver.
///
void TouchPadDriver_FT5336::shutdown() {

#ifdef TOUCHPAD_INT_PORT
	disableInt();
#endif
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'oeirntacio del touch pad
/// \param    orientation: La orientacio a seleccionar.
///
void TouchPadDriver_FT5336::setOrientation(
	TouchPadOrientation orientation) {

	_orientation = orientation;

	switch (orientation) {
		case TouchPadOrientation::normal:
		case TouchPadOrientation::rotate180:
			_padWidth = TOUCHPAD_PAD_WIDTH;
			_padHeight = TOUCHPAD_PAD_HEIGHT;
			break;

		case TouchPadOrientation::rotate90:
		case TouchPadOrientation::rotate270:
			_padWidth = TOUCHPAD_PAD_HEIGHT;
			_padHeight = TOUCHPAD_PAD_WIDTH;
			break;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Comprova si hi ha accio.
/// \return   True si hi ha accio en el touchpad.
///
int TouchPadDriver_FT5336::getTouchCount() {

	uint8_t numPoints = readRegister(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
    if (numPoints > FT5336_MAX_DETECTABLE_TOUCH)
    	numPoints = 0;
    return numPoints;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del touchpad.
/// \param    state: Buffer on deixar el resultat.
/// \return   True si s'ha detectat contacte.
///
bool TouchPadDriver_FT5336::getState(
	TouchPadState& state) {

	state.maxPoints = FT5336_MAX_DETECTABLE_TOUCH;
	state.numPoints = readRegister(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
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
		readData = readRegister(regAddressXLow);
		tempX = (readData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio X [11:8] i estat [15:12]
		//
		readData = readRegister(regAddressXHigh);
		state.action[c] = (TouchPadAction) ((readData & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT);
		tempX |= ((readData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Posicio YLow [7:0]
		//
		readData = readRegister(regAddressYLow);
		tempY = (readData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

		// Posicio YHigh [11:8]
		//
		readData = readRegister(regAddressYHigh);
		tempY |= ((readData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

		// Ajusta les coordinades a la orientacio
		//
		switch (_orientation) {
			case TouchPadOrientation::normal:
				state.x[c] = tempX;
				state.y[c] = tempY;
				break;

			case TouchPadOrientation::rotate90:
				state.x[c] = tempY;
				state.y[c] = tempX;
				break;

			case TouchPadOrientation::rotate180:
				state.x[c] = _padWidth - tempX;
				state.y[c] = _padHeight - tempY;
				break;

			case TouchPadOrientation::rotate270:
				state.x[c] = _padWidth - tempY;
				state.y[c] = _padHeight - tempX;
				break;
		}
	}

	return state.numPoints != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Activa la generacio d'interrupcions pel pin INT
///
void TouchPadDriver_FT5336::enableInt() {

   uint8_t value = (FT5336_G_MODE_INTERRUPT_TRIGGER & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

   // Set interrupt trigger mode in FT5336_GMODE_REG
   //
   writeRegister(FT5336_GMODE_REG, value);
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva la generacio d'interrupcions pel pin INT
///
void TouchPadDriver_FT5336::disableInt() {

	uint8_t value = (FT5336_G_MODE_INTERRUPT_POLLING & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT)) << FT5336_G_MODE_INTERRUPT_SHIFT;

	// Set interrupt polling mode in FT5336_GMODE_REG
	//
	writeRegister(FT5336_GMODE_REG, value);
}


/// ----------------------------------------------------------------------
/// \brief    Borra la interrupcio generada
///
void TouchPadDriver_FT5336::clearInt() {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la comunicacio amb el driver.
///
void TouchPadDriver_FT5336::initializeInterface() {

	// Inicialitza el pin d'interrupcio
	//
#ifdef TOUCHPAD_INT_PORT
	PinINT::initInput(GPIOSpeed::fast, GPIOPull::up);

	ExtiINT::init(EXTIPort(TOUCHPAD_INT_EXTI_PORT), EXTIMode::interrupt, EXTITrigger::rissing);

	INT::setInterruptVectorPriority(INTVector(TOUCHPAD_INT_IRQ), INTPriority(TOUCHPAD_INT_PRIORITY), INTSubPriority(TOUCHPAD_INT_SUBPRIORITY));
	INT::enableInterruptVector(INTVector(TOUCHPAD_INT_IRQ));
#endif

	// Inicialitza el canal I2C
	//
	_i2c.initSCLPin<PinSCL>();
	_i2c.initSDAPin<PinSDA>();
	_i2c.initMaster();
}


/// ----------------------------------------------------------------------
/// \brief    Esciu en un registre del driver.
/// \param    addr: Adressa I2C.
/// \param    reg: Numero de registre.
/// \param    value: El valor a escriure.
///
void TouchPadDriver_FT5336::writeRegister(
	uint8_t reg,
	uint8_t value) {

	uint8_t data[2];
	data[0] = reg;
	data[1] = value;

	_i2c.send(_addr, data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor d'un registre del driver.
/// \param    addr: L'adressa I2C.
/// \param    reg: Numero del registre.
/// \return   El valor del registre.
///
uint8_t TouchPadDriver_FT5336::readRegister(
	uint8_t reg) {

	uint8_t value;

	_i2c.send(_addr, &reg, 1);
	_i2c.receive(_addr, &value, sizeof(value));

	return value;
}


#endif // defined(USE_TOUCHPAD) && defined(TOUCHPAD_DRV_FT5336)

