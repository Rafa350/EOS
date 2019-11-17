#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxDisplay.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosMath.h"
#include "System/eosString.h"

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
    
    beginCommand();
    addCommandClear();
    addCommandRefresh();
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
    
    beginCommand();
    addCommandMoveTo(x, y);
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
    
    beginCommand();
    addCommandDrawLine(curX, curY, x, y);
    addCommandRefresh();
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

    beginCommand();
    addCommandDrawLine(x1, y1, x2, y2);
    addCommandRefresh();
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
    
    beginCommand();
    addCommandDrawRectangle(x1, y1, x2, y2);
    addCommandRefresh();
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
    
    beginCommand();
    addCommandDrawText(x, y, s, 0, -1);
    addCommandRefresh();
    endCommand();
}


int GfxDisplay::drawString(
    int x, 
    int y, 
    const String &s) {
    
    beginCommand();
    addCommandDrawText(x, y, s, 0, -1);    
    addCommandRefresh();
    endCommand();
}


void GfxDisplay::fillRectangle(
    int x1, 
    int y1, 
    int x2, 
    int y2) {

    beginCommand();
    addCommandFillRectangle(x1, y1, x2, y2);
    addCommandRefresh();
    endCommand();    
}


void GfxDisplay::fillCircle(int cx, int cy, int r) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Inicia la escriptura d'una comanda.
///
bool GfxDisplay::beginCommand() {

    bufferCount = 0;
    bufferError = false;
    return true;
}


/// ----------------------------------------------------------------------
/// \brief    Finalitza la escriptura d'una comanda del display.
///
bool GfxDisplay::endCommand() {
    
    if (bufferError)
        return false;
    
    else {
        I2CMasterTransaction *transaction = new I2CMasterTransaction(
            addr,  
            I2CMasterTransaction::Protocol::packed, 
            buffer, 
            bufferCount, 
            nullptr);
        if (!i2cService->startTransaction(transaction, 1000))
            delete transaction;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un UINT8 a la comanda.
/// \param    data: Les dades a escriure.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addUINT8(
    uint8_t data) {

    if (!bufferError) 
        fAddUINT8(data);    

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix un UINT16 a la comanda.
/// \param    data: Les dades a escriure.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addUINT16(
    uint16_t data) {

    if (!bufferError) 
        fAddUINT16(data);

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una sequencia de bytes a la comanda
/// \param    data: La sequencia de bytes.
/// \param    length: El numnero de bytes.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addBytes(
    const uint8_t *data,
    int length) {

    if (!bufferError) {
        if (bufferCount + length < bufferSize) {
            while (length--)
                fAddUINT8(*data++);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix la comanda 'CMD_CLEAR'
/// \return   true si l'operacio s'ha efectuat correctament.
/// 
bool GfxDisplay::addCommandClear() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            fAddUINT8(DSP_CMD_CLEAR);
        else
            bufferError = true;
    }

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    : Afegeix la comanda 'CMD_REFRESH'
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addCommandRefresh() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            fAddUINT8(DSP_CMD_REFRESH);
        else
            bufferError = true;
    }

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeiox la comanda 'CMD_SET_COLOR'
/// \param    fgColor: Color del primer pla.
/// \param    bkColor: Color de fons.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addCommandSetColor(
    uint8_t fgColor,
    uint8_t bkColor) {

    if (!bufferError) {
        if (bufferCount + (sizeof(uint8_t) * 3) < bufferSize) {
            fAddUINT8(DSP_CMD_SETCOLOR);
            fAddUINT8(fgColor);
            fAddUINT8(bkColor);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix la comanda 'CMD_SET_FONT'.
/// \param    font: Identificador del font.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addCommandSetFont(
    uint8_t font) {

    if (!bufferError) {
        if (bufferCount + (sizeof(uint8_t) * 2) < bufferSize) {
            fAddUINT8(DSP_CMD_SETFONT);
            fAddUINT8(font);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix la comanda 'CMD_MOVETO'.
/// \param    x: Coordinada X.
/// \param    y: Coordinada Y.
/// \return   true si l'operacio s'ha efectuat correctament.
///
bool GfxDisplay::addCommandMoveTo(
    int x,
    int y) {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) * 5 < bufferSize) {
            fAddUINT8(DSP_CMD_MOVETO);
            fAddUINT16(x);
            fAddUINT16(y);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool GfxDisplay::addCommandDrawLine(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) * 12 < bufferSize) {
            fAddUINT8(DSP_CMD_DRAWSHAPE);
            fAddUINT8(0xFF);
            fAddUINT8(0xFF);
            fAddUINT8(DRAWSHAPE_LINE);
            fAddUINT16(x1);
            fAddUINT16(y1);
            fAddUINT16(x2);
            fAddUINT16(y2);
        }
        else
           bufferError = true;
    }

    return bufferError;
}


bool GfxDisplay::addCommandDrawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!bufferError) {

        dspDrawShapeMessage msg;

        msg.cmd = DSP_CMD_DRAWSHAPE;
        msg.fillColor = 0xFF;
        msg.frameColor = 0xFF;
        msg.filled = false;
        msg.framed = true;
        msg.shape = DRAWSHAPE_RECT;
        msg.x1 = x1;
        msg.y1 = y1;
        msg.x2 = x2;
        msg.y2 = y2;

        addBytes((uint8_t*) &msg, 12);//sizeof(msg));
    }

    return bufferError;
}


bool GfxDisplay::addCommandFillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!bufferError) {
       if (bufferCount + sizeof(uint8_t) * 12 < bufferSize) {
            fAddUINT8(DSP_CMD_DRAWSHAPE);
            fAddUINT8(0xFF);
            fAddUINT8(0xFF);
            fAddUINT8(0x11); //DRAWSHAPE_RECT | (0 << 4) | (1 << 5));
            fAddUINT16(x1);
            fAddUINT16(y1);
            fAddUINT16(x2);
            fAddUINT16(y2);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool GfxDisplay::addCommandDrawText(
    int x,
    int y,
    const char *text,
    int offset,
    int length) {

    if (!bufferError) {

        if (length == -1)
            length = Math::min((int) strlen(&text[offset]), 256);
        else
            length = Math::min(length, 255);

        if (bufferCount + sizeof(uint8_t) * 8 + length < bufferSize) {
            fAddUINT8(DSP_CMD_DRAWTEXT);
            fAddUINT8(0xFF);
            fAddUINT8(0xFF);
            fAddUINT16(x);
            fAddUINT16(y);
            fAddUINT8(length);
            addBytes((uint8_t*) &text[offset], length);
        }
        else
            bufferError = true;
    }

    return bufferError;
}
