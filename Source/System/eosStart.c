#include "eos.h"



/*************************************************************************
 *
 *       Entrada a l'aplicacio desde el compilador
 *
 *       Funcio:
 *           void main(void)
 *
 *************************************************************************/

#ifdef eos_OPTION_Main
void main(void) {

    // Cria a la funcio d'entrada al EOS
    //
    eosMain();
}
#endif


void eosFatalError(eosResult result) {

    while (true)
        continue;
}