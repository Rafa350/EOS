#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "OSAL/osalKernel.h"
#include "System/Collections/eosStack.h"
#include <string.h>


using namespace eos;


const unsigned capacityDelta = 10;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param size: Tamany de cada element
/// \param initialCapacity: Capacitat inicial
///
GenericStack::GenericStack(
    unsigned size,
    unsigned initialCapacity):

    capacity(0),
    count(0),
    size(size),
    container(nullptr) {
    
    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericStack::~GenericStack() {
    
    if (container != nullptr)
        osalHeapFree(NULL, container);
}


/// ----------------------------------------------------------------------
/// \brief Inserta un element en la pila.
/// \param element: El element a insertar.
///
void GenericStack::push(
    const void *element) {
    
    eosAssert(element != nullptr);
        
    osalEnterCritical();
    
    if (count + 1 >= capacity)
        resize(capacity + capacityDelta);
    
    void *ptr = getPtr(count);
    memcpy(ptr, element, size);
    count += 1;
    
    osalExitCritical();
}


/// ----------------------------------------------------------------------
/// \brief Exteru el primer element de la pila
///
void GenericStack::pop() {
    
    eosAssert(count > 0);
    
    osalEnterCritical();

    if (count > 0) 
        count -= 1;    

    osalExitCritical();
}


/// --------------------------------------------------------------------
/// \brief Obte el punter al primer element de la pila
/// \return El punter al element. nullptr si la pila es buida.
///
void *GenericStack::top() const {
    
    return count > 0 ? getPtr(count - 1) : nullptr;
}


/// ---------------------------------------------------------------------
/// \brief Obte el primer element de la pila.
/// \param El punter al buffer on deixar l'element.
///
void GenericStack::top(const void *element) const {
    
    if (count > 0)
        memcpy(top(), element, size);
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element.
///
void *GenericStack::getPtr(
    unsigned index) const {

    return (void*) ((unsigned) container + (index * size));    
}


/// ----------------------------------------------------------------------
/// \brief Redimensiona el buffer de dades per encabir nous elements.
/// \param newCapacity: Nova capacitat de la pila.
///
void GenericStack::resize(
    unsigned newCapacity) {
    
    if (capacity < newCapacity) {
        void *ptr = container;
        container = osalHeapAlloc(NULL, newCapacity * size);
        if (ptr != nullptr) {
            memcpy(container, ptr, capacity);
            osalHeapFree(NULL, ptr);
        }
        capacity = newCapacity;
    }
}
