#ifndef __eosGuiButtons__
#define __eosGuiButtons__


namespace eos {

    class ButtonBase {
    };
    
    class PushButton: public ButtonBase {
    
        protected:
            void onTouch();
            void onRender();
    };
    
    class ToggleButton: public Buttonbase {

        protected:
            void onTouch();
            void onRender();
    };

}


#endif // __eosGuiButtons__