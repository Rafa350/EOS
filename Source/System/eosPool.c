#define __EOS_POOL_INTERNAL
#include "system/eosPool.h"


typedef struct __eosPool {
    unsigned maxItems;
    unsigned itemSize;
    BYTE *items;
} Pool;

typedef struct {
    bool allocated;
} ItemHeader;


eosHPool eosPoolCreate(unsigned elementSize, unsigned maxElements) {

    unsigned itemSize = sizeof(ItemHeader) + ((elementSize + 3) & 0xFFFFFFFC);

    eosHPool hPool = (eosHPool) eosAlloc(sizeof(Pool) + itemSize * maxElements);
    if (hPool == NULL)
        return  NULL;

    hPool->itemSize = itemSize;
    hPool->maxItems = maxElements;
    hPool->items = (BYTE*) hPool + sizeof(Pool);

    unsigned i;
    unsigned ii = (hPool->itemSize) * hPool->maxItems;
    for (i = 0; i < ii; i += hPool->itemSize) {
        ItemHeader *item = (ItemHeader*) &hPool->items[i];
        item->allocated = false;
    }

    return hPool;
}


void *eosPoolAlloc(eosHPool hPool) {

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


void eosPoolFree(void *p) {

    ((ItemHeader*)p)->allocated = false;
}
