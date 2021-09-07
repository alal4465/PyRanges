#pragma once
#include <concepts>
#include <algorithm>

namespace PyRanges {
	template <typename T>
	class PyIterator {
	public:
		using self_type = PyIterator<T>;
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::size_t;
	};
}
