#pragma once
#include <concepts>

namespace PyRanges {
	template <typename TIter>
	class PyIterable {
	public:
		virtual inline TIter begin() = 0;
		virtual inline TIter end() = 0;
		constexpr inline virtual ~PyIterable() = default;
	};
}
