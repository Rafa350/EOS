#include "System/eosVector.hpp"
#include "FreeRTOS.h"
#include "task.h"


using namespace eos;


/*************************************************************************
 *
 *       Constructor
 * 
 *       Funcio:
 *           GenericVector::GenericVector(
 *               unsigned itemSize,
 *               unsigned maxItems) 
 * 
 *       Entrada:
 *           itemSize: Tamany en bytes de cada item
 *           maxItems: Numero maxim d'items en el vector
 *
 *************************************************************************/

GenericVector::GenericVector(
    unsigned itemSize,
    unsigned maxItems) {
    
    this->itemSize = itemSize;
    this->maxItems = maxItems;
    
    data = pvPortMalloc(itemSize * maxItems);
}


/*************************************************************************
 *
 *       Destructor
 * 
 *       Funcio:
 *           GenericVector::~GenericVector() 
 *
 *************************************************************************/

GenericVector::~GenericVector() {
    
    vPortFree(data);
}


void GenericVector::set(unsigned index, void* data) {
    
    void *ptr = (void*)((unsigned) data + (itemSize * index));
    memcpy(ptr, data, itemSize);    
}
    

void GenericVector::get(unsigned index, void* data) {

    void *ptr = (void*)((unsigned) data + (itemSize * index));
    memcpy(data, ptr, itemSize);       
}
