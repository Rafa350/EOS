#include "eos.h"
#include <string.h>


#if defined(EOS_DEBUG)
extern "C" void eosErrorHandler(
    const char *file,
    unsigned line,
    const char *message) {

    char buffer[120];

    strncpy(buffer, message, sizeof(buffer));

    for (char *p = buffer; *p != '\0'; p++)
      	ITM_SendChar(*p);

    while (true)
        continue;
}
#endif

