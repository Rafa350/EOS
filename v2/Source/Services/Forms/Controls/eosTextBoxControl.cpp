module;


#include "eos.h"


export module Eos.Services.Forms.Controls.TextBox;


import Eos.Services.Forms;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;


export namespace eos {

    class TextBoxControl: public eos::Control {
        private:
            const char *_text;
            Color _textColor;

        protected:
            void onRender(Graphics *graphics) override;

        public:
            TextBoxControl(const Point &position, const Size &size, const char *text);

            inline void setText(const char *text) { setProperty(_text, text); };
            inline void setTextColor(Color color) { setProperty(_textColor, color); }

            inline const char *getText() const { return _text; }
            inline Color getTextColor() const { return _textColor; }
    };
}


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

	if (_text != nullptr) {

		Text text;
		text.setHorizontalAlign(eos::Text::HorizontalAlign::center);
		text.setForeground(Brush(_textColor));
		text.setBackground(Brush(getBackgroundColor()));
		text.setText(_text, (uint32_t) -1);

		graphics->paintText(Rect(getPosition(), getSize()), text);
	}
}
