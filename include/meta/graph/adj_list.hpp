#ifndef _55170AF3_744C_4231_A1D0_7526F90AF10C_HPP
#define _55170AF3_744C_4231_A1D0_7526F90AF10C_HPP

#include <algorithm>
#include <iterator>
#include <utility>

#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/iterator_range.hpp"

namespace meta::graph {

template <std::size_t V, std::size_t E>
struct adj_list {
  static std::size_t const vertices_size = V;
  static std::size_t const edges_size = E;

  detail::array<std::size_t, V> const vertices;
  detail::array<std::size_t, E> const edges;

  constexpr auto get(std::size_t n) const {
    auto b = edges.begin() + vertices[n];
    auto e = edges.begin() + (n + 1 < V ? vertices[n + 1] : E);
    return detail::make_iterator_range(b, e);
  }
};

template <typename T, std::size_t... Is>
constexpr auto make_adj_list(detail::array<T, Is>... xs) {
  constexpr auto V = sizeof...(Is);
  constexpr auto E = (... + Is);

  using namespace detail;

  array<std::size_t, V> sizes{Is...};
  array<std::size_t, V> vertices{};
  partial_sum(sizes.begin(), prev(sizes.end()), next(vertices.begin()));

  array<std::size_t, E> edges{};

  auto i = edges.begin();
  (..., (i = copy(xs.begin(), xs.end(), i)));

  return adj_list<V, E>{vertices, edges};
}
}  // namespace meta::graph
#endif
