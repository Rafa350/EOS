module Eos.Controllers.Pin.ISO808;


using namespace eos;


/// ---------------------------------------------------------------------------
/// @brief    Constructor.
///
Device_ISO808::Device_ISO808() :
    _oldState {0},
    _newState {0} {

}


/// ---------------------------------------------------------------------------
/// @brief    Actualitza l'estat de les sortides.
///
void Device_ISO808::update() {

    if (_newState != _oldState) {
        updateImpl(_newState);
        _oldState = _newState;
    }
}
