#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halEXTI.h"


typedef struct {
    EXTICallbackFunction function;
    void *pParam;
} CallbackInfo;


/// ----------------------------------------------------------------------
/// \brief Configura la linia d'interrupcio externa.
/// \param line: Numero de linia d'interrupcio.
/// \param options: Opcions.
///
static void SetupLine(
    EXTILine line,
	EXTIOptions options) {
    
    // Activa pullup
    //
    if ((options & HAL_EXTI_PULL_MASK) == HAL_EXTI_PULL_UP)
        CNPUESET = 1 << line;
    else
        CNPUECLR = 1 << line;    

    // Activa la interrupcio en la linia
    //
    if ((options & HAL_EXTI_ENABLE_MASK) == HAL_EXTI_ENABLE_YES)
        CNENSET = 1 << line;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins d'entrada d'interrupcio.
/// \param pInfo: Llista linies a configurar.
/// \param count: Numero de linies en la llista.
///
void halEXTIInitializeLines(
    const EXTIInitializeLineInfo *pInfo, 
    unsigned count) {
    
    // Activa el modul
    //
    CNCONbits.ON = 1;
    
    // Configura cada linia
    //
    for (unsigned i; i < count; i++) {
		const EXTIInitializeLineInfo *p = &pInfo[i];              
		SetupLine(p->line, p->options);
    }    
}


/// ----------------------------------------------------------------------
/// \brief Autoritza la generacio d'interrupcions en aquesta linia.
/// \param line: La linia.
///
void halEXTIEnableLine(
    EXTILine line) {
    
    CNENSET = 1 << line;
}


/// ----------------------------------------------------------------------
/// \brief Desactiva la generacio d'interrupcions en aquesta linia.
/// \param line: La linia.
///
void halEXTIDisableLine(
    EXTILine line) {
    
    CNENCLR = 1 << line;
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio
/// 
void isrCNHandler(void) {
    
}
