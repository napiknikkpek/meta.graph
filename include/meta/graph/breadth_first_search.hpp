#ifndef _29C86023_2F77_47FD_AA7A_4F84FDAB815B_HPP
#define _29C86023_2F77_47FD_AA7A_4F84FDAB815B_HPP

#include <type_traits>

#include "detail/array.hpp"
#include "detail/queue.hpp"
#include "tags.hpp"

namespace meta::graph {

template <typename G, typename Vis>
constexpr void breadth_first_search(G&& g, std::size_t s, Vis vis) {
  using namespace detail;

  using graph_t = std::decay_t<G>;

  queue<std::size_t, graph_t::vertices_size> q;
  array<color, graph_t::vertices_size> colors{};

  colors[s] = color::Gray;
  call(vis, discover_vertex, s);
  q.push(s);

  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    for (auto u : g.get(u)) {
      auto& clr = colors[u];
      if (clr == color::White) {
        clr = color::Gray;
        call(vis, discover_vertex, u);
        q.push(u);
      }
    }
    colors[u] = color::Black;
    call(vis, finish_vertex, u);
  }
}
}  // namespace meta::graph
#endif
