#include "eosHAL.h"
#include "peripheral/ports/plib_ports.h"


void halPortSetupOutput(
    unsigned port,
    unsigned pin) {

    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, (PORTS_CHANNEL) port, (PORTS_BIT_POS) pin);
}


void halPortSetupInput(
    unsigned port,
    unsigned pin) {

    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, (PORTS_CHANGE_NOTICE_PIN) CN16);
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, (PORTS_CHANNEL) port, (PORTS_BIT_POS) pin);
}


void halPortSet(
    unsigned port,
    unsigned pin,
    unsigned state) {

    PLIB_PORTS_PinWrite(PORTS_ID_0, (PORTS_CHANNEL) port, (PORTS_BIT_POS) pin, state);
}


unsigned halPortGet(
    unsigned port,
    unsigned pin) {

    return PLIB_PORTS_PinGet(PORTS_ID_0, (PORTS_CHANNEL) port, (PORTS_BIT_POS) pin);
}


void halPortToggle(
    unsigned port,
    unsigned pin) {

    PLIB_PORTS_PinToggle(PORTS_ID_0, (PORTS_CHANNEL) port, (PORTS_BIT_POS) pin);
}

