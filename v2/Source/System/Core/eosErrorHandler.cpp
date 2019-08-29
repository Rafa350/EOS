#include "eos.h"
#include "System/eosDebug.h"


using namespace eos;


#if defined(EOS_DEBUG)
extern "C" void eosErrorHandler(
    const char *file,
    unsigned line,
    const char *message) {

    Debug::print(message);

    while (true)
        continue;
}
#endif

