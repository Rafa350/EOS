#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "System/eosString.h"
#include "System/IO/eosStream.h"
#include "../../../MD-DSP04/DSP04Messages.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    stream: Stream on escriure la comanda.
///
GfxCommandBuilder::GfxCommandBuilder(
    Stream &stream):

    stream(stream) {    
}


/// ---------------------------------------------------------------------
/// \brief    Borra el contingut i comença de nou.
///
void GfxCommandBuilder::clear() {

    
}


/// ----------------------------------------------------------------------
/// \brief    Afageix un comanda per borrar pantalla.
///
void GfxCommandBuilder::cmdClear() {
    
    dspClearMessage msg;    
    msg.cmd = DSP_CMD_CLEAR;
    
    stream.write(&msg, sizeof(msg));    
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
    
    dspDrawShapeMessage msg;    
    msg.cmd = DSP_CMD_DRAWSHAPE;
    msg.fillColor = 0xFF;
    msg.frameColor = 0xFF;
    msg.filled = false;
    msg.framed = true;
    msg.shape = DRAWSHAPE_LINE;
    msg.x1 = x1;
    msg.y1 = y1;
    msg.x2 = x2;
    msg.y2 = y2;   
    
    stream.write(&msg, sizeof(msg));
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
    
    stream.write(&msg, sizeof(msg));
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

    dspDrawTextMessage msg;    
    msg.cmd = DSP_CMD_DRAWTEXT;
    msg.color = 0xFF;
    msg.font = 0xFF;
    msg.x = x;
    msg.y = y;
    msg.textLen = length;
    
    stream.write(&msg, sizeof(msg));
    stream.write((const char*)text, length);    
}


void GfxCommandBuilder::cmdMoveTo(
    int x, 
    int y) {
    
    dspMoveToMessage msg;
    msg.cmd = DSP_CMD_MOVETO;
    msg.x = x;
    msg.y = y;
    
    stream.write(&msg, sizeof(msg));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda per refrescar la pantalla.
///
void GfxCommandBuilder::cmdRefresh() {
    
    dspRefreshMessage msg;
    msg.cmd = DSP_CMD_REFRESH;

    stream.write(&msg, sizeof(msg));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda per seleccionar el color.
///
void GfxCommandBuilder::cmdSetColor(
    uint8_t fgColor, 
    uint8_t bkColor) {
    
    dspSetColorMessage msg;
    msg.cmd = DSP_CMD_SETCOLOR;
    msg.fgColor = fgColor;
    msg.bkColor = bkColor;

    stream.write(&msg, sizeof(msg));
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda per seleccionar el font.
/// \param    font: El font.
///
void GfxCommandBuilder::cmdSetFont(
    uint8_t font) {
    
    dspSetFontMessage msg;
    msg.cmd = DSP_CMD_SETFONT;
    msg.font = font;

    stream.write(&msg, sizeof(msg));   
}
