#include "system/eosMemory.h"
#include "System/eosTask.h"


typedef struct __eosPool {   // Pool
    unsigned maxItems;       // -Numero maxim d'items en el pool
    unsigned itemSize;       // -Tamsny de cada item
    BYTE *items;             // -Buffer de memoria
} eosPool;

typedef struct {             // Capcelera dels items del pool
    union {
        bool allocated;      // -Indica si esta en us
        UINT32 dummy;        // -Espai per alinear a 32 bits
    };
} ItemHeader;


/*************************************************************************
 *
 *       Crea un pool de memoria
 * 
 *       Funcio:
 *           eosPoolHandle eosPoolCreate(
 *               unsigned elementSize,
 *               unsigned maxElements) 
 * 
 *       Entrada:
 *           elementSize: Tamany de cada element
 *           maxElelemts: Numero maxim d'elements en el pool
 * 
 *       Retorn:
 *           Handler del pool
 * 
 *************************************************************************/

eosPoolHandle eosPoolCreate(
    unsigned elementSize,
    unsigned maxElements) {
    
    eosDebugVerify(elementSize > 0);
    eosDebugVerify(numElements > 0);

    unsigned itemSize = (sizeof(ItemHeader) + elementSize + 7) & ~0x7;

    eosPoolHandle hPool = (eosPoolHandle) eosAlloc(sizeof(eosPool) + itemSize * maxElements);
    if (hPool != NULL) {

        hPool->itemSize = itemSize;
        hPool->maxItems = maxElements;
        hPool->items = (BYTE*) hPool + sizeof(eosPool);

        unsigned i;
        unsigned ii = (hPool->itemSize) * hPool->maxItems;
        for (i = 0; i < ii; i += hPool->itemSize) {
            ItemHeader *item = (ItemHeader*) &hPool->items[i];
            item->allocated = false;
        }
    }
    
    return hPool;
}


/*************************************************************************
 *
 *       Obte un bloc de memoria del pool
 *
 *       Funcio:
 *           void *eosPoolAlloc(
 *               eosPoolHandle hPool) 
 * 
 *       Entrada:
 *           hPool: Handler del pool
 * 
 *       Retorn:
 *           Punter al bloc de memoria. NULL en cas d'error
 * 
 *************************************************************************/

void *eosPoolAlloc(
    eosPoolHandle hPool) {
    
    eosDebugVerify(hPool != NULL);
    
    void *p = NULL;
    
    eosTaskSuspendAll();

    unsigned i;
    unsigned ii = (hPool->itemSize) * hPool->maxItems;
    for (i = 0; i < ii; i += hPool->itemSize) {
        ItemHeader *item = (ItemHeader*) &hPool->items[i];
        if (!item->allocated) {
            item->allocated = true;
            p = (BYTE*) item + sizeof(ItemHeader);
            break;
        }
    }
    
    eosTaskResumeAll();

    return p;
}


/*************************************************************************
 *
 *       Allibera el bloc de memoria obtingut previament amb
 *       la funcio eosPoolAlloc
 * 
 *       Funcio:
 *           void eosPoolFree(
 *               void *p) 
 * 
 *       Entrada:
 *           p: Punter al bloc de memoria a alliverar
 *
 *************************************************************************/

void eosPoolFree(
    void *p) {
    
    eosDebugVerify(p != NULL);

    eosTaskSuspendAll();
    
    ((ItemHeader*)((BYTE*) p - sizeof(ItemHeader)))->allocated = false;
    
    eosTaskResumeAll();
}
