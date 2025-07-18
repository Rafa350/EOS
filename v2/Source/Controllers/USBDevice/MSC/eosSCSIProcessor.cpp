#include "Controllers/USBDevice/MSC/eosUSBDeviceClassMSC.h"
#include "Controllers/USBDevice/MSC/eosSCSIProcessor.h"
#include "Controllers/USBDevice/ST/st_usbd_core.h"
#include "System/eosMath.h"


using namespace eos;


static const uint8_t MSC_Page00_Inquiry_Data[LENGTH_INQUIRY_PAGE00] = {
	0x00,
	0x00,
	0x00,
	(LENGTH_INQUIRY_PAGE00 - 4U),
	0x00,
	0x80
};

static const uint8_t MSC_Page80_Inquiry_Data[LENGTH_INQUIRY_PAGE80] = {
	0x00,
	0x80,
	0x00,
	LENGTH_INQUIRY_PAGE80,
	0x20,     // Put Product Serial number
	0x20,
	0x20,
	0x20
};

static uint8_t MSC_Mode_Sense6_data[MODE_SENSE6_LEN] = {
	0x03,     /* MODE DATA LENGTH. The number of bytes that follow. */
	0x00,     /* MEDIUM TYPE. 00h for SBC devices. */
	0x00,     /* DEVICE-SPECIFIC PARAMETER. For SBC devices:
			 *   bit 7: WP. Set to 1 if the media is write-protected.
			 *   bits 6..5: reserved
			 *   bit 4: DPOFUA. Set to 1 if the device supports the DPO and FUA bits
			 *   bits 3..0: reserved */
	0x00      /* BLOCK DESCRIPTOR LENGTH */
};

static uint8_t MSC_Mode_Sense10_data[MODE_SENSE10_LEN] = {
	0x00,     /* MODE DATA LENGTH MSB. */
	0x06,     /* MODE DATA LENGTH LSB. The number of bytes that follow. */
	0x00,     /* MEDIUM TYPE. 00h for SBC devices. */
	0x00,     /* DEVICE-SPECIFIC PARAMETER. For SBC devices:
			 *   bit 7: WP. Set to 1 if the media is write-protected.
			 *   bits 6..5: reserved
			 *   bit 4: DPOFUA. Set to 1 if the device supports the DPO and FUA bits
			 *   bits 3..0: reserved */
	0x00,     /* LONGLBA Set to zero */
	0x00,     /* Reserved */
	0x00,     /* BLOCK DESCRIPTOR LENGTH MSB. */
	0x00      /* BLOCK DESCRIPTOR LENGTH LSB. */
};

static uint8_t MSC_Diagnostic_Data[DIAGNOSTIC_DATA_LEN] = {
	0x00, 	  // Byte 0: ADDITIONAL LENGTH (MSB)
	0x00, 	  // Byte 1: ADDITIONAL LENGTH (LSB)
	0x00, 	  // Byte 2: FRU CODE (most probable)
	0x00, 	  // Byte 3: FRU CODE
	0x00, 	  // Byte 4: FRU CODE
	0x00, 	  // Byte 5: FRU CODE (least probable)
	0x00, 	  // Byte 6: ERROR CODE (MSB)
	0x00, 	  // Byte 7: ERROR CODE (LSB)
};


/// ----------------------------------------------------------------------
/// \brief    Constructor.
///
SCSIProcessor::SCSIProcessor(
	MSCStorage *storage,
	USBD_HandleTypeDef *pdev) :

	_status {Status::reset},
	_storage {storage},
	_pdev {pdev},
	_senseTail {0},
	_senseHead {0},
	_mediumState {MediumState::unlocked} {
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el procesador.
/// \return   El resultat de l'operacio.
///
Result SCSIProcessor::initialize(
	uint8_t inEpAddr,
	uint8_t outEpAddr,
	USBD_MSC_BOT_HandleTypeDef *msc) {

	if (_status != Status::reset)
		return Results::errorState;

	_senseTail = 0;
	_senseHead = 0;
	_mediumState = MediumState::unlocked;

	_msc = msc;

	_inEpAddr = inEpAddr;
	_outEpAddr = outEpAddr;

	_status = Status::ready;

	return Results::success;
}


/// ----------------------------------------------------------------------
/// \brief   Procesa les comandes SCSI
/// \param   lun: Identificador LUN
/// \param   cmd: La comanda.
/// \return  El resultat de l'operacio.
///
bool SCSIProcessor::processCmd(
	uint8_t lun,
	const uint8_t *cmd) {

	switch (cmd[0]) {

		case SCSI_TEST_UNIT_READY:
			return testUnitReady(lun, cmd);

		case SCSI_REQUEST_SENSE:
			return requestSense(lun, cmd);

		case SCSI_INQUIRY:
			return inquiry(lun, cmd);

		case SCSI_START_STOP_UNIT:
			return startStopUnit(lun, cmd);

		case SCSI_ALLOW_MEDIUM_REMOVAL:
			return allowPreventMediumRemoval(lun, cmd);

		case SCSI_MODE_SENSE6:
			return modeSense6(lun, cmd);

		case SCSI_MODE_SENSE10:
			return modeSense10(lun, cmd);

		case SCSI_READ_FORMAT_CAPACITIES:
			return readFormatCapacity(lun, cmd);

		case SCSI_READ_CAPACITY10:
			return readCapacity10(lun, cmd);

		case SCSI_READ_CAPACITY16:
			return readCapacity16(lun, cmd);

		case SCSI_READ10:
			return read10(lun, cmd);

		case SCSI_READ12:
			return read12(lun, cmd);

		case SCSI_WRITE10:
			return write10(lun, cmd);

		case SCSI_WRITE12:
			return write12(lun, cmd);

		case SCSI_VERIFY10:
			return verify10(lun, cmd);

		case SCSI_REPORT_LUNS:
			return reportLuns(lun, cmd);

		case SCSI_RECEIVE_DIAGNOSTIC_RESULTS:
			return receiveDiagnosticResults(lun, cmd);

		default:
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
	}
}


void SCSIProcessor::senseCode(
	uint8_t lun,
	uint8_t sKey,
	uint8_t ASC) {

	_senseList[_senseTail].Skey = sKey;
	_senseList[_senseTail].w.b.ASC = ASC;
	_senseList[_senseTail].w.b.ASCQ = 0;

	_senseTail++;
	if (_senseTail == _senseListSize)
		_senseTail = 0;
}


bool SCSIProcessor::testUnitReady(
	uint8_t lun,
	const uint8_t *cmd) {

	_msc->bot_data_length = 0;

	if (_msc->cbw.dDataLength != 0) {
		senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
		return false;
	}

	if (_mediumState == MediumState::ejected) {
		senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
		_msc->bot_state = USBD_BOT_NO_DATA;
		return false;
	}

	if (!_storage->isReady(lun)) {
		senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
		_msc->bot_state = USBD_BOT_NO_DATA;
		return false;
	}

	return true;
}


bool SCSIProcessor::inquiry(
	uint8_t lun,
	const uint8_t *cmd) {

	if (_msc->cbw.dDataLength == 0) {
		senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
		return false;
	}

	if ((cmd[1] & 0x01) != 0) {
		if (cmd[2] == 0) {
			updateBotData(MSC_Page00_Inquiry_Data, LENGTH_INQUIRY_PAGE00);
		}
		else if (cmd[2] == 0x80) {
			updateBotData(MSC_Page80_Inquiry_Data, LENGTH_INQUIRY_PAGE80);
		}
		else {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_FIELD_IN_COMMAND);
			return false;
		}
	}

	else {
		auto pPage = (uint8_t*) & _storage->getInquiryData()[lun * STANDARD_INQUIRY_DATA_LEN];
		auto len = pPage[4] + 5;
		if (cmd[4] <= len)
			len = cmd[4];
		updateBotData(pPage, len);
	}

	return true;
}


bool SCSIProcessor::readFormatCapacity(
	uint8_t lun,
	const uint8_t *cmd) {

	unsigned blkSize;
	unsigned blkQuantity;

	auto ret = _storage->getCapacity(lun, blkQuantity, blkSize);
	if ((ret != 0) || (_mediumState == MediumState::ejected)) {
		senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
		return false;
	}

	_msc->bot_data[0] = 0;
	_msc->bot_data[1] = 0;
	_msc->bot_data[2] = 0;
	_msc->bot_data[3] = 0x08;
	_msc->bot_data[4] = (uint8_t)((blkQuantity - 1) >> 24);
	_msc->bot_data[5] = (uint8_t)((blkQuantity - 1) >> 16);
	_msc->bot_data[6] = (uint8_t)((blkQuantity - 1) >>  8);
	_msc->bot_data[7] = (uint8_t)(blkQuantity - 1);
	_msc->bot_data[8] = 0x02;
	_msc->bot_data[9] = (uint8_t)(blkSize >>  16);
	_msc->bot_data[10] = (uint8_t)(blkSize >>  8);
	_msc->bot_data[11] = (uint8_t)(blkSize);

	_msc->bot_data_length = 12;

	return true;
}


bool SCSIProcessor::readCapacity10(
	uint8_t lun,
	const uint8_t *params) {

	auto lunData = &_lunDataList[lun];

	auto ret = _storage->getCapacity(lun, lunData->blkQuantity, lunData->blkSize);
	if ((ret != 0) || (_mediumState == MediumState::ejected)) {
		senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
		return false;
	}

	auto bq = lunData->blkQuantity - 1;
	_msc->bot_data[0] = (uint8_t)(bq >> 24);
	_msc->bot_data[1] = (uint8_t)(bq >> 16);
	_msc->bot_data[2] = (uint8_t)(bq >>  8);
	_msc->bot_data[3] = (uint8_t)(bq);

	auto bs = lunData->blkSize;
	_msc->bot_data[4] = (uint8_t)(bs >> 24);
	_msc->bot_data[5] = (uint8_t)(bs >> 16);
	_msc->bot_data[6] = (uint8_t)(bs >> 8);
	_msc->bot_data[7] = (uint8_t)(bs);

	_msc->bot_data_length = 8;

	return true;
}


bool SCSIProcessor::readCapacity16(
	uint8_t lun,
	const uint8_t *params) {

	auto lunData = &_lunDataList[lun];

	auto ret = _storage->getCapacity(lun, lunData->blkQuantity, lunData->blkSize);
	if ((ret != 0) || (_mediumState == MediumState::ejected)) {
		senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
		return false;
	}

	_msc->bot_data_length =
		((uint32_t)params[10] << 24) |
		((uint32_t)params[11] << 16) |
		((uint32_t)params[12] <<  8) |
		(uint32_t)params[13];

	memset(_msc->bot_data, 0, _msc->bot_data_length);

	auto bq = lunData->blkQuantity - 1;
	_msc->bot_data[4] = (uint8_t)(bq >> 24);
	_msc->bot_data[5] = (uint8_t)(bq >> 16);
	_msc->bot_data[6] = (uint8_t)(bq >>  8);
	_msc->bot_data[7] = (uint8_t)bq;

	auto bs = lunData->blkSize;
	_msc->bot_data[8] = (uint8_t)(bs >>  24);
	_msc->bot_data[9] = (uint8_t)(bs >>  16);
	_msc->bot_data[10] = (uint8_t)(bs >>  8);
	_msc->bot_data[11] = (uint8_t)(bs);

	return true;
}


bool SCSIProcessor::requestSense(
	uint8_t lun,
	const uint8_t *cmd) {

	if (_msc->cbw.dDataLength == 0) {
		senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
		return false;
	}

	memset(_msc->bot_data, 0, REQUEST_SENSE_DATA_LEN);

	_msc->bot_data[0] = 0x70;
	_msc->bot_data[7] = REQUEST_SENSE_DATA_LEN - 6;

	if ((_senseHead != _senseTail)) {
		_msc->bot_data[2] = _senseList[_senseHead].Skey;
		_msc->bot_data[12] = _senseList[_senseHead].w.b.ASC;
		_msc->bot_data[13] = _senseList[_senseHead].w.b.ASCQ;
		_senseHead++;
		if (_senseHead == _senseListSize)
			_senseHead = 0;
	}

	_msc->bot_data_length = REQUEST_SENSE_DATA_LEN;
	if (cmd[4] < REQUEST_SENSE_DATA_LEN)
		_msc->bot_data_length = cmd[4];

	return true;
}


bool SCSIProcessor::startStopUnit(
	int8_t lun,
	const uint8_t *cmd) {

	if ((_mediumState == MediumState::locked) && ((cmd[4] & 0x03) == 0x02)) {
		senseCode(lun, ILLEGAL_REQUEST, INVALID_FIELD_IN_COMMAND);
		return false;
	}

	_msc->bot_data_length = 0;

	switch (cmd[4] & 0x03) {
		case 0x01: // LOEJ=0, START=1
			_mediumState = MediumState::unlocked;
			break;

		case 0x02: // LOEJ=1, START=0
			_mediumState = MediumState::ejected;
			break;

		case 0x03: // LOEJ=1, START=1
			_mediumState = MediumState::unlocked;
			break;
	}

	return true;
}


bool SCSIProcessor::allowPreventMediumRemoval(
	uint8_t lun,
	const uint8_t *cmd) {

	_msc->bot_data_length = 0;

	switch (cmd[4] & 0x03) {
		case 0x00:
			_mediumState = MediumState::unlocked;
			break;

		case 0x01:
			_mediumState = MediumState::locked;
			break;

		default:
			return false;
	}

	return true;
}


bool SCSIProcessor::modeSense6(
	uint8_t lun,
	const uint8_t *cmd) {

	unsigned len = MODE_SENSE6_LEN;

	if (_storage->isWriteProtected(lun))
		MSC_Mode_Sense6_data[2] |= (0x01 << 7);   // Set the WP (write protection) bit
	else
		MSC_Mode_Sense6_data[2] &= ~(0x01 << 7);  // Clear the WP (write protection) bit

	if (cmd[4] < len)
		len = cmd[4];

	updateBotData(MSC_Mode_Sense6_data, len);

	return true;
}


bool SCSIProcessor::modeSense10(
	uint8_t lun,
	const uint8_t *cmd) {

	unsigned len = MODE_SENSE10_LEN;

	if (_storage->isWriteProtected(lun))
		MSC_Mode_Sense10_data[3] |= (0x01 << 7);  // Set the WP (write protection) bit
	else
		MSC_Mode_Sense10_data[3] &= ~(0x01 << 7); // Clear the WP (write protection) bit

	if (cmd[8] < len)
		len = cmd[8];

	updateBotData(MSC_Mode_Sense10_data, len);

	return true;
}


bool SCSIProcessor::write10(
	uint8_t lun,
	const uint8_t *cmd) {

	auto lunData = &_lunDataList[lun];
	uint32_t len;

	if (_msc->bot_state == USBD_BOT_IDLE) {

		if (_msc->cbw.dDataLength == 0) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		/* case 8 : Hi <> Do */
		if ((_msc->cbw.bmFlags & 0x80) == 0x80) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
	        return false;
		}

		/* Check whether Media is ready */
		if (!_storage->isReady(lun)) {
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			return false;
		}

		/* Check If media is write-protected */
		if (_storage->isWriteProtected(lun)) {
			senseCode(lun, NOT_READY, WRITE_PROTECTED);
			return false;
		}

		lunData->addr =
			((uint32_t)cmd[2] << 24) |
			((uint32_t)cmd[3] << 16) |
			((uint32_t)cmd[4] << 8) |
			(uint32_t)cmd[5];

		lunData->len =
			((uint32_t)cmd[7] << 8) |
			(uint32_t)cmd[8];

		/* check if LBA address is in the right range */
		if (!checkAddressRange(lun, lunData->addr, lunData->len)) {
			return false;
		}

		len = lunData->len * lunData->blkSize;

		/* cases 3,11,13 : Hn,Ho <> D0 */
		if (_msc->cbw.dDataLength != len) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		len = min(len, (uint32_t) MSC_MEDIA_PACKET);

		/* Prepare EP to receive first data packet */
		_msc->bot_state = USBD_BOT_DATA_OUT;
		USBD_LL_PrepareReceive(_pdev, _outEpAddr, _msc->bot_data, len);
	}

	else
		return processWrite(lun);

	return true;
}


bool SCSIProcessor::write12(
	uint8_t lun,
	const uint8_t *cmd) {

	auto lunData = &_lunDataList[lun];
	uint32_t len;

	if (_msc->bot_state == USBD_BOT_IDLE) {
		if (_msc->cbw.dDataLength == 0) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		/* case 8 : Hi <> Do */
		if ((_msc->cbw.bmFlags & 0x80) == 0x80) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		if (!_storage->isReady(lun)) {
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			_msc->bot_state = USBD_BOT_NO_DATA;
			return false;
		}

		if (_storage->isWriteProtected(lun)) {
			senseCode(lun, NOT_READY, WRITE_PROTECTED);
			_msc->bot_state = USBD_BOT_NO_DATA;
			return false;
		}

		lunData->addr =
			((uint32_t)cmd[2] << 24) |
			((uint32_t)cmd[3] << 16) |
			((uint32_t)cmd[4] << 8) |
			(uint32_t)cmd[5];

		lunData->len =
			((uint32_t)cmd[6] << 24) |
			((uint32_t)cmd[7] << 16) |
			((uint32_t)cmd[8] << 8) |
			(uint32_t)cmd[9];

		if (!checkAddressRange(lun, lunData->addr, lunData->len))
			return false;

		len = lunData->len * lunData->blkSize;

		/* cases 3,11,13 : Hn,Ho <> D0 */
		if (_msc->cbw.dDataLength != len) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		len = min(len, (uint32_t) MSC_MEDIA_PACKET);

		/* Prepare EP to receive first data packet */
		_msc->bot_state = USBD_BOT_DATA_OUT;
		USBD_LL_PrepareReceive(_pdev, _outEpAddr, _msc->bot_data, len);
	}

	else /* Write Process ongoing */
		return processWrite(lun);

	return true;
}


bool SCSIProcessor::read10(
	uint8_t lun,
	const uint8_t *cmd) {

	auto lunData = &_lunDataList[lun];

	if (_msc->bot_state == USBD_BOT_IDLE) {

		/* case 10 : Ho <> Di */
		if ((_msc->cbw.bmFlags & 0x80) != 0x80) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		if (_mediumState == MediumState::ejected)	{
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			return false;
		}

		if (!_storage->isReady(lun)) {
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			return false;
		}

		lunData->addr =
			((uint32_t)cmd[2] << 24) |
			((uint32_t)cmd[3] << 16) |
			((uint32_t)cmd[4] <<  8) |
			(uint32_t)cmd[5];

		lunData->len =
			((uint32_t)cmd[7] <<  8) |
			(uint32_t)cmd[8];

		if (!checkAddressRange(lun, lunData->addr, lunData->len))
			return false;

		if (_msc->cbw.dDataLength != (lunData->len * lunData->blkSize)) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		_msc->bot_state = USBD_BOT_DATA_IN;
	}

	_msc->bot_data_length = MSC_MEDIA_PACKET;

	return processRead(lun);
}


bool SCSIProcessor::read12(
	uint8_t lun,
	const uint8_t *cmd) {

	auto lunData = &_lunDataList[lun];

	if (_msc->bot_state == USBD_BOT_IDLE) {

		if ((_msc->cbw.bmFlags & 0x80) != 0x80) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		if (_mediumState == MediumState::ejected) {
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			return false;
		}

		if (!_storage->isReady(lun)) {
			senseCode(lun, NOT_READY, MEDIUM_NOT_PRESENT);
			return false;
		}

		lunData->addr =
			((uint32_t)cmd[2] << 24) |
			((uint32_t)cmd[3] << 16) |
			((uint32_t)cmd[4] <<  8) |
			(uint32_t)cmd[5];

		lunData->len =
			((uint32_t)cmd[6] << 24) |
			((uint32_t)cmd[7] << 16) |
			((uint32_t)cmd[8] << 8) |
			(uint32_t)cmd[9];

		if (!checkAddressRange(lun, lunData->addr, lunData->len))
			return false;

		if (_msc->cbw.dDataLength != (lunData->len * lunData->blkSize)) {
			senseCode(lun, ILLEGAL_REQUEST, INVALID_CDB);
			return false;
		}

		_msc->bot_state = USBD_BOT_DATA_IN;
	}

	_msc->bot_data_length = MSC_MEDIA_PACKET;

	return processRead(lun);

}


bool SCSIProcessor::verify10(
	uint8_t lun,
	const uint8_t *cmd) {

	auto lunData = &_lunDataList[lun];

	if ((cmd[1] & 0x02) == 0x02) {
		senseCode(lun, ILLEGAL_REQUEST, INVALID_FIELD_IN_COMMAND);
		return false;
	}

	if (!checkAddressRange(lun, lunData->addr, lunData->len))
		return false;

	_msc->bot_data_length = 0U;

	return true;
}


bool SCSIProcessor::reportLuns(
	uint8_t lun,
	const uint8_t *cmd) {

	uint32_t lun_list_length;
	uint32_t total_length;

	static uint8_t lun_report[8U * (MSC_BOT_MAX_LUN + 1U)];

	memset(lun_report, 0, sizeof(lun_report));

	lun_list_length = 8U * (_msc->max_lun + 1U);
	lun_report[0] = (uint8_t)(lun_list_length >> 24);
	lun_report[1] = (uint8_t)(lun_list_length >> 16);
	lun_report[2] = (uint8_t)(lun_list_length >> 8);
	lun_report[3] = (uint8_t)(lun_list_length & 0xFFU);

	for (uint32_t lun_idx = 0U; lun_idx <= _msc->max_lun; lun_idx++)
		lun_report[(8U * (lun_idx + 1U)) + 1U] = lun_idx;

	/* Calculate the total length of the report LUNs buffer */
	total_length = lun_list_length + 8U;

	/* Update the BOT data with the report LUNs buffer */
	updateBotData(lun_report, (uint16_t)total_length);

	return true;
}


bool SCSIProcessor::receiveDiagnosticResults(
	uint8_t lun,
	const uint8_t *cmd) {

	unsigned length = (cmd[3] << 8) | cmd[4];
	if (length > 0) {
		if (length > DIAGNOSTIC_DATA_LEN)
			length = DIAGNOSTIC_DATA_LEN;

		updateBotData(MSC_Diagnostic_Data, length);
	}

	return true;
}


bool SCSIProcessor::checkAddressRange(
	uint8_t lun,
	uint32_t blk_offset,
	uint32_t blk_nbr) {

	auto lunData = &_lunDataList[lun];

	if ((blk_offset + blk_nbr) > lunData->blkQuantity) {
		senseCode(lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
		return false;
	}

	return true;
}


bool SCSIProcessor::processRead(
	uint8_t lun) {

	auto lunData = &_lunDataList[lun];
	uint32_t len;

	len = lunData->len * lunData->blkSize;

	len = min(len, (uint32_t) MSC_MEDIA_PACKET);

	if (_storage->read(lun, _msc->bot_data, lunData->addr, (len / lunData->blkSize)) != Results::success) {
		senseCode(lun, HARDWARE_ERROR, UNRECOVERED_READ_ERROR);
		return false;
	}

	USBD_LL_Transmit(_pdev, _inEpAddr, _msc->bot_data, len);

	lunData->addr += (len / lunData->blkSize);
	lunData->len -= (len / lunData->blkSize);

	_msc->csw.dDataResidue -= len;

	if (lunData->len == 0)
		_msc->bot_state = USBD_BOT_LAST_DATA_IN;

	return true;
}


bool SCSIProcessor::processWrite(
	uint8_t lun) {

	auto lunData = &_lunDataList[lun];
	uint32_t len;

	len = lunData->len * lunData->blkSize;
	len = MIN(len, MSC_MEDIA_PACKET);

	if (_storage->write(lun, _msc->bot_data, lunData->addr, (len / lunData->blkSize)) != Results::success) {
		senseCode(lun, HARDWARE_ERROR, WRITE_FAULT);
		return false;
	}

	lunData->addr += (len / lunData->blkSize);
	lunData->len -= (len / lunData->blkSize);

	_msc->csw.dDataResidue -= len;

	if (lunData->len == 0) {
		//botSendCSW(_pdev, USBD_CSW_CMD_PASSED);
		_msc->csw.dSignature = USBD_BOT_CSW_SIGNATURE;
		_msc->csw.bStatus = USBD_CSW_CMD_PASSED;
		_msc->bot_state = USBD_BOT_IDLE;

		USBD_LL_Transmit(_pdev, _inEpAddr, (uint8_t*) &_msc->csw, USBD_BOT_CSW_LENGTH);
		USBD_LL_PrepareReceive(_pdev, _outEpAddr, (uint8_t*) &_msc->cbw, USBD_BOT_CBW_LENGTH);
	}
	else {
		len = min((lunData->len * lunData->blkSize), (uint32_t) MSC_MEDIA_PACKET);
		USBD_LL_PrepareReceive(_pdev, _outEpAddr, _msc->bot_data, len);
	}

	return true;
}


bool SCSIProcessor::updateBotData(
	const uint8_t *buffer,
	unsigned length) {

	_msc->bot_data_length = length;
	memcpy(_msc->bot_data, buffer, length);

	return true;
}
