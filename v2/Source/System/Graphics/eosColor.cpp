#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosColor.h"


using namespace eos;


/*
/// ----------------------------------------------------------------------
/// \brief Contructor.
/// \param size: Tamany del buffer.
///
ColorBuffer::ColorBuffer(
    int size) {

#if defined(DISPLAY_COLOR_ARGB) || defined(DISPLAY_COLOR_RGB)
    buffer = new uint32_t[size];
#elif defined(DISPLAY_COLOR_565)
    buffer = new uint16_t[size];
#endif
}


/// ----------------------------------------------------------------------
/// \brief Destructor.
///
ColorBuffer::~ColorBuffer() {

    delete buffer;
}


/// ----------------------------------------------------------------------
/// \brief Constructor.
///
ColorPalette::ColorPalette() {

    colorTable[COLOR_PAL_Black] = Color(COLOR_Black);
    colorTable[COLOR_PAL_White] = Color(COLOR_White);
    colorTable[COLOR_PAL_Blue] = Color(COLOR_Blue);
    colorTable[COLOR_PAL_Cyan] = Color(COLOR_Cyan);
    colorTable[COLOR_PAL_Magenta] = Color(COLOR_Magenta);
    colorTable[COLOR_PAL_Silver] = Color(COLOR_Silver);
    colorTable[COLOR_PAL_Gray] = Color(COLOR_Gray);
    colorTable[COLOR_PAL_Maroon] = Color(COLOR_Maroon);
    colorTable[COLOR_PAL_Purple] = Color(COLOR_Purple);
    colorTable[COLOR_PAL_Teal] = Color(COLOR_Teal);
    colorTable[COLOR_PAL_Navy] = Color(COLOR_Navy);
}


/// ----------------------------------------------------------------------
/// \brief Assigna un color a la paleta.
/// \param index: Index del color.
/// \param color: El color a asignar.
///
void ColorPalette::setColor(
    uint8_t index,
    Color color) {

    if ((index >= 20) & (index <= 255))
        colorTable[index] = color;
}
*/
