#ifndef __EOS_DISPLAY_HPP
#define	__EOS_DISPLAY_HPP


#include "eos.hpp"
#include "System/eosTask.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {

    class DisplayService: IRunable {
        private:
            I2CMasterService *i2cService;
            uint8_t addr;
            uint8_t *buffer;
            unsigned bufferSize;
            unsigned bufferCount;
            bool bufferError;
            
        public:
            DisplayService(I2CMasterService *i2cService, uint8_t addr);
            bool BeginCommand();
            bool EndCommand();
            bool addUINT8(uint8_t data);
            bool addUINT16(uint8_t data);
            bool addString(const char *data);
            bool addBytes(const uint8_t *data, unsigned dataLen);
            bool addCommandClear();
            bool addCommandRefresh();
            bool addCommandSetColor(uint8_t fgColor, uint8_t bkColor);
            bool addCommandSetFont(uint8_t font);
            bool addCommandMoveTo(int x, int y);
            bool addCommandDrawLine(int x1, int y1, int x2, int y2);
            bool addCommandDrawRectangle(int x1, int y1, int x2, int y2);
            bool addCommandFillRectangle(int x1, int y1, int x2, int y2);
            bool addCommandDrawText(int x, int y, const char *text, unsigned offset, unsigned length);
        private:
            void run();
    };

}


#endif

