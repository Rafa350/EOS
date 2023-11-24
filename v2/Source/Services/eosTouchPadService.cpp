#include "eos.h"

#ifdef USE_TOUCHPAD

#include "HTL/STM32/htlEXTI.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosTouchPadDriver_FT5336.h"
#include "Services/eosTouchPadService.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    application: Aplicacio on afeigir el servei
/// \param    cfg: Parametres de configuracio.
///
TouchPadService::TouchPadService():
	_touchDriver {nullptr},
	_touchPadEvent {*this, &TouchPadService::touchPadEventHandler},
	_notifyEvent {nullptr},
	_notifyEventEnabled {false},
	_oldX {-1},
	_oldY {-1},
	_oldPressed {false} {
}


void TouchPadService::setNotifyEvent(
	INotifyEvent &event,
	bool enabled) {

	_notifyEvent = &event;
	_notifyEventEnabled = enabled;
}


/// ---------------------------------------------------------------------
/// \brief    Inicialitzacio abans del planificador.
///
void TouchPadService::onInitialize() {

    // Inicialitzacio del touch pad
    //
    _touchDriver = new TouchPadDriver_FT5336();
    _touchDriver->initialize();
    _touchDriver->setOrientation(TouchPadOrientation::rotate90);
    _touchDriver->setTouchPadEvent(_touchPadEvent);
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void TouchPadService::onTask() {
        
    // Repeteix indefinidament
    //
    while (true) {

		if (_lock.wait(-1)) {

			// Detecta variacions del estat del touchpad
			//
			bool pressed = false;
			int16_t x = -1;
			int16_t y = -1;
			while (_touchDriver->getTouchCount()) {

				// Obte l'estat
				//
				TouchPadState state;
				_touchDriver->getState(state);
				if (state.numPoints == 1) {
					pressed = true;
					x = state.x[0];
					y = state.y[0];
				}

				// Detecta canvis de contacte.
				//
				if (!_oldPressed && pressed) {
					if (_notifyEventEnabled) {
						NotifyEventArgs args = {
							.notifyType = NotifyType::press,
							.x = x,
							.y = y
						};
						_notifyEvent->execute(this, args);
					}
				}

				// Detecta canvis de posicio
				//
				else if (pressed && ((_oldX != x) || (_oldY != y))) {
					if (_notifyEventEnabled) {
						NotifyEventArgs args = {
							.notifyType = NotifyType::move,
							.x = x,
							.y = y
						};
						_notifyEvent->execute(this, args);
					}
				}

				_oldPressed = pressed;
				_oldX = x;
				_oldY = y;
			}

			if (_oldPressed) {
				if (_notifyEventEnabled) {
					NotifyEventArgs args = {
						.notifyType = NotifyType::release,
						.x = x,
						.y = y
					};
					_notifyEvent->execute(this, args);
				}

				_oldPressed = false;
			}
		}
    }
}


/// ----------------------------------------------------------------------
/// \brief    Despatxa la interrupcio a la funcio membre.
///
void TouchPadService::touchPadEventHandler(
	TouchPadDriver_FT5336 *sender) {

	_lock.releaseISR();
}


#endif
