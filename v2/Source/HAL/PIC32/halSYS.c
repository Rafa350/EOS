#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halINT.h"
#include "HAL/PIC32/halSYS.h"

#include "peripheral/pcache/plib_pcache.h"
#include "peripheral/bmx/plib_bmx.h"


/// ----------------------------------------------------------------------
/// \brief    Inicialitza les interrupcions.
///
static void initializeInterrupcions() {

    // Interrupcions en modus multicector
    //
    INTCONSET = _INTCON_MVEC_MASK;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el cache
//
static void __attribute__((nomips16)) initializeCache(
    unsigned sysclk) {

    // Set kseg0 coherency algorithm to "cacheable, non-coherent, write-back,
    // write-allocate. This is needed for the prefetch buffer
    //
    register unsigned long tmp;
    asm("mfc0 %0,$16,0" :  "=r"(tmp));
    tmp = (tmp & ~7) | 3;
    asm("mtc0 %0,$16,0" :: "r" (tmp));

    // Set the PFM wait states based on the system clock
    //
    #if defined(PLIB_PCACHE_ExistsWaitState)
    if (PLIB_PCACHE_ExistsWaitState(PCACHE_ID_0)) {
        int ws; /* number of wait states */
        if (sysclk <= 30000000)
            ws = 0;
        else if (sysclk <= 60000000)
            ws = 1;
        else
            ws = 2;

        PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, ws);
    }
    #endif

    // Enable Prefetch Cache Module
    //
    #if defined(PLIB_PCACHE_ExistsPrefetchEnable)
    if (PLIB_PCACHE_ExistsPrefetchEnable(PCACHE_ID_0))
        PLIB_PCACHE_PrefetchEnableSet(PCACHE_ID_0, PLIB_PCACHE_PREFETCH_ENABLE_ALL);
    #endif

    // Set the SRAM wait states to zero
    //
    #if defined (PLIB_BMX_ExistsDataRamWaitState)
    if (PLIB_BMX_ExistsDataRamWaitState(BMX_ID_0))
        PLIB_BMX_DataRamWaitStateSet(BMX_ID_0, PLIB_BMX_DATA_RAM_WAIT_ZERO);
    #endif
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els ports
///
static void initializePorts() {

    // Tots els port com a digitals
    //
    AD1PCFGSET = 0x00FF;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza el sistema
///
void halSYSInitialize() {

    __halINTDisableInterrupts();

    initializeInterrupcions();
    initializePorts();
    initializeCache(halSYSGetSystemClockFrequency());

    __halINTEnableInterrupts();
}
