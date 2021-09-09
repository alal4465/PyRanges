#pragma once
#include "PipeFunc.h"
#include "PyIterable.h"
#include "PyIterator.h"
#include <utility>
#include <type_traits>
#include <tuple>
#include <iterator>

namespace PyRanges {
	template <std::size_t I = 0, typename... Ts>
	constexpr inline auto check_tuples_contain_match(const std::tuple<Ts...>& tup1, const std::tuple<Ts...>& tup2) {
		auto current_elem_equal = std::get<I>(tup1) == std::get<I>(tup2);
		if constexpr (I == sizeof...(Ts) - 1) {
			return current_elem_equal;
		}
		else {
			return current_elem_equal || check_tuples_contain_match<I + 1>(tup1, tup2);
		}
	}

	template <typename... TIters>
	class ZipIterator final : PyIterator<std::tuple<typename TIters::value_type...>> {
	private:
		using value_tuple = std::tuple<typename TIters::value_type...>;
		using iterator_tuple = std::tuple<TIters...>;

	public:
		using self_type = ZipIterator<TIters...>;
		using PyIterator<value_tuple>::pointer;
		using PyIterator<value_tuple>::value_type;
		using PyIterator<value_tuple>::reference;
		using PyIterator<value_tuple>::iterator_category;
		using PyIterator<value_tuple>::difference_type;

		inline constexpr ZipIterator(TIters... iterators) noexcept : iterators_{ iterators... } {}
		
		constexpr inline self_type operator++() noexcept {
			std::apply([](TIters& ... iters) { ((++iters), ...); }, iterators_);
			return *this;
		}

		constexpr inline self_type operator++(int) noexcept {
			self_type cpy = *this;
			++(*this);
			return cpy;
		}

		constexpr inline bool operator==(const self_type& other) const noexcept {
			return check_tuples_contain_match(iterators_, other.iterators_);
		}
		
		constexpr inline bool operator!=(const self_type& other) const noexcept {
			return !(*this == other);
		}
		
		constexpr inline const value_tuple operator*() const noexcept {
			return std::apply([](TIters... iters) { return value_tuple(*iters...); }, iterators_);
		}

	private:
		iterator_tuple iterators_;
	};

	template <typename T>
	using select_iterator_for = std::conditional_t<
		std::is_const_v<std::remove_reference_t<T>>,
		typename std::decay_t<T>::const_iterator,
		typename std::decay_t<T>::iterator>;

	template <typename ... T>
	class ZipImpl final : PyIterable<ZipIterator<select_iterator_for<T> ...>>
	{
	public:
		using iterator = ZipIterator<select_iterator_for<T> ...>;

		template <typename ... Args>
		ZipImpl(Args && ... args)
			: containers_{ std::forward<Args>(args)... }
		{}

		constexpr inline iterator begin() override {
			return std::apply([](auto && ... args) {
				return iterator(std::begin(args)...);
			}, containers_);
		}

		constexpr inline iterator end() override {
			return std::apply([](auto && ... args) {
				return iterator(std::end(args)...);
			}, containers_);
		}

	private:
		std::tuple<T ...> containers_;
	};

	template <typename ... T>
	auto zip(T && ... t) {
		return ZipImpl<T ...>{std::forward<T>(t)...};
	}
}
