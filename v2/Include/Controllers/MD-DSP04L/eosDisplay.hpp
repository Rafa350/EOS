#ifndef __EOS_CONTROLLERS_MDDSP04L_DISPLAY_HPP
#define	__EOS_CONTROLLERS_MDDSP04L_DISPLAY_HPP


#include "eos.hpp"
#include "Services/eosI2CMaster.hpp"


namespace eos {
    
    class Display;
    typedef Display *DisplayHandle;
    
    typedef unsigned Color;

    class Display {
        private:
            I2CMasterService *i2cService;
            int curX;
            int curY;
            uint8_t addr;
            uint8_t *buffer;
            unsigned bufferSize;
            unsigned bufferCount;
            bool bufferError;
            
        public:
            Display(I2CMasterService *i2cService, uint8_t addr);
            ~Display();
            void setColor(Color color);
            //void setFont(Font *font);
            int getTextWidth(const char *text);
            int getTextHeight(const char *text);
            void putTTY(char ch);
            void putTTY(const char *s);
            void putTTY(const char *s, int length);
            void clear(Color color);
            inline void home() { moveTo(0, 0); }
            void moveTo(int x, int y);
            void lineTo(int x, int y);
            void arcTo(int x, int y, int cx, int cy);
            void drawLine(int x1, int y1, int x2, int y2);
            void drawRectangle(int x1, int y1, int x2, int y2);
            void drawCircle(int cx, int cy, int r);
            void drawBitmap1BPP(int x, int y, const uint8_t *bitmap, int sx, int sy, Color color);
            int drawChar(int x, int y, char c);
            int drawString(int x, int y, const char *s);
            void fillRectangle(int x1, int y1, int x2, int y2);
            void fillCircle(int cx, int cy, int r);              

        private:
            bool beginCommand();
            bool endCommand();
            bool addUINT8(uint8_t data);
            bool addUINT16(uint16_t data);
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
            inline static int min(int a, int b) {
                return a < b ? a : b; 
            }
            inline void fAddUINT8(uint8_t data) {
                buffer[bufferCount++] = data;
            }
            inline void fAddUINT16(uint16_t data) {
                buffer[bufferCount++] = data & 0x00FF;       
                buffer[bufferCount++] = (data & 0xFF00) >> 8;
            }
    };

}


#endif

