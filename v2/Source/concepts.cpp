module;


#include <concepts>


export module Eos.Concepts;


namespace eos {

	export template <typename T_>
	concept IsUInt = std::unsigned_integral<T_>;

	export template <typename T_>
	concept IsInt = std::signed_integral<T_>;

    export template <typename T_>
    concept IsClass = std::is_class_v<T_>;

    export template <typename T_>
    concept IsEnum = std::is_enum_v<T_>;
}
