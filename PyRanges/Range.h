#pragma once
#include <concepts>
#include <cstdint>
#include <algorithm>
#include "PyIterable.h"

namespace PyRanges {
	template<std::integral T>
	class RangeIterator {
	public:
		using self_type = RangeIterator;
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::size_t;

		constexpr inline RangeIterator(T cur, T dest, std::int64_t inc) noexcept :
			cur_(cur),
			dest_(dest),
			inc_(inc)
		{}

		constexpr inline self_type operator++() noexcept {
			if (inc_ >= 0) {
				cur_ = (cur_ + inc_ < dest_) ? (cur_ + inc_) : dest_;
			}
			else {
				cur_ = (cur_ + inc_ > dest_) ? (cur_ + inc_) : dest_;
			}
			return *this;
		}

		constexpr inline self_type operator++(int) noexcept {
			self_type cpy = *this;
			++(*this);
			return cpy;
		}

		constexpr inline bool operator==(const self_type& other) const noexcept {
			return cur_ == other.cur_ && dest_ == other.dest_ && inc_ == other.inc_;
		}

		constexpr inline bool operator!=(const self_type& other) const noexcept {
			return !(*this == other);
		}

		constexpr inline const value_type operator*() const noexcept { return cur_; }
		constexpr inline const pointer operator->() const noexcept { return &cur_; }
	private:
		T cur_;
		T dest_;
		std::int64_t inc_;
	};

	template<std::integral T>
	class Range final : public PyIterable<RangeIterator<T>> {
	public:
		inline constexpr Range(T start, T dest, std::int64_t inc = 1) :
			start_(start),
			dest_(calc_dest_limit(start, dest, inc)),
			inc_(inc)
		{
			if (inc_ == 0) {
				throw std::runtime_error("Range() arg 3 must not be zero");
			}
		}

		inline constexpr explicit Range(T dest) : Range(0, dest) {}

		using iterator = RangeIterator<T>;

		constexpr inline iterator begin() noexcept override {
			return cbegin();
		}

		constexpr inline iterator end() noexcept override {
			return cend();
		}

		constexpr inline iterator begin() const noexcept {
			return iterator(start_, dest_, inc_);
		}

		constexpr inline iterator end() const noexcept {
			return iterator(dest_, dest_, inc_);
		}

		// modifying the iterator data is not allowed as it won't change the range instance itself
		using const_iterator = iterator;

		constexpr inline const_iterator cbegin() const noexcept {
			return begin();
		}

		constexpr inline const_iterator cend() const noexcept {
			return end();
		}

	private:
		// handle the case in which dest may never be reached
		constexpr inline static T calc_dest_limit(T start, T dest, std::int64_t inc) {
			return inc >= 0 ? std::max(start, dest) : std::min(start, dest);
		}

		T start_;
		T dest_;
		std::int64_t inc_;
	};
}
