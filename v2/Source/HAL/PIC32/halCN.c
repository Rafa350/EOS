#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halCN.h"
#include "HAL/PIC32/halGPIO.h"
#include "HAL/PIC32/halINT.h"
#include "sys/attribs.h"


typedef struct {
    CNInterruptFunction function;
    void* params;
} CallbackInfo;


static CallbackInfo callback[HAL_CN_LINE_COUNT] = {
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
/// \brief    Configura la linia d'interrupcio externa.
/// \param    line: Numero de linia d'interrupcio.
/// \param    options: Opcions.
///
static void setupLine(
    CNLine line,
	CNOptions options) {
    
    eosAssert((line >= 0) && (line <= HAL_CN_LINE_COUNT));
       
    // Activa pullup
    //
    if ((options & HAL_CN_PULL_MASK) == HAL_CN_PULL_UP)
        CNPUESET = 1 << line; // PullUp Enable = 1
    else
        CNPUECLR = 1 << line; // PullUp Enable = 0;

    // Activa la linia individual
    //
    if ((options & HAL_CN_ENABLE_MASK) == HAL_CN_ENABLE_YES)
        CNENSET = 1 << line; // Enable = 1;
}


/// ----------------------------------------------------------------------
/// \brief   Inicialitza un pìn.
/// \param   line: Identificador de la linia.
/// \param   options: Opcions.
///
void halCNInitializeLine(CNLine line, CNOptions options) {

    // Activa el modul.
    //
    CNCONbits.ON = 1; // ON = 1

    // Configura la linia
    //
    setupLine(line, options)    ;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins d'entrada d'interrupcio.
/// \param    info: Llista linies a configurar.
/// \param    count: Numero de linies en la llista.
///
void halCNInitializeLines(
    const CNInitializeLineInfo* info, 
    unsigned count) {
    
	eosAssert(info != NULL);
	eosAssert(count > 0);

    // Activa el modul
    //
    CNCONbits.ON = 1; // ON = 1
    
    // Configura cada linia
    //
    for (unsigned i = 0; i < count; i++) {
		const CNInitializeLineInfo* p = &info[i];          
		setupLine(p->line, p->options);
    }    
}


/// ----------------------------------------------------------------------
/// \brief    Autoritza la generacio d'interrupcions en aquesta linia.
/// \param    line: La linia.
///
void halCNEnableLine(
    CNLine line) {
    
    eosAssert((line >= 0) && (line <= HAL_CN_LINE_COUNT));

    CNENSET = 1 << line; // Enable = 1
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva la generacio d'interrupcions en aquesta linia.
/// \param    line: La linia.
///
void halCNDisableLine(
    CNLine line) {
    
    eosAssert((line >= 0) && (line <= HAL_CN_LINE_COUNT));

    CNENCLR = 1 << line; // Enable = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la funcio callback per gestionar les interrupcions
/// \param    line: Linea CN a configurar.
/// \param    function: La funcio.
/// \param    params: Es parametres de la funcio.
///
void halCNSetInterruptFunction(
    CNLine line, 
    CNInterruptFunction function, 
    void* params) {

	eosAssert((line >= HAL_CN_LINE_0) && (line <= HAL_CN_LINE_15));

	callback[line].function = function;
	callback[line].params = params;   
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la prioritat de la interrupcio.
/// \param    priority: Prioritat.
/// \param    subPriority: Subprioritat.
///
void halCNSetInterruptPriority(
    unsigned priority, 
    unsigned subPriority) {
    
    IPC6bits.CNIP = priority; 
    IPC6bits.CNIS = subPriority;
}


/// ----------------------------------------------------------------------
/// \brief    Autoritza les interrrupcions
///
void halCNEnableInterrupts() {
    
    IEC1bits.CNIE = 1; // Interrupt Enable = 1
}


/// ----------------------------------------------------------------------
/// \brief    Desautoritza les interrrupcions
///
void halCNDisableInterrupts() {
    
    IEC1bits.CNIE = 0; // Interrupt Enable = 0
}


/// ----------------------------------------------------------------------
/// \brief Handler de la interrupcio
/// 
void isrCNHandler(void) {
    
    if (IFS1bits.CNIF) {    
        
        uint32_t newA = PORTA;
        uint32_t newB = PORTB;
        uint32_t newC = PORTC;
        uint32_t newD = PORTD;
        uint32_t newE = PORTE;
        uint32_t newF = PORTF;
        uint32_t newG = PORTG;
    
        // Obte la linia que ha generat la interrupcio
        //
        CNLine line = 0;
    
        // Crida a la funcio callback
        //
        if (callback[line].function != NULL)
            callback[line].function(line, callback[line].params);

        // Borra el flag d'interrupcio
        //
        IFS1bits.CNIF = 0; // Interrupt Flag = 0;
    }
}
