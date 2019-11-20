#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "System/eosString.h"
#include "System/IO/eosStream.h"


#include "../../../MD-DSP04/DSP04Messages.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    buffer: Buffer on deixar la comanda.
/// \param    bufferSize: Tamany del buffer.
///
GfxCommandBuilder::GfxCommandBuilder(
    uint8_t *buffer, 
    int bufferSize):

    stream(buffer, bufferSize) {    
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un byte en el stream.
/// \param    data: El byte a escriure.
///
void GfxCommandBuilder::writeByte(
    uint8_t data) {
    
    stream.write(data, 1);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una sequencia de bytes en el stream.
/// \param    data: Llista de bytes.
/// \param    size: Numero de bytes en la llista.
///
void GfxCommandBuilder::writeBytes(
    const uint8_t *data, 
    int size) {
    
    stream.write(data, size);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un enter de 16 bits en el stream.
/// \param    data: En enter de 16 bits a escriure.
///
void GfxCommandBuilder::writeInt16(
    int16_t data) {
    
    stream.write(&data, 2);
}


/// ----------------------------------------------------------------------
/// \brief    Afageix un comanda per borrar pantalla.
///
void GfxCommandBuilder::cmdClear() {
    
    writeByte(DSP_CMD_CLEAR);    
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda per dibuixar una linia.
/// \param    x1: Coordinada X del inici de la linia.
/// \param    y1: Coordinada Y del inici de la linia.
/// \param    x2: Coordinada X del final de la linia.
/// \param    y2: Coordinada Y del final del la linia.
///
void GfxCommandBuilder::cmdDrawLine(
    int x1, 
    int y1, 
    int x2, 
    int y2) {
    
    writeByte(DSP_CMD_DRAWSHAPE);
    writeByte(0xFF);
    writeByte(0xFF);
    writeByte(DRAWSHAPE_LINE);
    writeInt16(x1);
    writeInt16(y1);
    writeInt16(x2);
    writeInt16(y2);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda per dinuixar un rectangle.
/// \param    x1: Coordinada X del inici de la linia.
/// \param    y1: Coordinada Y del inici de la linia.
/// \param    x2: Coordinada X del final de la linia.
/// \param    y2: Coordinada Y del final del la linia.
///
void GfxCommandBuilder::cmdDrawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    dspDrawShapeMessage msg;

    msg.cmd = DSP_CMD_DRAWSHAPE;
    msg.fillColor = 0xFF;
    msg.frameColor = 0xFF;
    msg.filled = false;
    msg.framed = true;
    msg.shape = DRAWSHAPE_RECT;
    msg.x1 = x1;
    msg.y1 = y1;
    msg.x2 = x2;
    msg.y2 = y2;    
    
    writeBytes((uint8_t*) &msg, sizeof(msg));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda per dibuixar un text.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada Y de la posicio.
/// \param    text: El text a dibuixar.
///
void GfxCommandBuilder::cmdDrawText(
    int x,
    int y, 
    const String &text) {
    
    int length = text.getLength();

    writeByte(DSP_CMD_DRAWTEXT);
    writeByte(0xFF);
    writeByte(0xFF);
    writeInt16(x);
    writeInt16(y);
    writeByte(length);
    writeBytes((uint8_t*)(const char*) text, length);    
}

void GfxCommandBuilder::cmdLineTo(
    int x, 
    int y) {
    
}


void GfxCommandBuilder::cmdMoveTo(
    int x, 
    int y) {
    
    writeByte(DSP_CMD_MOVETO);
    writeInt16(x);
    writeInt16(y);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda per refrescar la pantalla.
///
void GfxCommandBuilder::cmdRefresh() {
    
    writeByte(DSP_CMD_REFRESH);    
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda per seleccionar el color.
///
void GfxCommandBuilder::cmdSetColor(
    uint8_t fgColor, 
    uint8_t bkColor) {
    
    writeByte(DSP_CMD_SETCOLOR);
    writeByte(fgColor);
    writeByte(bkColor);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda per seleccionar el font.
/// \param    font: El font.
///
void GfxCommandBuilder::cmdSetFont(
    uint8_t font) {
    
    writeByte(DSP_CMD_SETFONT);
    writeByte(font);
}
