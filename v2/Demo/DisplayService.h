#ifndef __AX_DISPLAYSERVICE_H
#define	__AX_DISPLAYSERVICE_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_I2CMASTER_H
#include "Services/eosI2CMaster.h"
#endif


typedef struct __axDisplayService *axDisplayServiceHandle;

typedef struct {
    eosI2CMasterServiceHandle hI2CMasterService;
    BYTE i2cAddr;
} axDisplayServiceParams;


extern axDisplayServiceHandle axDisplayServiceInitialize(axDisplayServiceParams *params);
extern bool axDisplayServiceIsReady(axDisplayServiceHandle hService);
extern void axDisplayServiceTask(axDisplayServiceHandle hService);

extern bool axDisplayBeginCommand(axDisplayServiceHandle hService);
extern bool axDisplayEndCommand(axDisplayServiceHandle hService);
extern bool axDisplayIsBusy(axDisplayServiceHandle hService);

extern bool axDisplayAddUINT8(axDisplayServiceHandle hService, UINT8 data);
extern bool axDisplayAddUINT16(axDisplayServiceHandle hService, UINT16 data);
extern bool axDisplayAddString(axDisplayServiceHandle hService, const char *data);
extern bool axDisplayAddBytes(axDisplayServiceHandle hService, const BYTE *data, unsigned dataLen);
extern bool axDisplayAddCommandClear(axDisplayServiceHandle hService);
extern bool axDisplayAddCommandRefresh(axDisplayServiceHandle hService);
extern bool axDisplayAddCommandSetColor(axDisplayServiceHandle hService, UINT8 fgColor, UINT8 bkColor);
extern bool axDisplayAddCommandSetFont(axDisplayServiceHandle hService, UINT8 font);
extern bool axDisplayAddCommandMoveTo(axDisplayServiceHandle hService, int x, int y);
extern bool axDisplayAddCommandDrawLine(axDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool axDisplayAddCommandDrawRectangle(axDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool axDisplayAddCommandFillRectangle(axDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool axDisplayAddCommandDrawText(axDisplayServiceHandle hService, int x, int y, const char *text, unsigned offset, unsigned length);


#endif

