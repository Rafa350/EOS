#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosContainer.h"
#include <string.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Obte memoria per un contenidor.
/// \param    capacity: Capacitat del contenidor.
/// \param    elementSize: Tamany del element.
/// \return   L'adressa del contenidor.
///
void* Container::alloc(
	unsigned capacity,
	unsigned elementSize) {

    eosAssert(capacity > 0);
    eosAssert(elementSize > 0);

    return osalHeapAlloc(nullptr, capacity * elementSize);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera la memoria d'un contenidor.
/// \param    container: El contenidor.
///
void Container::free(
	void* container) {

	osalHeapFree(nullptr, container);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia la capacitat d'un contenidor.
/// \param    container: El contenidor.
/// \param    oldCapacity: La capcitat actual del contenidor.
/// \param    newCapacity: La nova capcitat del contenidor.
/// \param    count: El numero d'elements que conte el contenidor.
/// \param    elementSize: El tamany de cada element.
/// \return   L'adressa del nou contenidor.
///
void *Container::resize(
	void* container,
	unsigned oldCapacity,
	unsigned newCapacity,
	unsigned count,
	unsigned elementSize) {

	void *newContainer = container;

    // Comprova si cal aumentar la capacitat.
    //
    if (oldCapacity < newCapacity) {

        // Reserva memoria per un nou contenidor
        //
        newContainer = Container::alloc(newCapacity, elementSize);

        // Comprova si hi havia un contenidor previ
        //
        if (container != nullptr) {

            // Copia les dades de l'antic contenidor al nou
            //
            memmove(newContainer, container, count * elementSize);

            // Allivera l'antic contenidor
            //
            Container::free(container);
        }
    }

    return newContainer;
}
