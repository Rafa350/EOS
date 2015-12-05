#include "eos.hpp"


#ifdef __DEBUG
void eosErrorHandler(
    const char *file,
    unsigned line,
    unsigned errorCode, 
    const char *message) {
    
    char buffer[120];
    
    strncpy(buffer, message, sizeof(buffer));
    
    while (true)
        continue;
}
#endif

