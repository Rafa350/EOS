#include "eos.h"
#include "HAL/STM32/halEXTI.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Services/eosTouchPadService.h"


using namespace eos;


static const TouchPadServiceConfiguration defaultConfiguration = {
	.serviceConfiguration = {
		.serviceName = "TouchPadService",
		.stackSize = OPT_GUI_TouchPadServiceStack,
		.priority = OPT_GUI_TouchPadServicePriority
	}
};


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    application: Aplicacio on afeigir el servei.
///
TouchPadService::TouchPadService(
	Application *application) :

	TouchPadService(application, defaultConfiguration) {
}


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    application: Aplicacio on afeigir el servei
/// \param    configuration: Parametres de configuracio.
///
TouchPadService::TouchPadService(
	Application *application,
	const TouchPadServiceConfiguration &configuration):

	Service(application, configuration.serviceConfiguration),
	touchDriver(nullptr),
	eventCallback(nullptr),
	oldX(-1),
	oldY(-1),
	oldPressed(false) {
}


/// ---------------------------------------------------------------------
/// \brief    Inicialitzacio abans del planificador.
///
void TouchPadService::onInitialize() {

    // Inicialitzacio del touch pad
    //
    touchDriver = FT5336Driver::getInstance();
    touchDriver->initialize();
    touchDriver->setOrientation(TouchPadOrientation::rotate90);

    halEXTISetCallbackFunction(TOUCHPAD_EXTI_LINE, interruptHandler, this);
}


/// ----------------------------------------------------------------------
/// \brief    Bucle d'execucio.
///
void TouchPadService::onTask() {

	if (eventCallback != nullptr) {

		if (lock.wait((unsigned) -1)) {

			// Detecta variacions del estat del touchpad
			//
			bool pressed = false;
			int x = -1;
			int y = -1;
			while (touchDriver->getTouchCount()) {

				// Obte l'estat
				//
				TouchPadState state;
				touchDriver->getState(state);
				if (state.numPoints == 1) {
					pressed = true;
					x = state.x[0];
					y = state.y[0];
				}

				// Detecta canvis de contacte.
				//
				if (!oldPressed && pressed) {

					TouchPadEventArgs args = {
						.event = TouchPadEventType::press,
						.x = x,
						.y = y
					};
				eventCallback->execute(args);
				}

				// Detecta canvis de posicio
				//
				else if (pressed && ((oldX != x) || (oldY != y))) {

					TouchPadEventArgs args = {
						.event = TouchPadEventType::move,
						.x = x,
						.y = y
					};
					eventCallback->execute(args);
				}

				oldPressed = pressed;
				oldX = x;
				oldY = y;
			}

			if (oldPressed) {
				TouchPadEventArgs args = {
					.event = TouchPadEventType::release,
					.x = x,
					.y = y
				};
				eventCallback->execute(args);

				oldPressed = false;
			}
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio. Desbloqueja el process.
///
void TouchPadService::interruptHandler() {

	lock.releaseISR();
}


/// ----------------------------------------------------------------------
/// \brief    Despatxa la interrupcio a la funcio membre.
///
void TouchPadService::interruptHandler(
	EXTILine line,
	void *param) {

	((TouchPadService*)param)->interruptHandler();
}
