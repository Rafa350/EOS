#define __EOS_COLLECTION_INTERNAL
#include "System/eosCollection.h"
#include "System/eosMemory.h"


typedef struct __eosCollection {       // Dades de la coleccio
    unsigned itemSize;                 // -Tamany de cada item en bytes
    unsigned maxItems;                 // -Numero maxim d'items
    unsigned numItems;                 // -Numero actual d'items
    BYTE *start;                       // -Punter al inici de la coleccio
} Collection;


/*************************************************************************
 *
 *       Crea una colleccio
 *
 *       Funcio:
 *           eosResult eosCollectionCreate(
 *               eosCollectionCreateParams *params,
 *               eosHCollection *hCollection)
 *
 *       Entrada:
 *           params     : Parametres de creacio de la coleccio
 *
 *       Sortida:
 *           hCollection: Handler de la coleccio
 *
 *       Retorn:
 *           eos_RESULT_SUCCESS si tot es correcte
 *
 *************************************************************************/

eosResult eosCollectionCreate(eosCollectionCreateParams *params,  eosHCollection *hCollection) {
    
#ifdef eos_OPTION_CheckInputParams
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hCollection == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    unsigned collectionSize = params->maxItems * params->itemSize;

    eosHCollection collection = eosAlloc(sizeof(Collection) + collectionSize);
    if (collection == NULL)
        return eos_ERROR_ALLOC;
    
    collection->itemSize = params->itemSize;
    collection->maxItems = params->maxItems;
    collection->numItems = 0;
    collection->start = (BYTE*) collection + sizeof(Collection);

    *hCollection = (eosHCollection) collection;

    return eos_RESULT_SUCCESS;
}


eosResult eosCollectionDestroy(eosHCollection hCollection) {

#ifdef eos_OPTION_CheckInputParams
    if (hCollection == NULL)
        return eos_ERROR_PARAM_NULL;
#endif
    
    eosFree((eosHCollection) hCollection);
}

eosResult eosCollectionAdd(eosHCollection hCollection, void *data) {

    eosHCollection collection = (eosHCollection) hCollection;

    if (collection->numItems == collection->maxItems)
        return eos_ERROR_OPERATION;

    memcpy(&collection->start[collection->numItems], data, collection->itemSize);
    collection->numItems++;

    return eos_RESULT_SUCCESS;
}


eosResult eosCollectionRemove(eosHCollection hCollection, void *data) {

}


eosResult eosCollectionEnumerate(eosHCollection hCollection) {

}


eosResult eosCollectionEnumerateNext(eosHCollection hCollection, void *data) {

}
