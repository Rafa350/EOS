export module Eos.System.Forms.PropertyObserver;


import Eos.Callbacks;


export namespace eos {

    class PropertyObserver {
    	public:
    		struct PropertyChangedEventArgs {
    			void *property;
    		};
    		using IPropertyChangedEvent = ICallbackP2<PropertyObserver*, PropertyChangedEventArgs*>;
    		template <typename Instance_> using PropertyChangedEvent = CallbackP2<Instance_, PropertyObserver*, PropertyChangedEventArgs*>;

        private:
            IPropertyChangedEvent *_propertyChangedEvent;

        private:
            void propertyChanged(void *property);

        protected:
            template <typename ValueType_>
                bool setProperty(ValueType_ &property, const ValueType_ &value);

            virtual void onPropertyChanged(void *property);

        public:
            PropertyObserver();
            virtual ~PropertyObserver() = default;

            inline void setPropertyChangedEvent(IPropertyChangedEvent &event) {
            	_propertyChangedEvent = &event;
            }
            inline void clearPropertyChangedEvent() {
            	_propertyChangedEvent = nullptr;
            }
    };
}


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
PropertyObserver::PropertyObserver():
	_propertyChangedEvent {nullptr} {
}


/// ---------------------------------------------------------------------------
/// @brief    Asigna el valor d'una propietat.
/// @tparam   ValueType_ : El tipus del valor.
/// @param    property   : La propietat.
/// @param    value      : El valor a asignar.
/// @return   Trus si el valor de la propietat ha canviat, false en
///           cas contrari.
///
template <typename ValueType_>
bool PropertyObserver::setProperty(
    ValueType_ &property,
    const ValueType_ &value) {

    if (property == value)
        return false;
    else {
        property = value;
        propertyChanged(&property);
        return true;
    }
}


/// ---------------------------------------------------------------------------
/// @brief    Procesa els canvis en el valor de la propietat.
/// @param    property : Punter a la propietat que ha canviat de valor.
///
void PropertyObserver::propertyChanged(
    void *property) {

    onPropertyChanged(property);
}


/// ---------------------------------------------------------------------------
/// @brief    Es crida quant ha canviat una propietat. Executa l'event
///           si esta definit.
/// @param    property : La propietat.
///
void PropertyObserver::onPropertyChanged(
    void *property) {

	if (_propertyChangedEvent != nullptr) {
		PropertyChangedEventArgs args = {
			.property {property}
		};
		_propertyChangedEvent->execute(this, &args);
	}
}
