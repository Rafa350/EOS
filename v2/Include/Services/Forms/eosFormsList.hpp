#ifndef __EOS_FORMSLIST_HPP
#define __EOS_FORMSLIST_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class ListForm;
    typedef ListForm *ListFormhandle;
    
    class ListForm: public Form {
        private:
            const char *title;
    
        public:
            ListForm(FormsServiceHandle service, FormHandle parent);
            ~ListForm();
    };    
}


#endif
