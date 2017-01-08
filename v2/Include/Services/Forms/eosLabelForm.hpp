#ifndef __EOS_LABELFORM_HPP
#define __EOS_LABELFORM_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "Controllers/Display/eosColor.hpp"


namespace eos {
       
    class LabelForm: public Form {
        private:
            const char *title;
            
        public:
            LabelForm(FormsService *service, Form *parent);

            void setTitle(const char *title);

        protected:
            void onPaint(FormsDisplay *display);
    };
}


#endif
