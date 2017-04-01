
#include "meta/graph/adj_list.hpp"
#include "meta/graph/strongly_connected_components.hpp"

using namespace meta::graph;
using namespace meta::graph::detail;

int main() {
  constexpr auto r = strongly_connected_components(
      make_adj_list(make_array(1, 2), make_array(2), make_array(1),
                    make_array(4), make_array(3)));
  constexpr auto expected = make_array(1, 2, 2, 0, 0);

  static_assert(equal(r.begin(), r.end(), expected.begin(), expected.end()));

  return 0;
}
