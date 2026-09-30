module;


#include "eos.h"
#include "HTL/htlGPIO.h"


export module Eos.Controllers.Display.Drivers.SSD1306.SPI;


export import Eos.Controllers.Display.Drivers.SSD1306;

import Eos.Hardware.SPI;
import Eos.System.Core.Task;
import Eos.System.Core.Ticks;
import Eos.Types;


export namespace eos {


    /// @brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI
    //
    class DisplayDevice_SSD1306_SPI: public DisplayDevice_SSD1306 {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = eos::hardware::spi::SPIDevice;

        protected:
            Pin const * const _pinCS;
            Pin const * const _pinDC;
            Pin const * const _pinRST;
            DevSPI * const _devSPI;

        public:
            DisplayDevice_SSD1306_SPI(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI);
            ~DisplayDevice_SSD1306_SPI();

            void initialize(const UInt8 *script, UInt32 scriptSize);
            void deinitialize();

            void writeCommand(const UInt8 *data, UInt32 dataSize) override;
            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };
}


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Constructor.
///
DisplayDevice_SSD1306_SPI::DisplayDevice_SSD1306_SPI(
    Pin *pinCS,
    Pin *pinDC,
    Pin *pinRST,
    DevSPI *devSPI) :

    DisplayDevice_SSD1306 {},

    _pinCS {pinCS},
    _pinDC {pinDC},
    _pinRST {pinRST},
    _devSPI {devSPI} {

}


/// ----------------------------------------------------------------------
/// @brief    Destructor.
///
DisplayDevice_SSD1306_SPI::~DisplayDevice_SSD1306_SPI() {

    deinitialize();
}


/// ----------------------------------------------------------------------
/// @brief    Inicialitzacio.
/// @param    pinCS: El pin CS (Chip Select)
/// @param    pinDC: El pin DC (Data/Command)
/// @param    devSPI: El dispositiu SPI
/// @param    pinRST: El pin RST (Hardware reset)
///
void DisplayDevice_SSD1306_SPI::initialize(
    const UInt8 *script,
    UInt32 scriptSize) {

    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        Task::delay(Ticks::fromMiliseconds(100));
        _pinRST->set();
        Task::delay(Ticks::fromMiliseconds(500));
    }

    writeScript(script, scriptSize);
}


/// ----------------------------------------------------------------------
/// @brief    Desinicialitzacio.
///
void DisplayDevice_SSD1306_SPI::deinitialize() {

    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un bloc de dades en el registre de comanda.
/// @brief    data: Les dades.
/// @param    dataSize: Tamany de les dades en bytes.
///
void DisplayDevice_SSD1306_SPI::writeCommand(
    const UInt8 *data,
    UInt32 dataSize) {

    _pinDC->clear();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, Ticks::fromMiliseconds(100));
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// @brief    Escriu un bloc de dades en el registre de dades.
/// @brief    data: Les dades.
/// @param    dataSize: Tamany de les dades en bytes.
///
void DisplayDevice_SSD1306_SPI::writeData(
    const UInt8 *data,
    UInt32 dataSize) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, Ticks::fromMiliseconds(100));
    _pinCS->set();
}
