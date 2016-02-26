#include "Controllers/MD-DSP04L/eosDisplay.hpp"
#include "../../../MD-DSP04/DSP04Messages.h"
#include "string.h"


#define BUFFER_SIZE               1000      // Tamany del buffer


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param i2cMaster: Servei de comunicacions I2C.
/// \param addr: Adressa I2C.
///
Display::Display(
    I2CMasterService *i2cService,
    uint8_t addr) {

    this->i2cService = i2cService;
    this->addr = addr;
    bufferSize = 1000;
    buffer = new uint8_t[bufferSize]();
}


void Display::setColor(Color color) {
    
}


//void Display::setFont(Font *font);
int Display::getTextWidth(const char *text) {
    
}


int Display::getTextHeight(const char *text) {
    
}


void Display::putTTY(char ch) {
    
}


void Display::putTTY(const char *s) {
    
}


void Display::putTTY(const char *s, int length) {
    
}


void Display::clear(Color color) {
    
}


void Display::moveTo(
    int x, 
    int y) {
    
    beginCommand();
    addCommandMoveTo(x, y);
    endCommand();
    
    curX = x;
    curY = y;
}

void Display::lineTo(
    int x, 
    int y) {
    
    beginCommand();
    addCommandDrawLine(curX, curY, x, y);
    endCommand();
    
    curX = x;
    curY = y;
}


void Display::arcTo(int x, int y, int cx, int cy) {
    
}


void Display::drawLine(
    int x1, 
    int y1, 
    int x2, 
    int y2) {

    beginCommand();
    addCommandDrawLine(x1, y1, x2, y2);
    endCommand();
}


void Display::drawRectangle(
    int x1, 
    int y1, 
    int x2, 
    int y2) {
    
    beginCommand();
    addCommandDrawRectangle(x1, y1, x2, y2);
    endCommand();
}


void Display::drawCircle(int cx, int cy, int r) {
    
}


void Display::drawBitmap1BPP(int x, int y, const uint8_t *bitmap, int sx, int sy, Color color) {
    
}


int Display::drawChar(int x, int y, char c) {
    
}


int Display::drawString(int x, int y, const char *s) {
    
}


void Display::fillRectangle(
    int x1, 
    int y1, 
    int x2, 
    int y2) {

    beginCommand();
    addCommandFillRectangle(x1, y1, x2, y2);
    endCommand();    
}


void Display::fillCircle(int cx, int cy, int r) {
    
}


/// ----------------------------------------------------------------------
/// \brief Inicia la escriptura d'una comanda.
///
bool Display::beginCommand() {

    bufferCount = 0;
    bufferError = false;
    return true;
}


/// ----------------------------------------------------------------------
/// \brief Finalitza la escriptura d'una comanda del display.
///
bool Display::endCommand() {
    
    if (bufferError)
        return false;
    
    else {
        if (i2cService->startTransaction(
            addr,
            buffer,
            bufferCount,
            100,
            nullptr)) {

            return true;
        }        
    }
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un UINT8 a la comanda.
/// \param data: Les dades a escriure.
/// \return true si l'operacio s'ha efectuat correctament.
///
bool Display::addUINT8(
    uint8_t data) {

    if (!bufferError) 
        fAddUINT8(data);    

    return bufferError;
}


/// ----------------------------------------------------------------------
/// \brief Afegeix un UINT16 a la comanda.
/// \param data: Les dades a escriure.
/// \return true si l'operacio s'ha efectuat correctament.
///
bool Display::addUINT16(
    uint16_t data) {

    if (!bufferError) 
        fAddUINT16(data);

    return bufferError;
}


/*************************************************************************
 *
 *       Afegeix una cadena a la comanda
 *
 *       Funcio:
 *           bool DisplayController::AddString(
 *               const char *data)
 *
 *       Entrada:
 *           hService: El handler del display
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool Display::addString(
    const char *data) {

    if (!bufferError) {
        char c;
        while ((c = *data++) != '\0')
            buffer[bufferCount++] = c;
    }

    return bufferError;
}


/*************************************************************************
 *
 *       Afegeix una sequencia de bytes a la comanda
 *
 *       Funcio:
 *           bool DisplayController::addBytes(
 *               const uint8_t *data,
 *               unsigned dataLen)
 *
 *       Entrada:
 *            data    : Les dades a escriure
 *            dataLen : Longitut de les dades en bytes
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool Display::addBytes(
    const uint8_t *data,
    unsigned dataLen) {

    if (!bufferError) {
        if (bufferCount + dataLen < bufferSize) {
            while (dataLen--)
                fAddUINT8(*data++);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool Display::addCommandClear() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            fAddUINT8(DSP_CMD_CLEAR);
        else
            bufferError = true;
    }

    return bufferError;
}


bool Display::addCommandRefresh() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            fAddUINT8(DSP_CMD_REFRESH);
        else
            bufferError = true;
    }

    return bufferError;
}


bool Display::addCommandSetColor(
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


bool Display::addCommandSetFont(
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


bool Display::addCommandMoveTo(
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


bool Display::addCommandDrawLine(
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


bool Display::addCommandDrawRectangle(
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


bool Display::addCommandFillRectangle(
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


bool Display::addCommandDrawText(
    int x,
    int y,
    const char *text,
    unsigned offset,
    unsigned length) {

    if (!bufferError) {

        unsigned len;
        if (length == -1)
            len = min(strlen(&text[offset]), 256);
        else
            len = min(length, 256);

        if (bufferCount + sizeof(uint8_t) * 8 + len < bufferSize) {
            fAddUINT8(DSP_CMD_DRAWTEXT);
            fAddUINT8(0xFF);
            fAddUINT8(0xFF);
            fAddUINT16(x);
            fAddUINT16(y);
            fAddUINT8(len);
            addBytes((uint8_t*) &text[offset], len);
        }
        else
            bufferError = true;
    }

    return bufferError;
}
