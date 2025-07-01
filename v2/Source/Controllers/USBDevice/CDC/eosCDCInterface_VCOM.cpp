#include "eos.h"
#include "Controllers/USBDevice/CDC/eosCDCInterface_VCOM.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


using namespace eos;


/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
USBD_CDC_LineCodingTypeDef LineCoding = {
  115200,                       /* baud rate */
  0x00,                         /* stop bits-1 */
  0x00,                         /* parity - none */
  0x08                          /* nb. of bits 8 */
};

uint8_t UserRxBuffer[APP_RX_DATA_SIZE]; /* Received Data over USB are stored in
                                         * this buffer */
uint8_t UserTxBuffer[APP_TX_DATA_SIZE]; /* Received Data over UART (CDC
                                         * interface) are stored in this buffer
                                         */

/// ---------------------------------------------------------------------
/// \brief    Constructor.
///
CDCInterface_VCOM::CDCInterface_VCOM(
	USBDeviceDriver *drvUSBD) {

	_usbd = drvUSBD->getHandle();
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio
///
int8_t CDCInterface_VCOM::initialize() {

	USBD_CDC_SetTxBuffer(_usbd, UserTxBuffer, 0);
	USBD_CDC_SetRxBuffer(_usbd, UserRxBuffer);

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Desinicialitzacio
///
int8_t CDCInterface_VCOM::deinitialize() {

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Procesa les comandes de control
/// \param    cmd: La comanda.
/// \param    data: Buffer de dades.
/// \param    dataSize: Tamany del buffer de dades.
///
int8_t CDCInterface_VCOM::control(
	ControlCmd cc,
	uint8_t *data,
	uint16_t dataSize) {

	switch (cc) {
		case ControlCmd::SEND_ENCAPSULATED_COMMAND:
			break;

		case ControlCmd::GET_ENCAPSULATED_RESPONSE:
			break;

		case ControlCmd::SET_COMM_FEATURE:
			break;

		case ControlCmd::GET_COMM_FEATURE:
			break;

		case ControlCmd::CLEAR_COMM_FEATURE:
			break;

		case ControlCmd::SET_LINE_CODING:
			break;

		case ControlCmd::GET_LINE_CODING:
			if (dataSize < 7)
				return -1;

			data[0] = (uint8_t) (LineCoding.bitrate);
			data[1] = (uint8_t) (LineCoding.bitrate >> 8);
			data[2] = (uint8_t) (LineCoding.bitrate >> 16);
			data[3] = (uint8_t) (LineCoding.bitrate >> 24);
			data[4] = LineCoding.format;
			data[5] = LineCoding.paritytype;
			data[6] = LineCoding.datatype;
			break;

		case ControlCmd::SET_CONTROL_LINE_STATE:
			break;

		case ControlCmd::SEND_BREAK:
			break;

		default:
			break;
	}

	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica que hi han dades disponibles
///
int8_t CDCInterface_VCOM::rxDataAvailable(
	uint8_t *data,
	uint32_t *length) {

	return 0;
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final de la transmissio.
///
int8_t CDCInterface_VCOM::txDataCompleted(
	uint8_t *data,
	uint32_t *length,
	uint8_t epnum) {

	return 0;
}
