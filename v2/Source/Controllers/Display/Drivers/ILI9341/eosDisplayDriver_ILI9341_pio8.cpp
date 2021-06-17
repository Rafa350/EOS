#include "eos.h"


#ifdef DISPLAY_IO_TYPE_PIO8


#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"
#include "Hal/halGPIO.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341Driver::lcdInitialize() {
    
    static const GPIOInitializePinInfo initCtrlPins[] = {
#ifdef DISPLAY_RST_PORT        
        {DISPLAY_RST_PORT, DISPLAY_RST_PIN, 
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE},
#endif        
        {DISPLAY_CS_PORT,  DISPLAY_CS_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE},
        {DISPLAY_RS_PORT,  DISPLAY_RS_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE},
#ifdef DISPLAY_RD_PORT
        {DISPLAY_RD_PORT,  DISPLAY_RD_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE},
#endif            
        {DISPLAY_WR_PORT,  DISPLAY_WR_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE}
    };

    static const GPIOInitializePortInfo initDataPort = 
        {DISPLAY_DATA_PORT, 0x00FF, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE};
       
    halGPIOInitializePins(initCtrlPins, sizeof(initCtrlPins) / sizeof(initCtrlPins[0]));
    halGPIOInitializePorts(&initDataPort, 1);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341Driver::lcdReset() {

    halTMRDelay(10);
    halGPIOSetPin(DISPLAY_RST_PORT, DISPLAY_RST_PIN);
    halTMRDelay(120);
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdOpen() {

    halINTDisableInterrupts();
    halGPIOClearPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341Driver::lcdClose() {

    halGPIOSetPin(DISPLAY_CS_PORT, DISPLAY_CS_PIN);
    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de comandes.
/// \param cmd: El byte a escriure.
///
void ILI9341Driver::lcdWriteCommand(
    uint8_t cmd) {

    halGPIOClearPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halGPIOClearPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
    halGPIOModePortOutput(DISPLAY_DATA_PORT, 0x00FF);
    halGPIOWritePort(DISPLAY_DATA_PORT, cmd);
    halGPIOSetPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param data: El byte a escriure.
///
void ILI9341Driver::lcdWriteData(
    uint8_t data) {

    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halGPIOClearPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
    halGPIOModePortOutput(DISPLAY_DATA_PORT, 0x00FF);
    halGPIOWritePort(DISPLAY_DATA_PORT, data);
    halGPIOSetPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
}

/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param data: El byte a escriure.
///
void ILI9341Driver::lcdWriteData(
    uint8_t *data, int32_t size) {

    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halGPIOModePortOutput(DISPLAY_DATA_PORT, 0x00FF);
    while (size--) {
        halGPIOClearPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
        halGPIOWritePort(DISPLAY_DATA_PORT, *data++);
        halGPIOSetPin(DISPLAY_WR_PORT, DISPLAY_WR_PIN);
    }
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ILI9341Driver::lcdReadData() {

#ifdef DISPLAY_RD_PORT
    halGPIOSetPin(DISPLAY_RS_PORT, DISPLAY_RS_PIN);
    halGPIOClearPin(DISPLAY_RD_PORT, DISPLAY_RD_PIN);
    halGPIOModePortInput(DISPLAY_DATA_PORT, 0x00FF);
    uint8_t data = halGPIOReadPort(DISPLAY_DATA_PORT);
    halGPIOSetPin(DISPLAY_RD_PORT, DISPLAY_RD_PIN);

    return data;
#else
    return 0;
#endif
}


#endif
