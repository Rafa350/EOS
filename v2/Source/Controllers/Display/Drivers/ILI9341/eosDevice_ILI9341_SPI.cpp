#include "eos.h"
#include "Controllers/Display/Drivers/ILI9341/eosDevice_ILI9341.h"
#include "System/Core/eosTask.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    pinCS: El pin CS.
/// \param    pinRS: El pin RS.
/// param     pinRST: eE pin RST.
/// \param    devSPI: El dispositiu SPI
///
Device_ILI9341_SPI::Device_ILI9341_SPI(
    Pin *pinCS,
    Pin *pinRS,
    Pin *pinRST,
    DevSPI *devSPI):

    Device_ILI9341(),

    _pinCS {pinCS},
    _pinRS {pinRS},
    _pinRST {pinRST},
    _devSPI {devSPI} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    script: Script d'inicialitzacio.
/// \param    scriptSize: Tamany del script en bytes.
///
void Device_ILI9341_SPI::initialize(
    const uint8_t *script,
    unsigned scriptSize) {

    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        Task::delay(20);
        _pinRST->set();
        Task::delay(120);
        _pinRST->set();
    }

    writeScript(script, scriptSize);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void Device_ILI9341_SPI::deinitialize() {

    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registrte de control.
/// \param    cmd: El byte a escriure.
///
void Device_ILI9341_SPI::writeCommand(
    uint8_t data) {

    _pinCS->clear();
    _pinRS->clear();
    _devSPI->transmit(&data, 1, Tick(1000));
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registrte de dades.
/// \param    data: El byte a escriure.
///
void Device_ILI9341_SPI::writeData(
    uint8_t data) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(&data, 1, Tick(1000));
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una llista de bytes en el registrte de dades.
/// \param    data: La llista de bytes.
/// \param    dataSize: El tamany de la llista en bytes
///
void Device_ILI9341_SPI::writeData(
    const uint8_t *data,
    unsigned dataSize) {

    _pinCS->clear();
    _pinRS->set();
    _devSPI->transmit(data, dataSize, Tick(1000));
    _pinCS->set();
}


