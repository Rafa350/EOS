#include "System/eosMemory.h"


#ifdef eos_OPTION_FREERTOS
#include "FreeRTOS.h"
#endif


/*************************************************************************
 *
 *       Obte un bloc de memoria
 *
 *       Funcio:
 *           void *eosAlloc(
 *               unsigned size)
 *
 *       Entrada:
 *           size       : El tamany del bloc en bytes
 *
 *       Retorn:
 *           L'adressa del bloc de momoria. NULL en cas d'error
 *
 *************************************************************************/

#ifndef eosAlloc
void *  eosAlloc(unsigned size) {

#ifdef eos_OPTION_FREERTOS
    return pvPortMalloc(size);
#else
    return malloc(size);
#endif
}
#endif


/*************************************************************************
 *
 *       Obte una bloc de memoria per una cadena
 *
 *       Funcio:
 *           void* eosAllocString(
 *               const char *str)
 *
 *       Entrada:
 *           str        : La cadena a memoritzar
 *
 *       Retorn:
 *           Punter al bloc de memoria, NULL en cas d'error
 *
 *************************************************************************/

void *eosAllocString(const char* str) {

    int size = strlen(str) + 1;
    return memcpy(eosAlloc(size), str, size);
}


/*************************************************************************
 *
 *       Modifica un bloc de memoria
 *
 *       Funcio:
 *           void* eosRealloc(
 *              void *p,
 *              unsigned size)
 *
 *       Entrada:
 *           p          : Punter al bloc a modificar
 *           size       : Tamany el bytes del bloc
 *
 *       Retorn:
 *           Punter al bloc de memoria, NULL en cas d'error
 *
 *************************************************************************/

void* eosRealloc(void *p, unsigned size) {

#ifdef eos_OPTION_FREERTOS
    void *p2 = pvPortMalloc(size);
    if (p2) {
        memcpy(p2, p, size);
        vPortFree(p);
    }
    return p2;
#else
    return realloc(p, size);
#endif
}


/*************************************************************************
 *
 *       Allibera un bloc de memoria
 *
 *       Funcio:
 *           void eosFree(
 *               void *p)
 *
 *       Entrada:
 *           p          : Adressa del bloc a alliberar
 *
 *************************************************************************/

#ifndef eosFree
void eosFree(void *p) {

#ifdef eos_OPTION_FREERTOS
    vPortFree(p);
#else
    free(p);
#endif
}
#endif


/*************************************************************************
 *
 *       Crea un bloc de memoria
 *
 *       Funcio:
 *           eosResult eosMemoryCreate(
 *               unsigned size,
 *               eosHandle *hMemory)
 *
 *       Entrada:
 *           size       : Tamany del bloc en bytes
 *
 *       Sortida:
 *           hMemory    : El handler del bloc de momoria
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosMemoryCreate(unsigned size, eosHandle *hMemory) {

    if (size == 0)
        return eos_ERROR_PARAM_NULL;
    if (hMemory == NULL)
        return eos_ERROR_PARAM_NULL;

    *hMemory = (eosHandle) eosAlloc(size);
    return (*hMemory == NULL) ? eos_ERROR_ALLOC : eos_RESULT_SUCCESS;
}


/*************************************************************************
 *
 *       Destrueix un bloc de memoria
 *
 *       Funcio:
 *           eosResult eosMemoryDestroy(
 *               eosHandle hMemory)
 *
 *       Entrada:
 *           hMemory    : El handler del bloc de momoria
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosMemoryDestroy(eosHandle hMemory) {

    if (hMemory == NULL)
        return eos_ERROR_PARAM_NULL;

    eosFree((void*) hMemory);

    return eos_RESULT_SUCCESS;
}
