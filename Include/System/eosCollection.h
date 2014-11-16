#ifndef __EOS_COLLECTION_H
#define	__EOS_COLLECTION_H

#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_COLLECTION_INTERNAL
struct __eosCollection {};
#endif

typedef struct __eosCollection *eosHCollection;

typedef struct {                  // Parametres d'inicialitzacio de la cua
    unsigned maxItems;            // -Numero maxim d'items en la cua
    unsigned itemSize;            // -Tamany de cada item
} eosCollectionCreateParams;


eosResult eosCollectionCreate(eosCollectionCreateParams *params, eosHCollection *hCollection);
eosResult eosCollectionDestroy(eosHCollection hCollection);

eosResult eosCollectionAdd(eosHCollection hCollection, void *data);
eosResult eosCollectionRemove(eosHCollection hCollection, void *data);

eosResult eosCollectionEnumerate(eosHCollection hCollection);
eosResult eosCollectionEnumerateNext(eosHCollection hCollection, void *data);


#endif
