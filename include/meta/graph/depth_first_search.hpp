#ifndef _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP
#define _A07964E1_8B74_4FFA_A8C4_80C5B51F73C2_HPP

#include <iterator>
#include <type_traits>
#include <utility>

#include <boost/hana/core/make.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>

#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/iterator_range.hpp"
#include "detail/stack.hpp"
#include "tags.hpp"

namespace meta::graph {

template <typename G, typename Vis, typename Colors>
constexpr void depth_first_search_1(G&& g, std::size_t s, Vis vis,
                                    Colors& colors) {
  using namespace detail;
  using graph_t = std::decay_t<G>;
  constexpr size_t V = graph_t::vertices_size;

  auto rng = make_iterator_range(g.get(s).begin(), g.get(s).end());
  stack<boost::hana::pair<std::size_t, std::decay_t<decltype(rng)>>, V> q;

  colors[s] = color::Gray;
  vis(discover, s);
  q.push(boost::hana::make_pair(s, rng));

  while (!q.empty()) {
    auto x = q.top();
    auto u = boost::hana::first(x);
    q.pop();

    auto outs = boost::hana::second(x);
    auto[b, e] = outs;
    while (b != e) {
      auto v = *b;
      if (colors[v] == color::White) {
        q.push(boost::hana::make_pair(u, make_iterator_range(++b, e)));
        u = v;
        colors[u] = color::Gray;
        vis(discover, u);
        b = g.get(u).first;
        e = g.get(u).last;
      } else {
        ++b;
      }
    }

    colors[u] = color::Black;
    vis(finish, u);
  }
}

template <typename G, typename Vis>
constexpr void depth_first_search(G&& g, Vis vis) {
  using namespace detail;
  using graph_t = std::decay_t<G>;
  constexpr size_t V = graph_t::vertices_size;

  array<color, V> colors{};

  for (std::size_t u = 0; u < V; ++u) {
    if (colors[u] == color::White) {
      depth_first_search_1(std::forward<G>(g), u, vis, colors);
    }
  }
}
}  // namespace meta::graph
#endif
