#include "eos.h"
#include "Services/Gui/eosGuiTouchPad.h"
#include "Controllers/TouchPad/eosTouchPadDriver.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"


using namespace eos;


static const char *serviceName = "GuiTouchPadService";
static const unsigned stackSize = OPT_GUI_TouchPadServiceStack;
static const TaskPriority priority = OPT_GUI_TouchPadServicePriority;


/// ----------------------------------------------------------------------
/// \brief Contrustor de l'objecte.
/// \param application: Aplicacio on afeigir el servei.
///
GuiTouchPadService::GuiTouchPadService(
	Application *application):

	Service(application, serviceName, stackSize, priority),
	touchDriver(nullptr),
	evNotify(nullptr) {
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
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void GuiTouchPadService::onTask() {

	if (evNotify != nullptr) {

		static int oldTouchCount = 0;

		int touchCount = touchDriver->getTouchCount();
		if (touchCount != oldTouchCount) {
			oldTouchCount = touchCount;

			TouchPadEventArgs a;

			if (touchCount == 0)
				a.isPressed = false;

			else {
				TouchPadState state;
				if (touchDriver->getState(state)) {

					a.isPressed =
						(state.action[0] == TouchPadAction::press) ||
						(state.action[0] == TouchPadAction::contact);
					a.x = state.x[0];
					a.y = state.y[0];
					evNotify->execute(&a);
				}
			}

			evNotify->execute(&a);
		}
	}

	Task::delay(50);
}
