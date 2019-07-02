#include "eos.h"
#include "System/Graphics/eosConsole.h"
#include "System/Graphics/eosGraphics.h"


using namespace eos;


Console::Console(
	Graphics *graphics,
	int cols,
	int rows):

	graphics(graphics),
	cols(cols),
	rows(rows) {

}
