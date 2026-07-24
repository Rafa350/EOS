#include "eos.h"
#include "Services/Forms/Controls/eosSelectionControl.h"


eos::SelectionControl::SelectionControl(
	const Point &position,
	const Size &size):

	Control {position, size},
	_values {nullptr},
	_numValues {0},
	_index {(uint32_t)-1} {


}
