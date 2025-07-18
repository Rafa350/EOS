#include "eos.h"
#include "eosAssert.h"
#include "HTL/htl.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "Controllers/USBDevice/ST/st_usbd_ctlreq.h"
#include "Controllers/USBDevice/HID/eosUSBDeviceClassHID.h"


using namespace eos;
using namespace htl;


extern uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ];
extern uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    iface: El interface que gestiona.
///
USBDeviceClassHID::USBDeviceClassHID(
	USBDeviceDriver *drvUSBD,
	uint8_t iface) :

	USBDeviceClass {drvUSBD, iface} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
/// \return   El resultat de l'operacio.
///
Result USBDeviceClassHID::initialize() {

	auto pdev = _drvUSBD->getHandle();
	USBD_RegisterClass(pdev, this);

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief    Inicializa la clase.
///
int8_t USBDeviceClassHID::classInitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();
	bool hs = pdev->dev_speed == USBD_SPEED_HIGH;

    // Prepara EP IN
   	//
   	USBD_LL_OpenEP(pdev, _inEpAddr, USBD_EP_TYPE_INTR, HID_EPIN_SIZE);
   	pdev->ep_in[_inEpAddr & 0x0F].is_used = 1;
    pdev->ep_in[_inEpAddr & 0x0F].bInterval = hs ? HID_HS_BINTERVAL : HID_FS_BINTERVAL;

  	return USBD_OK;
}


/// ----------------------------------------------------------------------
/// \brief     Desinicialitza la clase.
///
int8_t USBDeviceClassHID::classDeinitialize(
	uint8_t cfgidx) {

	auto pdev = _drvUSBD->getHandle();

	// Close EP IN
	//
	USBD_LL_CloseEP(pdev, _inEpAddr);
	pdev->ep_in[_inEpAddr & 0xFU].is_used = 0U;

	return USBD_OK;
}


int8_t USBDeviceClassHID::classSetup(
	USBD_SetupReqTypedef *req) {

	auto pdev = _drvUSBD->getHandle();

	USBD_StatusTypeDef ret = USBD_OK;

	switch (req->getType()) {

		case USBDRequestType::clase:
			break;

		case USBDRequestType::standard:
			switch (req->getRequestID()) {
				case USBDRequestID::getStatus:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint16_t status = 0;
						USBD_CtlSendData(pdev, (uint8_t*) &status, sizeof(status));
					}
					else
						ret = USBD_FAIL;
					break;

				case USBDRequestID::getInterface:
					if (pdev->dev_state == USBD_STATE_CONFIGURED) {
						uint8_t iface = 0;
						USBD_CtlSendData(pdev, &iface, sizeof(iface));
					}
					else
						ret = USBD_FAIL;
					break;

				case USBDRequestID::setInterface:
					if (pdev->dev_state != USBD_STATE_CONFIGURED)
						ret = USBD_FAIL;
					break;

				case USBDRequestID::clearFeature:
					break;

				default:
					ret = USBD_FAIL;
					break;
			}
			break;

		default:
			ret = USBD_FAIL;
			break;
	}

	if (ret == USBD_FAIL)
		USBD_CtlError(pdev, req);

	return ret;
}


int8_t USBDeviceClassHID::classEP0TxSent() {

	return USBD_FAIL;
}


int8_t USBDeviceClassHID::classEP0RxReady() {

	return USBD_FAIL;
}


/// ----------------------------------------------------------------------
/// \brief    Envia dades al endpoint.
/// \param    epnum: El endpoint.
/// \return   El resultat de l'operacio.
///
int8_t USBDeviceClassHID::classDataIn(
	uint8_t epnum) {

	auto pdev = _drvUSBD->getHandle();

	PCD_HandleTypeDef *pcd = (PCD_HandleTypeDef *)pdev->pData;

	if ((pdev->ep_in[epnum & 0xFU].total_length > 0) &&
       ((pdev->ep_in[epnum & 0xFU].total_length % pcd->IN_ep[epnum & 0xFU].maxpacket) == 0)) {

		pdev->ep_in[epnum & 0xFU].total_length = 0;
		USBD_LL_Transmit(pdev, epnum, nullptr, 0);
	}

    return USBD_OK;
}


int8_t USBDeviceClassHID::classDataOut(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassHID::classSOF() {

	return USBD_FAIL;
}


int8_t USBDeviceClassHID::classIsoINIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


int8_t USBDeviceClassHID::classIsoOUTIncomplete(
	uint8_t epnum) {

	return USBD_FAIL;
}


bool USBDeviceClassHID::classGetHSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {
/*
	auto pEpCmdDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_HS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_HS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);
*/
	return true;
}


bool USBDeviceClassHID::classGetFSConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {
/*
	auto pEpCmdDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef*) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);
*/
	return true;
}


bool USBDeviceClassHID::classGetOtherSpeedConfigurationDescriptor(
	uint8_t *&data,
	unsigned &length) {
/*
	auto pEpCmdDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _cmdEpAdd);
	if (pEpCmdDesc != nullptr)
		pEpCmdDesc->bInterval = CDC_FS_BINTERVAL;

	auto pEpOutDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _outEpAdd);
	if (pEpOutDesc != nullptr)
		pEpOutDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	auto pEpInDesc = (USBD_EpDescTypeDef *) USBD_GetEpDesc(USBD_CDC_CfgDesc, _inEpAdd);
	if (pEpInDesc != nullptr)
		pEpInDesc->wMaxPacketSize = CDC_DATA_FS_MAX_PACKET_SIZE;

	data = USBD_CDC_CfgDesc;
	length = sizeof(USBD_CDC_CfgDesc);
*/
	return true;
}


bool USBDeviceClassHID::classGetDeviceQualifierDescriptor(
	uint8_t *&data,
	unsigned &length) {

	data = USBD_HID_DeviceQualifierDesc;
	length = sizeof(USBD_HID_DeviceQualifierDesc);

	return true;
}


bool USBDeviceClassHID::usesEndPoint(
	uint8_t epAddr) const {

	return epAddr == _inEpAddr;
}

