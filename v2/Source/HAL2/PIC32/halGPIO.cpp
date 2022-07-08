#include "HAL2/hal.h"
#include "HAL2/PIC32/halGPIO.H"


using namespace hal;


typedef struct __attribute__((packed , aligned(4))) {
    volatile uint32_t TRISx;
    volatile uint32_t TRISxCLR;
    volatile uint32_t TRISxSET;
    volatile uint32_t TRISxINV;
    volatile uint32_t PORTx;
    volatile uint32_t PORTxCLR;
    volatile uint32_t PORTxSET;
    volatile uint32_t PORTxINV;
    volatile uint32_t LATx;
    volatile uint32_t LATxCLR;
    volatile uint32_t LATxSET;
    volatile uint32_t LATxINV;
    volatile uint32_t ODCx;
    volatile uint32_t ODCxCLR;
    volatile uint32_t ODCxSET;
    volatile uint32_t ODCxINV;
} GPIO_Registers;


/// ----------------------------------------------------------------------
/// \brief     Constructor.
/// \param     port: Identificador del port.
/// \param     pin: Identificador del pin.
//
GPIO::GPIO(
    GPIOPort port,
    GPIOPin pin) {

    _addr = _PORTA_BASE_ADDRESS - 0x10 + (static_cast<unsigned>(port) * 0x40);
    _mask = 1 << static_cast<unsigned>(pin);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    gpio: El objecte a copiar.
///
GPIO::GPIO(
    const GPIO &gpio) :

    _addr(gpio._addr),
    _mask(gpio._mask) {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com entrada.
/// \param    mode: Modus de treball del pin.
///
void GPIO::setMode(
    InpMode mode) {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    regs->TRISxSET = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el pin com sortida.
/// \param    mode: Modus de treball del pin.
///
void GPIO::setMode(
    OutMode mode) {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    regs->TRISxCLR = _mask;
    if (mode == OutMode::output_OD)
        regs->ODCxSET = _mask;
    else
        regs->ODCxCLR = _mask;
}


void GPIO::setSpeed(
    Speed speed) {

}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat SET al pin.
///
void GPIO::set() const {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    regs->PORTxSET = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el estat CLEAR al pin.
///
void GPIO::clear() const {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    regs->PORTxCLR = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix l'estat del pin.
///
void GPIO::toggle() const {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);
    regs->PORTxINV = _mask;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu l'estat del pin.
/// \param    s: eL ESTAT.
///
void GPIO::write(
    bool s) const {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    if (s)
        regs->PORTxSET = _mask;
    else
        regs->PORTxCLR = _mask;
}


/// ----------------------------------------------------------------------
/// \Brief    Llegeix l'estat del pin.
/// \return   L'estat del pin.
///
bool GPIO::read() const {

    GPIO_Registers *regs = reinterpret_cast<GPIO_Registers*>(_addr);

    return (regs->PORTx & _mask) != 0;
}


/// ----------------------------------------------------------------------
/// \brief    Operador =
/// \param    gpio: El objecte a asignar.
///
GPIO & GPIO::operator = (
    const GPIO &gpio) {

    _addr = gpio._addr;
    _mask = gpio._mask;

    return *this;
}
