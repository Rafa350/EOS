#include "eos.h"
#include "eosAssert.h"
#include "System/Collections/eosList.h"
#include "OSAL/osalHeap.h"


#include <string.h>
#include <stdint.h>


using namespace eos;


const unsigned capacityDelta = 10;



/// ----------------------------------------------------------------------
/// \brief Reserva un bloc de memoria.
/// \param[in] blockSize: Tamany del bloc en bytes.
/// \return L'adressa del bloc de memoria.
///
static void *memAlloc(
    unsigned blockSize) {
    
    return osalHeapAlloc(NULL, blockSize);
}


/// ----------------------------------------------------------------------
/// \brief Allivera un bloc de memoria.
/// \param[in] pBlock: Adressa del bloc de memoria.
///
static void memFree(
    void *pBlock) {
    
    osalHeapFree(NULL, pBlock);
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial en numero d'elements.
///
GenericList::GenericList(
    unsigned size,
    unsigned initialCapacity):

    size(size),
    count(0),
    capacity(0),
    initialCapacity(initialCapacity),
    container(nullptr) {

    eosAssert(size > 0);

    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia. Copia la llista no els elements que conte.
/// \param list: La llista a copiar.
///
GenericList::GenericList(
    const GenericList &other):

    size(other.size),
    count(0),
    capacity(0),
    initialCapacity(other.capacity),
    container(nullptr) {

    // Reserva memoria pel contenidor
    //
    resize(initialCapacity);

    // Copia el contingut de la llista
    //
    if (other.count > 0) {
        memcpy(container, other.container, other.count * size);
        count = other.count;
    }
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericList::~GenericList() {

    // Allivera la memoria del contenidor
    //
    if (container != nullptr)
        memFree(container);
}


/// \brief Afegeix un element al principi de la llista
/// \param element: Punter al element a afeigir.
///
void GenericList::addFront(
    const void *element) {

    // Si no hi ha espai en el contenidor, el fa mes gran
    //
    if (count == capacity)
        resize(capacity + capacityDelta);

    void *ptr0 = getPtr(0);
    void *ptr1 = getPtr(1);

    // Fa espai al principi de la llista
    //
    memcpy(ptr1, ptr0, (count - 1) * size);

    // Copia l'element al contenidor
    //
    memcpy(ptr0, element, size);

    // Incrementa el contador d'elements
    //
    count += 1;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element al final de la llista.
/// \param element: Punter al element a afeigir.
///
void GenericList::addBack(
    const void *element) {

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
}


/// ----------------------------------------------------------------------
/// \brief Elimina un element de la llista.
/// \param index: Index del element a eliminar.
///
void GenericList::removeAt(
    unsigned index) {

    // Comprova si l'index es dins del rang
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
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els elements de la llista
///
void GenericList::clear() {

    // Comprova si hi han elements
    //
    if (container != nullptr) {

        // Allivera la memoria del contenidor
        //
        memFree(container);
        container = nullptr;
        count = 0;
        capacity = 0;

        // Reserva memoria en el contenidor
        //
        resize(initialCapacity);
    }
}


/// ----------------------------------------------------------------------
/// \brief Retorna l'index d'un element. Si esta repetit retorna el
///        primer que trobi des del principi de la llista.
/// \param element: L'element a buscar.
/// \return El index del element. UINT32_MAX en cas que no el trobi.
///
unsigned GenericList::indexOf(
    const void *element) const {

    bool result = UINT32_MAX;

    // Obte l'index del element, recorrent el contenidor fins
    // que el trobi
    //
    for (unsigned index = 0; index < count; index++) {
        if (!memcmp(getPtr(index), element, size)) {
            result = index;
            break;
        }
    }

    return result;
}


/// ----------------------------------------------------------------------
/// \brief Obte el punter a un element de la llista.
/// \param index: Index del element:
/// \return Punter al element.
///
void *GenericList::get(
    unsigned index) const {

    return index < count ? getPtr(index) : nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element.
///
void *GenericList::getPtr(
    unsigned index) const {

    return (void*) ((unsigned) container + (index * size));
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
        container = memAlloc(newCapacity * size);

        // Comprova si hi havia un contenidor previ
        //
        if (ptr != nullptr) {

            // opia les dades de l'antic contenidor al nou
            //
            memcpy(container, ptr, count);

            // Allivera l'antic contenidor
            //
            memFree(ptr);
        }

        capacity = newCapacity;
    }
}
