#ifndef _C3C33C4F_6FC8_47D1_B1B4_38D09331B9CB_HPP
#define _C3C33C4F_6FC8_47D1_B1B4_38D09331B9CB_HPP

#include "depth_first_search.hpp"
#include "detail/stack.hpp"
#include "tags.hpp"

namespace meta::graph {

template <typename G>
constexpr auto topological_sort(G&& g) {
  using namespace detail;

  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;

  stack<std::size_t, V> res;

  depth_first_search(std::forward<G>(g), [&res](auto tag, std::size_t u) {
    if
      constexpr(is_same(tag, finish)) { res.push(u); }
  });

  return res.data;
}
}  // namespace meta::graph
#endif
