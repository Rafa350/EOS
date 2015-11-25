#ifndef __APP_MAINFORM_HPP
#define	__APP_MAINFORM_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Services/Forms/eosFormsMenus.hpp"


namespace app {
    
    using namespace eos;
    
    class MainForm: public Form {
        private:
            MenuFormHandle mainMenuForm;
        public:
            MainForm(FormsServiceHandle service);
            ~MainForm();
            
        private:
            void mainMenuFormEvCommandHandler(unsigned command);
            void doSetXJerk();
            void incDecEvChange(int value);
            void incDecEvSet(int value);
    };
    
}


#endif


