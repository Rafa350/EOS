export module Eos.Services.CanOpen._SDOServer;

import Eos.Services.CanOpen._Types;
import Eos.Types;


export namespace eos {

    class SDOServer: private NonCopyableClass {
        public:
            SDOServer();
            bool processFrame(CobID codId, const UInt8 *rxFrame, UInt8 *txFrame);
    };
}


using namespace eos;


SDOServer::SDOServer() {

}


bool SDOServer::processFrame(
    CobID codId,
    const UInt8 *rxFrame,
    UInt8 *txFrame) {

    return false;
}
