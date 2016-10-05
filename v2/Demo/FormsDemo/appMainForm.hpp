#ifndef __APP_MAINFORM_HPP
#define	__APP_MAINFORM_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosMenuForm.hpp"


namespace app {
    
    using namespace eos;
    
    class MainForm: public Form {
        private:
            MenuForm *menuForm;
            Form *editorForm;
            unsigned currentCommand;
            
        public:
            MainForm(FormsService *service);
            ~MainForm();
            
        protected:
            void onPaint(FormsDisplay *display);
            void onSelectorPress();
            void onSelectorMove(int16_t position, SelectorDirection direction);
            void onKeyPress(KeyCode keyCode);
    
        private:
            void menuClickItemHandler(MenuForm *menuForm, ItemId itemId);
            void menuDrawItemHandler(MenuForm *menuForm, DrawItemEventParams *params);
            void editorSelectorPressHandler(Form *form);
            void startEdit();
            void endEdit();
            void incDecEvChange(int value);
            void incDecEvSet(int value);
    };
    
}


#endif


