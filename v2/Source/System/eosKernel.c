#include "eos.h"

#include "HardwareProfile.h"

// Harmony
#include "peripheral/int/plib_int.h"
#include "peripheral/pcache/plib_pcache.h"
#include "peripheral/bmx/plib_bmx.h"


extern void appInitialize(void);


static void __attribute__((nomips16)) PerformanceConfig( 
    unsigned sysclk) {
    
    bool int_flag = false;
    register unsigned long tmp;

    /* Set kseg0 coherency algorithm to "cacheable, non-coherent, write-back, 
     * write-allocate. This is needed for the prefetch buffer */
    asm("mfc0 %0,$16,0" :  "=r"(tmp));
    tmp = (tmp & ~7) | 3;
    asm("mtc0 %0,$16,0" :: "r" (tmp));

    /* Set the PFM wait states based on the system clock */
    #if defined(PLIB_PCACHE_ExistsWaitState)
    if (PLIB_PCACHE_ExistsWaitState(PCACHE_ID_0))
    {
        int ws; /* number of wait states */
        if (sysclk <= 30000000)
            ws = 0;
        else if (sysclk <= 60000000)
            ws = 1;
        else
            ws = 2;

        /* Interrupts must be disabled when changing wait states */
        int_flag = (bool)(PLIB_INT_GetStateAndDisable( INT_ID_0 ) & 0x01);

        PLIB_PCACHE_WaitStateSet(PCACHE_ID_0, ws);

        if (int_flag)
        {
            PLIB_INT_Enable(INT_ID_0);
            int_flag = false;
        }
    }
    #endif // defined(PLIB_PCACHE_ExistsWaitState)

    /* Interrupts must be disabled when enabling the Prefetch Cache Module */
    int_flag = (bool)(PLIB_INT_GetStateAndDisable( INT_ID_0 ) & 0x01);

    /* Enable Prefetch Cache Module */
    #if defined(PLIB_PCACHE_ExistsPrefetchEnable)
    if (PLIB_PCACHE_ExistsPrefetchEnable(PCACHE_ID_0))
    {
        PLIB_PCACHE_PrefetchEnableSet(PCACHE_ID_0, PLIB_PCACHE_PREFETCH_ENABLE_ALL);
    }
    #endif

    /* Set the SRAM wait states to zero */
    #if defined (PLIB_BMX_ExistsDataRamWaitState)
    if (PLIB_BMX_ExistsDataRamWaitState(BMX_ID_0))
    {
        PLIB_BMX_DataRamWaitStateSet(BMX_ID_0, PLIB_BMX_DATA_RAM_WAIT_ZERO);
    }            
    #endif
    if (int_flag)
    {
        PLIB_INT_Enable(INT_ID_0);
    }
}


/*************************************************************************
 *
 *       Inicialitza el sistema
 *
 *       Funcio:
 *           void eosInitialize() 
 *
 *************************************************************************/

void eosInitialize() {
    
    // Inicialitzacio del sistema
    //
    PerformanceConfig(CLOCK_SYSTEM_HZ);

    // Inicialitza les interrupcions
    //
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    
    // Desactiva els ports analogics
    //
    AD1PCFG = 0xFFFF;
}



void __main(void) {
    
    eosInitialize();
    appInitialize();
    eosStartScheduler();
}