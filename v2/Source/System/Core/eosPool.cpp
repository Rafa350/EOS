#include "eos.hpp"
#include "system/Core/eosMemory.hpp"
#include "System/Core/eosTask.hpp"


using namespace eos;


typedef struct __eosPool {   // Pool
    unsigned maxItems;       // -Numero maxim d'items en el pool
    unsigned itemSize;       // -Tamsny de cada item
    uint8_t *items;          // -Buffer de memoria
} eosPool;

typedef struct {             // Capcelera dels items del pool
    union {
        bool allocated;      // -Indica si esta en us
        uint32_t dummy;      // -Espai per alinear a 32 bits
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
    
    unsigned itemSize = (sizeof(ItemHeader) + elementSize + 7) & ~0x7;

    eosPoolHandle hPool = (eosPoolHandle) eosHeapAlloc(nullptr, sizeof(eosPool) + itemSize * maxElements);
    if (hPool != nullptr) {

        hPool->itemSize = itemSize;
        hPool->maxItems = maxElements;
        hPool->items = (uint8_t*) hPool + sizeof(eosPool);

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
    
    void *p = NULL;
        
    Task::enterCriticalSection();

    unsigned i;
    unsigned ii = (hPool->itemSize) * hPool->maxItems;
    for (i = 0; i < ii; i += hPool->itemSize) {
        ItemHeader *item = (ItemHeader*) &hPool->items[i];
        if (!item->allocated) {
            item->allocated = true;
            p = (uint8_t*) item + sizeof(ItemHeader);
            break;
        }
    }

    Task::exitCriticalSection();

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
    
    Task::enterCriticalSection();
    
    ((ItemHeader*)((uint8_t*) p - sizeof(ItemHeader)))->allocated = false;

    Task::exitCriticalSection();
}
