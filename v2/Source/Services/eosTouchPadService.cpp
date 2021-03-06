#include "eos.h"
#include "HAL/STM32/halEXTI.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Services/eosTouchPadService.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    application: Aplicacio on afeigir el servei
/// \param    cfg: Parametres de configuracio.
///
TouchPadService::TouchPadService(
	Application* application) :

	Service(application),
	_touchDriver(nullptr),
	_eventCallback(nullptr),
	_oldX(-1),
	_oldY(-1),
	_oldPressed(false) {
}


/// ---------------------------------------------------------------------
/// \brief    Inicialitzacio abans del planificador.
///
void TouchPadService::onInitialize() {

    // Inicialitzacio del touch pad
    //
    _touchDriver = FT5336Driver::getInstance();
    _touchDriver->initialize();
    _touchDriver->setOrientation(TouchPadOrientation::rotate90);

    halEXTISetInterruptFunction(TOUCHPAD_INT_EXTI_LINE, interruptHandler, this);
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void TouchPadService::onTask(
	Task *task) {

	if (_eventCallback != nullptr) {

		if (_lock.wait(-1)) {

			// Detecta variacions del estat del touchpad
			//
			bool pressed = false;
			int x = -1;
			int y = -1;
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

					EventArgs args = {
						.event = EventType::press,
						.x = x,
						.y = y
					};
					_eventCallback->execute(args);
				}

				// Detecta canvis de posicio
				//
				else if (pressed && ((_oldX != x) || (_oldY != y))) {

					EventArgs args = {
						.event = EventType::move,
						.x = x,
						.y = y
					};
					_eventCallback->execute(args);
				}

				_oldPressed = pressed;
				_oldX = x;
				_oldY = y;
			}

			if (_oldPressed) {
				EventArgs args = {
					.event = EventType::release,
					.x = x,
					.y = y
				};
				_eventCallback->execute(args);

				_oldPressed = false;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio. Desbloqueja el process.
///
void TouchPadService::interruptHandler() {

	_lock.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    Despatxa la interrupcio a la funcio membre.
///
void TouchPadService::interruptHandler(
	EXTILine line,
	void *param) {

	TouchPadService* service = static_cast<TouchPadService*>(param);
	service->interruptHandler();
}
