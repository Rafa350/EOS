#ifndef __AX_DISPLAYSERVICE_H
#define	__AX_DISPLAYSERVICE_H


#ifndef __EOS_H
#include "eos.h"
#endif

#ifndef __EOS_I2CMASTER_H
#include "Services/eosI2CMaster.h"
#endif


typedef struct __eosDisplayService *eosDisplayServiceHandle;

typedef struct {
    eosI2CMasterServiceHandle hI2CMasterService;
    uint8_t i2cAddr;
} eosDisplayServiceParams;


extern eosDisplayServiceHandle eosDisplayServiceInitialize(eosDisplayServiceParams *params);

extern bool eosDisplayBeginCommand(eosDisplayServiceHandle hService);
extern bool eosDisplayEndCommand(eosDisplayServiceHandle hService);
extern bool eosDisplayIsBusy(eosDisplayServiceHandle hService);

extern bool eosDisplayAddUINT8(eosDisplayServiceHandle hService, uint8_t data);
extern bool eosDisplayAddUINT16(eosDisplayServiceHandle hService, uint16_t data);
extern bool eosDisplayAddString(eosDisplayServiceHandle hService, const char *data);
extern bool eosDisplayAddBytes(eosDisplayServiceHandle hService, const uint8_t *data, unsigned dataLen);
extern bool eosDisplayAddCommandClear(eosDisplayServiceHandle hService);
extern bool eosDisplayAddCommandRefresh(eosDisplayServiceHandle hService);
extern bool eosDisplayAddCommandSetColor(eosDisplayServiceHandle hService, uint8_t fgColor, uint8_t bkColor);
extern bool eosDisplayAddCommandSetFont(eosDisplayServiceHandle hService, uint8_t font);
extern bool eosDisplayAddCommandMoveTo(eosDisplayServiceHandle hService, int x, int y);
extern bool eosDisplayAddCommandDrawLine(eosDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool eosDisplayAddCommandDrawRectangle(eosDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool eosDisplayAddCommandFillRectangle(eosDisplayServiceHandle hService, int x1, int y1, int x2, int y2);
extern bool eosDisplayAddCommandDrawText(eosDisplayServiceHandle hService, int x, int y, const char *text, unsigned offset, unsigned length);


#endif

