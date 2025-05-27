#include "eos.h"

#include "appConfig.h"


using namespace app;


/// ----------------------------------------------------------------------
/// \brief    Procesa la interrupcio
///
extern "C" void USART1_IRQHandler() {

	hw::DevUART::pInst->interruptHandler();
}
