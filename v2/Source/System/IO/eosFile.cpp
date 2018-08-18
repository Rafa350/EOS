#include "System/IO/eosFile.h"
#include "Controllers/Fat/ff.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Comprofa l'existencia d'un fitxer.
/// \param fileName: El nom del fitxer.
/// \return True si existeix. False en cas contrari.
///
bool File::exists(
	const String &fileName) {

	return f_stat(fileName, nullptr) == FR_OK;
}
