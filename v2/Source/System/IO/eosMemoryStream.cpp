#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosMemoryStream.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief   Constructor del objecte.
/// \param   buffer: Buffer de dades del stream.
/// \param   bufferSize: Tamany del buffer en bytes.
///
MemoryStream::MemoryStream(
    uint8_t* buffer, 
    int bufferSize):

    buffer(buffer),
    bufferSize(bufferSize) {
    
    eosAssert(buffer != nullptr);
    eosAssert(buffserSize > 0);    
}


/// ----------------------------------------------------------------------
/// \brief    Destructor del objecte.
///
MemoryStream::~MemoryStream() {
    
}


/// ----------------------------------------------------------------------
/// \brief    Escriu dades en el stream.
/// \param    data: Dades a escriure.
/// \param    size: Numero de bytes a escriure.
/// \return   El numero de bytes escrits.
///
int MemoryStream::write(
    const void* data, 
    int size) {
    
    eosAssert(data != nullptr);
    eosAssert(size > 0);
    
    if ((bufferSize - writePosition) < size)
        size = bufferSize - writePosition;
    
    if (size > 0) {
        memcpy(buffer + writePosition, data, size);
        writePosition += size;
    }
    
    if (writePosition > length)
        length = writePosition;
    
    return size;
}
