#include "eos.h"
#include "HAL/halEXTI.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"
#include "Services/Gui/eosGuiTouchPad.h"


using namespace eos;


static GuiTouchPadServiceConfiguration defaultConfiguration = {
	.serviceConfiguration = {
		.serviceName = "GuiTouchPadService",
		.stackSize = OPT_GUI_TouchPadServiceStack,
		.priority = OPT_GUI_TouchPadServicePriority
	}
};


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param pApplication: Aplicacio on afeigir el servei.
///
GuiTouchPadService::GuiTouchPadService(
	Application *pApplication) :

	GuiTouchPadService(pApplication, defaultConfiguration) {

}


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param pApplication: Aplicacio on afeigir el servei
/// \param configuration: Parametres de configuracio.
///
GuiTouchPadService::GuiTouchPadService(
	Application *pApplication,
	const GuiTouchPadServiceConfiguration &configuration):

	Service(pApplication, configuration.serviceConfiguration),
	touchDriver(nullptr),
	evNotify(nullptr),
	oldX(-1),
	oldY(-1),
	oldPressed(false) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor de l'objecte.
///
GuiTouchPadService::~GuiTouchPadService() {

	if (evNotify != nullptr)
		delete evNotify;
}


/// ---------------------------------------------------------------------
/// \brief Inicialitzacio abans del planificador.
///
void GuiTouchPadService::onInitialize() {

    // Inicialitzacio del touch pad
    //
    touchDriver = FT5336Driver::getInstance();
    touchDriver->initialize();
    touchDriver->setOrientation(TouchPadOrientation::rotate90);

    halEXTISetCallbackFunction(TOUCHPAD_EXTI_LINE, interruptHandler, this);
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void GuiTouchPadService::onTask() {

	if (evNotify != nullptr) {

		bool pressed;
		int x;
		int y;

		// Detecta variacions del estat del touchpad
		//
		pressed = false;
		x = -1;
		y = -1;
		if (touchDriver->getTouchCount()) {

			// Obte l'estat
			//
			TouchPadState state;
			touchDriver->getState(state);

			if (state.numPoints == 1) {

				// Obte el indicador de contacte
				//
				pressed =
					(state.action[0] == TouchPadAction::press) ||
					(state.action[0] == TouchPadAction::contact);

				// Obte la pocicio del contacte
				//
				if (pressed) {
					x = state.x[0];
					y = state.y[0];
				}
				else {
					x = oldX;
					y = oldY;
				}
			}
		}

		// Detecta canvis de contacte.
		//
		if (oldPressed != pressed) {

			TouchPadEventArgs args = {
				.event = pressed ? TouchPadEventType::press : TouchPadEventType::release,
				.x = x,
				.y = y
			};
			evNotify->execute(args);
		}

		// Detecta canvis de posicio
		//
		else if (pressed && ((oldX != x) || (oldY != y))) {

			TouchPadEventArgs args = {
				.event = TouchPadEventType::move,
				.x = x,
				.y = y
			};
			evNotify->execute(args);
		}

		oldPressed = pressed;
		oldX = x;
		oldY = y;
	}

	Task::delay(10);
}


/// ----------------------------------------------------------------------
/// \brief Procesa la interrupcio. Desbloqueja el process.
///
void GuiTouchPadService::interruptHandler() {

}


/// ----------------------------------------------------------------------
/// \brief Despatxa la interrupcio a la funcio membre.
///
void GuiTouchPadService::interruptHandler(
	EXTILine line,
	void *pParam) {

	((GuiTouchPadService*)pParam)->interruptHandler();
}
