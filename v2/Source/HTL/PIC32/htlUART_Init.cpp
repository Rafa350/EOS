#include "eos.h"
#include "HTL/PIC32/htlUART.h"


using namespace htl;


void htl::UART_init(
    UARTRegisters *regs,
    UARTBaud baud,
    UARTWord word,
    UARTParity parity,
    UARTStop stop,
    UARTMode mode) {

    // Selecciona la velocitat
    //
    regs->UxBRG = (((clockFrequency >> 4) + (baud >> 1)) / baud) - 1;

    // Selecciona la paritat
    //
    regs->UxMODE.PDSEL = 0;

    // Selecciona els bits de stop
    //
    regs->UxMODE.STSEL = 0;

    // Activa la comunicacio
    //
    regs->UxMODE.ON = 1;
}


void htl::UART_deInit(
    UARTRegisters *regs) {

    regs->UxMODE.ON = 0;
}
