export module Eos.Services.Forms.Controls.TextBox;

import Eos.Math;
import Eos.Services.Forms;
import Eos.System.Graphics;
import Eos.System.Graphics.Color;
import Eos.System.Graphics.ColorDefinitions;
import Eos.Types;


export namespace eos {

    class TextBoxControl: public Control {
        private:
            const char *_text;
            Color _textColor;
            Text::HorizontalAlign _horizontalAlign;

        protected:
            void onPropertyChanged(void *property) override;
            void onRender(Graphics *graphics) override;

        public:
            TextBoxControl(const Point &position, const Size &size, const char *text);

            inline void setText(const char *value) { setProperty(_text, value); };
            inline void setTextColor(Color value) { setProperty(_textColor, value); }
            inline void setTextAlign(Text::HorizontalAlign value) { setProperty(_horizontalAlign, value); }

            inline const char *getText() const { return _text; }
            inline Color getTextColor() const { return _textColor; }
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
/// @param    position: Posicio del control.
/// @param    size: Tamany del control.
/// @param    text: Texte a mostrar.
///
TextBoxControl::TextBoxControl(
    const Point &position,
    const Size &size,
    const char *text):

    Control {position, size},
    _text {text},
    _textColor {Colors::white},
    _horizontalAlign {Text::HorizontalAlign::center} {

}


/// ---------------------------------------------------------------------------
/// @brief    Procesa el canvi de valor de les propietats.
/// @param    property: La propietat.
///
void TextBoxControl::onPropertyChanged(
	void *property) {

	if ((property == &_text))
		invalidate();

    else
		Control::onPropertyChanged(property);
}


/// ---------------------------------------------------------------------------
/// @brief    Renderitza el control.
/// @param    graphics: L'objecte per dibuixar.
///
void TextBoxControl::onRender(
    Graphics *graphics) {

	Control::onRender(graphics);

	if (_text != nullptr) {

		Text text;
		text.setHorizontalAlign(_horizontalAlign);
		text.setForeground(Brush(_textColor));
		text.setBackground(Brush(getBackgroundColor()));
		text.setText(_text, Math::maxU32);

        Rect r(getPosition(), getSize());
        graphics->paintText(r.inflated(-getBorderThickness()), text);
	}
}
