#include "eos.h"
#include "Controllers/USBDevice/CDC/eosUSBDeviceClassCDC.h"
#include "Controllers/USBDevice/CDC/ST/st_usbd_cdc.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Crea el objecte.
/// \param    devUSBD: El dispositiu USB
/// \param    interface: El interface de comunicacio
///
USBDeviceClassCDC::USBDeviceClassCDC(
	USBDeviceDriver *drvUSBD,
	CDCInterface *interface) :

	USBDeviceClass {drvUSBD},
	_interface {interface} {

}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el dispositiu.
///
void USBDeviceClassCDC::initialize() {

	auto handle = _drvUSBD->getHandle();

	USBD_RegisterClass(handle, USBD_CDC_CLASS);
	handle->pUserData[handle->classId] = _interface;
}


int8_t USBDeviceClassCDC::classInit(
	USBD_HandleTypeDef *pdev,
	uint8_t cfgidx) {

	USBD_memset(&_cdc, 0, sizeof(_cdc));

	pdev->pClassDataCmsit[pdev->classId] = &_cdc;
	pdev->pClassData = pdev->pClassDataCmsit[pdev->classId];

#ifdef USE_USBD_COMPOSITE
	/* Get the Endpoints addresses allocated for this class instance */
	CDCInEpAdd  = USBD_CoreGetEPAdd(pdev, USBD_EP_IN, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
	CDCOutEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_OUT, USBD_EP_TYPE_BULK, (uint8_t)pdev->classId);
	CDCCmdEpAdd = USBD_CoreGetEPAdd(pdev, USBD_EP_IN, USBD_EP_TYPE_INTR, (uint8_t)pdev->classId);
#endif /* USE_USBD_COMPOSITE */

    if (pdev->dev_speed == USBD_SPEED_HIGH) {

	    /* Open EP IN */
    	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, CDC_DATA_HS_IN_PACKET_SIZE);
    	pdev->ep_in[_inEpAdd & 0xFU].is_used = 1U;

    	/* Open EP OUT */
    	USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, CDC_DATA_HS_OUT_PACKET_SIZE);
    	pdev->ep_out[_outEpAdd & 0xFU].is_used = 1U;

    	/* Set bInterval for CDC CMD Endpoint */
    	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = CDC_HS_BINTERVAL;
    }

    else {

    	/* Open EP IN */
    	USBD_LL_OpenEP(pdev, _inEpAdd, USBD_EP_TYPE_BULK, CDC_DATA_FS_IN_PACKET_SIZE);
    	pdev->ep_in[_inEpAdd & 0xFU].is_used = 1U;

    	/* Open EP OUT */
    	USBD_LL_OpenEP(pdev, _outEpAdd, USBD_EP_TYPE_BULK, CDC_DATA_FS_OUT_PACKET_SIZE);
    	pdev->ep_out[_outEpAdd & 0xFU].is_used = 1U;

    	/* Set bInterval for CMD Endpoint */
    	pdev->ep_in[_cmdEpAdd & 0xFU].bInterval = CDC_FS_BINTERVAL;
    }

    /* Open Command IN EP */
    USBD_LL_OpenEP(pdev, _cmdEpAdd, USBD_EP_TYPE_INTR, CDC_CMD_PACKET_SIZE);
    pdev->ep_in[_cmdEpAdd & 0xFU].is_used = 1U;

    _cdc.RxBuffer = nullptr;

    /* Init  physical Interface components */
  	_interface->initialize();

  	/* Init Xfer states */
  	_cdc.TxState = 0U;
  	_cdc.RxState = 0U;

  	// S'ha d'inicialitzae en _interface->initialize();
  	//
  	if (_cdc.RxBuffer == NULL)
  		return USBD_EMEM;

  	if (pdev->dev_speed == USBD_SPEED_HIGH) {
  		/* Prepare Out endpoint to receive next packet */
  		USBD_LL_PrepareReceive(pdev, _outEpAdd, _cdc.RxBuffer, CDC_DATA_HS_OUT_PACKET_SIZE);
  	}
  	else  {
  		/* Prepare Out endpoint to receive next packet */
  		USBD_LL_PrepareReceive(pdev, _outEpAdd, _cdc.RxBuffer, CDC_DATA_FS_OUT_PACKET_SIZE);
  	}

	return USBD_OK;
}


int8_t USBDeviceClassCDC::classDeinit(
	USBD_HandleTypeDef *pdev,
	uint8_t cfgidx) {

	return 0;
}


int8_t USBDeviceClassCDC::classSetup(
	USBD_HandleTypeDef *pdev,
	USBD_SetupReqTypedef *req) {

	return 0;
}


int8_t USBDeviceClassCDC::classEP0TxSent() {

	return 0;
}


int8_t USBDeviceClassCDC::classEP0RxReady(
	USBD_HandleTypeDef *pdev) {

	return 0;
}


int8_t USBDeviceClassCDC::classDataIn(
	USBD_HandleTypeDef *pdev,
	uint8_t epnum) {

	return 0;
}


int8_t USBDeviceClassCDC::classDataOut(
	USBD_HandleTypeDef *pdev,
	uint8_t epnum) {

	return 0;
}


int8_t* USBDeviceClassCDC::classGetHSCfgDesc(
	uint16_t *length) {

	return 0;
}


int8_t* USBDeviceClassCDC::classGetFSCfgDesc(
	uint16_t *length) {

	return 0;
}


int8_t* USBDeviceClassCDC::classGetOtherSpeedCfgDesc(
	uint16_t *length) {

	return 0;
}


int8_t* USBDeviceClassCDC::classGetDeviceQualifierDescriptor(
	uint16_t *length) {

	return 0;
}
