#include "eos.h"
#include "eosAssert.h"
#include "HAL/PIC32/halCN.h"
#include "sys/attribs.h"


typedef struct {
    CNInterruptFunction isrFunction;
    void* isrParams;
} CNData;


static CNData dataTbl[HAL_CN_LINE_COUNT] = {
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
    else
        CNENCLR = 1 << line; // Enable = 0;
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
    setupLine(line, options);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza els pins d'entrada d'interrupcio.
/// \param    info: Llista linies a configurar.
/// \param    count: Numero de linies en la llista.
///
void halCNInitializeLines(
    const CNInitializeLineInfo *info,
    uint32_t count) {

	eosAssert(info != NULL);
	eosAssert(count > 0);

    // Activa el modul
    //
    CNCONbits.ON = 1; // ON = 1

    // Configura cada linia
    //
    for (uint32_t i = 0; i < count; i++) {
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
/// \brief    Asigna la funcio d'interrupcio.
/// \param    line: Linea CN a configurar.
/// \param    function: La funcio.
/// \param    params: Es parametres de la funcio.
///
void halCNSetInterruptFunction(
    CNLine line,
    CNInterruptFunction function,
    void* params) {

	eosAssert((line >= HAL_CN_LINE_0) && (line <= HAL_CN_LINE_15));

	dataTbl[line].isrFunction = function;
	dataTbl[line].isrParams = params;
}


/// ----------------------------------------------------------------------
/// \brief    Activa les interrupcions
///
void halCNEnableInterrupts() {

    IEC1bits.CNIE = 1;
}


/// ----------------------------------------------------------------------
/// \brief    Desactiva les interrupcions.
/// \return   True si estava previament activada.
///
uint32_t halCNDisableInterrupts() {

    uint32_t state = IEC1bits.CNIE == 1;
    IEC1bits.CNIE = 0;
    return state;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el indicador d'interrupcio.
/// \return   El valor del indicador.
///
bool halCNGetInterruptFlag() {

    return __halCNGetInterruptSourceFlag();
}


/// ----------------------------------------------------------------------
/// \brief    Borra el indicador d'interrupcio.
///
void halCNClearInterruptFlags() {

    __halCNClearInterruptSourceFlag();
}


/// ----------------------------------------------------------------------
///
void halCNInterruptHandler() {

    if (__halCNGetInterruptSourceFlag()) {

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
        CNData* data = &dataTbl[line];
        if (data->isrFunction != NULL)
            data->isrFunction(line, data->isrParams, HAL_CN_EVENT_TRIGGER);

        // Borra el flag d'interrupcio
        //
        __halCNClearInterruptSourceFlag();
    }
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el vector _CHANGE_NOTICE_VECTOR
///
void isrCNHandler(void) {

    halCNInterruptHandler();
}
