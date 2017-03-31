#ifndef _A69B3B3D_4FD1_4D94_8506_C49A50AFB3D1_HPP
#define _A69B3B3D_4FD1_4D94_8506_C49A50AFB3D1_HPP

namespace meta {
namespace graph {
namespace detail {

template <typename T>
struct iterator_range {
  T first;
  T last;

  constexpr T begin() { return first; }
  constexpr T end() { return last; }
};

template <typename T>
constexpr auto make_iterator_range(T a, T b) {
  return iterator_range<T>{a, b};
}
}
}
}
#endif
