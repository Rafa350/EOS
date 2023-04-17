#include "HTL/htlGPIO.h"


using namespace htl::gpio;


static void initOutput(internal::GPIORegisters*, PinMask, OutDriver, Speed);


Port::Port(
    internal::GPIORegisters *gpio) :

    _gpio(gpio) {

}


void Port::activate() {

}


void Port::deactivate() {


}


void Port::reset() {

}


void Port::initOutput(
    PinMask mask,
    OutDriver driver,
    Speed speed) {

    initOutput(_gpio, mask, driver, speed);
}


Pin::Pin(
    internal::GPIORegisters *gpio,
    PinID pinID) :

    _gpio(gpio),
    _pinMask(1 << (int)pinID) {

}


void Pin::initOutput(
    OutDriver driver,
    Speed speed,
    InitPinState state) {

    write(state);
    initOutput(_gpio, _pinMask, driver, speed);
}



void initOutput(
    internal::GPIORegisters *gpio,
    PinMask mask,
    OutDriver driver,
    Speed speed) {

    gpio->TRISxCLR = mask;

    switch (driver) {
        case OutDriver::openDrain:
            gpio->ODCxSET = mask;
            break;

        case OutDriver::pushPull:
            gpio->ODCxCLR = mask;
            break;

        default:
            break;
    }
}
