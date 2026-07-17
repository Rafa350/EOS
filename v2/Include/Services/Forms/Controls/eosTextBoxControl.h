#pragma once
#ifndef __eosTextBoxControl__
#define __eosTextBoxControl__


#include "eos.h"
#include "System/Graphics/eosColor.h"
#include "Services/Forms/eosControl.h"


namespace eos {

    class Graphics;

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


#endif // __eosTextBoxControl__
