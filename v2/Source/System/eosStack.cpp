#include "System/eosStack.hpp"
#include "System/eosTask.hpp"
#include "System/eosMemory.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/// ----------------------------------------------------------------------
/// \brief Constructor
/// \param size: Tamany de cada element
/// ºparam initialCapacity: Capacitat inicial
///
GenericStack::GenericStack(
    unsigned _size,
    unsigned initialCapacity):
    size(_size), 
    capacity(0),
    count(0),
    container(nullptr) {
    
    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericStack::~GenericStack() {
    
    if (container != nullptr)
        eosHeapFree(container);
}


/// ----------------------------------------------------------------------
/// \brief Inserta un element en la pila.
/// \param element: El element a insertar.
///
void GenericStack::genericPush(
    void *element) {
        
    Task::enterCriticalSection();
    
    if (count + 1 >= capacity)
        resize(capacity + capacityDelta);
    
    void *ptr = getPtr(count);
    memcpy(ptr, element, size);
    count += 1;
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Exteru el primer element de la pila
///
void GenericStack::genericPop() {
    
    Task::enterCriticalSection();

    if (count > 0) 
        count -= 1;    

    Task::exitCriticalSection();
}


/// --------------------------------------------------------------------
/// \brief Obte el punter al primer element de la pila
/// \return El punter al element. nullptr si la pila es buida.
///
void *GenericStack::genericTop() const {
    
    return count > 0 ? getPtr(count - 1) : nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element.
///
void *GenericStack::getPtr(
    unsigned index) const {

    return  (void*) ((unsigned) container + (index * size));    
}


/// ----------------------------------------------------------------------
/// \brief Redimensiona el buffer de dades per encabir nous elements.
/// \param newCapacity: Nova capacitat de la pila.
///
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