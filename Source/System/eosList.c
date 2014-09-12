#include "System/eosList.h"
#include "System/eosMemory.h"


typedef struct __ITEM {           // Item de la llista
    struct __ITEM *prev;          // -Element anterior
    struct __ITEM *next;          // -Element posterior
    struct __LIST *list;          // -Llista a la que pertany
    void *data;                   // -Dades
} Item, *PItem;

typedef struct __LIST {           // Llista
    struct __ITEM *first;         // -Primer element
    struct __ITEM *last;          // -Ultim element
} List, *PList;


/*************************************************************************
 *
 *       Crea una llista
 *
 *       Funcio:
 *           eosResult eosListCreate(
 *               eosHandle *hList)
 *
 *       Sortida:
 *           hList      : Handler de la llista
 *
 *       Retorn:
 *           eor_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosListCreate(eosHandle *hList) {

    if (hList == NULL)
        return eos_ERROR_PARAMS;

    PList list = eosAlloc(sizeof(List));
    if (list == NULL)
        return eos_ERROR_ALLOC;

    list->first = NULL;
    list->last = NULL;
    
    *hList = (eosHandle) list;

    return eos_RESULT_SUCCESS;
}


eosResult eosListDestroy(eosHandle hList) {

    if (hList == NULL)
        return eos_ERROR_PARAMS;

    eosListEmpty(hList);
    eosFree(hList);
}


eosResult eosLisEmpty(eosHandle hList) {

    if (hList == NULL)
        return eos_ERROR_PARAMS;

    PList list = (PList) hList;

    PItem item = list->last;
    while (item) {
        PItem p = item;
        item = item->prev;
        eosFree(p);
    }

}

eosResult eosListAdd(eosHandle hList, void *data) {

    if (hList == NULL)
        return eos_ERROR_PARAMS;

    PList list = (PList) hList;

    PItem item = eosAlloc(sizeof(Item));
    if (item == NULL)
        return eos_ERROR_ALLOC;
    
    if (list->first == NULL) {
        list->first = item;
        list->last = item;
        item->next = NULL;
        item->prev = NULL;
    } 
    else {
        item->next = NULL;
        item->prev = list->last;
        list->last = item;
    }
    item->list = list;

    return eos_RESULT_SUCCESS;
}