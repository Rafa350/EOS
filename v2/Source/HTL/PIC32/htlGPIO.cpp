#include "HTL/htlGPIO.h"


using namespace htlV2;


static void initOutput(GPIORegisters*, GPIOPinMask, GPIODriver, GPIOSpeed);


GPIOPort::GPIOPort(
    GPIORegisters *registers) :
    
    _registers(registers) {
    
}


void GPIOPort::activate() {
    
}


void GPIOPort::deactivate() {
    

}


void GPIOPort::reset() {
    
}


void GPIOPort::initOutput(
    GPIOPinMask mask, 
    GPIODriver driver, 
    GPIOSpeed speed) {
            
    initOutput(_registers, mask, driver, speed);
}


GPIOPin::GPIOPin(
    GPIORegisters *registers, 
    GPIOPinID pinID) :
    
    _registers(registers),
    _pinMask(1 << (int)pinID) {
    
}
    

void GPIOPin::initOutput(
    GPIODriver driver,
    GPIOSpeed speed,
    GPIOInitPinState state) {

    write(state);
    initOutput(_registers, _pinMask, driver, speed);
}



void initOutput(
    GPIORegisters *registers, 
    GPIOPinMask mask,
    GPIODriver driver,
    GPIOSpeed speed) {
    
    registers->TRISxCLR = mask;

    switch (driver) {
        case GPIODriver::openDrain:
            registers->ODCxSET = mask;
            break;
            
        case GPIODriver::pushPull:
            registers->ODCxCLR = mask;
            break;
            
        default:
            break;
    }
}
