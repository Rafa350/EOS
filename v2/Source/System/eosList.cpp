#include "System/eosList.hpp"
#include "System/eosMemory.hpp"


using namespace eos;

const unsigned sizeDelta = 10;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           GenericList::GenericList(
 *               unsigned elementSize) 
 * 
 *       Entrada:
 *           elementSize: Tamany en bytes de cada element
 *
 *************************************************************************/

GenericList::GenericList(
    unsigned elementSize) {
    
    this->elementSize = elementSize;
    this->count = 0;
    this->size = 0;
    this->data = nullptr;
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
    
    if (data != nullptr)
        eosHeapFree(data);
}


/*************************************************************************
 *
 *       Afegeix un element a la llista
 * 
 *       Funcio:
 *           void GenericList::addElement(
 *               void *element) 
 * 
 *       Entrada:
 *           element: Punter al element a afeigir
 *
 *************************************************************************/

void GenericList::addElement(
    void *element) {
    
    if (count + 1 >= size)
        resize(size + sizeDelta);
    
    void *ptr = (void*) ((unsigned) data + (count * elementSize));
    memmove(ptr, element, elementSize);
    count += 1;
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
    
    void *ptr = (void*) ((unsigned) data + (index * elementSize));
    //memmove(ptr, element, elementSize);
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
    
    return (void*) ((unsigned) data + (index * elementSize));
}


/*************************************************************************
 *
 *       Redimensiona el buffer de dades
 *
 *       Funcio:
 *           void GenericList::resize(
 *               unsigned newSize) 
 *
 *       Entrada:
 *           newSize : Numero d'elements 
 *
 *************************************************************************/

void GenericList::resize(
    unsigned newSize) {
    
    if (size < newSize) {
        void *ptr = data;
        data = eosHeapAlloc(nullptr, newSize * elementSize);
        if (ptr != nullptr) {
            memmove(data, ptr, size);
            eosHeapFree(ptr);
        }
        size = newSize;
    }
}