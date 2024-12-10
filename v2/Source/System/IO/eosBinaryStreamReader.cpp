#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosBinaryStreamReader.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    buffer: Buffer de dades.
/// \param    size: Tamany del buffer de dades.
///
BinaryStreamReader::BinaryStreamReader(
    const uint8_t *buffer,
    unsigned size):

    _begin {buffer},
    _end {buffer + size},
    _ptr {buffer} {

}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT8
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readU8(
    uint8_t &data) {

    if (_ptr + sizeof(uint8_t) <= _end) {
        uint8_t a = *_ptr++;
        data = a;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT16
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readU16(
    uint16_t &data) {

    if (_ptr + sizeof(uint16_t) <= _end) {
        uint8_t a = *_ptr++;
        uint8_t b = *_ptr++;
        data = (a << 8) | b;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor UINT32
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readU32(
    uint32_t &data) {

    if (_ptr + sizeof(uint32_t) <= _end) {
        uint8_t a = *_ptr++;
        uint8_t b = *_ptr++;
        uint8_t c = *_ptr++;
        uint8_t d = *_ptr++;
        data = (a << 24) + (b << 16) + (c << 8) + d;
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT8
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readI8(
    int8_t &data) {

    uint8_t v;
    if (readU8(v)) {
        data = static_cast<int8_t>(v);
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT16
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readI16(
    int16_t &data) {

    uint16_t v;
    if (readU16(v)) {
        data = static_cast<int16_t>(v);
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un valor INT32
/// \param    data: El valor a lleigit.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::readI32(
    int32_t &data) {

    uint32_t v;
    if (readU32(v)) {
        data = static_cast<int32_t>(v);
        return true;
    }
    else
        return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    size: El tamany del bloc en bytes.
/// \return   True si tot es correcte.
///
bool BinaryStreamReader::read(
	uint8_t *data,
	unsigned size) {

    eosAssert(data != nullptr);
    eosAssert(size > 0);

	if ((_ptr + size) <= _end) {
		memcpy(data, _ptr, size);
		_ptr += size;
		return true;
	}
	else
		return true;
}
