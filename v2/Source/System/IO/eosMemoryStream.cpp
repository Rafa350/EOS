module;


#include "eos.h"
#include "System/IO/eosStream.h"


export module Eos.IO.MemoryStream;


export namespace eos {

	/// \brief Stream en memoria de tamany fix.
	///
    class MemoryStream final: public Stream {
        private:
            uint8_t * const _begin;
            uint8_t * const _end;
            uint8_t *_ptr;

    	public:
            MemoryStream();
            MemoryStream(uint8_t *buffer, uint32_t size);

            Result initialize(uint8_t *buffer, uint32_t size);

            uint32_t getPosition() const;
            void setPosition(uint32_t position);

    		ResultU32 write(const uint8_t *buffer, uint32_t length) override;
    		ResultU32 read(uint8_t *buffer, uint32_t bufferSize) override;

            uint8_t *data() const;
            uint32_t size() const;
    };

}


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte.
///
eos::MemoryStream::MemoryStream():
	_begin {nullptr},
	_end {nullptr},
	_ptr {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief   Construeix l'objecte i l'inicialitza.
/// \param   buffer: Buffer de dades del stream.
/// \param   size: Tamany del buffer en bytes.
///
eos::MemoryStream::MemoryStream(
    uint8_t* buffer,
    uint32_t size):

    _begin {buffer},
    _end {buffer + size},
	_ptr {buffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Obte la posicio actual de lectura/escriptura.
/// \return   La posicio.
///
uint32_t eos::MemoryStream::getPosition() const {

	return _ptr - _begin;
}

/// ----------------------------------------------------------------------
/// \brief    Asigna la posicio de lectura/escriptura.
/// \param    position: La nova posicio. No pot sortir dels limits del buffer.
///
void eos::MemoryStream::setPosition(
	uint32_t position) {

	if ((_begin + position) < _end)
		_ptr = _begin + position;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    buffer: Dades a escriure.
/// \param    length: Longitut de dades en bytes.
/// \return   El nombre de bytes escrits i el resultat de l'operacio
///
eos::ResultU32 eos::MemoryStream::write(
    const uint8_t *buffer,
    uint32_t length) {

    if (_ptr + length >= _end)
        length = _end - _ptr;

    if (length > 0) {
        memcpy(_ptr, buffer, length);
        _ptr += length;
    }

	return {ResultU32::ErrorCodes::ok, length};
}


/// ----------------------------------------------------------------------
/// \brief    llegeix dades del stream.
/// \param    buffer: Buffer on deixar les dades lleigides.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   El nombre de bytes lleigits i el resultat de l'operacio
///
eos::ResultU32 eos::MemoryStream::read(
	uint8_t *buffer,
	uint32_t bufferSize) {

    if (_ptr + bufferSize >= _end)
        bufferSize = _end - _ptr;

    if (bufferSize > 0) {
    	memcpy(buffer, _ptr, bufferSize);
    	_ptr += bufferSize;
    }

	return {ResultU32::ErrorCodes::ok, bufferSize};
}


inline uint8_t *eos::MemoryStream::data() const {
	return _begin;
}


inline uint32_t eos::MemoryStream::size() const {
	return _end - _begin;
}

