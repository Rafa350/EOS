#include "HTL/PIC32/htlUART.h"


using namespace htl;


void htl::UART_initialize(
    UARTRegisters *regs) {

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


void htl::UART_deinitialize(
    UARTRegisters *regs) {

    regs->UxMODE.ON = 0;
}


void htl::UART_setProtocol(
    UARTRegisters *regs,
    UARTWordBits wordBits,
    UARTParity parity,
    UARTStopBits stopBits) {


}