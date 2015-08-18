#include "System/eosMemory.h"
#include "FreeRTOS.h"


typedef struct __eosHeap {   
} eosHeap;


/*************************************************************************
 *
 *       Crea un heap
 *
 *       Funcio:
 *           eosHeapHandle eosHeapCreate(
 *               unsigned size)
 *
 *       Entrada:
 *           size: Tamany del heap en bytes
 *
 *       Retorn:
 *           Handler del heap
 *
 *************************************************************************/

eosHeapHandle eosHeapCreate(
    unsigned size) {
    
    eosDebugVerify(size > 0);

    return NULL;
}


/*************************************************************************
 *
 *       Obte un bloc de memoria del heap
 *
 *       Funcio:
 *           void *eosHeapAlloc(
 *               eosHeapHandle hHeap,
 *               unsigned size)
 *
 *       Entrada:
 *           hHeap: Handler del heap. 
 *           size : Tamany del bloc de memoria
 *
 *       Retorn:
 *           Punter al bloc de memoria. NULL en cas d'error
 *
 *************************************************************************/

void *eosHeapAlloc(
    eosHeapHandle hHeap,
    unsigned size) {
    
    eosDebugVerify(size > 0);

    return pvPortMalloc(size);
}


/*************************************************************************
 *
 *       Allibera un bloc de memoria del heap
 *
 *       Funcio:
 *           void eosHeapFree(
 *               void *p)
 *
 *       Entrada:
 *           p: Punter al bloc de memoria
 *
 *************************************************************************/

void eosHeapFree(
    void *p) {
    
    eosDebugVerify(p != NULL);

    vPortFree(p);
}
