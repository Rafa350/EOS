#include "eos.h"


#if defined(ILI9341_INTERFACE_TYPE_PIC32PMP_8BIT) && defined(EOS_PIC32MX)

extern "C" {
#include "peripheral/pmp/plib_pmp.h"
}
#include "Controllers/Display/Drivers/eosILI9341.h"
#include "Hal/halGPIO.h"
#include "Hal/halTMR.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Inicialitza les comunicacions.
///
void ioInitialize() {

#ifdef ILI9341_RST_PORT
    halGPIOClearPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
    halGPIOInitializePinOutput(ILI9341_RST_PORT, ILI9341_RST_PIN);
#endif
    
    // Configura basica del modul PMP
    //
    PLIB_PMP_OperationModeSelect(PMP_ID_0, PMP_MASTER_READ_WRITE_STROBES_INDEPENDENT);
    PLIB_PMP_MultiplexModeSelect(PMP_ID_0, PMP_MUX_NONE);
    PLIB_PMP_AddressIncrementModeSelect(PMP_ID_0, PMP_ADDRESS_INCREMENT_DECREMENT_DISABLE);
    PLIB_PMP_StopInIdleEnable(PMP_ID_0);

    // Configura el port de dades
    //    
    PLIB_PMP_DataSizeSelect(PMP_ID_0, PMP_DATA_SIZE_8_BITS);

    // Configura el port d'adresses
    //
    PLIB_PMP_AddressPortEnable(PMP_ID_0, PMP_PMA0_PORT);
    
    // Configura el port CS
    //
    PLIB_PMP_ChipSelectFunctionSelect(PMP_ID_0, PMCS1_AS_ADDRESS_LINE_PMCS2_AS_CHIP_SELECT);
    PLIB_PMP_ChipSelectXPolaritySelect(PMP_ID_0, PMP_CHIP_SELECT_ONE, PMP_POLARITY_ACTIVE_LOW);   
    
    // Configura el port WE
    //
    PLIB_PMP_WriteEnableStrobePortEnable(PMP_ID_0);
    PLIB_PMP_WriteEnableStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_LOW);
    
    // Configura el port RD
    //
    PLIB_PMP_ReadWriteStrobePortEnable(PMP_ID_0);
    PLIB_PMP_ReadWriteStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_LOW);

    // Configura els wait states
    //
    PLIB_PMP_WaitStatesDataSetUpSelect(PMP_ID_0, PMP_DATA_WAIT_FOUR);
    PLIB_PMP_WaitStatesStrobeSelect(PMP_ID_0, PMP_STROBE_WAIT_1);
    PLIB_PMP_WaitStatesDataHoldSelect(PMP_ID_0, PMP_DATA_HOLD_1);

    // Configura les interrupcions
    //
    PLIB_PMP_InterruptModeSelect(PMP_ID_0, PMP_INTERRUPT_NONE);
    
    // Activa el modul
    //
    PLIB_PMP_Enable(PMP_ID_0);
}


/// ----------------------------------------------------------------------
/// \brief Reseteja el driver.
///
void ioReset() {

    halTMRDelay(10);
    halGPIOSetPin(ILI9341_RST_PORT, ILI9341_RST_PIN);
    halTMRDelay(120);
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el driver.
///
void ioBbegin() {

}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el driver.
///
void ioEnd() {

}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de comandes.
/// \param d: El byte a escriure.
///
void iuoWriteCommand(
    uint8_t d) {
    
    PLIB_PMP_AddressSet(PMP_ID_0, 0);

    while (PLIB_PMP_PortIsBusy(PMP_ID_0))
        continue;

    PLIB_PMP_MasterSend(PMP_ID_0, d);
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte en el registre de dades.
/// \param d: El byte a escriure.
///
void ioWriteData(
    uint8_t d) {

    PLIB_PMP_AddressSet(PMP_ID_0, 1);

    while (PLIB_PMP_PortIsBusy(PMP_ID_0))
        continue;

    PLIB_PMP_MasterSend(PMP_ID_0, d);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un byte en l'adressa seleccionada del driver.
/// \return El byte lleigit.
///
uint8_t ioReadData() {

#ifdef ILI9342_INTERFACE_WRITEONLY
    return 0;
    
#else
    PLIB_PMP_AddressSet(PMP_ID_0, 1);

    while (PLIB_PMP_PortIsBusy(PMP_ID_0))
        continue;

    return PLIB_PMP_MasterReceive(PMP_ID_0);
#endif
}


#endif
