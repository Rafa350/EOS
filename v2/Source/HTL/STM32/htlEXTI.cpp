#include "HTL/htl.h"
#include "HTL/STM32/htlEXTI.h"
#include "HTL/STM32/htlGPIO.h"


using namespace htl;
using namespace htl::exti;


unsigned internal::Activator::_activated = 0;


static void extiSetPort(uint32_t lineNum, htl::gpio::PortID portID);
static void extiSetMode(uint32_t lineNum, Mode mode);
static void extiSetEdge(uint32_t lineNum, Edge edge);



/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    lineID: Identificador de la linia.
///
EXTILine::EXTILine(
	LineID lineID) :

	_lineNum {uint32_t(lineID)} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza la linia d'interrupcio externa.
/// \param    portID: El port.
/// \param    mode: El modus event/interrupt
/// \param    edge: El flanc.
///
void EXTILine::initialize(
	htl::gpio::PortID portID,
	Mode mode,
	Edge edge) {

	activate();

	extiSetPort(_lineNum, portID);
	extiSetMode(_lineNum, mode);
	extiSetEdge(_lineNum, edge);
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio.
///
void EXTILine::deinitialize() {

	deactivate();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les interrupcions.
///
void EXTILine::interruptService() {

	uint32_t mask = 1 << _lineNum;

    #if defined(EOS_PLATFORM_STM32G0)

	// Procesa la interrupcio del flanc negatiu
	//
	if (EXTI->FPR1 & mask) {
		EXTI->FPR1 = mask;
	}

	// Procesa la interrupcio del flanc positiu
	//
	if (EXTI->RPR1 & mask) {
		EXTI->RPR1 = mask;
	}

    #else
    #error "Unknown platform"
    #endif
}


/// ----------------------------------------------------------------------
/// \brief    Asigna el port a la linia GPIO
/// \param    lineNUm: El numero de linia.
/// \param    portID: El identificador del port.
///
static void extiSetPort(
	uint32_t lineNum,
	htl::gpio::PortID portID) {

	#if defined(EOS_PLATFORM_STM32G0)

	/// Asigna el port GPIO a la linia EXTI
	//
    uint32_t tmp = EXTI->EXTICR[lineNum >> 2u];
    tmp &= ~(EXTI_EXTICR1_EXTI0 << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03u)));
    tmp |= ((uint32_t)portID << (EXTI_EXTICR1_EXTI1_Pos * (lineNum & 0x03u)));
    EXTI->EXTICR[lineNum >> 2u] = tmp;

	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el modus.
/// \param    lineNum: El numero de linia.
/// \param    mode: El modus.
///
static void extiSetMode(
	uint32_t lineNum,
	Mode mode) {

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == Mode::interrupt) || (mode == Mode::all))
		EXTI->IMR1 |= 1 << lineNum;
	else
		EXTI->IMR1 &= ~(1 << lineNum);

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == Mode::event) || (mode == Mode::all))
		EXTI->EMR1 |= 1 << lineNum;
	else
		EXTI->EMR1 &= ~(1 << lineNum);

	#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre IMR (Interrupt Mask Register);
	//
	if ((mode == EXTIMode::interrupt) || (mode == EXTIMode::all))
		EXTI->IMR |= 1 << uint32_t(line_);
	else
		EXTI->IMR &= ~(1 << uint32_t(line_));

	// Configura el registre EMR (Event Mask Register);
	//
	if ((mode == EXTIMode::event) || (mode == EXTIMode::all))
		EXTI->EMR |= 1 << uint32_t(line_);
	else
		EXTI->EMR &= ~(1 << uint32_t(line_));


	#else
		#error "Unknown platform"
	#endif
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el flanc.
/// \param    lineID: El identificador de la linmia.
/// \param    edge: El flanc.
///
void extiSetEdge(
	uint32_t lineNum,
	Edge edge) {

	#if defined(EOS_PLATFORM_STM32G0)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((edge == Edge::rissing) || (edge == Edge::all))
		EXTI->RTSR1 |= 1 << lineNum;
	else
		EXTI->RTSR1 &= ~(1 << lineNum);

	// Configura el registre FTSR1 (Falling Trigger Selection Register)
	//
	if ((edge == Edge::falling) || (edge == Edge::all))
		EXTI->FTSR1 |= 1 << lineNum;
	else
		EXTI->FTSR1 &= ~(1 << lineNum);

	#elif defined(EOS_PLATFORM_STM32F4) || defined(EOS_PLATFORM_STM32F7)

	// Configura el registre RTSR (Rising Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::rissing) || (trigger == EXTITrigger::all))
		EXTI->RTSR |= 1 << uint32_t(line_);
	else
		EXTI->RTSR &= ~(1 << uint32_t(line_));

	// Configura el registre FTSR (Falling Trigger Selection Register)
	//
	if ((trigger == EXTITrigger::falling) || (trigger == EXTITrigger::all))
		EXTI->FTSR |= 1 << uint32_t(line_);
	else
		EXTI->FTSR &= ~(1 << uint32_t(line_));

	#else
		#error "Unknown platform"
	#endif
}
