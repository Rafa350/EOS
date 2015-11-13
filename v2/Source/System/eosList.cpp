#include "System/eosList.hpp"
#include "System/eosMemory.hpp"
#include "System/eosTask.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           GenericList::GenericList(
 *               unsigned size,
 *               unsigned initialCapacity) 
 * 
 *       Entrada:
 *           size           : Tamany en bytes de cada element
 *           initialCapacity: Capacitat inicial de la llista
 *
 *************************************************************************/

GenericList::GenericList(
    unsigned _size,
    unsigned initialCapacity):
    size(_size),
    count(0),
    capacity(0),
    container(nullptr) {
    
    resize(initialCapacity);
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           GenericList::~GenericList() 
 *
 *************************************************************************/

GenericList::~GenericList() {
    
    if (container != nullptr)
        eosHeapFree(container);
}


/*************************************************************************
 *
 *       Afegeix un element a la llista
 * 
 *       Funcio:
 *           unsigned GenericList::addElement(
 *               void *element) 
 * 
 *       Entrada:
 *           element: Punter al element a afeigir
 * 
 *       Retorn:
 *           El index del element
 *
 *************************************************************************/

unsigned GenericList::addElement(
    void *element) {
    
    Task::enterCriticalSection();
    
    if (count + 1 >= capacity)
        resize(capacity + capacityDelta);
    
    void *ptr = getPtr(count);
    memcpy(ptr, element, size);
    count += 1;
    
    Task::exitCriticalSection();
    
    return count - 1;
}


/*************************************************************************
 *
 *       Elimina un element de la llista
 * 
 *       Funcio:
 *           void GenericList::removeElement(
 *               unsigned index) 
 * 
 *       Entrada:
 *           index: Index del element a eliminar
 *
 *************************************************************************/

void GenericList::removeElement(
    unsigned index) {
    
    Task::enterCriticalSection();
    
    void *ptr = getPtr(index);
    //memmmove(ptr, element, elementSize);
    
    Task::exitCriticalSection();
}


/*************************************************************************
 *
 *       Obte un element de la llista
 * 
 *       Funcio:
 *          void *GenericList::getElement(
 *              unsigned index) const 
 *
 *       Entrada:
 *           index: Index del element
 * 
 *       Retorn:
 *           Punter al element
 *
 *************************************************************************/

void *GenericList::getElement(
    unsigned index) const {
    
    Task::enterCriticalSection();
    void *p = index < count ? getPtr(index) : nullptr;
    Task::exitCriticalSection();
    
    return p;
}


/*************************************************************************
 *
 *       Obte l'adressa del element especificat
 * 
 *       Funcio:
 *           void *GenericList::getPtr(
 *               unsigned index) const
 * 
 *       Entrada:
 *           index: L'index del element
 * 
 *       Retorn:
 *           L'adresa del element
 *
 *************************************************************************/

void *GenericList::getPtr(
    unsigned index) const {

    return  (void*) ((unsigned) container + (index * size));    
}


/*************************************************************************
 *
 *       Redimensiona el buffer de dades
 *
 *       Funcio:
 *           void GenericList::resize(
 *               unsigned newCapacity) 
 *
 *       Entrada:
 *           newCapacity : Numero d'elements 
 *
 *************************************************************************/

void GenericList::resize(
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