#include "System/eosList.hpp"
#include "System/eosMemory.hpp"
#include "System/eosTask.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial de la llista.
///
GenericList::GenericList(
    unsigned _size,
    unsigned initialCapacity):
    size(_size),
    count(0),
    capacity(0),
    container(nullptr) {
    
    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericList::~GenericList() {
    
    if (container != nullptr)
        eosHeapFree(container);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la llista.
/// \param element: Punter al element a afeigir.
/// \return El index del element.
///
unsigned GenericList::genericAdd(
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


/// ----------------------------------------------------------------------
/// \brief Elimina un element de la llista.
/// \param index: Index del element a eliminar.
///
void GenericList::genericRemove(
    unsigned index) {
    
    Task::enterCriticalSection();
    
    void *ptr = getPtr(index);
    //memmmove(ptr, element, elementSize);
    
    Task::exitCriticalSection();
}


/// ----------------------------------------------------------------------
/// \brief Obte el puneter al un element de la llista.
/// \param index: Index del element:
/// \return Punter al element.
///
void *GenericList::genericGet(
    unsigned index) const {
    
    Task::enterCriticalSection();
    
    void *p = index < count ? getPtr(index) : nullptr;
    
    Task::exitCriticalSection();
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element
///
void *GenericList::getPtr(
    unsigned index) const {

    return  (void*) ((unsigned) container + (index * size));    
}


/// ----------------------------------------------------------------------
/// \brief Redimensiona el buffer de dades.
/// \param newCapacity : Numero d'elements.
///
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