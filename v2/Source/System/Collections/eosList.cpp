#include "System/Core/eosMemory.hpp"
#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"


using namespace eos;


const unsigned capacityDelta = 10;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial en numero d'elements.
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
    
    // Reserva memoria pel contenidor
    //
    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Destructor
///
GenericList::~GenericList() {
    
    // Allivera la memoria del contenidor
    //
    if (container != nullptr)
        eosHeapFree(container);
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element a la llista.
/// \param element: Punter al element a afeigir.
/// \return El index del element.
///
unsigned GenericList::genericAdd(
    const void *element) {
    
    eosAssert(element != nullptr, 0, "[GenericList::genericAdd] element != null");
    
    // Entra en la seccio critica
    //
    Task::enterCriticalSection();
    
    // Si no hi ha espai en el contenidor, el fa mes gran
    //
    if (count == capacity)
        resize(capacity + capacityDelta);
    
    // Copia el element al contenidor
    //
    void *ptr = getPtr(count);
    memcpy(ptr, element, size);
    
    // Incrementa el contador d'elements
    //
    count += 1;
    
    // Surt de la seccio critica
    //
    Task::exitCriticalSection();
    
    return count - 1;
}


/// ----------------------------------------------------------------------
/// \brief Elimina un element de la llista.
/// \param index: Index del element a eliminar.
///
void GenericList::genericRemove(
    unsigned index) {
    
    // Comprova si l'index es dins del rang
    //
    if (index < count) {
        
        // Entra en la seccio critica
        //
        Task::enterCriticalSection();

        // Comprova de nou, si l'index es dins del rang
        //
        if (index < count) {
            
            // Elimina l'element del contenidor
            //
            void *ptr = getPtr(index);
            memcpy(ptr, (const void*) ((char*) ptr + size), (count - index - 1) * size);
            
            // Decrementa el contador d'elements
            //
            count--;
        }

        // Surt de la seccio critica
        //
        Task::exitCriticalSection();
    }
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els elements de la llista
///
void GenericList::genericClear() {
   
    // Comprovas si hi han elements en el contenidor
    //
    if (container != nullptr) {

        // Entra en la seccio critica
        //
        Task::enterCriticalSection();
        
        // Comprova de nou, si hi han elements
        //
        if (container != nullptr) {
            
            // Allivera la memoria del contenidor
            //
            eosHeapFree(container);
            container = nullptr;
            count = 0;
            capacity = 0;
            
            // Reserva memoria en el contenidor
            //
            resize(initialCapacity);
        }
        
        // Surt de la seccio critica
        //
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
    const void *element) {
    
    eosAssert(element != nullptr, 0, "[GenericList::genericIndexOf] element != nullptr")
    
    bool result = UINT32_MAX;
    
    // Entra en la seccio critica
    //
    Task::enterCriticalSection();
  
    // Obte l'index del element, recorrent el contenidor fins
    // que el trobi
    //
    for (unsigned index = 0; index < count; index++) {
        if (!memcmp(getPtr(index), element, size)) {
            result = index;
            break;
        }
    }
    
    // Surt de la seccio critica
    //
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
    
    // Entra en la seccio critica
    //
    Task::enterCriticalSection();
    
    // Calcula el punter al element
    //
    void *p = index < count ? getPtr(index) : nullptr;
   
    // Surt de la seccio critica
    //
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
/// \brief Redimensiona el tamany del contenidor de dades.
/// \param newCapacity: Numero d'elements.
///
void GenericList::resize(
    unsigned newCapacity) {

    // Comprova si cal aumentar la capacitat. 
    //    
    if (capacity < newCapacity) {
        
        // Salva un punter al contenidor actual
        //
        void *ptr = container;
        
        // Reserva memoria per un nou contenidor
        //
        container = eosHeapAlloc(nullptr, newCapacity * size);
        
        // Comprova si hi havia un contenidor previ
        //
        if (ptr != nullptr) {
            
            // opia les dades de l'antic contenidor al nou
            //
            memcpy(container, ptr, count);
            
            // Allivera l'antic contenidor
            //
            eosHeapFree(ptr);
        }
                
        capacity = newCapacity;
    }
}