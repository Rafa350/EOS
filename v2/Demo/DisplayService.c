#include "DisplayService.h"
#include "System/eosMemory.h"
#include "Services/eosI2CMaster.h"
#include "../../../MD-DSP04/DSP04Messages.h"
#include "string.h"


#define BUFFER_SIZE               1000      // Tamany del buffer

typedef struct __eosDisplayService {         // Dades internes del servei
    eosI2CMasterServiceHandle hI2CMasterService; // -Handler del servei I2C
    uint8_t i2cAddr;                        // -Adressa I2C del display
    uint8_t *buffer;
    unsigned bufferSize;
    unsigned bufferCount;
    bool bufferError;
    bool isBusy;
} eosDisplayService;


static void onEndTransaction(eosI2CTransactionHandle hTransaction, void *context);

#define __addUINT8(hService, data)                                           \
    hService->buffer[hService->bufferCount++] = (data)

#define __addUINT16(hService, data)                                          \
    hService->buffer[hService->bufferCount++] = (data) & 0x00FF;             \
    hService->buffer[hService->bufferCount++] = ((data) & 0xFF00) >> 8



/*************************************************************************
 *
 *       Inicialitza el servei
 *
 *       Funcio:
 *           eosDisplayServiceHandle eosDisplayServiceInitialize(
 *               eosDisplayServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres del servei
 *
 *       Retorn:
 *           El handler del display. NULL en cas d'error
 *
 *************************************************************************/

eosDisplayServiceHandle eosDisplayServiceInitialize(
    eosDisplayServiceParams *params) {

    eosDisplayServiceHandle hService = (eosDisplayServiceHandle) eosAlloc(sizeof(eosDisplayService));
    if (hService != NULL) {

        hService->hI2CMasterService = params->hI2CMasterService;
        hService->i2cAddr = params->i2cAddr;

        hService->bufferSize = BUFFER_SIZE;
        hService->buffer = (uint8_t*) eosAlloc(hService->bufferSize);
        eosDebugVerify(hService->buffer != NULL);
        hService->isBusy = false;
    }

    return hService;
}


/*************************************************************************
 *
 *       Inicia l'escriptura d'una comanda pel display
 *
 *       Funcio:
 *           bool eosDisplayBeginCommand(
 *               elsDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *           true si tot es correcte, false si el display es ocupat
 *
 *************************************************************************/

bool eosDisplayBeginCommand(
    eosDisplayServiceHandle hService) {

    if (hService->isBusy)
        return false;
    else {
        hService->bufferCount = 0;
        hService->bufferError = false;
        return true;
    }
}


/*************************************************************************
 *
 *       Finalitza la escriptura d'una comanda del display
 *
 *       Funcio:
 *           bool eosDisplayEndCommand(
 *               eosDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 * 
 *************************************************************************/

bool eosDisplayEndCommand(
    eosDisplayServiceHandle hService) {
    
    if (hService->bufferError)
        return false;

    // Crea la transaccio
    //
    eosI2CTransactionParams transactionParams;
    memset(&transactionParams, 0, sizeof(transactionParams));
    transactionParams.address = hService->i2cAddr;
    transactionParams.txBuffer = hService->buffer;
    transactionParams.txCount = hService->bufferCount;
    transactionParams.onEndTransaction = onEndTransaction;
    transactionParams.context = hService;

    // Inicia la transaccio
    //
    if (eosI2CMasterStartTransaction(hService->hI2CMasterService, &transactionParams))
        hService->isBusy = true;

    return true;
}


/*************************************************************************
 *
 *       Afegeix un UINT8 a la comanda
 *
 *       Funcio:
 *           bool eosDisplayAddUINT8(
 *               eosDisplayServiceHandle hService,
 *               uint8_t data)
 *
 *       Entrada:
 *           hService: El handler del display
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool inline eosDisplayAddUINT8(
    eosDisplayServiceHandle hService,
    uint8_t data) {

    if (!hService->bufferError) {
        __addUINT8(hService, data);
    }

    return hService->bufferError;
}


/*************************************************************************
 *
 *       Afegeix un UINT16 a la comanda
 *
 *       Funcio:
 *           bool eosDisplayAddUINT16(
 *               eosDisplayServiceHandle hService,
 *               uint16_t data)
 *
 *       Entrada:
 *           hService: El handler del display
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool inline eosDisplayAddUINT16(
    eosDisplayServiceHandle hService,
    uint16_t data) {

    if (!hService->bufferError) {
        __addUINT16(hService, data);
    }

    return hService->bufferError;
}


/*************************************************************************
 *
 *       Afegeix una cadena a la comanda
 *
 *       Funcio:
 *           bool eosDisplayAddString(
 *               eosDisplayServiceHandle hService,
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

bool eosDisplayAddString(
    eosDisplayServiceHandle hService,
    const char *data) {

    if (!hService->bufferError) {
        char c;
        while ((c = *data++) != '\0')
            hService->buffer[hService->bufferCount++] = c;
    }

    return hService->bufferError;
}


/*************************************************************************
 *
 *       Afegeix una sequencia de bytes a la comanda
 *
 *       Funcio:
 *           bool eosDisplayAddBytes(
 *               eosDisplayServiceHandle hService,
 *               const uint8_t *data,
 *               unsigned dataLen)
 *
 *       Entrada:
 *            hService: El handler del servei
 *            data    : Les dades a escriure
 *            dataLen : Longitut de les dades en bytes
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool eosDisplayAddBytes(
    eosDisplayServiceHandle hService,
    const uint8_t *data,
    unsigned dataLen) {

    if (!hService->bufferError) {
        while (dataLen--)
            hService->buffer[hService->bufferCount++] = *data++;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandClear(
    eosDisplayServiceHandle hService) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(uint8_t) < hService->bufferSize)
            __addUINT8(hService, DSP_CMD_CLEAR);
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandRefresh(
    eosDisplayServiceHandle hService) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(uint8_t) < hService->bufferSize)
            __addUINT8(hService, DSP_CMD_REFRESH);
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandSetColor(
    eosDisplayServiceHandle hService,
    uint8_t fgColor,
    uint8_t bkColor) {

    if (!hService->bufferError) {
        if (hService->bufferCount + (sizeof(uint8_t) * 3) < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_SETCOLOR);
            __addUINT8(hService, fgColor);
            __addUINT8(hService, bkColor);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandSetFont(
    eosDisplayServiceHandle hService,
    uint8_t font) {

    if (!hService->bufferError) {
        if (hService->bufferCount + (sizeof(uint8_t) * 2) < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_SETFONT);
            __addUINT8(hService, font);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandMoveTo(
    eosDisplayServiceHandle hService,
    int x,
    int y) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(uint8_t) * 5 < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_MOVETO);
            __addUINT16(hService, x);
            __addUINT16(hService, y);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandDrawLine(
    eosDisplayServiceHandle hService,
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!hService->bufferError) {

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

        eosDisplayAddBytes(hService, (uint8_t*) &msg, 12);//sizeof(msg));
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandDrawRectangle(
    eosDisplayServiceHandle hService,
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!hService->bufferError) {

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

        eosDisplayAddBytes(hService, (uint8_t*) &msg, 12);//sizeof(msg));
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandFillRectangle(
    eosDisplayServiceHandle hService,
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!hService->bufferError) {

       if (hService->bufferCount + sizeof(uint8_t) * 12 < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_DRAWSHAPE);
            __addUINT8(hService, 0xFF);
            __addUINT8(hService, 0xFF);
            __addUINT8(hService, 0x11); //DRAWSHAPE_RECT | (0 << 4) | (1 << 5));
            __addUINT16(hService, x1);
            __addUINT16(hService, y1);
            __addUINT16(hService, x2);
            __addUINT16(hService, y2);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool eosDisplayAddCommandDrawText(
    eosDisplayServiceHandle hService,
    int x,
    int y,
    const char *text,
    unsigned offset,
    unsigned length) {

    if (!hService->bufferError) {

        unsigned len;
        if (length == -1)
            len = min(strlen(&text[offset]), 256);
        else
            len = min(length, 256);

        if (hService->bufferCount + sizeof(uint8_t) * 8 + len < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_DRAWTEXT);
            __addUINT8(hService, 0xFF);
            __addUINT8(hService, 0xFF);
            __addUINT16(hService, x);
            __addUINT16(hService, y);
            __addUINT8(hService, len);
            eosDisplayAddBytes(hService, &text[offset], len);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


/*************************************************************************
 *
 *       Comprova si el display es ocupat
 *
 *       Funcio:
 *           bool eosDisplayIsBusy(
 *               eosDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *         True si es ocupat, false en cas contrari
 *
 *************************************************************************/

bool eosDisplayIsBusy(
    eosDisplayServiceHandle hService) {

    return hService->isBusy;
}


/*************************************************************************
 *
 *       Procesa l'event END_TRANSACTION
 *
 *       Funcio:
 *           void onEndTransaction(
 *               eosI2CTransactionHandle hTransaction,
 *               void *context)
 *
 *       Entrada:
 *           hTransaction: La transaccio que ha generat l'event
 *           context     : Parametres
 *
 *************************************************************************/

static void onEndTransaction(
    eosI2CTransactionHandle hTransaction,
    void *context) {

    eosDisplayServiceHandle hService = (eosDisplayServiceHandle) context;
    hService->isBusy = false;
}