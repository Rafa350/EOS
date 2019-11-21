#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/eosString.h"
#include "System/IO/eosMemoryStream.h"

#include "../../../MD-DSP04/DSP04Messages.h"


#define BUFFER_SIZE               1000      // Tamany del buffer


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Contructor.
/// \param    i2cMaster: Servei de comunicacions I2C.
/// \param    addr: Adressa I2C.
///
GfxDisplay::GfxDisplay(
    I2CMasterService *i2cService,
    uint8_t addr) {

    this->i2cService = i2cService;
    this->addr = addr;
    
    bufferSize = BUFFER_SIZE;
    buffer = new uint8_t[bufferSize]();
}


void GfxDisplay::setColor(Color color) {
    
}


//void Display::setFont(Font *font);


int GfxDisplay::getTextWidth(const char *text) {
    
}


int GfxDisplay::getTextHeight(const char *text) {
    
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
    Color color) {
    
    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdClear();
    cb.cmdRefresh();
    endCommand();
}


/// ----------------------------------------------------------------------
/// \brief    : Mou la posicio actual.
/// \param    : x: Coordinada X de la nova posicio.
/// \param    : y: CoordinadaY de la posicio.
///
void GfxDisplay::moveTo(
    int x, 
    int y) {
    
    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdMoveTo(x, y);
    endCommand();
    
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
    
    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdDrawLine(curX, curY, x, y);
    cb.cmdRefresh();
    endCommand();
    
    curX = x;
    curY = y;
}


void GfxDisplay::arcTo(int x, int y, int cx, int cy) {
    
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

    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdDrawLine(x1, y1, x2, y2);
    cb.cmdRefresh();
    endCommand();
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
    
    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdDrawRectangle(x1, y1, x2, y2);
    cb.cmdRefresh();
    endCommand();
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
    
}


void GfxDisplay::drawBitmap1BPP(
    int x, 
    int y, 
    const uint8_t *bitmap, 
    int sx, 
    int sy, 
    Color color) {
    
}


int GfxDisplay::drawChar(
    int x, 
    int y, 
    char c) {
    
    static char s[2] = { 0, 0 };
    
    s[1] = 0;
    
    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    addCommandDrawText(x, y, s, 0, -1);
    addCommandRefresh();
    endCommand();
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

    MemoryStream ms(buffer, bufferSize);
    GfxCommandBuilder cb(ms);
    cb.cmdDrawText(x, y, text);
    cb.cmdRefresh();
    endCommand();
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
/// \brief    Finalitza la escriptura d'una comanda del display.
///
/*
bool GfxDisplay::refresh() {
    
    if (bufferError)
        return false;
    
    else {
        I2CMasterTransaction *transaction = new I2CMasterTransaction(
            addr,  
            I2CMasterTransaction::Protocol::packed, 
            stream->getBuffer(), 
            stream->getPosition(), 
            nullptr);
        if (!i2cService->startTransaction(transaction, 1000))
            delete transaction;
    }
}

*/