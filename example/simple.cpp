
#include "meta/graph/detail/algorithm.hpp"
#include "meta/graph/detail/array.hpp"
#include "meta/graph/detail/queue.hpp"

#include "meta/graph/adj_list.hpp"
#include "meta/graph/breadth_first_search.hpp"

namespace graph = meta::graph;

using namespace meta::graph::detail;

int main() {
  constexpr auto g =
      graph::make_adj_list(make_array(1, 2), make_array(2), make_array(1));

  constexpr auto r = graph::breadth_first_search(g, 0);

  static_assert(r.size() == 3);

  return 0;
}
