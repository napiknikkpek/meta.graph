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
  vis(discover, s);
  q.push(s);

  while (!q.empty()) {
    auto u = q.front();
    q.pop();

    for (auto v : g.get(u)) {
      auto& clr = colors[v];
      if (clr == color::White) {
        clr = color::Gray;
        vis(discover, v);
        q.push(v);
      }
    }
    colors[u] = color::Black;
    vis(finish, u);
  }
}
}  // namespace meta::graph
#endif
