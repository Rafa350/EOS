#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halEXTI.h"
#include "HAL/PIC32/halINT.h"
#include "sys/attribs.h"

#include "peripheral/int/plib_int.h"

typedef struct {
    EXTICallbackFunction function;
    void *pParam;
} CallbackInfo;

static CallbackInfo callback[HAL_EXTI_LINE_COUNT] = {
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL }
};


extern void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SOFT) isrCNWrapper(void);


/// ----------------------------------------------------------------------
/// \brief Configura la linia d'interrupcio externa.
/// \param line: Numero de linia d'interrupcio.
/// \param options: Opcions.
///
static void setupLine(
    EXTILine line,
	EXTIOptions options) {
    
    eosAssert((line >= 0) && (line <= HAL_EXTI_LINE_COUNT));
    
    // Activa pullup
    //
    if ((options & HAL_EXTI_PULL_MASK) == HAL_EXTI_PULL_UP)
        CNPUESET = 1 << line; // PullUp Enable = 1
    else
        CNPUECLR = 1 << line; // PullUp Enable = 0;

    // Activa la linia individual
    //
    if ((options & HAL_EXTI_ENABLE_MASK) == HAL_EXTI_ENABLE_YES)
        CNENSET = 1 << line; // Enable = 1;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins d'entrada d'interrupcio.
/// \param pInfo: Llista linies a configurar.
/// \param count: Numero de linies en la llista.
///
void halEXTIInitializeLines(
    const EXTIInitializeLineInfo *pInfo, 
    unsigned count) {
    
	eosAssert(pInfo != NULL);
	eosAssert(count > 0);

    // Activa el modul
    //
    CNCONbits.ON = 1; // ON = 1
    
    // Configura cada linia
    //
    for (unsigned i = 0; i < count; i++) {
		const EXTIInitializeLineInfo *p = &pInfo[i];              
		setupLine(p->line, p->options);
    }    
    
    // Activa les interrupcions
    //
    IFS1bits.CNIF = 0; // Interrupt Flag = 0
    IEC1bits.CNIE = 1; // Interrupt Enable = 1
    
    PLIB_INT_VectorPrioritySet(INT_ID_0, _CHANGE_NOTICE_VECTOR, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, _CHANGE_NOTICE_VECTOR, INT_SUBPRIORITY_LEVEL0);    
}


/// ----------------------------------------------------------------------
/// \brief Autoritza la generacio d'interrupcions en aquesta linia.
/// \param line: La linia.
///
void halEXTIEnableLine(
    EXTILine line) {
    
    eosAssert((line >= 0) && (line <= HAL_EXTI_LINE_COUNT));

    CNENSET = 1 << line; // Enable = 1
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la generacio d'interrupcions en aquesta linia.
/// \param line: La linia.
///
void halEXTIDisableLine(
    EXTILine line) {
    
    eosAssert((line >= 0) && (line <= HAL_EXTI_LINE_COUNT));

    CNENCLR = 1 << line; // Enable = 0;
}


/// ----------------------------------------------------------------------
/// \brief Asigna la funcio callback per gestionar les interrupcions
/// \param line: Linea EXTI a configurar.
/// \param function: La funcio.
///
void halEXTISetCallbackFunction(
    EXTILine line, 
    EXTICallbackFunction function, 
    void *pParam) {

	eosAssert((line >= HAL_EXTI_LINE_0) && (line <= HAL_EXTI_LINE_15));

	callback[line].function = function;
	callback[line].pParam = pParam;   
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio
/// 
void isrCNHandler(void) {
    
    if (IFS1bits.CNIF) {    
    
        // Obte la linia que ha generat la interrupcio
        //
        EXTILine line = 0;
    
        // Crida a la funcio callback
        //
        if (callback[line].function != NULL)
            callback[line].function(line, callback[line].pParam);

        // Borra el flag d'interrupcio
        //
        IFS1bits.CNIF = 0; // Interrupt Flag = 0;
    }
}
