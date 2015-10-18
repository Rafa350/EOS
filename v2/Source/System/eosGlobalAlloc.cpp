#include "System/eosMemory.hpp"


void *operator new(size_t size) {
    
    return eosHeapAlloc(nullptr, size);
}


void operator delete(void *ptr) {
    
    eosHeapFree(ptr);
}
