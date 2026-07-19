#pragma once
#ifndef __eosControl__
#define __eosControl__


#include "eos.h"
#include "eosCallbacks.h"
#include "Services/Forms/eosVisual.h"
#include "System/Collections/eosIntrusiveForwardList.h"
#include "System/Graphics/eosColor.h"
#include "System/Graphics/eosPoint.h"
#include "System/Graphics/eosSize.h"


namespace eos {

    class Control: public Visual {
    	public:
    		struct PropertyChangedEventArgs {
    			void *ptr;
    		};
    		using IPropertyChangedEvent = ICallbackP2<Control*, PropertyChangedEventArgs*>;
    		template <typename Instance_> using PropertyChangedEvent = CallbackP2<Instance_, Control*, PropertyChangedEventArgs*>;

        private:
            Color _backgroundColor;
            Color _borderColor;
            IPropertyChangedEvent *_propertyChangedEvent;

        protected:
            void onPropertyChanged(void *property) override;
            void onRender(Graphics *graphics) override;

        public:
            Control(const Point &position, const Size &size);
            Control(const Control &) = delete;
            Control(const Control &&) = delete;

            inline void setBackgroundColor(Color value) { setProperty(_backgroundColor, value); }
            inline void setBorderColor(Color value) { setProperty(_borderColor, value); }

            inline void setPropertyChangedEvent(IPropertyChangedEvent &event) {
            	_propertyChangedEvent = &event;
            }
            inline void clearPropertyChangedEvent() {
            	_propertyChangedEvent = nullptr;
            }

            inline Color getBackgroundColor() const { return _backgroundColor; }
            inline Color getBorderColor() const { return _borderColor; }
    };

}


#endif // __eosControl
