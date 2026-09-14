module;


#include "eos.h"
#include "eosTime.h"
#include "RTOS/rtosTask.h"
#include "HTL/htlGPIO.h"
#include "HTL/htlSPI.h"
#include "HTL/htlDMA.h"


export module Eos.Controllers.Display.Drivers.SSD1306.SPI;


export import Eos.Controllers.Display.Drivers.SSD1306;


export namespace eos {


    /// \brief Clase que representa un dispositiu SSD1306 amb
    //         interficie SPI
    //
    class DisplayDevice_SSD1306_SPI: public DisplayDevice_SSD1306 {
        public:
            using Pin = htl::gpio::PinDevice;
            using DevSPI = htl::spi::SPIDevice;

        protected:
            Pin const * const _pinCS;
            Pin const * const _pinDC;
            Pin const * const _pinRST;
            DevSPI * const _devSPI;

        public:
            DisplayDevice_SSD1306_SPI(Pin *pinCS, Pin *pinDC, Pin *pinRST, DevSPI *devSPI);
            ~DisplayDevice_SSD1306_SPI();

            void initialize(const uint8_t *script, size_t scriptSize);
            void deinitialize();

            void writeCommand(const uint8_t *data, size_t dataSize) override;
            void writeData(const uint8_t *data, size_t dataSize) override;
    };
}



/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
eos::DisplayDevice_SSD1306_SPI::DisplayDevice_SSD1306_SPI(
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
/// \brief    Destructor.
///
eos::DisplayDevice_SSD1306_SPI::~DisplayDevice_SSD1306_SPI() {

    deinitialize();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    pinCS: El pin CS (Chip Select)
/// \param    pinDC: El pin DC (Data/Command)
/// \param    devSPI: El dispositiu SPI
/// \param    pinRST: El pin RST (Hardware reset)
///
void eos::DisplayDevice_SSD1306_SPI::initialize(
    const uint8_t *script,
    unsigned scriptSize) {

    _pinCS->set();
    if (_pinRST != nullptr) {
        _pinRST->clear();
        rtos::Task::delay(Time::fromMiliseconds(100));
        _pinRST->set();
        rtos::Task::delay(Time::fromMiliseconds(500));
    }

    writeScript(script, scriptSize);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void eos::DisplayDevice_SSD1306_SPI::deinitialize() {

    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de comanda.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void eos::DisplayDevice_SSD1306_SPI::writeCommand(
    const uint8_t *data,
    unsigned dataSize) {

    _pinDC->clear();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, eos::Time::fromMiliseconds(100));
    _pinCS->set();
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el registre de dades.
/// \brief    data: Les dades.
/// \param    dataSize: Tamany de les dades en bytes.
///
void eos::DisplayDevice_SSD1306_SPI::writeData(
    const uint8_t *data,
    unsigned dataSize) {

    _pinDC->set();
    _pinCS->clear();
    _devSPI->transmit(data, dataSize, eos::Time::fromMiliseconds(100));
    _pinCS->set();
}
