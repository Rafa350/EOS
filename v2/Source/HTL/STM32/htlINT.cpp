#include "HTL/htl.h"
#include "HTL/STM32/htlINT.h"


#if defined(STM32G0)
/// ----------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El vector.
/// \param    prioriti: La prioritat.
///
void htl::irq::setInterruptVectorPriority(
    VectorID vectorId,
    Priority priority) {

    uint32_t priorityGroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(
        static_cast<IRQn_Type>(vectorId),
        NVIC_EncodePriority(priorityGroup, static_cast<uint32_t>(priority), 0));
}
#elif defined(STM32F4) || defined(STM32F7)
/// ----------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El vector.
/// \param    prioriti: La prioritat.
/// \param    subPriority: La subprioritat.
///
void htl::irq::setInterruptVectorPriority(
    VectorID vectorId,
    Priority priority,
    SubPriority subPriority) {

    uint32_t priorityGroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(
        static_cast<IRQn_Type>(vectorID),
        NVIC_EncodePriority(priorityGroup, static_cast<uint32_t>(priority),
        		static_cast<uint32_t>(subPriority)));
}
#endif
