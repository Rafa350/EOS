#include "HTL/PIC32/htlUART.h"


using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Inicialitz<a el modul UART.
/// \param    regs: EL bloc de registres.
///
void htl::UART_initialize(
    UARTRegisters *regs) {

    regs->UxMODE.IREN = 0;
    regs->UxMODE.PDSEL = 0;
    regs->UxMODE.STSEL = 0;
}


void htl::UART_deinitialize(
    UARTRegisters *regs) {

    regs->UxMODE.ON = 0;
}



void htl::UART_setTimming(
    UARTRegisters *regs,
    UARTBaudMode baudMode) {

    uint32_t baud;
    uint32_t clockFrequency = CLOCK_PERIPHERICAL_HZ;

    switch (baudMode) {
        default:
        case UARTBaudMode::_9600:
            baud = 9600;
            break;
    }


    regs->UxBRG = (((clockFrequency >> 4) + (baud >> 1)) / baud) - 1;
}


/// ----------------------------------------------------------------------
/// \brief    Configura el protocol de comunicacio.
/// \param    regs: El bloc de registres.
/// \param    wordBits: Nom,bre de bits de dades.
/// \param    parity: La paritat.
/// \param    stopBits: Nombre de bits de stol.
/// \param    handsake: El protocol.
///
void htl::UART_setProtocol(
    UARTRegisters *regs,
    UARTWordBits wordBits,
    UARTParity parity,
    UARTStopBits stopBits,
    UARTHandsake handsake) {

    // Selecciona la paritat i bits de dades
    //
    switch (parity) {
        case UARTParity::none:
            switch (wordBits) {
                case UARTWordBits::_8:
                    regs->UxMODE.PDSEL = 0b00;
                    break;

                case UARTWordBits::_9:
                    regs->UxMODE.PDSEL = 0b11;
                    break;
            }
            break;

        case UARTParity::even:
            regs->UxMODE.PDSEL = 0b01;
            break;

        case UARTParity::odd:
            regs->UxMODE.PDSEL = 0b10;
            break;
    }

    // Selecciona els bits de stop
    //
    switch (stopBits) {
        case UARTStopBits::_1:
            regs->UxMODE.STSEL = 0;
            break;

        case UARTStopBits::_2:
            regs->UxMODE.STSEL = 1;
            break;
    }

    // Selecciona el protocol
    //
    switch (handsake) {
        case UARTHandsake::none:
            break;

        case UARTHandsake::ctsrts:
            break;
    }
}