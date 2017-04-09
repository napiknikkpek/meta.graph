#ifndef _6B75FFB9_D5A7_4EB8_8BD7_DBEF87174145_HPP
#define _6B75FFB9_D5A7_4EB8_8BD7_DBEF87174145_HPP

#include <algorithm>

#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/iterator_range.hpp"

namespace meta::graph {

struct edge {
  std::size_t u;
  std::size_t v;

  constexpr auto source() const { return u; }

  constexpr auto target() const { return v; }

  constexpr auto opposite(std::size_t x) const { return u == x ? v : u; }
};

template <std::size_t V, std::size_t E, bool Directed = false>
class incidence_graph;

template <std::size_t V, std::size_t E, bool Directed = false>
constexpr incidence_graph<V, E, Directed> make_incidence_graph(
    detail::array<edge, E> const&);

template <std::size_t V, std::size_t E, bool Directed>
class incidence_graph {
 public:
  static std::size_t const vertices_size = V;
  static std::size_t const edges_size = E;
  static std::size_t const outs_size = Directed ? E : 2 * E;

  constexpr auto const& get_edge(std::size_t e) const { return edges[e]; }

  constexpr auto out_edges(std::size_t u) const {
    auto b = outs.begin() + offsets[u];
    auto e = outs.begin() + (u + 1 < V ? offsets[u + 1] : outs_size);
    return detail::make_iterator_range(b, e);
  }

 private:
  friend constexpr incidence_graph<V, E, Directed>
  make_incidence_graph<V, E, Directed>(detail::array<edge, E> const&);

  detail::array<edge, E> edges{};
  detail::array<std::size_t, V> offsets{};
  detail::array<std::size_t, outs_size> outs{};
};

template <std::size_t V, std::size_t E, bool Directed>
constexpr incidence_graph<V, E, Directed> make_incidence_graph(
    detail::array<edge, E> const& edges) {
  incidence_graph<V, E, Directed> g;
  using namespace detail;

  array<std::size_t, V> sizes{};
  for (std::size_t i = 0; i < E; ++i) {
    auto const& e = edges[i];
    g.edges[i] = e;
    ++sizes[e.u];
    if (!Directed) {
      ++sizes[e.v];
    }
  }

  partial_sum(sizes.begin(), prev(sizes.end()), next(g.offsets.begin()));

  array<std::size_t, V> counter{};
  for (std::size_t i = 0; i < E; ++i) {
    auto const& e = edges[i];

    g.outs[g.offsets[e.u] + counter[e.u]] = i;
    ++counter[e.u];
    if (!Directed) {
      g.outs[g.offsets[e.v] + counter[e.v]] = i;
      ++counter[e.v];
    }
  }

  return g;
}

}  // namespace meta::graph
#endif
