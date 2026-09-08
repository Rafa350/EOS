export module Eos.System.Forms.PropertyObserver;


export namespace eos {

    class PropertyObserver {
        private:
            void propertyChanged(void *ptr);

        protected:
            template <typename ValueType_> 
                bool setProperty(ValueType_ &property, const ValueType_ &value);

            virtual void onPropertyChanged(void *ptr) = 0;

        public:
            virtual ~PropertyObserver() = default;
    };
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
bool eos::PropertyObserver::setProperty(
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
/// @param    ptr : Punter a la propietat que ha canviat de valor.
///
void eos::PropertyObserver::propertyChanged(
    void *ptr) {
    
    onPropertyChanged(ptr);
}
