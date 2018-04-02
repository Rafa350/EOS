#include "Services/Gui/eosGuiTouchPad.h"


using namespace eos;

static const char *serviceName = "GuiTouchPadService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


GuiTouchPadService::GuiTouchPadService(
	Application *application):

	Service(application, serviceName, stackSize, priority),
	evNotify(nullptr) {
}


GuiTouchPadService::~GuiTouchPadService() {

	if (evNotify != nullptr)
		delete evNotify;
}


void GuiTouchPadService::initialize() {

}


void GuiTouchPadService::run(Task *task) {

	while (true) {

	}
}
