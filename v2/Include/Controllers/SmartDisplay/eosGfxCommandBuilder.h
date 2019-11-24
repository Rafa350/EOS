#ifndef __eosGfxCommandBuilder__
#define __eosGfxCommandBuilder__


#include "eos.h"


namespace eos {
    
    class String;

    class GfxCommandBuilder {
        private:
            uint8_t *buffer;
            int bufferSize;
            int bufferPos;

        private:


        public:
            GfxCommandBuilder(uint8_t *buffer, int bufferSize);

            void clear();
            
            void cmdClear();
            void cmdDrawLine(int x1, int y1, int x2, int y2);
            void cmdDrawRectangle(int x1, int y1, int x2, int y2);
            void cmdDrawEllipse(int x1, int y1, int x2, int y2);
            void cmdDrawText(int x, int y, const String &text);
            void cmdFillRectangle(int x1, int y1, int x2, int y2);
            void cmdFillEllipse(int x1, int y1, int x2, int y2);
            void cmdMoveTo(int x, int y);
            void cmdRefresh();
            void cmdSetColor(uint8_t fgColor, uint8_t bkColor);
            void cmdSetFont(uint8_t font);
            
            uint8_t *getBuffer() const { return buffer; }
            int getBufferPos() const { return bufferPos; }
            int getBufferSize() const { return bufferSize; }
    };

}


#endif // __eosGfxCommandBuilder__