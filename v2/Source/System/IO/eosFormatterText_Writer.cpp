module;


#include "eos.h"
#include <cstdarg>
#include <stdio.h>


module Eos.System.IO.Formatters.Text;



/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte i l'inicialitza
/// \param    stream: El stream d'escriptura.
///
eos::TextWriter::TextWriter(
	Stream *stream):

	_stream {stream} {

}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint8_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeU8(
	uint8_t data) {

	return writeU32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint16_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeU16(
	uint16_t data) {

	return writeU32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor uint32_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeU32(
	uint32_t data) {

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
bool eos::TextWriter::writeU8Hex(
	uint8_t data) {

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%02X", data);
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
bool eos::TextWriter::writeU16Hex(
	uint16_t data) {

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%04X", data);
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
bool eos::TextWriter::writeU32Hex(
	uint32_t data) {

	char buffer[16];
	int len = snprintf(buffer, sizeof(buffer), "%08lX", data);
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
bool eos::TextWriter::writeI8(
	int8_t data) {

	return writeI32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor int16_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeI16(
	int16_t data) {

	return writeI32(data);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor int32_t en format decimal.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeI32(
	int32_t data) {

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
bool eos::TextWriter::writeChar(
	char data) {

	constexpr unsigned length = sizeof(data);
	auto writeResult = _stream->write((const uint8_t*)&data, length);
	return writeResult.isSuccess() && (writeResult.value() == length);
}


/// ----------------------------------------------------------------------
/// \brief    Escriu una cadena C.
/// \param    data: La cadena a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeString(
	const char *data) {

	if (data != nullptr) {
		auto length = strlen(data);
		if (length > 0) {
			auto writeResult = _stream->write((const uint8_t*)data, length);
			return writeResult.isSuccess() && (writeResult.value() == length);
		}
	}

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor bool.
/// \param    data: El valor a escriure.
/// \return   True si tot es correcte.
///
bool eos::TextWriter::writeBool(
	bool data) {

	return writeString(data == 0 ? "false" : "true");
}
