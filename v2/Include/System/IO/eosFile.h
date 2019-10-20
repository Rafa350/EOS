#ifndef __eosFile__
#define __eosFile__


#include "eos.h"


namespace eos {

	class String;

    /// \brief Especifica com obrir el fitxer.
    enum class FileMode {
        append,		         ///! Afegeix al final, o crea un de nou.
        create,              ///! Crea un de nou, o el sobrescriu.
        createNew,           ///! Crea un de nou.
        open,                ///! Obre un fitxer existent.
        openOrCreate,        ///! Obre un fitxer, o el crea si no existeix.
        truncate             ///! Obre un fitxer existent, i el sobrescriu
    };

    /// \brief Especifica el tipus d'acces.
    enum class FileAccess {
        read,                ///! Lectura
        readWrite,           ///! Lectura i escriptura.
        write                ///! Escriptura.
    };

    /// \brief Clase per la gestio de fitxers en disc
    class File {
        public:
            static bool exists(const String &fileName);
            static void copy(const String &sourceFileName, const String &targetFileName);
            static void remove(const String &fileName);
    };
}


#endif // __eosFile__
