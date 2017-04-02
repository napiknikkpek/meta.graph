#ifndef _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP
#define _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <boost/hana/core/make.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/iterator_range.hpp"
#include "detail/stack.hpp"
#include "tags.hpp"

namespace meta::graph {

template <typename G, typename Vis, typename Colors>
constexpr void depth_first_search_1(G&& g, std::size_t s, Vis&& vis,
                                    Colors& colors) {
  using namespace detail;
  using namespace boost::hana::literals;
  using graph_t = std::decay_t<G>;
  constexpr size_t V = graph_t::vertices_size;

  auto rng = make_iterator_range(g.get(s).begin(), g.get(s).end());
  stack<boost::hana::tuple<std::size_t, std::decay_t<decltype(rng)>>, V> q;

  colors[s] = color::Gray;
  call(vis, root_vertex, s);
  call(vis, discover_vertex, s);
  q.push(boost::hana::make_tuple(s, rng));

  while (!q.empty()) {
    auto u = q.top()[0_c];
    auto outs = q.top()[1_c];
    q.pop();

    auto[b, e] = outs;
    while (b != e) {
      auto v = *b;
      auto clr = colors[v];
      if (clr == color::White) {
        call(vis, tree_edge, u, v);
        q.push(boost::hana::make_tuple(u, make_iterator_range(++b, e)));
        u = v;
        colors[u] = color::Gray;
        call(vis, discover_vertex, u);
        b = g.get(u).first;
        e = g.get(u).last;
      } else {
        if (clr == color::Gray)
          call(vis, back_edge, u, v);
        else
          call(vis, forward_or_cross_edge, u, v);
        ++b;
      }
    }

    colors[u] = color::Black;
    call(vis, finish_vertex, u);
  }
}

template <typename G, typename Vis>
constexpr void depth_first_search(G&& g, Vis&& vis) {
  using namespace detail;
  using graph_t = std::decay_t<G>;
  constexpr size_t V = graph_t::vertices_size;

  array<color, V> colors{};

  for (std::size_t u = 0; u < V; ++u) {
    if (colors[u] == color::White) {
      depth_first_search_1(std::forward<G>(g), u, std::forward<Vis>(vis),
                           colors);
    }
  }
}
}  // namespace meta::graph
#endif
