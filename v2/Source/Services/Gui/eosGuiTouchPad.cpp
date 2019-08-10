#include "eos.h"
#include "Services/Gui/eosGuiTouchPad.h"
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
	touch(nullptr),
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

	Task::delay(200);
}
