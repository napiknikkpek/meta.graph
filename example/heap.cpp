#include "meta/graph/detail/heap.hpp"

#include <iostream>

using namespace meta::graph::detail;

auto test1() {
  array<std::size_t, 6> weights{16, 2, 1, 10, 7, 3};
  auto h = make_heap(weights);

  array<std::size_t, 6> r{};
  for (std::size_t i = 0; i < 6; ++i) {
    r[i] = weights[h.pop()];
  }

  return r;
}

int main() {
  auto r = test1();

  for (auto x : r) std::cout << x << ' ';
  std::cout << std::endl;

  return 0;
}
