#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/eosString.h"
#include "../../../MD-DSP04/DSP04Messages.h"


using namespace eos;

static uint8_t __buffer[500];


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    i2cMaster: Servei de comunicacions I2C.
/// \param    addr: Adressa I2C.
///
GfxDisplay::GfxDisplay(
    I2CMasterService *i2cService,
    uint8_t addr) :

    cb(__buffer, sizeof(__buffer)),
    transactionCallback(this, &GfxDisplay::transactionHandler) {

    this->i2cService = i2cService;
    this->addr = addr;
}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el color.
/// \param    color: El color.
///
void GfxDisplay::setColor(
    uint8_t color) {

    this->color = color;

}


/// ----------------------------------------------------------------------
/// \brief    Selecciona el font.
/// \param    font: El font.
///
void GfxDisplay::setFont(
    uint8_t font) {

}


int GfxDisplay::getTextWidth(const char *text) {

    return 0;
}


int GfxDisplay::getTextHeight(const char *text) {

    return 0;
}


void GfxDisplay::putTTY(char ch) {

}


void GfxDisplay::putTTY(const char *s) {

}


void GfxDisplay::putTTY(const char *s, int length) {

}


/// ----------------------------------------------------------------------
/// \brief    Borra la pantalla.
/// \param    color: Color de borrat
///
void GfxDisplay::clear(
    uint8_t color) {

    cb.cmdClear();
}


/// ----------------------------------------------------------------------
/// \brief    : Mou la posicio actual.
/// \param    : x: Coordinada X de la nova posicio.
/// \param    : y: CoordinadaY de la posicio.
///
void GfxDisplay::moveTo(
    int x,
    int y) {

    cb.cmdMoveTo(x, y);

    curX = x;
    curY = y;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia desde la posicio actual fins a la indicada.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada X de la posicio.
/// \remarks  La nova posicio pasa a ser la posicio actual.
///
void GfxDisplay::lineTo(
    int x,
    int y) {

    cb.cmdDrawLine(curX, curY, x, y);

    curX = x;
    curY = y;
}


void GfxDisplay::arcTo(
    int x,
    int y,
    int cx,
    int cy) {

}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa una linia.
/// \param    x1: Coordinada X inicial.
/// \param    y1: Coordinada Y inicial.
/// \param    x2: Coordinada X final.
/// \param    y2: Coordinada Y final.
///
void GfxDisplay::drawLine(
    int x1,
    int y1,
    int x2,
    int y2) {

    cb.cmdDrawLine(x1, y1, x2, y2);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un rectangle.
/// \param    x1: Coordinada X inicial.
/// \param    y1: Coordinada Y inicial.
/// \param    x2: Coordinada X final.
/// \param    y2: Coordinada Y final.
///
void GfxDisplay::drawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    cb.cmdDrawRectangle(x1, y1, x2, y2);
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un cercle.
/// \param    x: Coordinada X del centre.
/// \param    y: Coordinada Y del centre.
/// \param    r: Radi.
///
void GfxDisplay::drawCircle(
    int cx,
    int cy,
    int r) {

    cb.cmdDrawEllipse(cx - r, cy - r, cx + r, cy + r);
}


void GfxDisplay::drawBitmap1BPP(
    int x,
    int y,
    const uint8_t *bitmap,
    int sx,
    int sy,
    uint8_t color) {

}


int GfxDisplay::drawChar(
    int x,
    int y,
    char c) {

    static char s[2] = { 0, 0 };

    s[1] = 0;

    cb.cmdDrawText(x, y, "c");

    return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un text.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada Y de la posicio.
/// \param    text: El text a dibuixar.
///
int GfxDisplay::drawString(
    int x,
    int y,
    const String &text) {

    cb.cmdDrawText(x, y, text);

    return 0;
}


void GfxDisplay::fillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

}


void GfxDisplay::fillCircle(int cx, int cy, int r) {

}


/// ----------------------------------------------------------------------
/// \brief    Refresca la patalla.
///
void GfxDisplay::refresh() {

    cb.cmdRefresh();

    i2cService->startTransaction(
        addr,
        I2CMasterService::TransactionProtocol::packet,
        cb.getBuffer(),
        cb.getBufferPos(),
        &transactionCallback);

    // Espara que finalitzi la transaccio
    //
    lock.wait(-1);

    // Prepara el commandBuilder per la propera comanda
    //
    cb.clear();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa el callback de la transaccio.
/// \param    args: Areguments del callback.
///
void GfxDisplay::transactionHandler(
    const I2CMasterService::TransactionEventArgs& args) {

    lock.release();
}