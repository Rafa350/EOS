#include "eos.h"

#ifdef USE_TOUCHPAD


#include "Controllers/TouchPad/Drivers/eosTouchPadDriver_FT5336.h"
#include "HTL/htlTMR.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlI2C.h"
#include "HTL/htlINT.h"
#include "HTL/STM32/htlINT.h"

#include <cmath>


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
///
TouchPadDriver_FT5336::TouchPadDriver_FT5336():
	_orientation {TouchPadOrientation::normal},
	_intNotifyEvent {*this, &TouchPadDriver_FT5336::intNotifyEventHandler},
	_touchPadEvent {nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el driver.
///
void TouchPadDriver_FT5336::initialize() {

	// Wait at least 200ms after power up before accessing registers
	// Trsi timing (Time of starting to report point after resetting) from FT5336GQQ datasheet
	//
	//halTMRDelay(200);
    initializeInterface();

   	enableInt();
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza el driver.
///
void TouchPadDriver_FT5336::deinitialize() {

	disableInt();
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona l'oeirntacio del touch pad
/// \param    orientation: La orientacio a seleccionar.
///
void TouchPadDriver_FT5336::setOrientation(
	TouchPadOrientation orientation) {

	_orientation = orientation;
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
/// \brief    Handler del event RisingEdgeEvent
///
void TouchPadDriver_FT5336::intNotifyEventHandler(
	htl::gpio::PinInterrupt *sender,
	htl::gpio::NotifyEventArgs &args) {

	if (args.id == htl::gpio::NotifyID::risingEdge) {
		if (_touchPadEvent != nullptr)
			_touchPadEvent->execute(this);
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat del touchpad.
/// \param    state: Buffer on deixar el resultat.
/// \return   True si s'ha detectat contacte.
///
bool TouchPadDriver_FT5336::getState(
	TouchPadState &state) {

	state.maxPoints = FT5336_MAX_DETECTABLE_TOUCH;
	state.numPoints = readRegister(FT5336_TD_STAT_REG) & FT5336_TD_STAT_MASK;
	if (state.numPoints > state.maxPoints)
		state.numPoints = 0;

	uint8_t cMax = std::min((uint8_t) TOUCHPAD_MAX_POINTS, state.numPoints);
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
				state.x[c] = _width - tempX;
				state.y[c] = _height - tempY;
				break;

			case TouchPadOrientation::rotate270:
				state.x[c] = _height - tempY;
				state.y[c] = _width - tempX;
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
	PinINT::pInst->initInput(gpio::InputMode::pullUp);

	auto pinINT = PinInterruptINT::pInst;
	pinINT->enableInterruptPin(htl::gpio::Edge::rising);
	pinINT->setNotifyEvent(_intNotifyEvent);

	irq::setInterruptVectorPriority(_vector, _priority, _subPriority);
	irq::enableInterruptVector(_vector);

	// Inicialitza el canal I2C
	//
	DevI2C::pInst->initialize(0x0B, 0x04, 0x02, 0x0F, 0x13);
	DevI2C::pInst->initPinSCL<PinSCL>();
	DevI2C::pInst->initPinSDA<PinSDA>();
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

	DevI2C::pInst->send(_i2cAddr, data, sizeof(data));
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

	DevI2C::pInst->send(_i2cAddr, &reg, 1);
	DevI2C::pInst->receive(_i2cAddr, &value, sizeof(value));

	return value;
}


#endif // USE_TOUCHPAD

