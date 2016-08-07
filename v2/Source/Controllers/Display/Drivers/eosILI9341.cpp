#include "Controllers/Display/Drivers/eosILI9341.hpp"


// Parametres de la pantalla
//
#define MAX_COLUMNS          240
#define MAX_ROWS             320

   
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
    
#define MAC_MX_OFF    0b00000000
#define MAC_MX_ON     0b10000000
#define MAC_MY_OFF    0b00000000
#define MAC_MY_ON     0b01000000
#define MAC_MV_OFF    0b00000000
#define MAC_MV_ON     0b00100000


using namespace eos;


static void selectRegion(int x1, int y1, int x2, int y2);
static void delay(unsigned ms);
static void send(uint8_t data);
static void writeCommand(uint8_t command);
static void writeParameter(uint8_t parameter);
static void writePixel(Color color, unsigned count);


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
ILI9341_DisplayDriver::ILI9341_DisplayDriver() {

    xScreenSize = MAX_COLUMNS;
    yScreenSize = MAX_ROWS;    
    
    xClipPos = 0;
    yClipPos = 0;
    xClipSize = xScreenSize;
    yClipSize = yScreenSize;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza la pantalla.
///
void ILI9341_DisplayDriver::initialize() {

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
        2, CMD_MEMORY_ACCESS_CONTROL, 0x08, 
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
    
    // Inicialitza els pins de control
    //
    ILI9341_initRST();
    ILI9341_initCS();
    ILI9341_initRS();
    
    // Inicialitza els pins de comunicacio
    //
#if defined(ILI9341_INTERFACE_4WIRE2)
    ILI9341_initCLK();
    ILI9341_initSO();
    ILI9341_initSI();
#else
#error "No s'ha especificat el tipus de comunicacio amb el driver"  
#endif    
    
    // Reset del controlador
    //
    delay(5);
    ILI9341_clrRST();
    delay(10);
    ILI9341_setRST();
    delay(120);
    
    // Sequencia d'inicialitzacio del controlador
    //
    writeCommand(CMD_SLEEP_OUT);
    delay(120);

    uint8_t c;
    const uint8_t *p = initData;
    while ((c = *p++) != 0) {
        writeCommand(*p++);
        while (--c != 0)
            writeParameter(*p++);
    }

    writeCommand(CMD_SLEEP_OUT);
    delay(120);

    writeCommand(CMD_DISPLAY_ON);
    delay(50);
}
    

/// ----------------------------------------------------------------------
/// \brief Desativa la pantalla
///
void ILI9341_DisplayDriver::shutdown() {
    
    writeCommand(CMD_DISPLAY_OFF);
}


/// ----------------------------------------------------------------------
/// \brief Selecciona l'orientacio de la pantalla.
/// \param orientation: Orientacio (0=0, 1=90, 2=180, 3=270)
///
void ILI9341_DisplayDriver::setOrientation(
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

    writeCommand(CMD_MEMORY_ACCESS_CONTROL);
    writeParameter(data);    
}


/// ----------------------------------------------------------------------
/// \bried Selecciona la regio on dibuixar.
/// \param xPos: Coordinada X esquerra.
/// \param yPos: Coodinada Y superior.
/// \param xSize: Coordinada X dreta.
/// \param ySize: Coordinada Y inferior.
///
void ILI9341_DisplayDriver::setClip(
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize) {
    
    xClipPos = xPos < 0 ? 0 : xPos;
    yClipPos = yPos < 0 ? 0 : yPos;
    xClipSize = xSize > xScreenSize ? xScreenSize : xSize;
    yClipSize = ySize > yScreenSize ? yScreenSize : ySize;
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla
/// \param color: Color per borrar
///
void ILI9341_DisplayDriver::clear(
    Color color) {
    
    selectRegion(0, 0, xScreenSize - 1, yScreenSize - 1);
    writeCommand(CMD_MEMORY_WRITE);
    writePixel(color, xScreenSize * yScreenSize);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param xPos: Coordinada X.
/// \param yPos: Coordinada Y.
/// \param color: Color del pixel.
///
void ILI9341_DisplayDriver::setPixel(
    int xPos, 
    int yPos,
    Color color) {
    
    if ((xPos >= 0) && (xPos < xScreenSize) && 
        (yPos >= 0) && (yPos < yScreenSize)) {
        
        selectRegion(xPos, yPos, xPos, yPos);
        writeCommand(CMD_MEMORY_WRITE);
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
void ILI9341_DisplayDriver::setHPixels(
    int xPos, 
    int yPos, 
    int size,
    Color color) {
    
    if ((yPos >= 0) && (yPos < yScreenSize)) {
        
        if (xPos < 0)
            xPos = 0;
        if (xPos + size >= xScreenSize)
            size = xScreenSize - xPos;
        
        selectRegion(xPos, yPos, xPos + size - 1, yPos);
        writeCommand(CMD_MEMORY_WRITE);
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
void ILI9341_DisplayDriver::setVPixels(
    int xPos, 
    int yPos, 
    int size,
    Color color) {
    
    if ((xPos >= 0) && (xPos < xScreenSize)) {
       
        if (yPos < 0)
            yPos = 0;
        if (yPos + size >= yScreenSize)
            size = yScreenSize - yPos;
        
        selectRegion(xPos, yPos, xPos, yPos + size - 1);
        writeCommand(CMD_MEMORY_WRITE);
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
void ILI9341_DisplayDriver::setPixels(
    int xPos, 
    int yPos, 
    int xSize, 
    int ySize, 
    Color color) {
    
    if ((xPos >= 0) && (xPos + xSize < xScreenSize) &&
        (yPos >= 0) && (yPos + ySize < yScreenSize)) {
     
        selectRegion(xPos, yPos, xPos + xSize - 1, yPos + ySize - 1);
        writeCommand(CMD_MEMORY_WRITE);
        writePixel(color, xSize * ySize);
    }    
}


/// ----------------------------------------------------------------------
/// \brief Selecciona la finestra de treball per les transferencies de 
///        pixels.
/// \param x1: Coordinada X origen.
/// \param y1: Coordinada Y oriden.
/// \param x2: Coordinada X final.
/// \param y2: Coordinada Y final.
///
static void selectRegion(
    int x1, 
    int y1, 
    int x2, 
    int y2) {    
    
    writeCommand(CMD_COLUMN_ADDRESS_SET);
	writeParameter(x1 >> 8);
	writeParameter(x1);
	writeParameter(x2 >> 8);
	writeParameter(x2);
    
	writeCommand(CMD_PAGE_ADDRESS_SET);
	writeParameter(y1 >> 8);
	writeParameter(y1);
	writeParameter(y2 >> 8);
	writeParameter(y2);
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
/// \brief Transmiteix dades al controlador.
/// \param data: Les dades a transmetre.
///
static void send(uint8_t data) {

    uint8_t mask;
    for (mask = 0x80; mask; mask >>= 1) {
        ILI9341_clrCLK();
        if ((data & mask) != 0)
            ILI9341_setSO();
        else
            ILI9341_clrSO();
        ILI9341_setCLK();
    }    
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda en el controlador.
/// \param command: La comanda a escriure.
///
static void writeCommand(
    uint8_t command) {
    
    ILI9341_clrRS();         // RS = 0
    ILI9341_clrCS();         // CS = 0
    send(command);
    ILI9341_setCS();         // CS = 1
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de parametre en el controlador.
/// \param parameter: El parametre a escriure.
///
static void writeParameter(
    uint8_t parameter) {
    
    ILI9341_setRS();         // RS = 1
    ILI9341_clrCS();         // CS = 0
    send(parameter);
    ILI9341_setCS();         // CS = 1
}


/// ----------------------------------------------------------------------
/// \brief Escriu un color en el controlador.
/// \param data: El color a escriure.
/// \param count: Numero de copies a escriure.
///
static void writePixel(
    Color color,
    unsigned count) {
    
    
#if defined(ILI9341_COLORMODE_565)    

    uint8_t r = (color & 0x00FF0000) >> 19;
    uint8_t g = (color & 0x0000FF00) >> 10;
    uint8_t b = (color & 0x000000FF) >> 3;

    uint8_t c0 = (r << 3) | ((g & 0x38) >> 3);
    uint8_t c1 = ((g & 0x03) << 5) | b;
    
    ILI9341_setRS();
    ILI9341_clrCS();
    while (count--) {
        send(c0);
        send(c1);
    }
    ILI9341_setCS();
    
#elif defined(ILI9341_COLORMODE_666)
   
    uint8_t r = (color & 0x00FC0000) >> 16;
    uint8_t g = (color & 0x0000FC00) >> 8;
    uint8_t b = color & 0x000000FC;
    
    ILI9341_setRS();
    ILI9341_clrCS();
    while (count--) {
        send(r);
        send(g);
        send(b);
    }
    ILI9341_setCS();
    
#endif    
}
