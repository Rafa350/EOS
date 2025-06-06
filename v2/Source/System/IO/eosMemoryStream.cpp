#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosMemoryStream.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Construeix l'objecte.
///
MemoryStream::MemoryStream():
	_begin {nullptr},
	_end {nullptr},
	_ptr {nullptr} {

}


/// ----------------------------------------------------------------------
/// \brief   Construeix l'objecte i l'inicialitza.
/// \param   buffer: Buffer de dades del stream.
/// \param   size: Tamany del buffer en bytes.
///
MemoryStream::MemoryStream(
    uint8_t* buffer,
    unsigned size):

    _begin {buffer},
    _end {buffer + size},
	_ptr {buffer} {
}


/// ----------------------------------------------------------------------
/// \brief    Obte la posicio actual de lectura/escriptura.
/// \return   La posicio.
///
unsigned MemoryStream::getPosition() const {

	return _ptr - _begin;
}

/// ----------------------------------------------------------------------
/// \brief    Asigna la posicio de lectura/escriptura.
/// \param    position: La nova posicio. No pot sortir dels limits del buffer.
///
void MemoryStream::setPosition(
	unsigned position) {

	if ((_begin + position) < _end)
		_ptr = _begin + position;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    data: Dades a escriure.
/// \return   El nombre de bytes escrits i el resultat de l'operacio
///
ResultU32 MemoryStream::write(
    const uint8_t *data,
    unsigned size) {

    if (_ptr + size >= _end)
        size = _end - _ptr;

    if (size > 0) {
        memcpy(_ptr, data, size);
        _ptr += size;
    }

    return ResultU32(Results::success, size);
}


/// ----------------------------------------------------------------------
/// \brief    llegeix dades del stream.
/// \param    data: Buffer on deixar les dades lleigides.
/// \return   El nombre de bytes lleigits i el resultat de l'operacio
///
ResultU32 MemoryStream::read(
	uint8_t *data,
	unsigned size) {

    if (_ptr + size >= _end)
        size = _end - _ptr;

    if (size > 0) {
    	memcpy(data, _ptr, size);
    	_ptr += size;
    }

	return ResultU32(Results::success, size);
}

