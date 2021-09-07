#pragma once
#include "pipes.h"
#include <utility>
#include <type_traits>
#include <iterator>
#include <vector>

namespace PyRanges {
	template <PyIterableOrRange TContainer>
	constexpr inline auto enumerate(const TContainer& container) {
		using InnerType = typename std::remove_reference_t<decltype(*std::begin(container))>;
		std::vector<std::pair<std::size_t, InnerType>> enum_result;

		std::size_t index = 0;
		for (const auto& item : container) {
			enum_result.push_back({ index, item });
			index++;
		}

		return enum_result;
	}
}
