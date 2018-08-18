#include "System/IO/eosFileStream.h"
#include "Controllers/Fat/ff.h"


#define MAX_FILES 10

using namespace eos;


static FIL files[MAX_FILES];
static int fileIndex = 0;


/// ----------------------------------------------------------------------
/// \brief Constructor per defecte de l'objecte.
///
FileStream::FileStream():

	fileId(0xFF) {
}


/// ----------------------------------------------------------------------
/// \brief Contructor de l'objecte.
/// \param fileName: El nom del fitxer.
/// \param mode: El modus d'apertura del fitxer.
/// \param access: El tipus d'acces.
///
FileStream::FileStream(
	const String &fileName,
	FileMode mode,
	FileAccess access):

	fileId(0xFF) {

	open(fileName, mode, access);
}


/// ----------------------------------------------------------------------
/// \brief Destructoir de l'objecte.
///
FileStream::~FileStream() {

	close();
}


/// ----------------------------------------------------------------------
/// \brief Obra el stream.
/// \param fileName: El nom del fitxer.
/// \param mode: El modus d'apertura del fitxer.
/// \param access: El tipus d'acces.
/// \return True si l'ha pogut obrir.
///
bool FileStream::open(
	const String &fileName,
	FileMode mode,
	FileAccess access) {

	if (fileId == 0xFF) {

		BYTE fmode = 0;

		switch (mode) {
			case FileMode::create:
				fmode |= FA_CREATE_ALWAYS;
				break;

			case FileMode::createNew:
				fmode |= FA_CREATE_NEW;
				break;

			case FileMode::open:
				fmode |= FA_OPEN_EXISTING;
				break;

			case FileMode::openOrCreate:
				fmode |= FA_OPEN_ALWAYS;
				break;

			case FileMode::append:
				fmode |= FA_OPEN_APPEND;
				break;
		}

		switch (access) {
			case FileAccess::read:
				fmode |= FA_READ;
				break;

			case FileAccess::write:
				fmode |= FA_WRITE;
				break;

			case FileAccess::readWrite:
				fmode |= FA_READ | FA_WRITE;
				break;
		}

		if (f_open(&files[fileIndex], fileName, fmode) == FR_OK)
			fileId = fileIndex++;
	}

	return fileId != 0xFF;
}

/// ----------------------------------------------------------------------
/// \brief Tanca el stream si es obert.
/// \return True si l'ha pogut tancar.
///
bool FileStream::close() {

	if (fileId != 0xFF) {
		f_close(&files[fileId]);
		fileId = 0xFF;
	}

	return fileId == 0xFF;
}


uint32_t FileStream::read(void *data, uint32_t size) {

	return size;
}


uint32_t FileStream::write(void *data, uint32_t size) {

	return size;
}
