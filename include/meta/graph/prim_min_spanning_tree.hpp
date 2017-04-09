#ifndef _34E72C11_05C8_4A45_867F_407B57AA7E8B_HPP
#define _34E72C11_05C8_4A45_867F_407B57AA7E8B_HPP

#include <algorithm>
#include <type_traits>

#include "detail/array.hpp"
#include "detail/heap.hpp"
#include "detail/stack.hpp"

namespace meta::graph {

template <typename G>
constexpr auto prim_min_spanning_tree(
    G&& g,
    detail::array<std::size_t, std::decay_t<G>::edges_size> const& weights) {
  using namespace detail;
  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;
  constexpr std::size_t E = graph_t::edges_size;

  array<bool, V> contained{};
  array<std::size_t, V> observed{};
  array<std::size_t, V> current{};
  for (std::size_t i = 0; i < V; ++i) {
    observed[i] = std::numeric_limits<std::size_t>::max();
  }
  auto h = make_heap<V, std::max<std::size_t>(E / V, 2)>(observed);

  observed[0] = 0;
  h.down(0);

  while (h.size != 0) {
    auto u = h.pop();
    contained[u] = true;
    for (auto e : g.out_edges(u)) {
      auto v = g.get_edge(e).opposite(u);
      auto w = weights[e];
      if (!contained[v] && w < observed[v]) {
        current[v] = e;
        observed[v] = w;
        h.increase(v);
      }
    }
  }

  stack<std::size_t, V - 1> res;
  for (std::size_t i = 1; i < V; ++i) {
    res.push(current[i]);
  }

  return res.data;
}

}  // namespace meta::graph
#endif
