#include "eos.h"



/*************************************************************************
 *
 *       Entrada a l'aplicacio
 *
 *       Funcio:
 *           void main(void)
 *
 *************************************************************************/

#ifdef eosOPTION_Main
void main(void) {

    // Crida a la funcio d'entrada al EOS
    //
    eosMain();
}
#endif


void eosFatalError(eosResult result) {

    while (true)
        continue;
}