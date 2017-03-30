#ifndef _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP
#define _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP

#include <iterator>
#include <type_traits>

#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/iterator_range.hpp"
#include "detail/stack.hpp"

namespace meta {
namespace graph {

enum class color { White = 0, Gray, Black };

template <typename G>
constexpr auto depth_first_search(G&& g, std::size_t s) {
  using namespace detail;

  using graph_t = std::decay_t<G>;

  constexpr size_t V = graph_t::vertices_size;
  constexpr size_t E = graph_t::edges_size;

  stack<std::size_t, E> q;
  array<color, V> colors{};
  stack<std::size_t, V> res;

  q.push(s);

  while (!q.empty()) {
    auto x = q.top();

    if (colors[x] != color::White) {
      colors[x] = color::Black;
      q.pop();
      continue;
    }

    res.push(x);
    colors[x] = color::Gray;

    auto adj = g.get(x);
    for (auto i :
         make_iterator_range(std::make_reverse_iterator(adj.end()),
                             std::make_reverse_iterator(adj.begin()))) {
      auto clr = colors[i];
      if (clr == color::White) {
        q.push(i);
      }
    }
  }

  return res.data;
}
}
}
#endif
