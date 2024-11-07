#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosTextStreamWriter.h"

#include <cstdarg>
#include <stdio.h>


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte amb els valors inicials.
///
TextStreamWriter::TextStreamWriter() :

    _stream {nullptr} {
}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza
/// \param    stream: El stream d'escriptura.
///
TextStreamWriter::TextStreamWriter(
	Stream *stream):

	_stream {stream} {

	eosAssert(stream != nullptr);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitza l'objecte.
/// \param    stream: El stream d'escriptura.
///
void TextStreamWriter::initialize(
	Stream *stream) {

	eosAssert(stream != nullptr);

	_stream = stream;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU8(uint8_t data) {

	return writeU32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU16(uint16_t data) {

	return writeU32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU32(uint32_t data) {

	eosAssert(_stream != nullptr);

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%lu", data);
	if (len) {
		_stream->write((const uint8_t*)buffer, len);
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t en format hexadecimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU8Hex(uint8_t data) {

	eosAssert(_stream != nullptr);

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%2X", data);
	if (len) {
		_stream->write((const uint8_t*)buffer, len);
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t en format hexadecimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU16Hex(uint16_t data) {

	eosAssert(_stream != nullptr);

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%4X", data);
	if (len) {
		_stream->write((const uint8_t*)buffer, len);
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t en format hexadecimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeU32Hex(uint32_t data) {

	eosAssert(_stream != nullptr);

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%8lX", data);
	if (len) {
		_stream->write((const uint8_t*)buffer, len);
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor int8_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeI8(int8_t data) {

	return writeI32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor int16_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeI16(int16_t data) {

	return writeI32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor int32_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeI32(int32_t data) {

	eosAssert(_stream != nullptr);

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%li", data);
	if (len) {
		_stream->write((const uint8_t*)buffer, len);
		return true;
	}
	else
		return false;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un caracter.
/// \param    data: El caracter a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeChar(
	char data) {

	unsigned count;
	unsigned length = sizeof(data);
	return _stream->write((const uint8_t*)&data, length, &count).isSuccess() && (count == length);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una cadena C.
/// \param    data: La cadena a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeString(
	const char *data) {

	eosAssert(_stream != nullptr);

	unsigned count;
	unsigned length = strlen(data);
	return _stream->write((const uint8_t*)data, length, &count).isSuccess() && (count == length);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor bool.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool TextStreamWriter::writeBool(bool data) {

	eosAssert(_stream != nullptr);

	return writeString(data == 0 ? "false" : "true");
}
