#include "Controllers/Display/Drivers/eosST7565.hpp"


ST7565_IO::ST7565_IO() {
    
}


void ST7565_IO::initialize() {
    
} 


void ST7565_IO::reset() {
    
}


void ST7565_IO::begin() {
    
}


void ST7565_IO::end() {
    
}


void ST7565_IO::address(
    uint8_t addr) {
        
}


void ST7565_IO::write(
    uint8_t data) {

    GSCR_A0Hi();
    GSCR_CSLo();
    GSCR_WriteByte(data);
    GSCR_CSHi();
}


uint8_t ST7565_IO::read() {
    
}
