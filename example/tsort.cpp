
#include "meta/graph/adj_list.hpp"
#include "meta/graph/topological_sort.hpp"

using namespace meta::graph;
using namespace meta::graph::detail;

int main() {
  constexpr auto r = topological_sort(make_adj_list(
      make_array(1, 2), make_array(2), make_array(1, 3), make_array(0)));
  constexpr auto expected = make_array(3, 2, 1, 0);

  static_assert(equal(r.begin(), r.end(), expected.begin(), expected.end()));
  return 0;
}
