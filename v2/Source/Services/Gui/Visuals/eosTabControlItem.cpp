#include "eos.h"
#include "Services/Gui/Visuals/eosTabControlItem.h"


using namespace eos;


TabControlItem::TabControlItem(
	Visual* header,
	Visual* content):

	_header(header),
	_content(content) {
}
