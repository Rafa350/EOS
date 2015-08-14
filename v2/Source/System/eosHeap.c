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

    return pvPortMalloc(size);
}


/*************************************************************************
 *
 *       Obte una bloc de memoria per una cadena
 *
 *       Funcio:
 *           void* eosHealAllocString(
 *               eosHeapHandle hHeap,
 *               const char *str)
 *
 *       Entrada:
 *           hHeap: Handler del heap
 *           str  : La cadena a memoritzar
 *
 *       Retorn:
 *           Punter al bloc de memoria, NULL en cas d'error
 *
 *************************************************************************/

void *eosHeapAllocString(
    eosHeapHandle hHeap,
    const char* str) {

    unsigned size = strlen(str) + 1;
    return memcpy(eosHeapAlloc(hHeap, size), str, size);
}


/*************************************************************************
 *
 *       Modifica un bloc de memoria del heap
 *
 *       Funcio:
 *           void *eosHeapRealloc(
 *               eosHeapHandle hHeap,
 *               void *p,
 *               unsigned size)
 *
 *       Entrada:
 *           hHeap: Handler del heap
 *           p    : El bloc de momoria
 *           size : El nou tamany del bloc de memoria
 *
 *       Retorn:
 *           Punter al bloc de memoria. NULL en cas d'error
 *
 *************************************************************************/

void *eosHeapRealloc(
    eosHeapHandle hHeap,
    void *p,
    unsigned size) {

    void *np = eosHeapAlloc(hHeap, size);
    return np;
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

    vPortFree(p);
}
