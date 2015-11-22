#ifndef __EOS_FORMINCDEC_HPP
#define __EOS_FORMSINCDEC_HPP


#include "eos.hpp"
#include "Services/Forms/eosForms.hpp"
#include "System/eosCallbacks.hpp"


namespace eos {
    
    class IncDecForm;
    typedef IncDecForm *IncDecFormHandle;
    
    class IncDecForm: public Form {
        private:
            typedef ICallbackP1<unsigned> IIncDecFormChangeEvent;
            typedef ICallbackP1<unsigned> IIncDecFormSetEvent;
            
        private:
            int value;
            int minValue;
            int maxValue;
            int delta;
            const char *title;
            const char *prefix;
            const char *suffix;
            IIncDecFormChangeEvent *evChange;
            IIncDecFormSetEvent *evSet;
            
        public:
            IncDecForm(FormsServiceHandle service, FormHandle parent);
            ~IncDecForm();
            
            template <class cls>
            void setEvChange(cls *instance, void (cls::*method)(int)) { 
                
                evChange = new CallbackP1<cls, int>(instance, method);
            }
            
            template <class cls>
            void setEvSet(cls *instance, void (cls::*method)(int)) { 
                
                evSet = new CallbackP1<cls, int>(instance, method);
            }
            
            void setMinValue(int minValue);
            void setMaxValue(int maxValue);
            void setValue(int value);
            void setDelta(int delta);
            void setTitle(const char *title);
            void setPrefix(const char *prefix);
            void setSuffix(const char *suffix);
            
            /// \brief Retorna el valor actual.
            /// \return El valor actual.
            ///
            int getValue() const { return value; }
        private:
            void dispatchMessage(Message &message);
            void onActivate(FormHandle deactivateForm);
            void onPaint(DisplayServiceHandle displayService);
            void incValue();
            void decValue();
            void setValue();
    };

}


#endif
