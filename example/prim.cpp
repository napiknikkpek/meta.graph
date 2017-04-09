#include <initializer_list>

#include "meta/graph/detail/array.hpp"
#include "meta/graph/incidence_graph.hpp"
#include "meta/graph/prim_min_spanning_tree.hpp"

#include <iostream>

using namespace meta::graph;
using namespace meta::graph::detail;

constexpr auto test1() {
  constexpr auto g = make_incidence_graph<9>(array<edge, 14>{{{0, 1},
                                                              {0, 7},
                                                              {1, 7},
                                                              {1, 2},
                                                              {7, 8},
                                                              {7, 6},
                                                              {8, 2},
                                                              {8, 6},
                                                              {2, 3},
                                                              {2, 5},
                                                              {6, 5},
                                                              {3, 5},
                                                              {3, 4},
                                                              {4, 5}}});

  constexpr array<std::size_t, 14> weights{4, 8, 11, 8, 7,  1, 2,
                                           6, 7, 4,  2, 14, 9, 10};

  constexpr auto r = prim_min_spanning_tree(g, weights);

  std::size_t res = 0;
  for (auto x : r) {
    res += weights[x];
  }
  return res;
}

int main() {
  constexpr array<edge, 3> edges{{{0, 1}, {1, 2}, {1, 3}}};
  constexpr auto g = make_incidence_graph<4>(edges);
  constexpr array<std::size_t, 3> weights{1, 2, 3};
  constexpr auto r = prim_min_spanning_tree(g, weights);
  static_assert(test1() == 37);

  return 0;
}
