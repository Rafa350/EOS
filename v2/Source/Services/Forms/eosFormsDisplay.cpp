#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Controllers/Display/eosDisplay.hpp"


using namespace eos;


#define CMD_END               0
#define CMD_CLEAR             1
#define CMD_DRAWLINE          2
#define CMD_DRAWRECTANGLE     3
#define CMD_DRAWTEXT          4
#define CMD_FILLRECTANGLE     5
#define CMD_SETCOLOR          6
#define CMD_SETFONT           7

static uint8_t __buffer[8192];


/// ---------------------------------------------------------------------
/// \brier Contructor.
/// \param display: Handler del controlador del display.
///
FormsDisplay::FormsDisplay(
    Display *_display):
    display(_display) {
    
    bufferSize = sizeof(__buffer);
    buffer = __buffer;
    //buffer = (uint8_t*) eosHeapAlloc(nullptr, bufferSize);
    
    buffer[0] = CMD_END;     // Marca de final
    wrIdx = 0;               // Inicialitza el punter d'escriptura
    wrError = false;         // Borrel'indicador d'error
}


/// ----------------------------------------------------------------------
/// \brief Inicia el proces de dibuix de la pantalla.
///
void FormsDisplay::beginDraw(
    int16_t x,
    int16_t y, 
    int16_t width,
    int16_t height) {
    
}


/// ----------------------------------------------------------------------
/// \brief Finalitza el proces de dibuix de pantalla.
///
void FormsDisplay::endDraw() {
    
    render();
}


/// ----------------------------------------------------------------------
/// \brief Selecciona el color per dibuixar.
/// \param color: El color.
///
void FormsDisplay::setColor(
    unsigned color) {
    
    if (wrCheck(5)) {
        wr8(CMD_SETCOLOR);
        wr32(color);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \brief Borra la pantalla.
/// \param color: Color
///
void FormsDisplay::clear(
    Color color) {
    
    if (wrCheck(5)) {
        wr8(CMD_CLEAR);
        wr32(color);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa una linia.
/// \param x1: Coordinada x inicial.
/// \param y1: Coordinada y inicial.
/// \param x2: Coordinada x final.
/// \param y2: Coordinada y final.
///
void FormsDisplay::drawLine(
    int16_t x1, 
    int16_t y1, 
    int16_t x2, 
    int16_t y2) {
    
    if (wrCheck(9)) {
        wr8(CMD_DRAWLINE);
        wr16(x1);
        wr16(y1);
        wr16(x2);
        wr16(y2);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::drawRectangle(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    if (wrCheck(9)) {
        wr8(CMD_DRAWRECTANGLE);
        wr16(x);
        wr16(y);
        wr16(x + width - 1);
        wr16(y + height - 1);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un texte.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param text: Texte a dibuixar.
/// \param offset: Posicio del primer caracter a dibuixar.
/// \param length: Numero de caracters a dibuixar.
///
void FormsDisplay::drawText(
    int16_t x, 
    int16_t y, 
    const char* text, 
    int16_t offset,
    int16_t length) {
    
    if (wrCheck(11 + strlen(text))) {
        wr8(CMD_DRAWTEXT);
        wr16(x);
        wr16(y);
        wrs(text);
        wr16(offset);
        wr16(length);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \brief Dibuixa un rectangle ple.
/// \param x: Coordinada x de la posicio.
/// \param y: Coordinada y de la posicio.
/// \param width: Amplada.
/// \param height: Alçada.
///
void FormsDisplay::fillRectangle(
    int16_t x, 
    int16_t y, 
    int16_t width, 
    int16_t height) {
    
    if (wrCheck(9)) {
        wr8(CMD_FILLRECTANGLE);
        wr16(x);
        wr16(y);
        wr16(x + width - 1);
        wr16(y + height - 1);
        wrEND();
    }
}


/// ----------------------------------------------------------------------
/// \bried Renderitza la llista de visualitzacio
///
void FormsDisplay::render() {

    bool done = false;
    rdIdx = 0;
    while (!done) {
        switch (rd8()) {
            case CMD_END:
                done = true;
                break;
                
            case CMD_SETCOLOR:
                display->setColor(rd32());
                break;
                
            case CMD_CLEAR:
                display->clear(rd32());
                break;
                
            case CMD_DRAWLINE:
                display->drawLine(rd16(), rd16(), rd16(), rd16());
                break;

            case CMD_DRAWRECTANGLE:
                display->drawRectangle(rd16(), rd16(), rd16(), rd16());
                break;
                
            case CMD_DRAWTEXT:
                display->drawText(rd16(), rd16(), rds(), rd16(), rd16());
                break;                

            case CMD_FILLRECTANGLE:
                display->fillRectangle(rd16(), rd16(), rd16(), rd16());
                break;
        }
    }

    buffer[0] = CMD_END;     // Marca de final
    wrIdx = 0;               // Inicia el punter d'escriptura
    wrError = false;         // Borra l'indicador d'error
}


/// ----------------------------------------------------------------------
/// \bried Escriu un enter de 8 bits en la llista de visualitzacio.
/// \param d: Les dades a escriure.
///
void FormsDisplay::wr8(
    uint8_t d) {
    
    buffer[wrIdx++] = d;
}


/// ----------------------------------------------------------------------
/// \bried Escriu un enter de 16 bits en la llista de visualitzacio.
/// \param d: Les dades a escriure.
///
void FormsDisplay::wr16(
    uint16_t d) {
    
    buffer[wrIdx++] = d >> 8;
    buffer[wrIdx++] = d;
}


/// ----------------------------------------------------------------------
/// \bried Escriu un enter de 32 bits en la llista de visualitzacio.
/// \param d: Les dades a escriure.
///
void FormsDisplay::wr32(
    uint32_t d) {
    
    buffer[wrIdx++] = d >> 24;
    buffer[wrIdx++] = d >> 16;
    buffer[wrIdx++] = d >> 8;
    buffer[wrIdx++] = d;
}


/// ----------------------------------------------------------------------
/// \brief Escriu la marca de final.
///
void FormsDisplay::wrEND() {
    
    buffer[wrIdx] = CMD_END;    
}


/// ----------------------------------------------------------------------
/// \bried Escriu un cadena de texte en la llista de visualitzacio.
/// \param s: La cadena a escriure.
///
void FormsDisplay::wrs(
    const char *s) {
    
    uint16_t l = strlen(s);
    wr16(l);
    while (l--)
        wr8(*s++);
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un enter de 8 bits.
/// \return El enter lleigit
//
uint8_t FormsDisplay::rd8() {

    return buffer[rdIdx++];
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un enter de 16 bits.
/// \return El enter lleigit
//
uint16_t FormsDisplay::rd16() {
    
    return (rd8() << 8) | rd8();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix un enter de 32 bits.
/// \return El enter lleigit
//
uint32_t FormsDisplay::rd32() {
    
    return (rd16() << 16) | rd16();
}


/// ----------------------------------------------------------------------
/// \brief Llegeix una cadena de texte.
/// \return El enter lleigit
//
const char *FormsDisplay::rds() {
    
    uint16_t l = rd16();
    
    const char *s = (const char*) &buffer[rdIdx];
    rdIdx += l;
    
    return s;
}


bool FormsDisplay::wrCheck(
    uint16_t size) {

    if (!wrError) 
        wrError = (wrIdx + size + 1) >= bufferSize;
    return !wrError;
}