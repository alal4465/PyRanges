#pragma once
#include <concepts>
#include "PyIterable.h"
#include <ranges>

namespace PyRanges {
	struct PipeFunc;

	template <typename T>
	concept PyIterableOrRange = std::derived_from<T, PyIterable<typename T::iterator>> || std::ranges::range<T>;

	template <typename T, typename TContainer>
	concept ProcessFunction = std::derived_from<T, PipeFunc> && std::invocable<T, TContainer>;

	struct PipeFunc {
		template <PyIterableOrRange TContainer, ProcessFunction<TContainer> TPred> 
		friend constexpr inline auto operator| (const TContainer& container, TPred pred) {
			return pred(container);
		}

		constexpr inline virtual ~PipeFunc() = default;
	};
}
