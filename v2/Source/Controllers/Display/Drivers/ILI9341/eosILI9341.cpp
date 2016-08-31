#include "Controllers/Display/Drivers/eosILI9341.hpp"


#if !defined(ILI9341_COLORMODE_565) && !defined(ILI9341_COLORMODE_666)
#error "No se especifico ILI9342_COLORMODE_xxx"
#endif


// Parametres de la pantalla
//
#define MAX_COLUMNS          240
#define MAX_ROWS             320

// Adresses del controlador
//
#define ADDR_COMMAND           0
#define ADDR_DATA              1
   
// Comandes del controlador
//
#define CMD_NOP                                            0x00
#define CMD_SOFTWARE_RESET                                 0x01
#define CMD_READ_DISPLAY_INFORMATION                       0x04
#define CMD_READ_DISPLAY_STATUS                            0x09
#define CMD_READ_DISPLAY_POWER_MODE                        0x0A
#define CMD_READ_DISPLAY_MADCTL                            0x0B
#define CMD_READ_DISPLAY_PIXEL_FORMAT                      0x0C
#define CMD_READ_DISPLAY_IMAGE_FORMAT                      0x0D
#define CMD_READ_DISPLAY_SINGLE_MODE                       0x0E
#define CMD_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT            0x0F
#define CMD_ENTER_SLEEP_MODE                               0x10
#define CMD_SLEEP_OUT                                      0x11
#define CMD_PARTIAL_MODE_ON                                0x12
#define CMD_NORMAL_DISPLAY_MODE_ON                         0x13
#define CMD_DISPLAY_INVERSION_OFF                          0x20
#define CMD_DISPLAY_INVERSION_ON                           0x21
#define CMD_GAMMA_SET                                      0x26
#define CMD_DISPLAY_OFF                                    0x28
#define CMD_DISPLAY_ON                                     0x29
#define CMD_COLUMN_ADDRESS_SET                             0x2A
#define CMD_PAGE_ADDRESS_SET                               0x2B
#define CMD_MEMORY_WRITE                                   0x2C
#define CMD_COLOR_SET                                      0x2D
#define CMD_MEMORY_READ                                    0x2E
#define CMD_PARTIAL_AREA                                   0x30
#define CMD_VERTICAL_SCROLLING_DEFINITION                  0x33
#define CMD_TEARING_EFFECT_LINE_OFF                        0x34
#define CMD_TEARING_EFFECT_LINE_ON                         0x35
#define CMD_MEMORY_ACCESS_CONTROL                          0x36
#define CMD_VERTICAL_SCROLLING_START_ADDRESS               0x37
#define CMD_IDLE_MODE_OFF                                  0x38
#define CMD_IDLE_MODE_ON                                   0x39
#define CMD_PIXEL_FORMAT_SET                               0x3A
#define CMD_WRITE_MEMORY_CONTINUE                          0x3C
#define CMD_READ_MEMORY_CONTINUE                           0x3D
#define CMD_SET_TEAR_SCANLINE                              0x44
#define CMD_GET_SCANLINE                                   0x45
#define CMD_WRITE_DISPLAY_BRIGNESS                         0x51
#define CMD_READ_DISPLAY_BRIGNESS                          0x52
#define CMD_WRITE_CTRL_DISPLAY                             0x53
#define CMD_READ_CTRL_DISPLAY                              0x54
#define CMD_WRITE_CONTENT_ADAPTIVE_BRIGNESS_CONTROL        0x55
#define CMD_READ_CONTENT_ADAPTIVE_BRIGNESS_CONTROL         0x56
#define CMD_WRITE_CABC_MINIMUM_BRIGNESS                    0x5E
#define CMD_READ_CABC_MINIMUM_BRIGNESS                     0x5F
#define CMD_READ_ID1                                       0xDA
#define CMD_READ_ID2                                       0xDB
#define CMD_READ_ID3                                       0xDC
#define CMD_RGB_INTERFACE_SIGNAL_CONTROL                   0xB0
#define CMD_FRAME_RATE_CONTROL_1                           0xB1
#define CMD_FRAME_RATE_CONTROL_2                           0xB2
#define CMD_FRAME_RATE_CONTROL_3                           0xB3
#define CMD_DISPLAY_INVERSION_CONTROL                      0xB4
#define CMD_BLANKING_PORCH_CONTROL                         0xB5
#define CMD_DISPLAY_FUNCTION_CONTROL                       0xB6
#define CMD_ENTRY_MODE_SET                                 0xB7
#define CMD_BACKLIGHT_CONTROL_1                            0xB8
#define CMD_BACKLIGHT_CONTROL_2                            0xB9
#define CMD_BACKLIGHT_CONTROL_3                            0xBA
#define CMD_BACKLIGHT_CONTROL_4                            0xBB
#define CMD_BACKLIGHT_CONTROL_5                            0xBC
#define CMD_BACKLIGHT_CONTROL_7                            0xBE
#define CMD_BACKLIGHT_CONTROL_8                            0xBF
#define CMD_POWER_CONTROL_1                                0xC0
#define CMD_POWER_CONTROL_2                                0xC1
#define CMD_VCOM_CONTROL_1                                 0xC5
#define CMD_VCOM_CONTROL_2                                 0xC7
#define CMD_NV_MEMORY_WRITE                                0xD0
#define CMD_NV_MEMORY_PROTECTION_KEY                       0xD1
#define CMD_NV_MEMORY_STATUS_READ                          0xD2
#define CMD_READ_ID4                                       0xD3
#define CMD_POSITIVE_GAMMA_CORRECTION                      0xE0
#define CMD_NEGATIVE_GAMMA_CORRECTION                      0xE1
#define CMD_DIGITAL_GAMMA_CONTROL_1                        0xE2
#define CMD_DIGITAL_GAMMA_CONTROL_2                        0xE3
#define CMD_INTERFACE_CONTROL                              0xF6
#define CMD_POWER_CONTROL_A                                0xCB
#define CMD_POWER_CONTROL_B                                0xCF
#define CMD_DRIVER_TIMING_CONTROL_A                        0xE8
#define CMD_DRIVER_TIMING_CONTROL_B                        0xEA
#define CMD_POWER_ON_SEQUENCE_CONTROL                      0xED
#define CMD_ENABLE_3G                                      0xF2
#define CMD_PUMP_RATIO_CONTROL                             0xF7
    
// Parametres de la comanda MEMORY_ACCESS_CONTROL
//
#define MAC_MX_OFF    0b00000000
#define MAC_MX_ON     0b10000000
#define MAC_MY_OFF    0b00000000
#define MAC_MY_ON     0b01000000
#define MAC_MV_OFF    0b00000000
#define MAC_MV_ON     0b00100000


using namespace eos;


static void delay(unsigned ms);


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
ILI9341_Driver::ILI9341_Driver() {

    xScreenSize = MAX_COLUMNS;
    yScreenSize = MAX_ROWS;    
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la pantalla.
///
void ILI9341_Driver::initialize() {

    static const uint8_t initData[] = {
        4, CMD_POWER_CONTROL_B, 0x00, 0xC3, 0x30,        
     	5, CMD_POWER_ON_SEQUENCE_CONTROL, 0x64, 0x03, 0X12, 0X81,         
        4, CMD_DRIVER_TIMING_CONTROL_A, 0x85, 0x10, 0x79,        
        6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,        
        2, CMD_PUMP_RATIO_CONTROL, 0x20,
        3, CMD_DRIVER_TIMING_CONTROL_B, 0x00, 0x00,
       	2, CMD_POWER_CONTROL_1, 0x22, 
        2, CMD_POWER_CONTROL_2, 0x11, 
        3, CMD_VCOM_CONTROL_1, 0x3D, 0x20, 
        2, CMD_VCOM_CONTROL_2, 0xAA,
        2, CMD_MEMORY_ACCESS_CONTROL, 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF, 
#if defined(ILI9341_COLORMODE_565)        
        2, CMD_PIXEL_FORMAT_SET, 0x55,
#elif defined(ILI9341_COLORMODE_666)        
        2, CMD_PIXEL_FORMAT_SET, 0x66,
#endif        
        3, CMD_FRAME_RATE_CONTROL_1, 0x00, 0x13,
        3, CMD_DISPLAY_FUNCTION_CONTROL, 0x0A, 0xA2,
        3, CMD_INTERFACE_CONTROL, 0x01, 0x30, 
        2, CMD_ENABLE_3G, 0x00, 
        2, CMD_GAMMA_SET, 0x01,
        16, CMD_POSITIVE_GAMMA_CORRECTION, 0x0F, 0x3F, 0x2F, 0x0C, 0x10, 0x0A, 
            0x53, 0xD5, 0x40, 0x0A, 0x13, 0x03, 0x08, 0x03, 0x00,
        16, CMD_NEGATIVE_GAMMA_CORRECTION, 0x00, 0x00, 0x10, 0x03, 0x0F, 0x05, 
            0x2C, 0xA2, 0x3F, 0x05, 0x0E, 0x0C, 0x37, 0x3C, 0x0F,
        0
    };
    
    // inicialitza les comunicacions
    //
    io.initialize();

    // Reseteja el controlador
    //
    io.reset();
    
    // Sequencia d'inicialitzacio del controlador
    //
    io.begin();
    io.write(ADDR_COMMAND, CMD_SLEEP_OUT);
    delay(120);

    uint8_t c;
    const uint8_t *p = initData;
    while ((c = *p++) != 0) {
        io.write(ADDR_COMMAND, *p++);
        io.address(ADDR_DATA);
        while (--c != 0)
            io.write(*p++);
    }

    io.write(ADDR_COMMAND, CMD_SLEEP_OUT);
    delay(120);

    io.write(ADDR_COMMAND, CMD_DISPLAY_ON);
    delay(50);
    
    io.end();
}
    

/// ----------------------------------------------------------------------
/// \brief Desativa la pantalla
///
void ILI9341_Driver::shutdown() {
    
    io.begin();
    io.write(ADDR_COMMAND, CMD_DISPLAY_OFF);
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona l'orientacio de la pantalla.
/// \param orientation: Orientacio (0=0, 1=90, 2=180, 3=270)
///
void ILI9341_Driver::setOrientation(
    Orientation orientation) {
    
    uint8_t data;
    
    switch (orientation) {
        case Orientation::normal:
            xScreenSize = MAX_COLUMNS;
            yScreenSize = MAX_ROWS;
            data = 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF;
            break;
            
        case Orientation::rotate90:
            xScreenSize = MAX_ROWS;
            yScreenSize = MAX_COLUMNS;
            data = 0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_OFF;
            break;
            
        case Orientation::rotate180:
            xScreenSize = MAX_COLUMNS;
            yScreenSize = MAX_ROWS;
            data = 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_ON;
            break;
            
        case Orientation::rotate270:            
            xScreenSize = MAX_ROWS;
            yScreenSize = MAX_COLUMNS;
            data = 0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_ON;
            break;
    }

    io.begin();
    io.write(ADDR_COMMAND, CMD_MEMORY_ACCESS_CONTROL);
    io.write(ADDR_DATA, data);    
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla
/// \param color: Color per borrar
///
void ILI9341_Driver::clear(
    Color color) {
    
    selectRegion(0, 0, xScreenSize, yScreenSize);
    startMemoryWrite();
    writePixel(color, xScreenSize * yScreenSize);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param xPos: Coordinada X.
/// \param yPos: Coordinada Y.
/// \param color: Color del pixel.
///
void ILI9341_Driver::setPixel(
    int xPos, 
    int yPos,
    Color color) {
    
    // Comprova si es visible
    //
    if ((xPos >= 0) && (xPos < xScreenSize) && 
        (yPos >= 0) && (yPos < yScreenSize)) {
      
        // Dibuixa el pixel
        //
        selectRegion(xPos, yPos, 1, 1);
        startMemoryWrite();
        writePixel(color, 1);    
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals.
/// \param xPos: Coordinada X.
/// \param yPos: Colordinada Y.
/// \param size: Tamany de la serie.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setHPixels(
    int xPos, 
    int yPos, 
    int size,
    Color color) {
    
    // Comprova si es visible
    //
    if ((yPos >= 0) && (yPos < yScreenSize)) {
      
        // Retalla els extrems de la linia
        //
        if (xPos < 0)
            xPos = 0;
        if (xPos + size >= xScreenSize)
            size = xScreenSize - xPos;
        
        // Dibuiza la linia
        //
        selectRegion(xPos, yPos, size, 1);
        startMemoryWrite();
        writePixel(color, size);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical.
/// \param xPos: Coordinada X.
/// \param yPos: Coordinada Y.
/// \param size: Tamany de la serie.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setVPixels(
    int xPos, 
    int yPos, 
    int size,
    Color color) {
    
    // Comprova si es visible
    //
    if ((xPos >= 0) && (xPos < xScreenSize)) {
      
        // Retalla els extrems de la linia
        //
        if (yPos < 0)
            yPos = 0;
        if (yPos + size >= yScreenSize)
            size = yScreenSize - yPos;
        
        // Dibuixa la linia
        //
        selectRegion(xPos, yPos, 1, size);
        startMemoryWrite();
        writePixel(color, size);
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param xPos: Posicio X.
/// \param yPos: Posicio Y.
/// \param xSize: Amplada de la regio.
/// \param ySize: Alçada de la regio.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setPixels(
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize, 
    Color color) {
    
    // Comprova si es visible
    //
    if ((xPos >= 0) && (xPos + xSize < xScreenSize) &&
        (yPos >= 0) && (yPos + ySize < yScreenSize)) {
  
        // Retalla la regio
        //
        if (xPos < 0)
            xPos = 0;
        if (yPos < 0)
            yPos = 0;
     
        // Dibuixa la regio
        //
        selectRegion(xPos, yPos, xSize, ySize);
        startMemoryWrite();
        writePixel(color, xSize * ySize);
    }    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param xPos: Posicio X.
/// \param yPos: Posicio Y.
/// \param xSize: Amplada de la regio.
/// \param ySize: Alçada de la regio.
/// \param colors: Color dels pixels.
///
void ILI9341_Driver::writePixels(
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize, 
    const Color* colors) {
    
    if ((xPos >= 0) && (xPos + xSize < xScreenSize) &&
        (yPos >= 0) && (yPos + ySize < yScreenSize)) {
     
        selectRegion(xPos, yPos, xSize, ySize);
        startMemoryWrite();
        writePixel(colors, xSize * ySize);
    }    
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels.
/// \param xPos: Posicio X.
/// \param yPos: Posicio Y.
/// \param xSize: Amplada de la regio.
/// \param ySize: Alçada de la regio.
/// \params colors: Buffer on deixar els pixels.
///
void ILI9341_Driver::readPixels(
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize, 
    Color *colors) {
    
    if ((xPos >= 0) && (xPos + xSize < xScreenSize) &&
        (yPos >= 0) && (yPos + ySize < yScreenSize)) {
    
        selectRegion(xPos, yPos, xSize, ySize);
        startMemoryRead();
        readPixel(colors, xSize * ySize);
    }
}

/// ----------------------------------------------------------------------
/// \brief Realitza un scroll vertical de la pantalla.
/// \param delta: Numero de lineas a desplaçar. El signe indica la direccio.
///
void ILI9341_Driver::vScroll(
    int delta, 
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize) {
    
    static Color buffer[MAX_COLUMNS];
/*    
    if ((delta != 0) && (xClipSize > 0) && (yClipSize > 0)) {
        
        if (delta > 0) {

            for (int i = yClipPos; i < yClipSize - yClipPos - delta; i++) {

                selectRegion(xClipPos, i + delta, xClipSize, 1);
                startMemoryRead();
                readPixel(buffer, xClipSize);

                selectRegion(xClipPos, i, xClipSize, 1);
                startMemoryWrite();
                writePixel(buffer, xClipSize);
            }
        }
        
        else if (delta < 0) {

        }
    }
 */
}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal de la pantalla.
/// \param delta: Numero de lineas a desplaçar. El signe indica la direccio.
///
void ILI9341_Driver::hScroll(
    int delta, 
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize) {
   
}


/// ----------------------------------------------------------------------
/// \brief Selecciona la regio de treball per les transferencies de 
///        pixels.
/// \param x: Coordinada X origen.
/// \param y: Coordinada Y oriden.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
///
void ILI9341_Driver::selectRegion(
    int x, 
    int y, 
    int width, 
    int height) {   
    
    int x2 = x + width - 1;
    int y2 = y + height - 1;
    
    io.begin();
    
    io.write(ADDR_COMMAND, CMD_COLUMN_ADDRESS_SET);
    io.address(ADDR_DATA);
	io.write(x >> 8);
	io.write(x);
	io.write(x2 >> 8);
	io.write(x2);
    
	io.write(ADDR_COMMAND, CMD_PAGE_ADDRESS_SET);
    io.address(ADDR_DATA);
	io.write(y >> 8);
	io.write(y);
	io.write(y2 >> 8);
	io.write(y2);
    
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Inicia la escritura de memoria.
///
void ILI9341_Driver::startMemoryWrite() {
    
    io.begin();
    io.write(ADDR_COMMAND, CMD_MEMORY_WRITE);
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Inicia la lectura de memoria.
///
void ILI9341_Driver::startMemoryRead() {
    
    io.begin();
    io.write(ADDR_COMMAND, CMD_MEMORY_READ);
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Retard.
/// \params ms: Temps de retard en ms.
///
static void delay(unsigned ms) {
    
/*    unsigned startTime = ReadCT();
    while (((ReadCT() - startTime) * 1000) < ms)
        continue;
 */
    for (unsigned i = 0, ii = 10000 * ms; i < ii; i++)
        Nop();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un color en el controlador.
/// \param data: El color.
/// \param count: Numero de copies a escriure.
///
void ILI9341_Driver::writePixel(
    Color color,
    unsigned count) {    
    
#if defined(ILI9341_COLORMODE_565)    

    uint8_t c1 = (uint32_t)(((color & 0x00F80000) >> 16) | ((color & 0x0000E000) >> 13));
    uint8_t c2 = (uint32_t)(((color & 0x00001C00) >> 5) | ((color &0x000000F8) >> 3));
    
    io.begin();
    io.address(ADDR_DATA);
    while (count--) {
        io.write(c1);
        io.write(c2);
    }
    io.end();
    
#elif defined(ILI9341_COLORMODE_666)
    
    uint8_t c1 = (uint32_t)(color & 0x00FC0000) >> 16;
    uint8_t c2 = (uint32_t)(color & 0x0000FC00) >> 8;
    uint8_t c3 = (uint32_t)color & 0x000000FC;
   
    io.begin();
    io.address(ADDR_DATA);
    while (count--) {
        io.write(c1);
        io.write(c2);
        io.write(c3);
    }
    io.end();
    
#endif    
}


/// ----------------------------------------------------------------------
/// \brief Escriu una llista de colors en el controlador
/// \param colors: Llista de colors.
/// \param count: Numero d'elements en la llista.
///
void ILI9341_Driver::writePixel(
    const Color *colors, 
    unsigned count) {
    
    while (count--)
        writePixel(*colors++, 1);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una sequencia de colors.
/// \param colors: Llista de colors.
/// \param count: Numero de colors a lleigir.
///
void ILI9341_Driver::readPixel(
    Color *colors, 
    unsigned count) {
 
    io.begin();
    io.address(ADDR_DATA);
    io.read();               // Dummy read
    io.read();               // Dummy read
    while (count--) {
        
#if defined(ILI9341_COLORMODE_565)        
        uint8_t volatile c1 = io.read();
        uint8_t volatile c2 = io.read();
        uint8_t volatile c3 = io.read();
        Color color = RGB(c1, c2, c3);
        *colors++ = color;
        
#elif defined(ILI9341_COLORMODE_666)        
#endif        
        
    }
    io.end();
}
