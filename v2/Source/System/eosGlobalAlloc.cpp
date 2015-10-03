#include "FreeRTOS.h"
#include "task.h"


void *operator new(size_t size) {
    
    return pvPortMalloc(size);
}

void operator delete(void *ptr) {
    
    vPortFree(ptr);
}
