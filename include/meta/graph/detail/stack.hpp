#ifndef _21F5B9D8_0496_47C9_980D_D37C5458516A_HPP
#define _21F5B9D8_0496_47C9_980D_D37C5458516A_HPP

#include "array.hpp"

namespace meta::graph::detail {

template <typename T, std::size_t Size>
struct stack {
  array<T, Size> data{};
  std::size_t index = 0;

  constexpr T& top() { return data[index - 1]; }
  constexpr T const& top() const { return data[index - 1]; }

  constexpr bool empty() const { return index == 0; }
  constexpr std::size_t size() const { return index; }

  constexpr void push(const T& value) { data[index++] = value; }
  constexpr void push(T&& value) { data[index++] = std::move(value); }

  constexpr void pop() { --index; }
};
}  // namespace meta::graph::detail
#endif
