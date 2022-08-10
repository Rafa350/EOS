#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/Drivers/ILI9341/eosDisplayDriver_ILI9341.h"
#include "Controllers/Display/Drivers/ILI9341/eosILI9341Defs.h"
#include "System/Graphics/eosColor.h"
#include "HAL/halTMR.h"


using namespace eos;
using namespace htl;


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'interficie amb el controlador.
///
void DisplayDriver_ILI9341::initializeInterface() {

	// Inicialitza el modul GPIO
	//
#ifdef DISPLAY_RST_PIN
	GPIO_RST.initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	GPIO_RST::clear();
#endif
	GPIO_CS::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	GPIO_CS::set();
	GPIO_RS::initOutput(htl::GPIODriver::pushPull, htl::GPIOSpeed::fast);
	GPIO_RS::clear();

	// Inicialitza el modul SPI
    //
	SPI::initSCKPin<GPIO_SCK>();
	SPI::initMOSIPin<GPIO_MOSI>();
	SPI::initMaster(SPIMode::mode0, SPISize::size8, SPIFirstBit::msb, SPIClockDivider::clkdiv_16);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el controlador.
///
void DisplayDriver_ILI9341::initializeController() {

	// Inicialitza el controlador del display
	//
#if defined(DISPLAY_ER_TFT028_4)
    static const uint8_t initCommands[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
        6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,
        4, CMD_POWER_CONTROL_B, 0x00, 0xC3, 0x30,
     	5, CMD_POWER_ON_SEQUENCE_CONTROL, 0x64, 0x03, 0X12, 0x81,
        6, CMD_POWER_CONTROL_A, 0x39, 0x2C, 0x00, 0x34, 0x02,
        2, CMD_PUMP_RATIO_CONTROL, 0x20,
        3, CMD_DRIVER_TIMING_CONTROL_B, 0x00, 0x00,
       	2, CMD_POWER_CONTROL_1, 0x22,
        2, CMD_POWER_CONTROL_2, 0x11,
        3, CMD_VCOM_CONTROL_1, 0x3D, 0x20,
        2, CMD_VCOM_CONTROL_2, 0xAA,
        2, CMD_MEMORY_ACCESS_CONTROL, 0x08 | MAC_MV_OFF | MAC_MX_OFF | MAC_MY_OFF,
        3, CMD_FRAME_RATE_CONTROL_1, 0x00, 0x13,
        3, CMD_DISPLAY_FUNCTION_CONTROL, 0x0A, 0xA2,
        3, CMD_INTERFACE_CONTROL, 0x01, 0x30,
        2, CMD_ENABLE_3G, 0x00,
        2, CMD_GAMMA_SET, 0x01,
        16, CMD_POSITIVE_GAMMA_CORRECTION, 0x0F, 0x3F, 0x2F, 0x0C, 0x10, 0x0A,
            0x53, 0xD5, 0x40, 0x0A, 0x13, 0x03, 0x08, 0x03, 0x00,
        16, CMD_NEGATIVE_GAMMA_CORRECTION, 0x00, 0x00, 0x10, 0x03, 0x0F, 0x05,
            0x2C, 0xA2, 0x3F, 0x05, 0x0E, 0x0C, 0x37, 0x3C, 0x0F,
        OP_END
    };

#elif defined(STM32F429I_DISC1)
    static const uint8_t initCommands[] = {
        __SOFTWARE_RESET,
        OP_DELAY, 250,
        OP_DELAY, 250,
		__POWER_CONTROL_A(0x39, 0x2C, 0x00, 0x34, 0x62),
    	__POWER_CONTROL_B(0x00, 0xC1, 0x30),
    	__DRIVER_TIMING_CONTROL_A(0x85, 0x00, 0x78),
    	__DRIVER_TIMING_CONTROL_B(0x00, 0x00),
		__POWER_ON_SEQUENCE_CONTROL(0x64, 0x03, 0x12, 0x81),
		__PUMP_RATIO_CONTROL(0x20),
    	__POWER_CONTROL_1(0x23),
    	__POWER_CONTROL_2(0x10),
		__VCOM_CONTROL_1(0x3E, 0x28),
		__VCOM_CONTROL_2(0x86),
    	__MEMORY_ACCESS_CONTROL(0x08 | MAC_MV_OFF | MAC_MX_ON | MAC_MY_OFF),
		__FRAME_RATE_CONTROL_1(0x00, 0x18),
		__DISPLAY_FUNCTION_CONTROL(0x08, 0x82, 0x27, 0x00),
		__ENABLE_3G(0x00),
		__GAMMA_SET(0x01),
    	__POSITIVE_GAMMA_CORRECTION( 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
    			0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00),
    	__NEGATIVE_GAMMA_CORRECTION(0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
    			0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F),
        OP_END
    };
#endif

#ifdef DISPLAY_RST_PORT
    halTMRDelay(10);
    CPIO_RST::set();
    halTMRDelay(120);
#endif

    uint8_t c;
    const uint8_t *p = initCommands;

    open();
    while ((c = *p++) != OP_END) {
        switch (c) {
            case OP_DELAY:
                halTMRDelay(*p++);
                break;

            default:
                writeCommand(*p++);
                while (--c != 0)
                    writeData(*p++);
                break;
        }
    }

    if constexpr (Color::format == ColorFormat::rgb565) {
    	writeCommand(CMD_PIXEL_FORMAT_SET);
    	writeData(0x55);
    }
    /*else if constexpr (CI::format == ColorFormat::rgb666) {
    	hwWriteCommand(CMD_PIXEL_FORMAT_SET);
    	hwWriteData(0x66);
    }*/

    close();
}


/// ----------------------------------------------------------------------
/// \brief Inicia una transferencia de dades amb el controlador.
///
void DisplayDriver_ILI9341::open() {

	GPIO_CS::clear();
}


/// ----------------------------------------------------------------------
/// \brief Finalitza una transferencia de dades amb el controlador.
///
void DisplayDriver_ILI9341::close() {

	GPIO_CS::set();
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de comanda en el controlador.
/// \param cmd: El byte a escriure.
///
void DisplayDriver_ILI9341::writeCommand(
    uint8_t cmd) {

	GPIO_RS::clear();
    SPI::send(&cmd, sizeof(cmd));
}


/// ----------------------------------------------------------------------
/// \brief Escriu un byte de dades en el controlador
/// \param data: El byte a escriure.
///
void DisplayDriver_ILI9341::writeData(
    uint8_t data) {

	GPIO_RS::set();
    SPI::send(&data, sizeof(data));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades en el controlador
/// \param    data: Buffer de dades.
/// \param    length: Numero de bytes en el buffer.
///
void DisplayDriver_ILI9341::writeData(
	const uint8_t* data,
	int length) {

	GPIO_RS::set();
    SPI::send(data, length);
}

