#include "eos.h"
#include "stdlib.h"


/*************************************************************************
 *
 *       Obte un bloc de memoria
 *
 *       Funcio:
 *           void *eosMemAlloc(unsigned size)
 *
 *       Entrada:
 *           size: El tamany del bloc en bytes
 *
 *       Retorn:
 *           L'adressa del bloc de momoria. NULL en cas d'error
 *
 *************************************************************************/

void *eosMemAlloc(unsigned size) {

    return malloc(size);
}


/*************************************************************************
 *
 *       Allibera un bloc de memoria
 *
 *       Funcio:
 *           void eosMemFree(void *p)
 *
 *       Entrada:
 *           p: Adressa del bloc a alliberar
 *
 *************************************************************************/

void eosMemFree(void *p) {

    free(p);
}
