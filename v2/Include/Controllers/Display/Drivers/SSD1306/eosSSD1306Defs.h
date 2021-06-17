#ifndef __eosSSD1306Defs__
#define __eosSSD1306Defs__


// Comandes del controlador
//
#define CMD_NOP                             0xE3
#define CMD_SET_CONTRAST_CONTROL            0x81
#define CMD_SET_NORMAL_DISPLAY              0xA6
#define CMD_SET_INVERSE_DISPLAY             0xA7
#define CMD_DISPLAY_ON                      0xAF
#define CMD_DISPLAY_OFF                     0xAE
#define CMD_SET_PRECHARGE_PERIOD            0xD9
#define CMD_SET_DISPLAY_CLOCK               0xD5
#define CMD_SET_MULTIPLEX_RATIO             0xA8
#define CMD_SET_MEMORY_MODE                 0x20
#define CMD_SET_SEGMENT_REMAP               0xA0
#define CMD_SET_SCAN_DIRECTION              0xC0
#define CMD_SET_HARDWARE_CONFIGURATION      0xDA
#define CMD_SET_DISPLAY_OFFSET              0xD3
#define CMD_SET_START_LINE                  0x40


#define OP_END                              0
#define OP_DELAY                            255
#define OP_CMD_DISPLAY_OFF                  1, CMD_DISPLAY_OFF
#define OP_CMD_DISPLAY_ON                   1, CMD_DISPLAY_ON
#define OP_CMD_SET_DISPLAY_OFFSET(p)        2, CMD_SET_DISPLAY_OFFSET, p
#define OP_CMD_SET_START_LINE(p)            1, CMD_SET_START_LINE | p
#define OP_CMD_SET_CONTRAST_CONTROL(p)      1, CMD_SET_CONTRAST_CONTROL, p
#define OP_CMD_SET_PRECHARGE_PERIOD(p)    	2, CMD_SET_PRECHARGE_PERIOD, p
#define OP_CMD_SET_DISPLAY_CLOCK(p)         2, CMD_SET_DISPLAY_CLOCK, p
#define OP_CMD_SET_MULTIPLEX_RATIO(p)       2, CMD_SET_MULTIPLEX_RATIO, p
#define OP_CMD_SET_MEMORY_MODE(p)           2, CMD_SET_MEMORY_MODE, p
#define OP_CMD_SET_SEGMENT_REMAP(p)         1, CMD_SET_SEGMENT_REMAP | p
#define OP_CMD_SET_COM_SCAN_DIR(p)          1, CMD_SET_SCAN_DIRECTION | (p << 4)
#define OP_CMD_SET_COM_HARDWARE_CFG(p)      1, CMD_SET_HARDWARE_CONFIGURATION, p


#endif // __eosSSD1306Defs__
