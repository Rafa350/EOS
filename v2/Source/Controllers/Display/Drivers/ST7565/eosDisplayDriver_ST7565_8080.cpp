#include "eos.h"
#include "Controllers/Display/Drivers/ST7565/eosDisplayDriver_ST7565.h"
#include "HTL/htlGPIO.h"


#if (DISPLAY_INTERFACE != DISPLAY_INTERFACE_ST7565_8080)
#error Interface no soportado
#endif


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el interficie.
///
void DisplayDriver_ST7565::initializeInterface() {
    
	#ifdef DISPLAY_CS_GPIO
		DISPLAY_CS_GPIO::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::high, htl::GPIOInitState::set);
	#endif
	DISPLAY_A0_GPIO::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::high);
	DISPLAY_WR_GPIO::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::high, htl::GPIOInitState::set);
	DISPLAY_RD_GPIO::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::high, htl::GPIOInitState::set);
} 


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre de dades.
/// \param    data: El valor a escriure.
///
void DisplayDriver_ST7565::writeDataRegister(
    uint8_t data) {

    DISPLAY_A0_GPIO::set();
	#ifdef DISPLAY_CS_GPIO
		DISPLAY_CS_GPIO::clear();
	#endif
    writeRegister(data);
	#ifdef DISPLAY_CS_GPIO
		DISPLAY_CS_GPIO::set();
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre de control.
/// \param    cmd: El valor a escriure.
///
void DisplayDriver_ST7565::writeCtrlRegister(
    uint8_t cmd) {

    DISPLAY_A0_GPIO::clear();
	#ifdef DISPLAY_CS_GPIO
		DISPLAY_CS_GPIO::clear();
	#endif
    writeRegister(cmd);
	#ifdef DISPLAY_CS_GPIO
		DISPLAY_CS_GPIO::set();
	#endif

    // Retard per procesar la comanda
    //
    uint8_t i;
    for (i = 0; i < 10; i++)
        continue;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el registre del controlador.
/// \param    data: El byte a escriure.
/// \remarks  El controlador ha d'estar configurat per
///           rebre el byte en el registre correcte.
///
void DisplayDriver_ST7565::writeRegister(
    uint8_t data) {

}
