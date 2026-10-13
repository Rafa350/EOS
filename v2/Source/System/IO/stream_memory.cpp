module;


#include "eos.h"


export module Eos.System.IO.Streams.Memory;


export import Eos.System.IO.Streams;

import Eos.Result;
import Eos.Types;


export namespace eos {

   class MemoryStream final: public Stream {
        private:
            UInt8 * const _begin;
            UInt8 * const _end;
            UInt8 *_ptr;

    	public:
            MemoryStream(UInt8 *buffer, UInt32 bufferSize);

            UInt32 getPosition() const;
            void setPosition(UInt32 position);

    		StdResultU32 write(const UInt8 *buffer, UInt32 length) override;
    		StdResultU32 read(UInt8 *buffer, UInt32 bufferSize) override;

            UInt8 *buffer() const { return _begin; }
            UInt32 bufferSize() const { return _end - _begin; }
    };
}


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief   Construeix l'objecte i l'inicialitza.
/// \param   buffer: Buffer de dades del stream.
/// \param   bufferSize: Tamany del buffer en bytes.
///
MemoryStream::MemoryStream(
    UInt8* buffer,
    UInt32 bufferSize):

    _begin {buffer},
    _end {buffer + bufferSize},
	_ptr {buffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Obte la posicio actual de lectura/escriptura.
/// \return   La posicio.
///
UInt32 MemoryStream::getPosition() const {

	return _ptr - _begin;
}


/// ----------------------------------------------------------------------
/// \brief    Asigna la posicio de lectura/escriptura.
/// \param    position: La nova posicio. No pot sortir dels limits del buffer.
///
void MemoryStream::setPosition(
	UInt32 position) {

	if ((_begin + position) < _end)
		_ptr = _begin + position;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    buffer: Dades a escriure.
/// \param    length: Longitut de dades en bytes.
/// \return   El nombre de bytes escrits i el resultat de l'operacio
///
StdResultU32 MemoryStream::write(
    const UInt8 *buffer,
    UInt32 length) {

    if (_ptr + length >= _end)
        length = _end - _ptr;

    if (length > 0) {
        memcpy(_ptr, buffer, length);
        _ptr += length;
    }

	return {length};
}


/// ----------------------------------------------------------------------
/// \brief    llegeix dades del stream.
/// \param    buffer: Buffer on deixar les dades lleigides.
/// \param    bufferSize: Tamany del buffer en bytes.
/// \return   El nombre de bytes lleigits i el resultat de l'operacio
///
StdResultU32 MemoryStream::read(
	UInt8 *buffer,
	UInt32 bufferSize) {

    if (_ptr + bufferSize >= _end)
        bufferSize = _end - _ptr;

    if (bufferSize > 0) {
    	memcpy(buffer, _ptr, bufferSize);
    	_ptr += bufferSize;
    }

	return {bufferSize};
}
