#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Pin/Drivers/VNI8200XP/eosDevice_VNI8200XP.h"


using namespace eos;
using namespace htl;


static uint8_t calcParity(uint8_t data);


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
Device_VNI8200XP_SPI::Device_VNI8200XP_SPI():
    _state {State::reset},
    _curPinState {0},
    _oldPinState {0},
    _devSPI {nullptr},
    _pinSS {nullptr},
    _pinOUTEN {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \param    devSPI: El dispositiu SPI
/// \param    pinSS: El pin de seleccio.
/// \param    pinOUTEN: El pin de seleccio de les sortides.
///
Device_VNI8200XP::Result Device_VNI8200XP_SPI::initialize(
    DevSPI *devSPI,
    Pin *pinSS,
    Pin *pinOUTEN) {

    eosAssert(devSPI != nullptr);
    eosAssert(pinSS != nullptr);
    eosAssert(_state == State::reset);

    if (_state == State::reset) {

        _devSPI = devSPI;
        _pinSS = pinSS;
        _pinOUTEN = pinOUTEN;

        _pinSS->set();
        if (_pinOUTEN != nullptr)
            _pinOUTEN->clear();

        _state = State::ready;

        return Result::ok;
    }
    else
        return Result::error;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita les sortides.
///
void Device_VNI8200XP_SPI::enable() const {

    eosAssert(_state == State::ready);

    if (_state == State::ready) {
        if (_pinOUTEN != nullptr)
            _pinOUTEN->set();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita les sortides.
///
void Device_VNI8200XP_SPI::disable() const {

    eosAssert(_state == State::ready);

    if (_state == State::ready) {
        if (_pinOUTEN != nullptr)
            _pinOUTEN->clear();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza les sortides en funcio del estat intern.
///
void Device_VNI8200XP_SPI::update() {

    eosAssert(_state == State::ready);
    
    if (_state == State::ready) {

        _state = State::updating;

        if (_curPinState != _oldPinState) {

            uint8_t txData[2], rxData[2];

            txData[0] = _curPinState;
            txData[1] = calcParity(_curPinState);

            _pinSS->clear();
            _devSPI->transmit(txData, rxData, sizeof(txData));
            _pinSS->set();

            _oldPinState = _curPinState;
        }

        _state = State::ready;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Activa els pins especificats.
/// \param    pinMask: Mascara dels pins a activar.
///
void Device_VNI8200XP_SPI::set(
    uint8_t pinMask) {

    _curPinState |= pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva els pins especificats.
/// \param    pinMask: Mascara dels pins a desactivar.
///
void Device_VNI8200XP_SPI::clear(
    uint8_t pinMask) {

    _curPinState &= ~pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Inverteix els pins especificats.
/// \param    pinMask: Mascara dels pins a invertir.
///
void Device_VNI8200XP_SPI::toggle(
    uint8_t pinMask) {

    _curPinState ^= pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu els pins.
/// \param    pinMask: Mascara dels pins a escriure.
/// \param    pinState: El estat a escriure.
///
void Device_VNI8200XP_SPI::write(
    uint8_t pinMask,
    bool pinState) {

    if (pinState)
        _curPinState |= pinMask;
    else
        _curPinState &= ~pinMask;
}


/// ----------------------------------------------------------------------
/// \brief    Obte l'estat dels pins.
/// \return   El estat.
///
uint8_t Device_VNI8200XP_SPI::read() const {

    return _curPinState;
}


/// ----------------------------------------------------------------------
/// \brief    Calcula la paritat de les dades.
/// \param    data: Les dades sobre les que es calcula la paritat.
/// \return   La paritat calculada.
///
static uint8_t calcParity(
    uint8_t data) {

    uint8_t p0, p1, p2, np0;

    p0 = data ^ (data >> 1);
    p0 = p0 ^ (p0 >> 2);
    p0 = p0 ^ (p0 >> 4);
    p0 = p0 & 0x01;

    p1 = data ^ (data >> 2);
    p1 = p1 ^ (p1 >> 4);

    p2 = p1 & 0x01;

    p1 = p1 & 0x02;
    p1 = p1 >> 1;

    np0 = (~p0) & 0x01;

    return (p2 << 3) | (p1 << 2) | (p0 << 1) | np0;
}
