#ifndef _F3A1643D_142B_44C0_A82B_112CC3E5E772_HPP
#define _F3A1643D_142B_44C0_A82B_112CC3E5E772_HPP

#include "meta/graph/adj_list.hpp"
#include "meta/graph/algorithm.hpp"
#include "meta/graph/array.hpp"

namespace meta::graph {

template <typename G>
constexpr auto transpose(G&& g) {
  using namespace detail;

  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;
  constexpr std::size_t E = graph_t::edges_size;

  array<std::size_t, V> sizes{};
  for (std::size_t u = 0; u < V; ++u) {
    for (auto v : g.get(u)) {
      ++sizes[v];
    }
  }

  array<std::size_t, V> vertices{};
  partial_sum(sizes.begin(), prev(sizes.end()), next(vertices.begin()));
  array<std::size_t, V> indices = vertices;
  array<std::size_t, E> edges{};

  for (std::size_t u = 0; u < V; ++u) {
    for (auto v : g.get(u)) {
      edges[indices[v]++] = u;
    }
  }

  return adj_list<V, E>{vertices, edges};
}
}  // namespace meta::graph
#endif
