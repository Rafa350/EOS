#include "eos.h"
#include "System/IO/eosStream.h"
#include "System/IO/eosStreamWriter.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
///
StreamWriter::StreamWriter(
    Stream &stream):

    stream(stream) {
    
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint8_t.
/// \param    data: El valor a escriure.
///
void StreamWriter::write(
    uint8_t data) {
    
    stream.write((uint8_t*)&data, sizeof(uint8_t));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint16_t.
/// \param    data: El valor a escriure.
///
void StreamWriter::write(
    uint16_t data) {
    
    stream.write((uint8_t*)&data, sizeof(uint16_t));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un valor de tipus uint32_t.
/// \param    data: El valor a escriure.
///
void StreamWriter::write(
    uint32_t data) {
    
    stream.write((uint8_t*)&data, sizeof(uint32_t));
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de memoria
/// \param    data: Punter al bloc de memoria.
/// \param    size: El tamany en bytes del bloc de memoria.
///
void StreamWriter::write(
    const void *data, 
    int size) {
    
    stream.write(data, size);
}
