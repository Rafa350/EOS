#ifndef __eosGfxCommandBuilder__
#define __eosGfxCommandBuilder__


#include "eos.h"
#include "System/IO/eosStream.h"


namespace eos {
    
    class String;

    class GfxCommandBuilder {
        private:
            Stream &stream;

        private:


        public:
            GfxCommandBuilder(Stream &stream);

            void clear();
            
            void cmdClear();
            void cmdDrawLine(int x1, int y1, int x2, int y2);
            void cmdDrawRectangle(int x1, int y1, int x2, int y2);
            void cmdDrawText(int x, int y, const String &text);
            void cmdMoveTo(int x, int y);
            void cmdRefresh();
            void cmdSetColor(uint8_t fgColor, uint8_t bkColor);
            void cmdSetFont(uint8_t font);
    };

}


#endif // __eosGfxCommandBuilder__