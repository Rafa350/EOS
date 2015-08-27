#include "DisplayService.h"
#include "System/eosMemory.h"
#include "Services/eosI2CMaster.h"
#include "../MD-DSP04/DSP04Messages.h"
#include "string.h"


#define BUFFER_SIZE               1000      // Tamany del buffer

typedef enum {                              // Estat del servei
    serviceInitializing,                    // -Initcialitzant el servei
    serviceRunning,                         // -Executant el servei
    serviceWaitingEndTransaction            // -Esperant el final de la transaccio
} axDisplayServiceState;

typedef struct __axDisplayService {         // Dades internes del servei
    axDisplayServiceState state;            // -Estat del servei
    eosI2CMasterServiceHandle hI2CMasterService; // -Handler del servei I2C
    BYTE i2cAddr;                           // -Adressa I2C del display
    BYTE *buffer;
    unsigned bufferSize;
    unsigned bufferCount;
    bool bufferError;
    bool isBusy;
} axDisplayService;


static void onEndTransaction(eosI2CTransactionHandle hTransaction);

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
 *           axDisplayServiceHandle axDisplayServiceInitialize(
 *               axDisplayServiceParams *params)
 *
 *       Entrada:
 *           params: Parametres del servei
 *
 *       Retorn:
 *           El handler del display. NULL en cas d'error
 *
 *************************************************************************/

axDisplayServiceHandle axDisplayServiceInitialize(
    axDisplayServiceParams *params) {

    axDisplayServiceHandle hService = (axDisplayServiceHandle) eosAlloc(sizeof(axDisplayService));
    if (hService == NULL)
        return NULL;

    hService->state = serviceInitializing;
    hService->hI2CMasterService = params->hI2CMasterService;
    hService->i2cAddr = params->i2cAddr;

    hService->bufferSize = BUFFER_SIZE;
    hService->buffer = (BYTE*) eosAlloc(hService->bufferSize);
    hService->isBusy = false;

    return hService;
}


/*************************************************************************
 *
 *       Comprova si el servei esta inicialitzat
 *
 *       Funcio:
 *           bool axDisplayServiceIsReady(
 *               axDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *       Retorn:
 *           true si es inicialitzat, false en cas contrari
 *
 *************************************************************************/

bool axDisplayServiceIsReady(
    axDisplayServiceHandle hService) {

    return hService->state != serviceInitializing;
}


/*************************************************************************
 *
 *       Procesa les tasques del servei
 *
 *       Funcio:
 *           void eosDisplayServiceTask(
 *               eosDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del servei
 *
 *************************************************************************/

void axDisplayServiceTask(
    axDisplayServiceHandle hService) {

    switch (hService->state) {
        case serviceInitializing:
            if (eosI2CMasterServiceIsReady(hService->hI2CMasterService))
                hService->state = serviceRunning;
            break;

        case serviceRunning:
            break;
    }
}


/*************************************************************************
 *
 *       Inicia l'escriptura d'una comanda pel display
 *
 *       Funcio:
 *           bool axDisplayBeginCommand(
 *               axDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *           true si tot es correcte, false si el display es ocupat
 *
 *************************************************************************/

bool axDisplayBeginCommand(
    axDisplayServiceHandle hService) {

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
 *           bool axDisplayEndCommand(
 *               axDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 * 
 *************************************************************************/

bool axDisplayEndCommand(
    axDisplayServiceHandle hService) {
    
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
 *           bool axDisplayAddUINT8(
 *               axDisplayServiceHandle hService,
 *               UINT8 data)
 *
 *       Entrada:
 *           hService: El handler del display
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool inline axDisplayAddUINT8(
    axDisplayServiceHandle hService,
    UINT8 data) {

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
 *           bool axDisplayAddUINT16(
 *               axDisplayServiceHandle hService,
 *               UINT16 data)
 *
 *       Entrada:
 *           hService: El handler del display
 *           data    : Les dades a escriure
 *
 *       Retorn:
 *           true si l'operacio s'ha efectuat correctament
 *
 *************************************************************************/

bool inline axDisplayAddUINT16(
    axDisplayServiceHandle hService,
    UINT16 data) {

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
 *           bool axDisplayAddString(
 *               axDisplayServiceHandle hService,
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

bool axDisplayAddString(
    axDisplayServiceHandle hService,
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
 *           bool axDisplayAddBytes(
 *               axDisplayServiceHandle hService,
 *               const BYTE *data,
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

bool axDisplayAddBytes(
    axDisplayServiceHandle hService,
    const BYTE *data,
    unsigned dataLen) {

    if (!hService->bufferError) {
        while (dataLen--)
            hService->buffer[hService->bufferCount++] = *data++;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandClear(
    axDisplayServiceHandle hService) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(BYTE) < hService->bufferSize)
            __addUINT8(hService, DSP_CMD_CLEAR);
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandRefresh(
    axDisplayServiceHandle hService) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(BYTE) < hService->bufferSize)
            __addUINT8(hService, DSP_CMD_REFRESH);
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandSetColor(
    axDisplayServiceHandle hService,
    UINT8 fgColor,
    UINT8 bkColor) {

    if (!hService->bufferError) {
        if (hService->bufferCount + (sizeof(BYTE) * 3) < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_SETCOLOR);
            __addUINT8(hService, fgColor);
            __addUINT8(hService, bkColor);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandSetFont(
    axDisplayServiceHandle hService,
    UINT8 font) {

    if (!hService->bufferError) {
        if (hService->bufferCount + (sizeof(BYTE) * 2) < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_SETFONT);
            __addUINT8(hService, font);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandMoveTo(
    axDisplayServiceHandle hService,
    int x,
    int y) {

    if (!hService->bufferError) {
        if (hService->bufferCount + sizeof(BYTE) * 5 < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_MOVETO);
            __addUINT16(hService, x);
            __addUINT16(hService, y);
        }
        else
            hService->bufferError = true;
    }

    return hService->bufferError;
}


bool axDisplayAddCommandDrawLine(
    axDisplayServiceHandle hService,
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

        axDisplayAddBytes(hService, (BYTE*) &msg, 12);//sizeof(msg));
    }

    return hService->bufferError;
}


bool axDisplayAddCommandDrawRectangle(
    axDisplayServiceHandle hService,
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

        axDisplayAddBytes(hService, (BYTE*) &msg, 12);//sizeof(msg));
    }

    return hService->bufferError;
}


bool axDisplayAddCommandFillRectangle(
    axDisplayServiceHandle hService,
    int x1,
    int y1,
    int x2,
    int y2) {

    if (!hService->bufferError) {

       if (hService->bufferCount + sizeof(BYTE) * 12 < hService->bufferSize) {
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


bool axDisplayAddCommandDrawText(
    axDisplayServiceHandle hService,
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

        if (hService->bufferCount + sizeof(BYTE) * 8 + len < hService->bufferSize) {
            __addUINT8(hService, DSP_CMD_DRAWTEXT);
            __addUINT8(hService, 0xFF);
            __addUINT8(hService, 0xFF);
            __addUINT16(hService, x);
            __addUINT16(hService, y);
            __addUINT8(hService, len);
            axDisplayAddBytes(hService, &text[offset], len);
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
 *           bool axDisplayIsBusy(
 *               axDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hService: El handler del display
 *
 *       Retorn:
 *         True si es ocupat, false en cas contrari
 *
 *************************************************************************/

bool axDisplayIsBusy(
    axDisplayServiceHandle hService) {

    return hService->isBusy;
}


/*************************************************************************
 *
 *       Procesa l'event END_TRANSACTION
 *
 *       Funcio:
 *           void onEndTransaction(
 *               eosI2CTransactionHandle hTransaction,
 *               axDisplayServiceHandle hService)
 *
 *       Entrada:
 *           hTransaction: La transaccio que ha generat l'event
 *           hService    : El handler del display
 *
 *************************************************************************/

static void onEndTransaction(
    eosI2CTransactionHandle hTransaction) {

    axDisplayServiceHandle hService = (axDisplayServiceHandle) eosI2CMasterGetTransactionContext(hTransaction);
    hService->isBusy = false;
}
