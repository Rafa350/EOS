#include "eosQueue.h"


typedef void (*Action)(void *args);

typedef struct {
    Action action;
    void *args;
} QueueElement;


eosResult eosExecutionQueueCreate(eosHandle *handle) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    eosQueueCreateParams createParams;
    createParams.length = 100;
    createParams.size = sizeof(QueueElement);
    return eosQueueCreate(&createParams, handle);
}


eosResult eosExecutionQueuePut(eosHandle handle, Action action, void *args) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    if (action == NULL)
        return eos_ERROR_PARAMS;

    QueueElement qe;
    qe.action = action;
    qe.args = args;

    return eosQueuePut(handle, &qe);
}

eosResult eosExecutionQueueDispatch(eosHandle handle) {

    if (handle == NULL)
        return eos_ERROR_PARAMS;

    QueueElement qe;
    eosResult r;
    while ((r = eosQueueGet(handle, &qe)) == eos_RESULT_SUCCESS)
        qe.action(qe.args);

    return eos_RESULT_SUCCESS;
}