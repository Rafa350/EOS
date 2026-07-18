#include "eos.h"
#include "Services/Forms/Controls/eosTextBoxControl.h"
#include "System/Graphics/eosBrush.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosColorDefinitions.h"
#include "System/Graphics/eosGraphics.h"
#include "System/Graphics/eosPen.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosRect.h"
#include "System/Graphics/eosText.h"


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    position: Posicio del control.
/// \param    size: Tamany del control.
/// \param    text: Texte a mostrar.
///
eos::TextBoxControl::TextBoxControl(
    const Point &position,
    const Size &size,
    const char *text):

    Control {position, size},
    _text {text},
    _textColor {Colors::white} {

}


/// ----------------------------------------------------------------------
/// \brief    Renderitza el control.
/// \param    graphics: L'objecte per dibuixar.
///
void eos::TextBoxControl::onRender(
    eos::Graphics *graphics) {

	Control::onRender(graphics);

	Text text;
	text.setHorizontalAlign(eos::Text::HorizontalAlign::center);
    text.setForeground(Brush(_textColor));
    text.setBackground(Brush(getBackgroundColor()));
	text.setText(_text, (uint32_t) -1);

	graphics->paintText(Rect(getPosition(), getSize()), text);
}
