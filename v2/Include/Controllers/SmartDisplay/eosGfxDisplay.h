#ifndef __eosGfxDisplay__
#define	__eosGfxDisplay__


#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "Services/eosI2CMasterService.h"
#include "System/eosCallbacks.h"
#include "System/Core/eosSemaphore.h"


namespace eos {
    
    class String;
    
    class GfxDisplay {
        private:
            typedef CallbackP1<GfxDisplay, const I2CMasterService::TransactionEventArgs&> TransactionCallback;

        private:
            I2CMasterService *i2cService;
            BinarySemaphore lock;
            int curX;
            int curY;
            uint8_t color;
            uint8_t addr;
            uint8_t *buffer;
            GfxCommandBuilder cb;
            TransactionCallback transactionCallback;
            
        private:
            void transactionHandler(const I2CMasterService::TransactionEventArgs &args);
            
        public:
            GfxDisplay(I2CMasterService *i2cService, uint8_t addr);
            ~GfxDisplay();
            void setColor(uint8_t color);
            void setFont(uint8_t font);
            int getTextWidth(const char *text);
            int getTextHeight(const char *text);
            void putTTY(char ch);
            void putTTY(const char *s);
            void putTTY(const char *s, int length);
            void clear(uint8_t color);
            void refresh();
            inline void home() { moveTo(0, 0); }
            void moveTo(int x, int y);
            void lineTo(int x, int y);
            void arcTo(int x, int y, int cx, int cy);
            void drawLine(int x1, int y1, int x2, int y2);
            void drawRectangle(int x1, int y1, int x2, int y2);
            void drawEllipse(int x1, int y1, int x2, int y2);
            void drawCircle(int cx, int cy, int r);
            void drawBitmap1BPP(int x, int y, const uint8_t *bitmap, int sx, int sy, uint8_t color);
            int drawChar(int x, int y, char c);
            int drawString(int x, int y, const String &s);
            void fillRectangle(int x1, int y1, int x2, int y2);
            void fillEllipse(int x1, int y1, int x2, int y2);
            void fillCircle(int cx, int cy, int r);     
    };
}


#endif // __eosGfxDisplay__

