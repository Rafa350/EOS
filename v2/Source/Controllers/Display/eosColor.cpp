#include "Controllers/Display/eosColor.hpp"


using namespace eos;


Color Color::mix(
    Color c, 
    uint8_t mix) {
    
    return Color(
        (uint16_t)((uint16_t) r * mix + (c.r * (256 - mix))) >> 8,
        (uint16_t)((uint16_t) g * mix + (c.g * (256 - mix))) >> 8,  
        (uint16_t)((uint16_t) b * mix + (c.b * (256 - mix))) >> 8);
}
