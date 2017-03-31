#include "meta/graph/detail/algorithm.hpp"
#include "meta/graph/detail/array.hpp"

#include "meta/graph/adj_list.hpp"
#include "meta/graph/depth_first_search.hpp"

using namespace meta::graph;
using namespace meta::graph::detail;

int main() {
  constexpr auto g = make_adj_list(make_array(1, 2), make_array(2),
                                   make_array(1, 3), make_array(0));

  constexpr auto r = depth_first_search_new(g, 0);
  constexpr auto expected = make_array(0, 1, 2, 3);

  static_assert(equal(r.begin(), r.end(), expected.begin(), expected.end()));

  return 0;
}
