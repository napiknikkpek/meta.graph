#include "meta/graph/detail/sort.hpp"
#include "meta/graph/detail/algorithm.hpp"

using namespace meta::graph::detail;

constexpr auto test1() {
  array<std::size_t, 5> res{3, 2, 5, 1, 2};
  array<std::size_t, 5> data{3, 2, 5, 1, 2};
  array<std::size_t, 5> asdf{2, 1, 3, 0, 1};
  insert_sort(res.begin(), res.end());

  return res;
}

int main() {
  constexpr auto res = test1();
  constexpr array<std::size_t, 5> expected{1, 2, 2, 3, 5};

  static_assert(
      equal(res.begin(), res.end(), expected.begin(), expected.end()));
  return 0;
}
