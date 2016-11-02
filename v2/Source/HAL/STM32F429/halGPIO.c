#include "hal/halGPIO.h"


/// ----------------------------------------------------------------------
/// \brief Configura un pin.
/// \param port: Identificador del port.
/// \param pin: Identificador del pin.
/// \param direction: Direccio.
///
void halGPIOInitializePin(
    GPIOPort port,
    GPIOPin pin,
    GPIODirection direction) {
   
    if (direction == GPIO_DIRECTION_OUTPUT)
        PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, port, pin);
    else if (direction == GPIO_DIRECTION_INPUT)
        PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, port, pin);
}


/// ----------------------------------------------------------------------
/// \brief Configura un port.
/// \param port: El handler del port.
/// \param direction: Direccio.
/// \param mask: Mascara.
///
void halGPIOInitializePort(
    GPIOPort port,
    GPIODirection direction,
    uint16_t mask) {

    if (direction == GPIO_DIRECTION_OUTPUT)
        PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, port, mask);
    else if (direction == GPIO_DIRECTION_INPUT)
        PLIB_PORTS_DirectionInputSet(PORTS_ID_0, port, mask);
}
