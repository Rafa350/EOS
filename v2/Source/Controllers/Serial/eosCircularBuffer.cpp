#include "eos.h"
#include "Controllers/Serial/eosCircularBuffer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    buffer: Buffer de dades.
/// \param    bufferSize: Tamany del buffer de dades en bytes.
///
CircularBuffer::CircularBuffer(
	uint8_t *buffer,
	uint16_t bufferSize) :

	_buffer(buffer),
	_bufferSize(bufferSize),
	_pushIdx(0),
	_popIdx(0),
	_count(0) {

}


/// ----------------------------------------------------------------------
/// \brief    Inserta un byte de dades.
/// \param    data: El byte de dades.
///
void CircularBuffer::push(
	uint8_t data) {

	if (_count < _bufferSize) {
		_count++;
		_buffer[_pushIdx++] = data;
		if (_pushIdx == _bufferSize)
			_pushIdx = 0;
	}
}


/// ----------------------------------------------------------------------
/// \brief    Inserta un bloc de dades.
/// \param    data: El bloc de dades.
/// \param    dataLength: El tamany del bloc de dades en bytes.
///
void CircularBuffer::push(
	const uint8_t *data,
	uint16_t dataLength) {

	if (_count + dataLength < _bufferSize)
		while (dataLength--)
			push(*data++);
}


/// ----------------------------------------------------------------------
/// \brief    Exteru un byte del buffer.
/// \return   El valor del byte.
///
uint8_t CircularBuffer::pop() {

	uint8_t data = 0;

	if (_count > 0) {
		_count--;
		data = _buffer[_popIdx++];
		if (_popIdx == _bufferSize)
			_popIdx = 0;
	}

	return data;
}


/// ----------------------------------------------------------------------
/// \brief    Buida el buffer.
///
void CircularBuffer::clear() {

	_pushIdx = 0;
	_popIdx = 0;
	_count = 0;
}
