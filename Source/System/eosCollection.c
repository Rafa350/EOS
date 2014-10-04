#include "System/eosCollection.h"
#include "System/eosMemory.h"


typedef struct {                       // Dades de la coleccio
    unsigned itemSize;                 // -Tamany de cada item en bytes
    unsigned maxItems;                 // -Numero maxim d'items
    unsigned numItems;                 // -Numero actual d'items
    BYTE *start;                       // -Punter al inici de la coleccio
} Collection, *PCollection;


/*************************************************************************
 *
 *       Crea una colleccio
 *
 *       Funcio:
 *           eosResult eosCollectionCreate(
 *               eosCollectionCreateParams *params,
 *               eosHandle *hCollection)
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

eosResult eosCollectionCreate(eosCollectionCreateParams *params,  eosHandle *hCollection) {
    
#ifdef eos_OPTION_CheckInputParams
    if (params == NULL)
        return eos_ERROR_PARAM_NULL;
    if (hCollection == NULL)
        return eos_ERROR_PARAM_NULL;
#endif

    unsigned collectionSize = params->maxItems * params->itemSize;

    PCollection collection = eosAlloc(sizeof(Collection) + collectionSize);
    if (collection == NULL)
        return eos_ERROR_ALLOC;
    
    collection->itemSize = params->itemSize;
    collection->maxItems = params->maxItems;
    collection->numItems = 0;
    collection->start = (BYTE*) collection + sizeof(Collection);

    *hCollection = (eosHandle) collection;

    return eos_RESULT_SUCCESS;
}


eosResult eosCollectionDestroy(eosHandle hCollection) {

#ifdef eos_OPTION_CheckInputParams
    if (hCollection == NULL)
        return eos_ERROR_PARAM_NULL;
#endif
    
    eosFree((PCollection) hCollection);
}

eosResult eosCollectionAdd(eosHandle hCollection, void *data) {

    PCollection collection = (PCollection) hCollection;

    if (collection->numItems == collection->maxItems)
        return eos_ERROR_OPERATION;

    memcpy(&collection->start[collection->numItems], data, collection->itemSize);
    collection->numItems++;

    return eos_RESULT_SUCCESS;
}


eosResult eosCollectionRemove(eosHandle hCollection, void *data) {

}


eosResult eosCollectionEnumerate(eosHandle hCollection) {

}


eosResult eosCollectionEnumerateNext(eosHandle hCollection, void *data) {

}

