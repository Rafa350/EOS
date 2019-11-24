#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "appDisplayService.h"

#include "DSP04Messages.h"

using namespace eos;
using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    application: Applicacio a la que pertany el servei.
/// \param    display: El display
///
DisplayService::DisplayService(
    Application *application,
    GfxDisplay *display):
    
    AppLoopService(application),
    display(display) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio
/// \remarks  S'executa d'ins del planificador.
///
void DisplayService::onSetup() {
    
    x = 0;
    y = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Executa les tasques del servei.
///
void DisplayService::onLoop() {
    
    Task::delay(1000);
    
    while (true) {
    
        display->clear(0x00);
        display->drawRectangle(x, y, x + 5, y + 5);
        display->refresh();    
    
        Task::delay(100);
    
        x += 1;
        if (x > 128 - 5)
            x = 0;
        y += 1;
        if (y > 64 - 4)
            y = 0;
    }
}


