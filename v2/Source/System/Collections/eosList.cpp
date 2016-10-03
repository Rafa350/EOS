#include "System/Core/eosTask.hpp"
#include "System/Collections/eosList.hpp"
#include "eosListImpl.hpp"


using namespace eos;


#define __ASSERT(cond, code, message) \
                             eosAssert(cond, code, message);

#define __LOCK()             Task::enterCriticalSection()
#define __UNLOCK()           Task::exitCriticalSection()


/// ----------------------------------------------------------------------
/// \brief Constructor.
/// \param size: Tamany en bytes de cada element.
/// \param initialCapacity: Capacitat inicial en numero d'elements.
///
GenericList::GenericList(
    unsigned size,
    unsigned initialCapacity):
    impl(new GenericListImpl(size, initialCapacity)) {
}


/// ----------------------------------------------------------------------
/// \brief Constructor copia. Copia la llista no els elements que conte.
/// \param list: La llista a copiar.
///
GenericList::GenericList(
    const GenericList &list):
    impl(new GenericListImpl(list.impl)) {
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
GenericList::~GenericList() {
    
    delete impl;
}


/// \brief Afegeix un element al principi de la llista
/// \param element: Punter al element a afeigir.
///
void GenericList::addFront(
    const void *element) {

    __ASSERT(element != nullptr, 0, "[GenericList::genericAdd] element != null");

    __LOCK();
    impl->addFront(element);
    __UNLOCK();
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un element al final de la llista.
/// \param element: Punter al element a afeigir.
///
void GenericList::addBack(
    const void *element) {
    
    __ASSERT(element != nullptr, 0, "[GenericList::genericAdd] element != null");
    
    __LOCK();
    impl->addBack(element);
    __UNLOCK();
}


/// ----------------------------------------------------------------------
/// \brief Elimina un element de la llista.
/// \param index: Index del element a eliminar.
///
void GenericList::remove(
    unsigned index) {
    
    __ASSERT(index < impl->getCount(), 0, "[GenericList::genericRemove] index < count");
    
    __LOCK();
    impl->remove(index);
    __UNLOCK();
}


/// ----------------------------------------------------------------------
/// \brief Elimina tots els elements de la llista
///
void GenericList::clear() {
   
    __LOCK();
    impl->clear();
    __UNLOCK();
}


/// ----------------------------------------------------------------------
/// \brief Retorna l'index d'un element. Si esta repetit retorna el 
///        primer que trobi des del principi de la llista.
/// \param element: L'element a buscar.
/// \return El index del element. UINT32_MAX en cas que no el trobi.
///
unsigned GenericList::indexOf(
    const void *element) {
    
    __ASSERT(element != nullptr, 0, "[GenericList::genericIndexOf] element != nullptr")

    unsigned index;

    __LOCK();
    index = impl->indexOf(element);
    __UNLOCK();
    
    return index;
}


/// ----------------------------------------------------------------------
/// \brief Obte el punter a un element de la llista.
/// \param index: Index del element:
/// \return Punter al element.
///
void *GenericList::get(
    unsigned index) const {
    
    __ASSERT(index < impl->getCount(), 0, "[Genericist::genericGet] index < count");

    void *p;
    __LOCK();
    p = impl->getAt(index);
    __UNLOCK();
    
    return p;
}


/// ----------------------------------------------------------------------
/// \brief Retorna el numero d'elements en la llista.
/// \return El nombre d'elements.
///
unsigned GenericList::getCount() const {
    
    return impl->getCount();
}


/// ----------------------------------------------------------------------
/// \bried Indica si la llista es buida.
/// \return True si la llista es buida.
///
bool GenericList::isEmpty() const {

    return impl->isEmpty();
}