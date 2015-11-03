#include "Services/eosDisplay.hpp"
#include "../../../MD-DSP04/DSP04Messages.h"
#include "string.h"


#define BUFFER_SIZE               1000      // Tamany del buffer


#define min(a, b)    (a) < (b) ? a : b

#define __addUINT8(data)                           \
    buffer[bufferCount++] = (data)

#define __addUINT16(data)                          \
    buffer[bufferCount++] = (data) & 0x00FF;       \
    buffer[bufferCount++] = ((data) & 0xFF00) >> 8


using namespace eos;


/*************************************************************************
 *
 *       Constructor
 *
 *       Funcio:
 *           DisplayService::DisplayService(
 *               I2CMasterService *i2cService,
 *               uint8_t addr) 
 *
 *       Entrada:
 *           i2cMaster: Servei de comunicacions i2c
 *           addr     : Adressa i2c
 *
 *************************************************************************/

DisplayService::DisplayService(
    I2CMasterService *i2cService,
    uint8_t addr) {

    i2cService = i2cService;
    addr = addr;
    bufferSize = 1000;
    buffer = new uint8_t[](bufferSize);
}


/*************************************************************************
 *
 *       Inicia l'escriptura d'una comanda pel display
 *
 *       Funcio:
 *           bool DisplayService::BeginCommand()
 *
 *       Retorn:
 *           true si tot es correcte, false si el display es ocupat
 *
 *************************************************************************/

bool DisplayService::BeginCommand() {

    bufferCount = 0;
    bufferError = false;
    return true;
}


/*************************************************************************
 *
 *       Finalitza la escriptura d'una comanda del display
 *
 *       Funcio:
 *           bool DisplayService::EndCommand()
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 * 
 *************************************************************************/

bool DisplayService::EndCommand() {
    
    if (bufferError)
        return false;
    
    else {
        if (i2cService->startTransaction(
            addr,
            buffer,
            bufferCount,
            0,
            nullptr)) {

            return true;
        }
        
    }
}


/*************************************************************************
 *
 *       Afegeix un UINT8 a la comanda
 *
 *       Funcio:
 *           bool DisplayService::addUINT8(
 *               uint8_t data)
 *
 *       Entrada:
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool DisplayService::addUINT8(
    uint8_t data) {

    if (!bufferError) {
        __addUINT8(hService, data);
    }

    return bufferError;
}


/*************************************************************************
 *
 *       Afegeix un UINT16 a la comanda
 *
 *       Funcio:
 *           bool DisplayService::AddUINT16(
 *               uint16_t data)
 *
 *       Entrada:
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool DisplayService::addUINT16(
    uint16_t data) {

    if (!bufferError) {
        __addUINT16(hService, data);
    }

    return bufferError;
}


/*************************************************************************
 *
 *       Afegeix una cadena a la comanda
 *
 *       Funcio:
 *           bool DisplayService::AddString(
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

bool DisplayService::addString(
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
 *           bool DisplayService::addBytes(
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

bool DisplayService::addBytes(
    const uint8_t *data,
    unsigned dataLen) {

    if (!bufferError) {
        while (dataLen--)
            buffer[bufferCount++] = *data++;
    }

    return bufferError;
}


bool DisplayService::addCommandClear() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            __addUINT8(DSP_CMD_CLEAR);
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandRefresh() {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) < bufferSize)
            __addUINT8(DSP_CMD_REFRESH);
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandSetColor(
    uint8_t fgColor,
    uint8_t bkColor) {

    if (!bufferError) {
        if (bufferCount + (sizeof(uint8_t) * 3) < bufferSize) {
            __addUINT8(DSP_CMD_SETCOLOR);
            __addUINT8(fgColor);
            __addUINT8(bkColor);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandSetFont(
    uint8_t font) {

    if (!bufferError) {
        if (bufferCount + (sizeof(uint8_t) * 2) < bufferSize) {
            __addUINT8(DSP_CMD_SETFONT);
            __addUINT8(font);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandMoveTo(
    int x,
    int y) {

    if (!bufferError) {
        if (bufferCount + sizeof(uint8_t) * 5 < bufferSize) {
            __addUINT8(DSP_CMD_MOVETO);
            __addUINT16(x);
            __addUINT16(y);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandDrawLine(
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
        msg.shape = DRAWSHAPE_LINE;
        msg.x1 = x1;
        msg.y1 = y1;
        msg.x2 = x2;
        msg.y2 = y2;

        addBytes((uint8_t*) &msg, 12);//sizeof(msg));
    }

    return bufferError;
}


bool DisplayService::addCommandDrawRectangle(
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


bool DisplayService::addCommandFillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!bufferError) {

       if (bufferCount + sizeof(uint8_t) * 12 < bufferSize) {
            __addUINT8(DSP_CMD_DRAWSHAPE);
            __addUINT8(0xFF);
            __addUINT8(0xFF);
            __addUINT8(0x11); //DRAWSHAPE_RECT | (0 << 4) | (1 << 5));
            __addUINT16(x1);
            __addUINT16(y1);
            __addUINT16(x2);
            __addUINT16(y2);
        }
        else
            bufferError = true;
    }

    return bufferError;
}


bool DisplayService::addCommandDrawText(
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
            __addUINT8(DSP_CMD_DRAWTEXT);
            __addUINT8(0xFF);
            __addUINT8(0xFF);
            __addUINT16(x);
            __addUINT16(y);
            __addUINT8(len);
            addBytes(&text[offset], len);
        }
        else
            bufferError = true;
    }

    return bufferError;
}
