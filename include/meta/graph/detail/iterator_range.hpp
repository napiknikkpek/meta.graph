#ifndef _A69B3B3D_4FD1_4D94_8506_C49A50AFB3D1_HPP
#define _A69B3B3D_4FD1_4D94_8506_C49A50AFB3D1_HPP

namespace meta {
namespace graph {
namespace detail {

template <typename T>
struct iterator_range {
  T b;
  T e;

  constexpr T begin() { return b; }
  constexpr T end() { return e; }
};

template <typename T>
constexpr auto make_iterator_range(T a, T b) {
  return iterator_range<T>{a, b};
}
}
}
}
#endif
