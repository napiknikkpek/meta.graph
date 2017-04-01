#include "meta/graph/detail/stack.hpp"

#include "meta/graph/adj_list.hpp"
#include "meta/graph/breadth_first_search.hpp"

using namespace meta::graph;
using namespace meta::graph::detail;

constexpr auto bfs() {
  constexpr auto g = make_adj_list(make_array(1, 2), make_array(2),
                                   make_array(1, 3), make_array(0));
  stack<std::size_t, g.vertices.size()> res;
  breadth_first_search(g, 0, [&res](auto tag, std::size_t u) {
    if
      constexpr(is_same(discover, tag)) { res.push(u); }
  });
  return res.data;
}

int main() {
  constexpr auto r = bfs();
  constexpr auto expected = make_array(0, 1, 2, 3);

  static_assert(equal(r.begin(), r.end(), expected.begin(), expected.end()));

  return 0;
}
