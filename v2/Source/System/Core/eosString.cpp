#include "System/Core/eosString.hpp"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Contructor.
///
String::String() {
    
    buffer = nullptr;
}


/// ----------------------------------------------------------------------
/// \brief Contructor copia.
/// \param s: La string a copiar.
///
String::String(const String& other) {
    
}


/// ----------------------------------------------------------------------
/// \bried Contructor.
/// \param s: Texte de la cadena.
///
String::String(const char *text) {
    
}