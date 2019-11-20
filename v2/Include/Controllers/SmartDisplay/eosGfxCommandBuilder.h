
class GfxCommandBuilder {
    private:
        MemoryStream stream;
        
    private:
        void writeByte(uint8_t data);
        void writeBytes(const uint8_t *data, int data);
        void writeInt16(int16_t data);
        
    public:
        GfxCommandBuilder(uint8_t *buffer, int bufferSize);
        
        void cmdClear();
        void cmdDrawLine(int x1, int y1, int x2, int y2);
        void cmdDrawRectangle(int x1, int y1, int x2, int y2);
        void cmdDrawText(int x, int y, const String &text);
        void cmdLineTo(int x, int y);
        void cmdMoveTo(int x, int y);
        void cmdRefresh();
        void cmdSetColor(uint8_t fgColor, uint8_t bkColor);
        void cmdSetFont(uint8_t font);
    
};
