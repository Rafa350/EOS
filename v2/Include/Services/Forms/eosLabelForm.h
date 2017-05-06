#ifndef __EOS_LABELFORM_H
#define __EOS_LABELFORM_H


#include "eos.h"
#include "Services/Forms/eosForms.h"


namespace eos {
    
    typedef enum class __LabelAlign {
        left,
        right
    } LabelAlign;
       
    class LabelForm: public Form {
        private:
            const char *title;
            LabelAlign labelAlign;
            
        public:
            LabelForm(FormsService *service, Form *parent);

            void setTitle(const char *title);
            void setLabelAlign(LabelAlign labelAlign);
            inline const char* getTitle() const { return title; }
            inline LabelAlign getLabelAlign() const { return labelAlign; }

        protected:
            void onPaint(FormsDisplay *display);
    };
}


#endif
