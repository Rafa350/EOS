#include "eos.h"

#ifdef __PIC32MX


#ifdef eosOPT_FREERTOS
#include "FreeRTOS.h"
#endif


/*************************************************************************
 *
 *       Obte un bloc de memoria
 *
 *       Funcio:
 *           void *eosAlloc(unsigned size)
 *
 *       Entrada:
 *           size: El tamany del bloc en bytes
 *
 *       Retorn:
 *           L'adressa del bloc de momoria. NULL en cas d'error
 *
 *************************************************************************/

#ifndef eosAlloc
void *eosAlloc(unsigned size) {

#ifdef eosOPT_FREERTOS
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
 *           void* eosAllocString(const char *str)
 *
 *       Entrada:
 *           str: La cadena a memoritzar
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
 *           void* eosRealloc(void *p, unsigned size)
 *
 *       Entrada:
 *           p   : Punter al bloc a modificar
 *           size: Tamany el bytes del bloc
 *
 *       Retorn:
 *           Punter al bloc de memoria, NULL en cas d'error
 *
 *************************************************************************/

void* eosRealloc(void *p, unsigned size) {

#ifdef eosOPT_FREERTOS
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
 *           void eosFree(void *p)
 *
 *       Entrada:
 *           p: Adressa del bloc a alliberar
 *
 *************************************************************************/

#ifndef eosFree
void eosFree(void *p) {

#ifdef eosOPT_FREERTOS
    vPortFree(p);
#else
    free(p);
#endif
}
#endif


#endif // ifdef(__PIC32MX)