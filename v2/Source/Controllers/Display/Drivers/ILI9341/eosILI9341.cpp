#include "eos.hpp"
#include "Controllers/Display/Drivers/eosILI9341.hpp"
#include "HAL/halTMR.h"


#if !defined(ILI9341_COLORMODE_565) && !defined(ILI9341_COLORMODE_666)
#error "No se especifico ILI9342_COLORMODE_xxx"
#endif


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
    
// Parametres de la comanda MEMORY_ACCESS_CONTROL
//
#define MAC_MX_OFF    0b00000000
#define MAC_MX_ON     0b10000000
#define MAC_MY_OFF    0b00000000
#define MAC_MY_ON     0b01000000
#define MAC_MV_OFF    0b00000000
#define MAC_MV_ON     0b00100000


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
ILI9341_Driver::ILI9341_Driver() {

    screenWidth = MAX_COLUMNS;
    screenHeight = MAX_ROWS;    
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
    io.wrCommand(CMD_SLEEP_OUT);
    halTMRDelay(120);

    uint8_t c;
    const uint8_t *p = initData;
    while ((c = *p++) != 0) {
        io.wrCommand(*p++);
        while (--c != 0)
            io.wrData(*p++);
    }

    io.wrCommand(CMD_SLEEP_OUT);
    halTMRDelay(120);

    io.wrCommand(CMD_DISPLAY_ON);
    halTMRDelay(50);
    
    io.end();
}
    

/// ----------------------------------------------------------------------
/// \brief Desativa la pantalla
///
void ILI9341_Driver::shutdown() {
    
    io.begin();
    io.wrCommand(CMD_DISPLAY_OFF);
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
            screenWidth = MAX_COLUMNS;
            screenHeight = MAX_ROWS;
            data = 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF;
            break;
            
        case Orientation::rotate90:
            screenWidth = MAX_ROWS;
            screenHeight = MAX_COLUMNS;
            data = 0x08 | MAC_MV_ON | MAC_MX_ON | MAC_MY_OFF;
            break;
            
        case Orientation::rotate180:
            screenWidth = MAX_COLUMNS;
            screenHeight = MAX_ROWS;
            data = 0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_ON;
            break;
            
        case Orientation::rotate270:            
            screenWidth = MAX_ROWS;
            screenHeight = MAX_COLUMNS;
            data = 0x08 | MAC_MV_ON | MAC_MX_OFF | MAC_MY_ON;
            break;
    }

    io.begin();
    io.wrCommand(CMD_MEMORY_ACCESS_CONTROL);
    io.wrData(data);    
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla
/// \param color: Color per borrar
///
void ILI9341_Driver::clear(
    Color color) {
    
    selectRegion(0, 0, screenWidth, screenHeight);
    startMemoryWrite();
    writePixel(color, screenWidth * screenHeight);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un pixel.
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param color: Color del pixel.
///
void ILI9341_Driver::setPixel(
    int16_t x, 
    int16_t y,
    Color color) {
    
    selectRegion(x, y, 1, 1);
    startMemoryWrite();
    writePixel(color, 1);    
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels horitzontals. 
/// \param x: Coordinada X.
/// \param y: Colordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setHPixels(
    int16_t x, 
    int16_t y, 
    int16_t length,
    Color color) {
    
    selectRegion(x, y, length, 1);
    startMemoryWrite();
    writePixel(color, length);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia de pixels en vertical. 
/// \param x: Coordinada X.
/// \param y: Coordinada Y.
/// \param length: Longitut de la linia.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setVPixels(
    int16_t x, 
    int16_t y, 
    int16_t length,
    Color color) {
    
    selectRegion(x, y, 1, length);
    startMemoryWrite();
    writePixel(color, length);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param color: Color dels pixels.
///
void ILI9341_Driver::setPixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    Color color) {
    
    selectRegion(x, y, width, height);
    startMemoryWrite();
    writePixel(color, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una regio rectangular de pixels.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \param colors: Color dels pixels.
///
void ILI9341_Driver::writePixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    const Color* colors) {
    
    selectRegion(x, y, width, width);
    startMemoryWrite();
    writePixel(colors, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una regio rectangular de pixels. No hi ha cap tipus de 
///        comprovacio de la validesa dels parametres.
/// \param x: Posicio X.
/// \param y: Posicio Y.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
/// \params colors: Buffer on deixar els pixels.
///
void ILI9341_Driver::readPixels(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height, 
    Color *colors) {
    
    selectRegion(x, y, width, height);
    startMemoryRead();
    readPixel(colors, width * height);
}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll vertical de la pantalla.
/// \param delta: Numero de lineas a desplaçar. El signe indica la direccio.
/// \param x: Posicio x de la regio.
/// \param y: Posicio y de la regio.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
///
void ILI9341_Driver::vScroll(
    int16_t delta, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    static Color buffer[MAX_COLUMNS];
    
    if (delta > 0) {

        for (int16_t i = y; i < height - y - delta; i++) {

            selectRegion(x, i + delta, width, 1);
            startMemoryRead();
            readPixel(buffer, width);

            selectRegion(x, i, width, 1);
            startMemoryWrite();
            writePixel(buffer, width);
        }
    }

    else if (delta < 0) {

    }
}


/// ----------------------------------------------------------------------
/// \brief Realitza un scroll horitzontal de la pantalla.
/// \param delta: Numero de lineas a desplaçar. El signe indica la direccio.
/// \param delta: Numero de lineas a desplaçar. El signe indica la direccio.
/// \param x: Posicio x de la regio.
/// \param y: Posicio y de la regio.
/// \param width: Amplada de la regio.
/// \param height: Alçada de la regio.
///
void ILI9341_Driver::hScroll(
    int16_t delta, 
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
   
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
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {   
    
    int16_t x2 = x + width - 1;
    int16_t y2 = y + height - 1;
    
    io.begin();
    
    io.wrCommand(CMD_COLUMN_ADDRESS_SET);
	io.wrData(x >> 8);
	io.wrData(x);
	io.wrData(x2 >> 8);
	io.wrData(x2);
    
	io.wrCommand(CMD_PAGE_ADDRESS_SET);
	io.wrData(y >> 8);
	io.wrData(y);
	io.wrData(y2 >> 8);
	io.wrData(y2);
    
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Inicia la escritura de memoria.
///
void ILI9341_Driver::startMemoryWrite() {
    
    io.begin();
    io.wrCommand(CMD_MEMORY_WRITE);
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Inicia la lectura de memoria.
///
void ILI9341_Driver::startMemoryRead() {
    
    io.begin();
    io.wrCommand(CMD_MEMORY_READ);
    io.end();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un color en el controlador.
/// \param data: El color.
/// \param count: Numero de copies a escriure.
///
void ILI9341_Driver::writePixel(
    Color color,
    int32_t count) {    
    
#if defined(ILI9341_COLORMODE_565)    

    uint32_t c = color.c;
    uint8_t c1 = (uint32_t)(((c & 0x00F80000) >> 16) | ((c & 0x0000E000) >> 13));
    uint8_t c2 = (uint32_t)(((c & 0x00001C00) >> 5) | ((c &0x000000F8) >> 3));
    
    io.begin();
    while (count--) {
        io.wrData(c1);        
        io.wrData(c2);
    }
    io.end();
    
#elif defined(ILI9341_COLORMODE_666)
    
    uint32_t c = color.c;
    uint8_t c1 = (uint32_t)(c & 0x00FC0000) >> 16;
    uint8_t c2 = (uint32_t)(c & 0x0000FC00) >> 8;
    uint8_t c3 = (uint32_t)(c & 0x000000FC);
   
    io.begin();
    while (count--) {
        io.wrData(c1);
        io.wrData(c2);
        io.wrData(c3);
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
    int32_t count) {
    
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
    int32_t count) {
 
    io.begin();
    io.rdData();               // Dummy read
    io.rdData();               // Dummy read
    while (count--) {
        
#if defined(ILI9341_COLORMODE_565)        
        uint8_t volatile c1 = io.rdData();
        uint8_t volatile c2 = io.rdData();
        uint8_t volatile c3 = io.rdData();
        Color color(c1, c2, c3);
        *colors++ = color;
        
#elif defined(ILI9341_COLORMODE_666)        
#endif        
        
    }
    io.end();
}
