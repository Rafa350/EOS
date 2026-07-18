#include "eos.h"
#include "Services/Display/eosProperties.h"


/// ----------------------------------------------------------------------
/// /brief    Constructor.
/// /param    name: Nomde la propietat.
///
eos::Property::Property(
    const char *name):

    _manager {nullptr},
    _name {name} {

}


/// ----------------------------------------------------------------------
/// \brief    Enllaça e'objecte 'PropertyManager' amb l'objecte 'Property'
/// \param    manager: L'objecte 'PropertyManager'.
/// \param    property : L'objecte 'Property'
///
void eos::__link(
    eos::PropertyManager *manager, 
    eos::Property *property) {

    if (property->_manager == nullptr) {
        manager->_properties.pushFront(property);
        property->_manager = manager;
    }
}
