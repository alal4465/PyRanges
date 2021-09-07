#pragma once
#include <concepts>
#include "PyIterable.h"
#include <ranges>

namespace PyRanges {
	template <typename T>
	concept PyIterableOrRange = std::derived_from<T, PyRanges::PyIterable<typename T::iterator>> || std::ranges::range<T>;

	template <PyIterableOrRange TContainer, std::invocable<TContainer> TPred>
	constexpr inline auto operator| (const TContainer& container, TPred pred) {
		return pred(container);
	}
}
