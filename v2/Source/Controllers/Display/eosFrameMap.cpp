#include "eos.h"
#include "eosAssert.h"
#include "Controllers/Display/eosFrameMap.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \remarks  Crea el objecte, pero queda pendent d'inicialitzar per que
///           sigui operatiu.
///
FrameMap::FrameMap():

	_map(nullptr) {
}


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    width: Amplada de la imatge.
/// \param    height: Alçada de la imatge:
/// \param    blockWidth: Amplada de cada bloc.
/// \param    blockHeight: Alçada de cada block.
/// \remarks  Es crea l'objecte i queda inicialitzat i llest pel seu us.
///
FrameMap::FrameMap(
	int width,
	int height,
	int blockWidth,
	int blockHeight):

	_map(nullptr) {

	eosAssert(width > 0);
	eosAssert(height > 0);
	eosAssert((blockWidth > 0) && (blockWidth <= width));
	eosAssert((blockHeight > 0) && (blockHeight <= height));

	initialize(width, height, blockWidth, blockHeight);
}


/// ----------------------------------------------------------------------
/// \brief    Destructor del objecte.
///
FrameMap::~FrameMap() {

	if (_map != nullptr)
		delete[] _map;
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio.
/// \param    width: Amplada de la imatge.
/// \param    height: Alçada de la imatge:
/// \param    blockWidth: Amplada de cada bloc.
/// \param    blockHeight: ALçada de cada block.

void FrameMap::initialize(
	int width,
	int height,
	int blockWidth,
	int blockHeight) {

	eosAssert(width > 0);
	eosAssert(height > 0);
	eosAssert((blockWidth > 0) && (blockWidth <= width));
	eosAssert((blockHeight > 0) && (blockHeight <= height));
	eosAssert(_map == nullptr);

	_columns = (width + blockWidth - 1) / blockWidth;
	_rows = (height + blockHeight - 1) / blockHeight;
	_blockWidth = blockWidth;
	_blockHeight = blockHeight;

	_mapSize = ((_columns * _rows) + 7) / 8;
	_map = new uint8_t[_mapSize];
	memset(_map, 0x00, _mapSize);
}


/// ----------------------------------------------------------------------
/// \brief    Neteja els blocs.
///
void FrameMap::clear() {

	eosAssert(_map == nullptr);
	eosAssert(_mapSize > 0);

	memset(_map, 0x00, _mapSize);
}
