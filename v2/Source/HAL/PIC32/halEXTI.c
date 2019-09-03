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
    
  
    
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza els pins d'entrada d'interrupcio.
/// \param pInfo: Llista d'elements deconfiguracio.
/// \param count: Numero d'elements de la llista.
///
void halEXTIInitializePins(
    const EXTIInitializePinInfo *pInfo, 
    unsigned count) {
    
    for (uint_fast8_t i; i < count; i++) {

		const EXTIInitializePinInfo *p = &pInfo[i];              
		SetupLine(p->, p->options);
    }    
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio
/// 
void isrCNHandler(void) {
    
}
