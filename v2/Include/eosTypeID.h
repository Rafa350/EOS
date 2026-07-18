#pragma once


namespace eos {

	constexpr uint32_t fnv1a(const char* str, uint32_t hash = 2166136261u) {
		return (*str)
			? fnv1a(str + 1, (hash ^ uint32_t(*str)) * 16777619u)
			: hash;
	}

	template<typename Type_, typename ValueType_ = unsigned>
	struct TypeID {
		using ValueType = ValueType_;
		static constexpr ValueType value = (ValueType) fnv1a(__PRETTY_FUNCTION__);
	};

}
