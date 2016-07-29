#ifndef __APP_MAINFORM_HPP
#define	__APP_MAINFORM_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosMenuForm.hpp"


namespace app {
    
    using namespace eos;
    
    class MainForm: public Form {
        private:
            MenuFormHandle menuForm;
            FormHandle editorForm;
            unsigned currentCommand;
        public:
            MainForm(FormsServiceHandle service);
            ~MainForm();
            
        protected:
            void onPaint(FormsDisplayHandle display);
    
        private:
            void menuClickItemEventHandler(MenuFormHandle menuForm, unsigned itemId);
            void editorSelectorPressEventHandler(FormHandle form);
            void startEdit();
            void endEdit();
            void incDecEvChange(int value);
            void incDecEvSet(int value);
    };
    
}


#endif


