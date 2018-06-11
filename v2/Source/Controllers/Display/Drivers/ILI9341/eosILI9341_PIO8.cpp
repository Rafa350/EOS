#include "eos.h"


#ifdef ILI9341_IO_TYPE_PIO8


#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halTMR.h"
#include "Hal/halINT.h"
#include "Hal/halGPIO.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ILI9341_Driver::lcdInitialize() {
    
    static const GPIOInitializePinInfo initCtrlPins[] = {
#ifdef ILI9341_RST_PORT        
        {ILI9341_RST_PORT, ILI9341_RST_PIN, 
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE},
#endif        
        {ILI9341_CS_PORT,  ILI9341_CS_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE},
        {ILI9341_RS_PORT,  ILI9341_RS_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_CLR, HAL_GPIO_AF_NONE},
#ifdef ILI9341_RD_PORT
        {ILI9341_RD_PORT,  ILI9341_RD_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE},
#endif            
        {ILI9341_WR_PORT,  ILI9341_WR_PIN,  
            HAL_GPIO_MODE_OUTPUT_PP | HAL_GPIO_INIT_SET, HAL_GPIO_AF_NONE}
    };

    static const GPIOInitializePortInfo initDataPort = 
        {ILI9341_DATA_PORT, 0x00FF, HAL_GPIO_MODE_OUTPUT_PP, HAL_GPIO_AF_NONE};
       
    halGPIOInitializePins(initCtrlPins, sizeof(initCtrlPins) / sizeof(initCtrlPins[0]));
    halGPIOInitializePort(&initDataPort);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ILI9341_Driver::lcdReset() {

    halTMRDelay(10);
    halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
    halTMRDelay(120);
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdOpen() {

    halINTDisableInterrupts();
    halGPIOClearPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ILI9341_Driver::lcdClose() {

    halGPIOSetPin(ILI9341_CS_PORT, ILI9341_CS_PIN);
    halINTEnableInterrupts();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de comandes.
/// \param cmd: El byte a escriure.
///
void ILI9341_Driver::lcdWriteCommand(
    uint8_t cmd) {

    halGPIOClearPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halGPIOClearPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
    halGPIOModePortOutput(ILI9341_DATA_PORT, 0x00FF);
    halGPIOWritePort(ILI9341_DATA_PORT, cmd);
    halGPIOSetPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param data: El byte a escriure.
///
void ILI9341_Driver::lcdWriteData(
    uint8_t data) {

    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halGPIOClearPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
    halGPIOModePortOutput(ILI9341_DATA_PORT, 0x00FF);
    halGPIOWritePort(ILI9341_DATA_PORT, data);
    halGPIOSetPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
}

/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param data: El byte a escriure.
///
void ILI9341_Driver::lcdWriteData(
    uint8_t *data, int32_t size) {

    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halGPIOModePortOutput(ILI9341_DATA_PORT, 0x00FF);
    while (size--) {
        halGPIOClearPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
        halGPIOWritePort(ILI9341_DATA_PORT, *data++);
        halGPIOSetPin(ILI9341_WR_PORT, ILI9341_WR_PIN);
    }
}

/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ILI9341_Driver::lcdReadData() {

#ifdef ILI9341_RD_PORT
    halGPIOSetPin(ILI9341_RS_PORT, ILI9341_RS_PIN);
    halGPIOClearPin(ILI9341_RD_PORT, ILI9341_RD_PIN);
    halGPIOModePortInput(ILI9341_DATA_PORT, 0x00FF);
    data = halGPIOReadPort(ILI9341_DATA_PORT);
    halGPIOSetPin(ILI9341_RD_PORT, ILI9341_RD_PIN);

    return data;
#else
    return 0;
#endif
}


#endif
