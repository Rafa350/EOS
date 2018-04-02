#include "Services/Gui/eosGui.h"


using namespace eos;


static const char *serviceName = "GuiService";
static const unsigned stackSize = 512;
static const TaskPriority priority = TaskPriority::normal;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param info: Parametres d'inicialitzacio
///
GuiService::GuiService(
	Application *application,
	const GuiServiceInitializeInfo *info):

	Service(application, serviceName, stackSize, priority) {

}


void GuiService::initialize() {

}


/// ----------------------------------------------------------------------
/// \brief Tasca de control del servei.
/// \param task: La tasca que s'esta executant.
///
void GuiService::run(Task *task) {

	while (true) {

	}
}
