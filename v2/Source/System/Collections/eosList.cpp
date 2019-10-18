#include "eos.h"
#include "eosAssert.h"
#include "OSAL/osalHeap.h"
#include "System/Collections/eosList.h"
#include <string.h>


/// ----------------------------------------------------------------------
/// \brief    Obte memoria per un contenidor.
/// \param    capacity: Capacitat del contenidor.
/// \param    elementSize: Tamany del element.
/// \return   L'adressa del contenidor.
///
void *eos::allocContainer(
	unsigned capacity,
	unsigned elementSize) {

    return osalHeapAlloc(nullptr, capacity * elementSize);
}


/// ----------------------------------------------------------------------
/// \brief    Allivera la memoria d'un contenidor.
/// \param    container: El contenidor.
///
void eos::freeContainer(
	void *container) {

	osalHeapFree(nullptr, container);
}


/// ----------------------------------------------------------------------
/// \brief    Canvia la capacitat d'un contenidor.
/// \param    oldContainer: El contenidor.
/// \param    oldCapacity: La capcitat actual del contenidor.
/// \param    newCapacity: La nova capcitat del contenidor.
/// \param    count: El numero d'elements que conte el contenidor.
/// \param    elementSize: El tamany de cada element.
/// \return   L'adressa del nou contenidor.
///
void *eos::resizeContainer(
	void *oldContainer,
	unsigned oldCapacity,
	unsigned newCapacity,
	unsigned count,
	unsigned elementSize) {

	void *newContainer = oldContainer;

    // Comprova si cal aumentar la capacitat.
    //
    if (oldCapacity < newCapacity) {

        // Reserva memoria per un nou contenidor
        //
        newContainer = allocContainer(newCapacity, elementSize);

        // Comprova si hi havia un contenidor previ
        //
        if (oldContainer != nullptr) {

            // Copia les dades de l'antic contenidor al nou
            //
            memcpy(newContainer, oldContainer, count * elementSize);

            // Allivera l'antic contenidor
            //
            freeContainer(oldContainer);
        }
    }

    return newContainer;
}


/// ----------------------------------------------------------------------
/// \brief    Inserta un element en un contenidor.
/// \params   container: El contenidor.
/// \param    count: Numero d'elements en el contenidor.
/// \param    position: Posicio d'insercio.
/// \param    element: L'element a insertar.
/// \param    elementSize: Tamany del element.
///
void eos::insertElement(
	void *container,
	unsigned count,
	unsigned position,
	void *element,
	unsigned elementSize) {

	// TODO
}


/// ----------------------------------------------------------------------
/// \brief    Elimina un element d'un contenidor.
/// \params   container: El contenidor.
/// \param    count: Numero d'elements en el contenidor.
/// \param    position: Posicio d'insercio.
/// \param    elementSize: Tamany del element.
///
void eos::removeElement(
	void *container,
	unsigned count,
	unsigned position,
	unsigned elementSize) {

	// TODO
}

/*
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
    container(nullptr) {

    // Copia el contingut de la llista
    //
    if (other.count > 0) {
        resize(other.count);
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
        osalHeapFree(NULL, container);
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
        osalHeapFree(NULL, container);
        container = nullptr;
        count = 0;
        capacity = 0;

        // Reserva memoria en el contenidor
        //
        resize(0);
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
/// \brief    Obte el punter al primer element de la llista.
/// \return   El punter.
///
void *GenericList::getFront() const {

	return count > 0 ? getPtr(0) : nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Obte el punter al ultim element de la llista.
/// \return   El punter.
///
void *GenericList::getBack() const {

	return count > 0 ? getPtr(count - 1) : nullptr;
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
        container = static_cast<char*>(osalHeapAlloc(NULL, newCapacity * size));

        // Comprova si hi havia un contenidor previ
        //
        if (ptr != nullptr) {

            // opia les dades de l'antic contenidor al nou
            //
            memcpy(container, ptr, count);

            // Allivera l'antic contenidor
            //
            osalHeapFree(NULL, ptr);
        }

        capacity = newCapacity;
    }
}


void GenericList::copy(
    void *dst, 
    void *src, 
    unsigned count) {
    
}
*/
