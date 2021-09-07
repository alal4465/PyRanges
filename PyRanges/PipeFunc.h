#pragma once
#include <concepts>
#include "PyIterable.h"
#include <ranges>

namespace PyRanges {
	struct PipeFunc;

	template <typename T>
	concept PyIterableOrRange = std::derived_from<T, PyIterable<typename T::iterator>> || std::ranges::range<T>;

	template <typename T>
	concept ProcessFunction = std::derived_from<T, PipeFunc>;

	struct PipeFunc {
		template <PyIterableOrRange TContainer, ProcessFunction TPred> 
		requires std::invocable<TPred, TContainer>
		friend constexpr inline auto operator| (const TContainer& container, TPred pred) {
			return pred(container);
		}

		constexpr inline virtual ~PipeFunc() = default;
	};
}
