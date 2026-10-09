module;


#include "hardware.h"


export module Eos.Hardware.Interrupts;


export import Eos.Hardware.Interrupts.__VECTORS;

import Eos.Configuration.Platform;
import Eos.Types;


namespace eos::hardware::interrupts {

    namespace internal  {

        enum class Priority_Type1 {p0, p1, p2, p3};
        enum class Priority_Type2 {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};

        enum class SubPriority_Type1 {sp0};
	    enum class SubPriority_Type2 {sp0, sp1, sp2, sp3};

        template <PlatformID platformId_>
        struct PlatformTraits {
        };

        template <>
        struct PlatformTraits<PlatformID::STM32_G0B1_RE> {
    		using Priority = Priority_Type1;
            using SubPriority = SubPriority_Type1;
        };
    }

    export class Irq: private StaticClass<Irq> {
        private:
            using PlatformTraits  = internal::PlatformTraits<Platform::id>;

        public:
            using VectorID = internal::VectorID;
            using Priority = PlatformTraits::Priority;
            using SubPriority = PlatformTraits::SubPriority;

		    static inline void setInterruptPriority(VectorID vectorId, Priority priority);
		    static void setInterruptPriority(VectorID vectorId, Priority priority, SubPriority subPriority);

		    static void enableInterrupt(VectorID vectorId);
		    static void disableInterrupt(VectorID vectorId);

            static bool getInterruptState();
            static void enableInterrupts();
            static void disableInterrupts();
            static void restoreInterrupts(bool state);
    };
}


using namespace eos;
using namespace eos::hardware::interrupts;


/// --------------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El vector.
/// \param    prioriti: La prioritat.
///
void Irq::setInterruptPriority(
    VectorID vectorId,
    Priority priority) {

    setInterruptPriority(vectorId, priority, SubPriority::sp0);
}


/// ---------------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El vector.
/// \param    prioriti: La prioritat.
/// \param    subPriority: La subprioritat.
///
void Irq::setInterruptPriority(
    VectorID vectorId,
    Priority priority,
    SubPriority subPriority) {

    UInt32 priorityGroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(
        static_cast<IRQn_Type>(vectorId),
        NVIC_EncodePriority(
            priorityGroup,
            static_cast<UInt32>(priority),
        	static_cast<UInt32>(subPriority)));
}


/// --------------------------------------------------------------------------
/// @brief    Habilita una interrrupcio.
/// @param    vectorId : El identificador del vector d'interrupcio.
///
void Irq::enableInterrupt(
	VectorID vectorId) {

	NVIC_EnableIRQ(static_cast<IRQn_Type>(vectorId));
}


/// --------------------------------------------------------------------------
/// @brief    Desabilita una interrrupcio.
/// @param    vectorId : El identificador del vector d'interrupcio.
///
void Irq::disableInterrupt(
	VectorID vectorId) {

	NVIC_DisableIRQ(static_cast<IRQn_Type>(vectorId));
}


bool Irq::getInterruptState() {

    return __get_PRIMASK() == 0;
}


void Irq::enableInterrupts() {

    __enable_irq();
}


void Irq::disableInterrupts() {

    __disable_irq();
}


void Irq::restoreInterrupts(
    bool state) {

    if (state)
        __enable_irq();
}
