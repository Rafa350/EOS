#pragma once
#ifndef __eosProperties__
#define __eosProperties__


#include "eos.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

    class Property;
    class PropertyManager;

    using PropertyList = eos::IntrusiveForwardList<Property, 0>;
    using PropertyListNode = eos::IntrusiveForwardListNode<Property, 0>;

    void __link(PropertyManager *manager, Property *property);


    class Property: public PropertyListNode {
        private:
            PropertyManager *_manager;
            const char * const _name;

        protected:
            Property(const char *name);

        public:
            virtual ~Property() = default;

            inline const char *getName() const { return _name; }

        friend void __link(PropertyManager *manager, Property *property);
    };


    template <typename ValueType_>
    class PropertyX: public Property {
        private:
            ValueType_ _value;

        public:
            PropertyX(const char *name):
                Property(name) {
            }

            bool setValue(ValueType_ value) {
                if (_value != value) {
                    _value = value;
                    return true;
                }
                else
                    return false;
            }
            inline ValueType_ getValue() const { return _value; }
    };


    using PropertyI8 = PropertyX<int8_t>;
    using PropertyI16 = PropertyX<int16_t>;
    using PropertyI32 = PropertyX<int32_t>;
    using PropertyU8 = PropertyX<uint8_t>;
    using PropertyU16 = PropertyX<uint16_t>;
    using PropertyU32 = PropertyX<uint32_t>;
    using PropertyBool = PropertyX<bool>;


    class PropertyManager {
        private:
            PropertyList _properties;

        public:
            PropertyManager();

        friend void __link(PropertyManager *manager, Property *property);
    };

}


#endif // __eosProperties__