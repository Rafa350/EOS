#include "system/eosMemory.h"


typedef struct __eosPool {
    unsigned maxItems;
    unsigned itemSize;
    BYTE *items;
} eosPool;

typedef struct {
    bool allocated;
} ItemHeader;


eosPoolHandle eosPoolCreate(
    unsigned elementSize,
    unsigned maxElements) {

    unsigned itemSize = sizeof(ItemHeader) + ((elementSize + 3) & 0xFFFFFFFC);

    eosPoolHandle hPool = (eosPoolHandle) eosAlloc(sizeof(eosPool) + itemSize * maxElements);
    if (hPool == NULL)
        return  NULL;

    hPool->itemSize = itemSize;
    hPool->maxItems = maxElements;
    hPool->items = (BYTE*) hPool + sizeof(eosPool);

    unsigned i;
    unsigned ii = (hPool->itemSize) * hPool->maxItems;
    for (i = 0; i < ii; i += hPool->itemSize) {
        ItemHeader *item = (ItemHeader*) &hPool->items[i];
        item->allocated = false;
    }

    return hPool;
}


void *eosPoolAlloc(
    eosPoolHandle hPool) {

    unsigned i;
    unsigned ii = (hPool->itemSize) * hPool->maxItems;
    for (i = 0; i < ii; i += hPool->itemSize) {
        ItemHeader *item = (ItemHeader*) &hPool->items[i];
        if (!item->allocated) {
            item->allocated = true;
            return (BYTE*) item + sizeof(ItemHeader);
        }
    }

    return NULL;
}


void eosPoolFree(
    void *p) {

    ((ItemHeader*)((BYTE*) p - sizeof(ItemHeader)))->allocated = false;
}
