module Eos.Controllers.Display.Drivers.ILI9341;

import Eos.System.Core.Task;
import Eos.System.Core.Ticks;


using namespace eos;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    pinCS: El pin CS.
/// @param    pinRS: El pin RS.
/// @param     pinRST: eE pin RST.
/// @param    devSPI: El dispositiu SPI
///
Device_ILI9341_SPI::Device_ILI9341_SPI(
    PinDevice *pinCS,
    PinDevice *pinRS,
    PinDevice *pinRST,
    SPIDevice *devSPI):

    Device_ILI9341(),

    _pinCS {pinCS},
    _pinRS {pinRS},
    _pinRST {pinRST},
    _devSPI {devSPI} {

}


/// ---------------------------------------------------------------------------
/// @brief    Inicialitzacio.
/// @param    script: Script d'inicialitzacio.
/// @param    scriptSize: Tamany del script en bytes.
///
void Device_ILI9341_SPI::initialize(
    const UInt8 *script,
    UInt32 scriptSize) {

    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        Task::delay(Ticks::fromMiliseconds(20));
        _pinRST->set();
        Task::delay(Ticks::fromMiliseconds(120));
        _pinRST->set();
    }

    writeScript(script, scriptSize);
}


/// ---------------------------------------------------------------------------
/// @brief    Desinicialitzacio.
///
void Device_ILI9341_SPI::deinitialize() {

    _pinCS->set();
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un byte en el registrte de control.
/// @param    cmd: El byte a escriure.
///
void Device_ILI9341_SPI::writeCommand(
    UInt8 data) {

    _pinCS->clear();
    _pinRS->clear();
    _devSPI->transmit(&data, 1, Ticks::fromMiliseconds(1000));
    _pinCS->set();
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu un byte en el registrte de dades.
/// @param    data: El byte a escriure.
///
void Device_ILI9341_SPI::writeData(
    UInt8 data) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(&data, 1, Ticks::fromMiliseconds(1000));
    _pinCS->set();
}


/// ---------------------------------------------------------------------------
/// @brief    Escriu una llista de bytes en el registrte de dades.
/// @param    data: La llista de bytes.
/// @param    dataSize: El tamany de la llista en bytes
///
void Device_ILI9341_SPI::writeData(
    const UInt8 *data,
    UInt32 dataSize) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(data, dataSize, Ticks::fromMiliseconds(1000));
    _pinCS->set();
}
