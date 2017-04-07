#ifndef _9CC5053B_3A92_4EAE_977C_A00853955303_HPP
#define _9CC5053B_3A92_4EAE_977C_A00853955303_HPP

#include "array.hpp"

namespace meta::graph::detail {

template <typename Iter>
constexpr void insert_sort(Iter b, Iter e) {
  if (b == e) return;

  auto i = b;
  for (; i != e; ++i) {
    auto x = *i;
    auto j = i;
    while (j != b && *(j - 1) > x) {
      *(j) = *(j - 1);
      --j;
    }
    *j = x;
  }
}
}
#endif
