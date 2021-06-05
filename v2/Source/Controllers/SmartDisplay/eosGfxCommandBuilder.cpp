#include "eos.h"
#include "Controllers/SmartDisplay/eosGfxCommandBuilder.h"
#include "System/eosString.h"
#include "../../../MD-DSP04/DSP04Messages.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    buffer: Buffer on generar la comanda.
/// \param    bufferSize: Tamany del buffer.
///
GfxCommandBuilder::GfxCommandBuilder(
    uint8_t *buffer, int bufferSize):

    buffer(buffer),
    bufferSize(bufferSize),
    bufferPos(0) {
}


/// ---------------------------------------------------------------------
/// \brief    Borra el contingut i comenÃ§a de nou.
///
void GfxCommandBuilder::clear() {

    bufferPos = 0;
}


/// ----------------------------------------------------------------------
/// \brief    Afageix un comanda CLEAR.
///
void GfxCommandBuilder::cmdClear() {

    DspClearMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_CLEAR;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda DRAWSHAPE per dibuixar una linia.
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

    DspDrawShapeMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
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
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda DRAWSHAPE per dibuixar un rectangle.
/// \param    x1: Coordinada X de la cantonada superior-esquerra.
/// \param    y1: Coordinada Y de la cantionada supterior-esquerra.
/// \param    x2: Coordinada X de la cantonada inferior-dreta.
/// \param    y2: Coordinada Y de la cantonada inferior-dreta.
///
void GfxCommandBuilder::cmdDrawRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    DspDrawShapeMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
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
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda DRAWSHAPE per dibuixar una el·lipse.
/// \param    x1: Coordinada X de la cantonada superior-esquerra.
/// \param    y1: Coordinada Y de la cantionada supterior-esquerra.
/// \param    x2: Coordinada X de la cantonada inferior-dreta.
/// \param    y2: Coordinada Y de la cantonada inferior-dreta.
///
void GfxCommandBuilder::cmdDrawEllipse(
    int x1,
    int y1,
    int x2,
    int y2) {

    DspDrawShapeMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_DRAWSHAPE;
        msg.fillColor = 0xFF;
        msg.frameColor = 0xFF;
        msg.filled = false;
        msg.framed = true;
        msg.shape = DRAWSHAPE_ELLIPSE;
        msg.x1 = x1;
        msg.y1 = y1;
        msg.x2 = x2;
        msg.y2 = y2;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda DRAWTEXT.
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada Y de la posicio.
/// \param    text: El text a dibuixar.
///
void GfxCommandBuilder::cmdDrawText(
    int x,
    int y,
    const String &text) {

    DspDrawTextMessage msg;

    int length = text.getLength();
    int size = length + sizeof(msg);

    if (bufferPos + size < bufferSize) {
        msg.cmd = DSP_CMD_DRAWTEXT;
        msg.color = 0xFF;
        msg.font = 0xFF;
        msg.x = x;
        msg.y = y;
        msg.textLen = length;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        memcpy(&buffer[bufferPos + sizeof(msg)], (const char*)text, length);
        bufferPos += size;
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda DRAWSHAPE per dibuixar un rectangle.
/// \param    x1: Coordinada X de la cantonada superior-esquerra.
/// \param    y1: Coordinada Y de la cantionada supterior-esquerra.
/// \param    x2: Coordinada X de la cantonada inferior-dreta.
/// \param    y2: Coordinada Y de la cantonada inferior-dreta.
///
void GfxCommandBuilder::cmdFillRectangle(
    int x1,
    int y1,
    int x2,
    int y2) {

    DspDrawShapeMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_DRAWSHAPE;
        msg.fillColor = 0xFF;
        msg.frameColor = 0xFF;
        msg.filled = true;
        msg.framed = false;
        msg.shape = DRAWSHAPE_RECT;
        msg.x1 = x1;
        msg.y1 = y1;
        msg.x2 = x2;
        msg.y2 = y2;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda DRAWSHAPE per dibuixar una el·lipse.
/// \param    x1: Coordinada X de la cantonada superior-esquerra.
/// \param    y1: Coordinada Y de la cantionada supterior-esquerra.
/// \param    x2: Coordinada X de la cantonada inferior-dreta.
/// \param    y2: Coordinada Y de la cantonada inferior-dreta.
///
void GfxCommandBuilder::cmdFillEllipse(
    int x1,
    int y1,
    int x2,
    int y2) {

    DspDrawShapeMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_DRAWSHAPE;
        msg.fillColor = 0xFF;
        msg.frameColor = 0xFF;
        msg.filled = true;
        msg.framed = false;
        msg.shape = DRAWSHAPE_ELLIPSE;
        msg.x1 = x1;
        msg.y1 = y1;
        msg.x2 = x2;
        msg.y2 = y2;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda 'MOVETO'
/// \param    x: Coordinada X de la posicio.
/// \param    y: Coordinada Y de la posicio.
///
void GfxCommandBuilder::cmdMoveTo(
    int x,
    int y) {

    DspMoveToMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_MOVETO;
        msg.x = x;
        msg.y = y;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda 'REFRESH'.
///
void GfxCommandBuilder::cmdRefresh() {

    DspRefreshMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_REFRESH;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix una comanda 'SETCOLOR'.
///
void GfxCommandBuilder::cmdSetColor(
    uint8_t fgColor,
    uint8_t bkColor) {

    DspSetColorMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_SETCOLOR;
        msg.fgColor = fgColor;
        msg.bkColor = bkColor;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
        bufferPos += sizeof(msg);
    }
}


/// ----------------------------------------------------------------------
/// \brief    Afegeig una comanda 'SETFONT'.
/// \param    font: El font.
///
void GfxCommandBuilder::cmdSetFont(
    uint8_t font) {

    DspSetFontMessage msg;

    if (bufferPos + sizeof(msg) < bufferSize) {
        msg.cmd = DSP_CMD_SETFONT;
        msg.font = font;
        memcpy(&buffer[bufferPos], &msg, sizeof(msg));
    }
}
