#include "System/Core/eosMemory.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial de la llista.
///
GenericList::GenericList(
    unsigned _size,
    unsigned _initialCapacity):
    size(_size),
    initialCapacity(_initialCapacity),
    count(0),
    capacity(0),
    container(nullptr) {
    
    eosAssert(_size > 0, 0, "[GenericList::ctor] size > 0");
    
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
    
    eosAssert(element != nullptr, 0, "[GenericList::genericAdd] element != null")
    
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
    
    if (index < count) {
        
        Task::enterCriticalSection();

        if (index < count) {
            void *ptr = getPtr(index);
            memcpy(ptr, (const void*) ((char*) ptr + size), (count - index) * size);
            count--;
        }

        Task::exitCriticalSection();
    }
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els elements de la llista
///
void GenericList::genericClear() {
   
    if (container != nullptr) {

        Task::enterCriticalSection();
        
        if (container != nullptr) {
            eosHeapFree(container);
            count = 0;
            capacity = 0;
            resize(initialCapacity);
        }
        
        Task::exitCriticalSection();
    }
}


/// ----------------------------------------------------------------------
/// \brief Retorna l'index d'un element. Si esta repetit retorna el 
///        primer que trobi des del principi de la llista.
/// \param element: L'element a buscar.
/// \return El index del element. UINT32_MAX en cas que no el trobi.
///
unsigned GenericList::genericIndexOf(
    void *element) {
    
    eosAssert(element != nullptr, 0, "[GenericList::genericIndexOf] element != nullptr")
    
    bool result = UINT32_MAX;
    
    Task::enterCriticalSection();
    
    for (unsigned index = 0; index < count; index++) {
        if (!memcmp(getPtr(index), element, size)) {
            result = index;
            break;
        }
    }
    
    Task::exitCriticalSection();
    
    return result;
}


/// ----------------------------------------------------------------------
/// \brief Obte el punter a un element de la llista.
/// \param index: Index del element:
/// \return Punter al element.
///
void *GenericList::genericGet(
    unsigned index) const {
    
    eosAssert(index < count, 0, "[Genericist::genericGet] index < count");
    
    Task::enterCriticalSection();
    
    void *p = index < count ? getPtr(index) : nullptr;
    
    Task::exitCriticalSection();
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element.
///
void *GenericList::getPtr(
    unsigned index) const {
    
    return  (void*) ((unsigned) container + (index * size));    
}


/// ----------------------------------------------------------------------
/// \brief Redimensiona el buffer de dades.
/// \param newCapacity: Numero d'elements.
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