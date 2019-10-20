#include "eos.h"
#include "eosAssert.h"
#include "System/IO/eosFileStream.h"
#include "System/Core/eosPoolAllocator.h"
#include "System/Core/eosString.h"

#include "ff.h"


#define MAX_FILES 10


using namespace eos;


// Pools de memoria
//
static PoolAllocator<FileStream> fileStreamAllocator(MAX_FILES);
static PoolAllocator<FIL> fileAllocator(MAX_FILES);


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte de l'objecte.
///
FileStream::FileStream():

	hFile(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Contructor de l'objecte.
/// \param    fileName: El nom del fitxer.
/// \param    mode: El modus d'apertura del fitxer.
/// \param    access: El tipus d'acces.
///
FileStream::FileStream(
	const String &fileName,
	FileMode mode,
	FileAccess access):

	hFile(nullptr) {

	open(fileName, mode, access);
}


/// ----------------------------------------------------------------------
/// \brief    Destructoir de l'objecte.
///
FileStream::~FileStream() {

	close();
}


/// ----------------------------------------------------------------------
/// \brief    Obra el stream.
/// \param    fileName: El nom del fitxer.
/// \param    mode: El modus d'apertura del fitxer.
/// \param    access: El tipus d'acces.
/// \return   True si l'ha pogut obrir.
///
bool FileStream::open(
	const String &fileName,
	FileMode mode,
	FileAccess access) {

	if (hFile != nullptr)
		return false;

	BYTE fmode = 0;

	switch (mode) {
		case FileMode::create:
		case FileMode::truncate:
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

	hFile = fileAllocator.allocate(sizeof(FIL));
	if (hFile == nullptr)
		return false;

	if (f_open((FIL*)hFile, fileName, fmode) != FR_OK) {
		fileAllocator.deallocate((FIL*)hFile);
		hFile = nullptr;
		return false;
	}

	return true;
}

/// ----------------------------------------------------------------------
/// \brief    Tanca el stream si es obert.
/// \return   True si l'ha pogut tancar.
///
bool FileStream::close() {

	if (hFile == nullptr)
		return false;

	if (f_close((FIL*)hFile) != FR_OK)
		return false;

	fileAllocator.deallocate((FIL*)hFile);
	hFile = nullptr;

	return true;
}


/// ----------------------------------------------------------------------
/// \brief    Llegeix un bloc de dades.
/// \param    data: Punter al bloc de dades.
/// \param    size: Tamany del bloc de dades.
/// \return:  Numero de bytes lleigits. -1 en cas d'error.
///
int FileStream::read(
	void *data,
	int size) {

	UINT rCount;

	if (f_read((FIL*)hFile, data, size, &rCount) != FR_OK)
		return -1;

	return rCount;
}


/// ----------------------------------------------------------------------
/// \brief    Escriu un bloc de dades.
/// \param    data: Punter al bloc de dades.
/// \param    size: Tamany en bytes del bloc de dades.
/// \return   El numero de bytes escrits. -1 en cas d'error.
///
int FileStream::write(
	void *data,
	int size) {

	UINT wCount;

	if (f_write((FIL*) hFile, data, size, &wCount) != FR_OK)
		return -1;

	return wCount;
}


/// ----------------------------------------------------------------------
/// \brief    Operador 'new'.
/// \param    size: El tamany de memoria solicitat.
/// \return   El bloc de memoria obtingut.
///
void *FileStream::operator new(
	size_t size) {

	return fileStreamAllocator.allocate(size);
}


/// ----------------------------------------------------------------------
/// \brief    Operador 'delete'.
/// \param    p: El bloc de memoria a alliverar.
///
void FileStream::operator delete(
	void *p) {

	fileStreamAllocator.deallocate(static_cast<FileStream*>(p));
}
