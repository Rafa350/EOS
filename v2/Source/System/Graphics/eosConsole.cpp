#include "eos.h"
#include "System/Graphics/eosConsole.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief Constructor de l'objecte.
/// \param graphics: Objecte 'Graphics' per dibuixar.
/// \param columns: Numero de columnes.
/// \param rows: Numero de fil·leres.
///
Console::Console(
	Graphics *graphics,
	unsigned columns,
	unsigned rows):

	graphics(graphics),
	rows(rows),
	columns(columns),
	row(0),
	column(0) {

}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a l'origen.
///
void Console::home() {

	column = 0;
	row = 0;
}


/// ----------------------------------------------------------------------
/// \brief Mou el cursor a la posicio indicada.
/// \param column: Columna.
/// \param row: Fil·lera.
///
void Console::moveTo(
	unsigned column,
	unsigned row) {

	this->column = column;
	this->row = row;
}
