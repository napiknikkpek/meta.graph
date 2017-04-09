#ifndef _A62DEF22_3F29_4148_8211_6837C131CFB9_HPP
#define _A62DEF22_3F29_4148_8211_6837C131CFB9_HPP

#include <cstdlib>
#include <type_traits>

namespace meta::graph::detail {

template <typename T, std::size_t Size>
struct array {
  static std::size_t const size = Size;

  T elems[Size];

  constexpr T& operator[](std::size_t n) { return elems[n]; }
  constexpr T const& operator[](std::size_t n) const { return elems[n]; }

  constexpr T* begin() noexcept { return elems; }
  constexpr T const* begin() const noexcept { return elems; }
  constexpr T* end() noexcept { return elems + Size; }
  constexpr T const* end() const noexcept { return elems + Size; }
};

template <typename D, typename... T>
constexpr auto make_array(T&&... t) {
  return array<D, sizeof...(T)>{std::forward<D>(t)...};
}
}  // namespace meta::graph::detail
#endif
