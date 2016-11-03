#include "eos.hpp"
#include <string.h>


#if defined(EOS_DEBUG)
void eosErrorHandler(
    const char *file,
    unsigned line,
    const char *message) {

    char buffer[120];

    strncpy(buffer, message, sizeof(buffer));

    while (true)
        continue;
}
#endif

