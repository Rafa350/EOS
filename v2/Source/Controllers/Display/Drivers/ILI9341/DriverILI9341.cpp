export module Eos.Controllers.Display.Drivers.ILI9341;

import Eos.Controllers.Display;
import Eos.Hardware.DMA;
import Eos.Hardware.GPIO;
import Eos.Hardware.SPI;
import Eos.System.Graphics.Color;
import Eos.Types;


using namespace eos::hardware::dma;
using namespace eos::hardware::gpio;
using namespace eos::hardware::spi;


export namespace eos {

    class Device_ILI9341;

    class DisplayDriver_ILI9341: public DisplayDriver {
    	private:
            Device_ILI9341 * const _devILI9341;
            Int16 _displayWidth;
            Int16 _displayHeight;
    		Int16 _maxX;
    		Int16 _maxY;

        public:
            DisplayDriver_ILI9341(Device_ILI9341 *devILI9341, Int16 displayWidth, Int16 displayHeight);

            void initialize() override;
            void deinitialize() override;

            void enable() override;
            void disable() override;

            inline Int16 getMaxX() const override { return _maxX; }
            inline Int16 getMaxY() const override { return _maxY; }
            inline Int16 getWidth() const override { return _displayWidth; }
            inline Int16 getHeight() const override { return _displayHeight; }

            void clear(Color color) override;

            void setPixel(Int16 x, Int16 y, Color color) override;
            void setHPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setVPixels(Int16 x, Int16 y, Int16 size, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, Color color) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const Color *colors, Int16 pitch) override;
            void setPixels(Int16 x, Int16 y, Int16 width, Int16 height, const void *pixels, ColorFormat format, Int16 pitch) override;

            void refresh() override;

        private:
            void writeRegion(Color color);
            void writeRegion(Color color, UInt32 count);
            void writeRegion(const Color *colors, UInt32 count);
            void readRegion(Color *colors, UInt32 count);
            void selectRegion(Int16 x1, Int16 y1, Int16 x2, Int16 y2);
    };

    class Device_ILI9341: private NonCopyableClass {
        public:
            struct OpCode {
                static constexpr UInt8 DELAY = 0xFF;
                static constexpr UInt8 END   = 0x00;
            };
            struct Command {
                static constexpr UInt8 NOP                                     = 0x00;
                static constexpr UInt8 SOFTWARE_RESET                          = 0x01;
                static constexpr UInt8 READ_DISPLAY_INFORMATION                = 0x04;
                static constexpr UInt8 READ_DISPLAY_STATUS                     = 0x09;
                static constexpr UInt8 READ_DISPLAY_POWER_MODE                 = 0x0A;
                static constexpr UInt8 READ_DISPLAY_MADCTL                     = 0x0B;
                static constexpr UInt8 READ_DISPLAY_PIXEL_FORMAT               = 0x0C;
                static constexpr UInt8 READ_DISPLAY_IMAGE_FORMAT               = 0x0D;
                static constexpr UInt8 READ_DISPLAY_SINGLE_MODE                = 0x0E;
                static constexpr UInt8 READ_DISPLAY_SELF_DIAGNOSTIC_RESULT     = 0x0F;
                static constexpr UInt8 ENTER_SLEEP_MODE                        = 0x10;
                static constexpr UInt8 SLEEP_OUT                               = 0x11;
                static constexpr UInt8 PARTIAL_MODE_ON                         = 0x12;
                static constexpr UInt8 NORMAL_DISPLAY_MODE_ON                  = 0x13;
                static constexpr UInt8 DISPLAY_INVERSION_OFF                   = 0x20;
                static constexpr UInt8 DISPLAY_INVERSION_ON                    = 0x21;
                static constexpr UInt8 GAMMA_SET                               = 0x26;
                static constexpr UInt8 DISPLAY_OFF                             = 0x28;
                static constexpr UInt8 DISPLAY_ON                              = 0x29;
                static constexpr UInt8 COLUMN_ADDRESS_SET                      = 0x2A;
                static constexpr UInt8 PAGE_ADDRESS_SET                        = 0x2B;
                static constexpr UInt8 MEMORY_WRITE                            = 0x2C;
                static constexpr UInt8 COLOR_SET                               = 0x2D;
                static constexpr UInt8 MEMORY_READ                             = 0x2E;
                static constexpr UInt8 PARTIAL_AREA                            = 0x30;
                static constexpr UInt8 VERTICAL_SCROLLING_DEFINITION           = 0x33;
                static constexpr UInt8 TEARING_EFFECT_LINE_OFF                 = 0x34;
                static constexpr UInt8 TEARING_EFFECT_LINE_ON                  = 0x35;
                static constexpr UInt8 MEMORY_ACCESS_CONTROL                   = 0x36;
                static constexpr UInt8 VERTICAL_SCROLLING_START_ADDRESS        = 0x37;
                static constexpr UInt8 IDLE_MODE_OFF                           = 0x38;
                static constexpr UInt8 IDLE_MODE_ON                            = 0x39;
                static constexpr UInt8 PIXEL_FORMAT_SET                        = 0x3A;
                static constexpr UInt8 WRITE_MEMORY_CONTINUE                   = 0x3C;
                static constexpr UInt8 READ_MEMORY_CONTINUE                    = 0x3D;
                static constexpr UInt8 SET_TEAR_SCANLINE                       = 0x44;
                static constexpr UInt8 GET_SCANLINE                            = 0x45;
                static constexpr UInt8 WRITE_DISPLAY_BRIGNESS                  = 0x51;
                static constexpr UInt8 READ_DISPLAY_BRIGNESS                   = 0x52;
                static constexpr UInt8 WRITE_CTRL_DISPLAY                      = 0x53;
                static constexpr UInt8 READ_CTRL_DISPLAY                       = 0x54;
                static constexpr UInt8 WRITE_CONTENT_ADAPTIVE_BRIGNESS_CONTROL = 0x55;
                static constexpr UInt8 READ_CONTENT_ADAPTIVE_BRIGNESS_CONTROL  = 0x56;
                static constexpr UInt8 WRITE_CABC_MINIMUM_BRIGNESS             = 0x5E;
                static constexpr UInt8 READ_CABC_MINIMUM_BRIGNESS              = 0x5F;
                static constexpr UInt8 READ_ID1                                = 0xDA;
                static constexpr UInt8 READ_ID2                                = 0xDB;
                static constexpr UInt8 READ_ID3                                = 0xDC;
                static constexpr UInt8 RGB_INTERFACE_SIGNAL_CONTROL            = 0xB0;
                static constexpr UInt8 FRAME_RATE_CONTROL_1                    = 0xB1;
                static constexpr UInt8 FRAME_RATE_CONTROL_2                    = 0xB2;
                static constexpr UInt8 FRAME_RATE_CONTROL_3                    = 0xB3;
                static constexpr UInt8 DISPLAY_INVERSION_CONTROL               = 0xB4;
                static constexpr UInt8 BLANKING_PORCH_CONTROL                  = 0xB5;
                static constexpr UInt8 DISPLAY_FUNCTION_CONTROL                = 0xB6;
                static constexpr UInt8 ENTRY_MODE_SET                          = 0xB7;
                static constexpr UInt8 BACKLIGHT_CONTROL_1                     = 0xB8;
                static constexpr UInt8 BACKLIGHT_CONTROL_2                     = 0xB9;
                static constexpr UInt8 BACKLIGHT_CONTROL_3                     = 0xBA;
                static constexpr UInt8 BACKLIGHT_CONTROL_4                     = 0xBB;
                static constexpr UInt8 BACKLIGHT_CONTROL_5                     = 0xBC;
                static constexpr UInt8 BACKLIGHT_CONTROL_7                     = 0xBE;
                static constexpr UInt8 BACKLIGHT_CONTROL_8                     = 0xBF;
                static constexpr UInt8 POWER_CONTROL_1                         = 0xC0;
                static constexpr UInt8 POWER_CONTROL_2                         = 0xC1;
                static constexpr UInt8 VCOM_CONTROL_1                          = 0xC5;
                static constexpr UInt8 VCOM_CONTROL_2                          = 0xC7;
                static constexpr UInt8 NV_MEMORY_WRITE                         = 0xD0;
                static constexpr UInt8 NV_MEMORY_PROTECTION_KEY                = 0xD1;
                static constexpr UInt8 NV_MEMORY_STATUS_READ                   = 0xD2;
                static constexpr UInt8 READ_ID4                                = 0xD3;
                static constexpr UInt8 POSITIVE_GAMMA_CORRECTION               = 0xE0;
                static constexpr UInt8 NEGATIVE_GAMMA_CORRECTION               = 0xE1;
                static constexpr UInt8 DIGITAL_GAMMA_CONTROL_1                 = 0xE2;
                static constexpr UInt8 DIGITAL_GAMMA_CONTROL_2                 = 0xE3;
                static constexpr UInt8 INTERFACE_CONTROL                       = 0xF6;
                static constexpr UInt8 POWER_CONTROL_A                         = 0xCB;
                static constexpr UInt8 POWER_CONTROL_B                         = 0xCF;
                static constexpr UInt8 DRIVER_TIMING_CONTROL_A                 = 0xE8;
                static constexpr UInt8 DRIVER_TIMING_CONTROL_B                 = 0xEA;
                static constexpr UInt8 POWER_ON_SEQUENCE_CONTROL               = 0xED;
                static constexpr UInt8 ENABLE_3G                               = 0xF2;
                static constexpr UInt8 PUMP_RATIO_CONTROL                      = 0xF7;
            };

        protected:
            Device_ILI9341();

            void writeScript(const UInt8 *script, UInt32 scriptSize);

        public:
            virtual ~Device_ILI9341() = default;

            virtual void writeCommand(UInt8 cmd) = 0;
            virtual void writeData(UInt8 data) = 0;
            virtual void writeData(const UInt8 *data, UInt32 dataSize) = 0;
    };

    class Device_ILI9341_SPI: public Device_ILI9341 {
        protected:
            PinDevice * const _pinCS;
            PinDevice * const _pinRS;
            PinDevice * const _pinRST;
            SPIDevice * const _devSPI;

        public:
            Device_ILI9341_SPI(PinDevice *pinCS, PinDevice *pinRS, PinDevice *pinRST, SPIDevice *devSPI);

            void initialize(const UInt8 *script, UInt32 scriptSize);
            void deinitialize();

            void writeCommand(UInt8 data) override;
            void writeData(UInt8 data) override;
            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };

    class Device_ILI9341_SPIDMA: public Device_ILI9341_SPI {
        protected:
            DMADevice * const _devDMA;

        public:
            Device_ILI9341_SPIDMA(PinDevice *pinCS, PinDevice *pinRS, PinDevice *pinRST, SPIDevice *devSPI, DMADevice *devDMA);

            void writeData(const UInt8 *data, UInt32 dataSize) override;
    };
}
