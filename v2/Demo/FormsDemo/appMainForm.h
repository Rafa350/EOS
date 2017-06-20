#ifndef __APP_MAINFORM_H
#define	__APP_MAINFORM_H


#include "eos.h"
#include "Services/Forms/eosForms.h"
#include "Services/Forms/eosMenuForm.h"
#include "Services/Forms/eosLabelForm.h"
#include "Services/Forms/eosNumericEditorForm.h"


namespace app {

    using namespace eos;
    
    class MainForm: public Form {
        private:
            MenuForm *menuForm;
            LabelForm *label1;
            LabelForm *label2;
            NumericEditorForm *valueEditor1;
            NumericEditorForm *valueEditor2;
            Form *editorForm;
            unsigned currentCommand;

        public:
            MainForm(FormsService *service);
            ~MainForm();

        protected:
            void onPaint(FormsDisplay *display);
#ifdef eosFormsService_UseSelector
            void onSelectorInc(uint16_t delta);
            void onSelectorDec(uint16_t delta);
            void onSelectorPress();
#endif
#ifdef eosFormsService_UseKeyboard
            void onKeyPress(KeyCode keyCode);
#endif
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


