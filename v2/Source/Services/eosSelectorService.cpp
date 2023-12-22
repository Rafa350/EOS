#include "Services/eosSelectorService.h"


using namespace eos;


#define PATTERN_MASK    0b00001111


/// ----------------------------------------------------------------------
/// \brief Constructor
///
SelectorService::SelectorService(
    PinDriver *drvINA,
    PinDriver *drvINB,
    PinDriver *drvSW) :
    
    _drvINA {drvINA},
    _drvINB {drvINB},
    _drvSW {drvSW},
    _position {0},
    _button {false},
    _patternA {0},
    _patternB{0},
    _patternSW {0},
    _shiftA {0},
    _shiftB {0},
    _shiftSW {0},
    _transition {0},
    _changedEvent {nullptr},
    _changedEventEnabled {false} {
}


/// ----------------------------------------------------------------------
/// \brief    Configura el event 'Changed'
/// \param    event: El event.
/// \param    enabled: True si es vol habilitar.
///
void SelectorService::setChangedEvent(
    IChangedEvent &event,
    bool enabled) {

    _changedEvent = &event;
    _changedEventEnabled = enabled;
}


/// ----------------------------------------------------------------------
/// \brief    Habilita l'event 'Changed'
///
void SelectorService::enableChangedEvent() {

    _changedEventEnabled = _changedEvent != nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Deshabilita l'event 'Changed'
///
void SelectorService::disableChangedEvent() {

    _changedEventEnabled = false;
}


/// ----------------------------------------------------------------------
/// \brief Procesa les tasques del servei
/// \param task: La tasca actual.
///
bool SelectorService::onTask() {

    if (scanEncoder()) {
        if (_changedEventEnabled) {
            ChangedEventArgs args = {
                .position = _position,
                .button = _button
            };
            _changedEvent->execute(this, args);
        }
    }

    Task::delay(50);

    return true;
}


uint8_t SelectorService::getINA() const {

    return _drvINA->read() ? 0x01 : 0x00;
}


uint8_t SelectorService::getINB() const {

    return _drvINB->read() ? 0x01 : 0x00;
}


uint8_t SelectorService::getSW() const {

    return _drvSW->read() ? 0x01 : 0x00;
}


bool SelectorService::scanEncoder() {

    bool moved = false;
    bool pressed = false;

    // Comprova la entrada INA
    //
    _shiftA = ((_shiftA << 1) | getINA()) & PATTERN_MASK;
    if (_shiftA == _patternA) {
        _transition = (uint8_t)((_transition << 2) | ((_shiftA & 1) ? 0x00 : 0x01));
        _patternA = ~_patternA & PATTERN_MASK;
        moved = true;
    }

    // Comprova la entrada INB
    //
    _shiftB = ((_shiftB << 1) | getINB()) & PATTERN_MASK;
    if (_shiftB == _patternB) {
        _transition = (uint8_t)((_transition << 2) | ((_shiftB & 1) ? 0x02 : 0x03));
        _patternB = ~_patternB & PATTERN_MASK;
        moved = true;
    }

    // Procesa les transicions per detectar el patro de moviment
    //
    if (moved) {
        if (_transition == 0b01110010)
            _position++;
        else if (_transition == 0b11011000)
            _position--;
    }

    // Comprova la entrada SW
    //
    _shiftSW = ((_shiftSW << 1) | getSW()) & PATTERN_MASK;
    if (_shiftSW == _patternSW) {
        _button = (_shiftSW & 1) == 0;
        _patternSW = ~_patternSW & PATTERN_MASK;
        pressed = true;
    }

    return moved || pressed;
}
