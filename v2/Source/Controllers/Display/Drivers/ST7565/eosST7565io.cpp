#include "Screen/Gscr/GScr.h"


/*************************************************************************
 *
 *       Escriu un byte de dades en el display
 *
 *       Funcio:
 *           void ST7565_WriteData(
 *               uint8_t data) 
 *
 *       Entrada:
 *           cmd: La comanda
 *
 *************************************************************************/
 
void ST7565_WriteData(
    uint8_t data) {

    GSCR_A0Hi();
    GSCR_CSLo();
    GSCR_WriteByte(data);
    GSCR_CSHi();
}


/*************************************************************************
 *
 *       Escriu un byte de comanda en el display
 *
 *       Funcio:
 *           void ST7565_WriteCtrl(
 *               uint8_t cmd) 
 *
 *       Entrada:
 *           cmd: La comanda
 *
 *************************************************************************/
 
void ST7565_WriteCtrl(
    uint8_t cmd) {
 
    GSCR_A0Lo();
    GSCR_CSLo();
    GSCR_WriteByte(cmd);
    GSCR_CSHi();

    // Retard per procesar la comanda
    //
    uint8_t i;
    for (i = 0; i < 10; i++)
        continue;
}
