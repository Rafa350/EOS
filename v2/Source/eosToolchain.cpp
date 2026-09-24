module;


#include "eos.h"


export module Eos.Configuration.Toolchain;


import Eos.Types;


export namespace eos {

    enum  class ToolchainID {
        unknown,
        gcc,
        clang,
        xc32
    };

#ifdef EOS_TOOLCHAIN_GNU
    constexpr ToolchainID currentToolchain = ToolchainID::gcc;
#else
    #error "Undefined toolchain"
#endif

    template <ToolchainID id_>
    struct Toolchain {
    };

    template <>
    struct Toolchain<ToolchainID::gcc> {
        static constexpr ToolchainID id = ToolchainID::gcc;
    };

    template <>
    struct Toolchain<ToolchainID::clang> {
        static constexpr ToolchainID id = ToolchainID::clang;
    };

    template <>
    struct Toolchain<ToolchainID::xc32> {
        static constexpr ToolchainID id = ToolchainID::xc32;
    };

}
