#include "Services/Gui/eosGuiTouchPad.h"
#include "Controllers/TouchPad/Drivers/eosFT5336.h"


using namespace eos;

static const char *serviceName = "GuiTouchPadService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Contrustor de l'objecte.
/// \param application: Aplicacio on afeigir el servei.
///
GuiTouchPadService::GuiTouchPadService(
	Application *application):

	Service(application, serviceName, stackSize, priority),
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
    touch = new TouchPad(touchDriver);
}


/// ----------------------------------------------------------------------
/// \brief Bucle d'execucio.
///
void GuiTouchPadService::onTask() {

	TouchPadState tpState;

	if (touch->getState(tpState)) {
		if (evNotify != nullptr) {

			TouchPadEventArgs a;
			for (int i = 0; i < TOUCHPAD_MAX_POINTS; i++) {
				a.x[i] = tpState.x[i];
				a.y[i] = tpState.y[i];
			}

			evNotify->execute(&a);
		}
	}

	Task::delay(250);
}
