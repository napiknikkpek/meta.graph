#ifndef _29C86023_2F77_47FD_AA7A_4F84FDAB815B_HPP
#define _29C86023_2F77_47FD_AA7A_4F84FDAB815B_HPP

#include <type_traits>

#include "detail/array.hpp"
#include "detail/queue.hpp"

namespace meta {
namespace graph {

enum class color { White = 0, Gray, Black };

template <typename G>
constexpr auto breadth_first_search(G&& g, std::size_t s) {
  using namespace detail;

  using graph_t = std::decay_t<G>;

  queue<std::size_t, graph_t::vertices_size> q;
  array<color, graph_t::vertices_size> colors{};

  colors[s] = color::Gray;
  q.push(s);

  while (!q.empty()) {
    auto x = q.front();
    q.pop();

    for (auto child : g.get(x)) {
      auto& clr = colors[child];
      if (clr == color::White) {
        q.push(child);
        clr = color::Gray;
      }
    }
    colors[x] = color::Black;
  }

  return q.data;
}
}
}
#endif
