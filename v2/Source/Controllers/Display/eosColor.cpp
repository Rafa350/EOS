#include "Controllers/Display/eosColor.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Mescla un color
/// \param c: El color a mesclar.
/// \param mix: Valor alpha de la mescla.
/// \return El resultat de la mescla.
///
Color Color::mix(
    Color c, 
    uint8_t mix) {
    
    return Color(
        (uint16_t)((uint16_t) getR() * mix + (c.getR() * (255 - mix))) >> 8,
        (uint16_t)((uint16_t) getG() * mix + (c.getG() * (255 - mix))) >> 8,  
        (uint16_t)((uint16_t) getB() * mix + (c.getB() * (255 - mix))) >> 8);
}


/// ----------------------------------------------------------------------
/// \brief Converteix un color a la seva representacio interna.
/// \return El resultat de l'operacio.
///
#if !defined(DISPLAY_COLOR_565)
uint16_t Color::to565() const {

    return (((uint32_t)(((c & 0x00F80000) >> 16) | ((c & 0x0000E000) >> 13))) << 8) |
           (uint32_t)(((c & 0x00001C00) >> 5) | ((c &0x000000F8) >> 3));
    
}
#endif


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
    
    if (index >= 20 & index <= 255)
        colorTable[index] = color;
}