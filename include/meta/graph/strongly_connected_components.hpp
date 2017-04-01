#ifndef _103056F1_0D45_404A_8B10_680E81220B9C_HPP
#define _103056F1_0D45_404A_8B10_680E81220B9C_HPP

#include "adj_list.hpp"
#include "depth_first_search.hpp"
#include "detail/algorithm.hpp"
#include "detail/array.hpp"

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

template <typename G>
constexpr auto strongly_connected_components(G&& g) {
  using namespace detail;

  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;

  array<std::size_t, V> fin{};
  auto fi = std::make_reverse_iterator(fin.end());

  depth_first_search(std::forward<G>(g),
                     [&fi](auto tag, std::size_t u) mutable {
                       if
                         constexpr(is_same(tag, finish)) { *fi++ = u; }
                     });

  auto gt = transpose(std::forward<G>(g));

  array<std::size_t, V> res{};

  array<color, V> colors{};
  std::size_t index = 0;
  for (auto x : fin) {
    if (colors[x] != color::White) continue;
    depth_first_search_1(gt, x,
                         [&res, index](auto tag, std::size_t u) {
                           if
                             constexpr(is_same(tag, discover)) {
                               res[u] = index;
                             }
                         },
                         colors);
    ++index;
  }

  return res;
}

}  // namespace meta::graph
#endif
