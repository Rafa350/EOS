#include "eos.hpp"


#ifdef __DEBUG
void eosErrorHandler(
    unsigned errorCode, 
    const char *message) {
    
    char buffer[120];
    
    strncpy(buffer, message, sizeof(buffer));
    
    while (true)
        continue;
}
#endif

