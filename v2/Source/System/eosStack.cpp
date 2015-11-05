#include "System/eosStack.hpp"
#include "System/eosTask.hpp"
#include "System/eosMemory.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           GenericStack::GenericStack(
 *               unsigned size,
 *               unsigned initialCapacity) 
 *
 *       Entrada:
 *           size           : Tamany de cada element
 *           initialCapacity: Capacitat inicial
 * 
 *************************************************************************/

GenericStack::GenericStack(
    unsigned _size,
    unsigned initialCapacity):
    size(_size), 
    capacity(0),
    count(0),
    container(nullptr) {
    
    resize(initialCapacity);
}


/*************************************************************************
 *
 *       Destructor
 *
 *       Funcio:
 *           GenericStack::~GenericStack()
 *
 *************************************************************************/

GenericStack::~GenericStack() {
    
    if (container != nullptr)
        eosHeapFree(container);
}


void GenericStack::pushElement(
    void *element) {
        
    Task::enterCriticalSection();
    
    if (count + 1 >= capacity)
        resize(capacity + capacityDelta);
    
    void *ptr = getPtr(count);
    memcpy(ptr, element, size);
    count += 1;
    
    Task::exitCriticalSection();
}


void GenericStack::popElement() {
    
    Task::enterCriticalSection();

    if (count > 0) 
        count -= 1;    

    Task::exitCriticalSection();
}


void *GenericStack::topElement() const {
    
    return count > 0 ? getPtr(count - 1) : nullptr;
}



/*************************************************************************
 *
 *       Obte l'adressa del element especificat
 * 
 *       Funcio:
 *           void *GenericStack::getPtr(
 *               unsigned index) const
 * 
 *       Entrada:
 *           index: L'index del element
 * 
 *       Retorn:
 *           L'adresa del element
 *
 *************************************************************************/

void *GenericStack::getPtr(
    unsigned index) const {

    return  (void*) ((unsigned) container + (index * size));    
}


/*************************************************************************
 *
 *       Redimensiona el buffer de dades
 *
 *       Funcio:
 *           void GenericStack::resize(
 *               unsigned newCapacity) 
 *
 *       Entrada:
 *           newCapacity : Nova capacitat de la pila
 *
 *************************************************************************/

void GenericStack::resize(
    unsigned newCapacity) {
    
    if (capacity < newCapacity) {
        void *ptr = container;
        container = eosHeapAlloc(nullptr, newCapacity * size);
        if (ptr != nullptr) {
            memcpy(container, ptr, capacity);
            eosHeapFree(ptr);
        }
        capacity = newCapacity;
    }
}