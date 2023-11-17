#include "HTL/htl.h"
#include "HTL/STM32/htlINT.h"


using namespace htl;
using namespace htl::irq;


/// ----------------------------------------------------------------------
/// \brief    Configura la prioritat d'un vector d'interrupcio.
/// \param    vectorID: El vector.
/// \param    prioriti: La prioritat.
/// \param    subPriority: La subprioritat.
///
void htl::irq::setInterruptVectorPriority(
    VectorID vectorID,
    Priority priority,
    SubPriority subPriority) {

    uint32_t priorityGroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(
        static_cast<IRQn_Type>(vectorID),
        NVIC_EncodePriority(
            priorityGroup,
            static_cast<uint32_t>(priority),
            static_cast<uint32_t>(subPriority)));

}
