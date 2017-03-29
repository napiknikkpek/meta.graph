#ifndef _49454131_02A8_4F1D_82AC_38FF0E7EDBB7_HPP
#define _49454131_02A8_4F1D_82AC_38FF0E7EDBB7_HPP

#include "array.hpp"

namespace meta {
namespace graph {
namespace detail {

template <typename T, std::size_t Size>
struct queue {
  array<T, Size> data{};
  std::size_t beg = 0;
  std::size_t end = 0;

  constexpr T& front() { return data[beg]; }
  constexpr T const& front() const { return data[beg]; }
  constexpr T& back() { return data[end]; }
  constexpr T const& back() const { return data[end]; }

  constexpr bool empty() const { return beg == end; }
  constexpr std::size_t size() const { return end - beg; }

  constexpr void push(const T& value) { data[end++] = value; }
  constexpr void push(T&& value) { data[end++] = std::move(value); }

  constexpr void pop() { ++beg; }
};
}
}
}
#endif
