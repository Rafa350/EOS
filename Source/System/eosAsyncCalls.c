void doAirAssistON() {
}

void doAirAssistOFF() {
}

void onTrigger() {

    callOnDelay(doAirAssistON, 100);
    callOnDelay(doVaccumON, 120);
    callOnInputChange(onPrintLabelSuccess, INP_LR, ON, ONCE);
    callOnDelay(onPrintLabelTimeout, 3000);

    outPulse(OUT_PL, 200);
}

void onPrintLabelSuccess() {

    callCancelAll();

    doAirAssistOFF();
    doPistonDown();
    
    callOnChangeInput(onPistonBottom, INP_PB, ON, ONCE);
}

void onPrintLabelTimeout() {

    callCancelAll();
    call(onError);
    
    doAirAssistOFF();
    doVaccumOFF();
}

void onPistonBottom() {

    callOnInputChange(onPistonTop, INP_PT, ON, ONCE);
    doVaccumOFF();
    doAirJetPULSE();
    doPistonUp();
}

void onPistonTop() {

    callOnInputChange(onTrigger, INP_ST, ON, ONCE);
}

void onError() {
}