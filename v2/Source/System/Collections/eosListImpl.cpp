#include "eosAssert.h"
#include "System/Collections/eosList.h"
#include "eosListImpl.h"

#include <string.h>
#include <stdint.h>


using namespace eos;


const unsigned capacityDelta = 10;


#define __ALLOC(s)           (void*) new char[s]
#define __FREE(p)            delete [] (char*)p;


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial en numero d'elements.
///
GenericListImpl::GenericListImpl(
    unsigned _size,
    unsigned _initialCapacity):

    size(_size),
    count(0),
    capacity(0),
    initialCapacity(_initialCapacity),
    container(nullptr) {

    eosArgumentIsNotZero(size);

    // Reserva memoria pel contenidor
    //
    resize(initialCapacity);
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia. Copia la llista no els elements que conte.
/// \param list: La llista a copiar.
///
GenericListImpl::GenericListImpl(
    const GenericListImpl *impl):

    size(impl->size),
    count(0),
    capacity(0),
    initialCapacity(impl->capacity),
    container(nullptr) {

    // Reserva memoria pel contenidor
    //
    resize(initialCapacity);

    // Copia el contingut de la llista
    //
    if (impl->count > 0) {
        memcpy(container, impl->container, impl->count * size);
        count = impl->count;
    }
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericListImpl::~GenericListImpl() {

    // Allivera la memoria del contenidor
    //
    if (container != nullptr)
        __FREE(container);
}


/// \brief Afegeix un element al principi de la llista
/// \param element: Punter al element a afeigir.
///
void GenericListImpl::addFront(
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
void GenericListImpl::addBack(
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
void GenericListImpl::remove(
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
void GenericListImpl::clear() {

    // Comprova si hi han elements
    //
    if (container != nullptr) {

        // Allivera la memoria del contenidor
        //
        __FREE(container);
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
unsigned GenericListImpl::indexOf(
    const void *element) {

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
void *GenericListImpl::getAt(
    unsigned index) const {

    return index < count ? getPtr(index) : nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Obte l'adressa del element especificat.
/// \param index: L'index del element.
/// \return L'adresa del element.
///
void *GenericListImpl::getPtr(
    unsigned index) const {

    return (void*) ((unsigned) container + (index * size));
}


/// ----------------------------------------------------------------------
/// \brief Redimensiona el tamany del contenidor de dades.
/// \param newCapacity: Numero d'elements.
///
void GenericListImpl::resize(
    unsigned newCapacity) {

    // Comprova si cal aumentar la capacitat.
    //
    if (capacity < newCapacity) {

        // Salva un punter al contenidor actual
        //
        void *ptr = container;

        // Reserva memoria per un nou contenidor
        //
        container = __ALLOC(newCapacity * size);

        // Comprova si hi havia un contenidor previ
        //
        if (ptr != nullptr) {

            // opia les dades de l'antic contenidor al nou
            //
            memcpy(container, ptr, count);

            // Allivera l'antic contenidor
            //
            __FREE(ptr);
        }

        capacity = newCapacity;
    }
}
