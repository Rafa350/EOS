#include "eos.h"


/*************************************************************************
 *
 *       Inicialitzacio de l'aplicacio d'usuari
 *
 *       Funcio:
 *           void usrSetup(void)
 *
 *************************************************************************/

void usrSetup(void) {

    //eosOutPulse(0, 1000);
    //eosOutPulse(1, 2000);
    //eosTimStart(0, 5000);
    //eosOutBlink(3, 250);
    //eosOutBlink(4, 350);
    //eosOutBlink(5, 450);

    eosStpMove(0, 0, 0, 0, 1000);
}


/*************************************************************************
 *
 *       Bucle principal de l'aplicacio
 *
 *       Funcio:
 *           void usrLoop(void)
 *
 *************************************************************************/

void usrLoop(void) {

    if (eosTimGet(0)) {
        eosOutSet(0, eosInpGet(0) || eosInpGet(2));
        eosOutSet(1, eosInpGet(1) || eosInpGet(2));
    }

    if (!eosStpIsBusy(0))
        eosStpMove(0, 0, 0, 0, 1000);
}
