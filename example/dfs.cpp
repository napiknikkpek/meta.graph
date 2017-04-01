#include "meta/graph/detail/algorithm.hpp"
#include "meta/graph/detail/array.hpp"

#include "meta/graph/adj_list.hpp"
#include "meta/graph/depth_first_search.hpp"
#include "meta/graph/tags.hpp"

using namespace meta::graph;
using namespace meta::graph::detail;

constexpr auto dfs() {
  constexpr auto g = make_adj_list(make_array(1, 2), make_array(2),
                                   make_array(1, 3), make_array(0));
  stack<std::size_t, g.vertices.size()> res;

  depth_first_search(g, [&res](auto tag, std::size_t u) {
    if
      constexpr(is_same(tag, discover)) { res.push(u); }
  });
  return res.data;
}

int main() {
  constexpr auto g = make_adj_list(make_array(1, 2), make_array(2),
                                   make_array(1, 3), make_array(0));

  constexpr auto r = dfs();
  constexpr auto expected = make_array(0, 1, 2, 3);

  static_assert(equal(r.begin(), r.end(), expected.begin(), expected.end()));

  return 0;
}
