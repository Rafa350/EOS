#pragma once


namespace eos {

    class PropertyObserver {
        protected:
            template <typename T_>
            void setProperty(T_ &property, const T_ &value) {
                if (property != value) {
                    property = value;
                    propertyChanged(&property);
                }
            }

            virtual void onPropertyChanged(void *ptr) = 0;

        private:
            inline void propertyChanged(void *ptr) {
                onPropertyChanged(ptr);
            }

        public:
            virtual ~PropertyObserver() = default;
    };
}

