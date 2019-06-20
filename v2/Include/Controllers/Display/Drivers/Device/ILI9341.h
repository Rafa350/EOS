#ifndef __ILI9341__
#define __ILI9341__


#include "eos.h"


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
#define CMD_INTERFACE_CONTROL                              0xF6
#define CMD_PUMP_RATIO_CONTROL                             0xF7

// Parametres de la comanda MEMORY_ACCESS_CONTROL
//
#define MAC_MX_OFF    0b00000000
#define MAC_MX_ON     0b10000000
#define MAC_MY_OFF    0b00000000
#define MAC_MY_ON     0b01000000
#define MAC_MV_OFF    0b00000000
#define MAC_MV_ON     0b00100000


// Macros de creacio de taules de comandes
//
#define __SOFTWARE_RESET \
	1, CMD_SOFTWARE_RESET

#define __READ_DISPLAY_INFORMATION
#define __READ_DISPLAY_STATUS
#define __READ_DISPLAY_POWER_MODE
#define __READ_DISPLAY_MADCTL
#define __READ_DISPLAY_PIXEL_FORMAT
#define __READ_DISPLAY_IMAGE_FORMAT
#define __READ_DISPLAY_SINGLE_MODE
#define __READ_DISPLAY_SELF_DIAGNOSTIC_RESULT
#define __ENTER_SLEEP_MODE

#define __SLEEP_OUT \
	1, CMD_SLEEP_OUT

#define __PARTIAL_MODE_ON
#define __NORMAL_DISPLAY_MODE_ON
#define __DISPLAY_INVERSION_OFF
#define __DISPLAY_INVERSION_ON

#define __GAMMA_SET(p1) \
	2, CMD_GAMMA_SET, p1

#define __DISPLAY_OFF

#define __DISPLAY_ON \
	1, CMD_DISPLAY_ON

#define __COLUMN_ADDRESS_SET(p1, p2, p3, p4) \
	5, CMD_COLUMN_ADDRESS_SET, p1, p2, p3, p4

#define __PAGE_ADDRESS_SET(p1, p2, p3, p4) \
	5, CMD_PAGE_ADDRESS_SET, p1, p2, p3, p4

#define __MEMORY_WRITE \
	1, CMD_MEMORY_WRITE

#define __COLOR_SET
#define __MEMORY_READ
#define __PARTIAL_AREA
#define __VERTICAL_SCROLLING_DEFINITION
#define __TEARING_EFFECT_LINE_OFF
#define __TEARING_EFFECT_LINE_ON

#define __MEMORY_ACCESS_CONTROL(p1) \
	2, CMD_MEMORY_ACCESS_CONTROL, p1

#define __VERTICAL_SCROLLING_START_ADDRESS
#define __IDLE_MODE_OFF
#define __IDLE_MODE_ON

#define __PIXEL_FORMAT_SET(p1) \
	2, CMD_PIXEL_FORMAT_SET, p1

#define __WRITE_MEMORY_CONTINUE
#define __READ_MEMORY_CONTINUE
#define __SET_TEAR_SCANLINE
#define __GET_SCANLINE
#define __WRITE_DISPLAY_BRIGNESS
#define __READ_DISPLAY_BRIGNESS
#define __WRITE_CTRL_DISPLAY
#define __READ_CTRL_DISPLAY
#define __WRITE_CONTENT_ADAPTIVE_BRIGNESS_CONTROL
#define __READ_CONTENT_ADAPTIVE_BRIGNESS_CONTROL
#define __WRITE_CABC_MINIMUM_BRIGNESS
#define __READ_CABC_MINIMUM_BRIGNESS
#define __READ_ID1
#define __READ_ID2
#define __READ_ID3

#define __RGB_INTERFACE_SIGNAL_CONTROL(p1) \
	2, CMD_RGB_INTERFACE_SIGNAL_CONTROL, p1

#define __FRAME_RATE_CONTROL_1(p1, p2) \
	3, CMD_FRAME_RATE_CONTROL_1, p1, p2

#define __FRAME_RATE_CONTROL_2
#define __FRAME_RATE_CONTROL_3
#define __DISPLAY_INVERSION_CONTROL
#define __BLANKING_PORCH_CONTROL

#define __DISPLAY_FUNCTION_CONTROL(p1, p2, p3, p4) \
	5, CMD_DISPLAY_FUNCTION_CONTROL, p1, p2, p3, p4

#define __ENTRY_MODE_SET
#define __BACKLIGHT_CONTROL_1
#define __BACKLIGHT_CONTROL_2
#define __BACKLIGHT_CONTROL_3
#define __BACKLIGHT_CONTROL_4
#define __BACKLIGHT_CONTROL_5
#define __BACKLIGHT_CONTROL_7
#define __BACKLIGHT_CONTROL_8

#define __POWER_CONTROL_1(p1) \
	2, CMD_POWER_CONTROL_1, p1

#define __POWER_CONTROL_2(p1) \
	2, CMD_POWER_CONTROL_2, p1

#define __VCOM_CONTROL_1(p1, p2) \
	3, CMD_VCOM_CONTROL_1, p1, p2

#define __VCOM_CONTROL_2(p1) \
	2, CMD_VCOM_CONTROL_2, p1

#define __NV_MEMORY_WRITE
#define __NV_MEMORY_PROTECTION_KEY
#define __NV_MEMORY_STATUS_READ
#define __READ_ID4

#define __POSITIVE_GAMMA_CORRECTION(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15) \
	16, CMD_POSITIVE_GAMMA_CORRECTION, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15

#define __NEGATIVE_GAMMA_CORRECTION(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15) \
	16, CMD_NEGATIVE_GAMMA_CORRECTION, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15

#define __DIGITAL_GAMMA_CONTROL_1
#define __DIGITAL_GAMMA_CONTROL_2

#define __POWER_CONTROL_A(p1, p2, p3, p4, p5) \
	6, CMD_POWER_CONTROL_A, p1, p2, p3, p4, p5

#define __POWER_CONTROL_B(p1, p2, p3) \
	4, CMD_POWER_CONTROL_B, p1, p2, p3

#define __DRIVER_TIMING_CONTROL_A(p1, p2, p3) \
	4, CMD_DRIVER_TIMING_CONTROL_A, p1, p2, p3

#define __DRIVER_TIMING_CONTROL_B(p1, p2) \
	3, CMD_DRIVER_TIMING_CONTROL_B, p1, p2

#define __POWER_ON_SEQUENCE_CONTROL(p1, p2, p3, p4) \
	5, CMD_POWER_ON_SEQUENCE_CONTROL, p1, p2, p3, p4

#define __ENABLE_3G(p1) \
	2, CMD_ENABLE_3G, p1

#define __INTERFACE_CONTROL(p1, p2, p3) \
	4, CMD_INTERFACE_CONTROL, p1, p2, p3

#define __PUMP_RATIO_CONTROL(a) \
	2, CMD_PUMP_RATIO_CONTROL, a


namespace eos {
    
    class ILI9341 {
        public:
            void initialize();
            void open();
            void close();
            void writeCommand(uint8_t cmd);
            void writeData(uint8_t data);
            void writeData(uint8_t *data, int size);
            uint8_t readData();
    };
    
}


#endif // __ILI9341__