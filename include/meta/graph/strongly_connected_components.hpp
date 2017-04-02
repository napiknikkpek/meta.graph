#ifndef _103056F1_0D45_404A_8B10_680E81220B9C_HPP
#define _103056F1_0D45_404A_8B10_680E81220B9C_HPP

#include "adj_list.hpp"
#include "depth_first_search.hpp"
#include "detail/algorithm.hpp"
#include "detail/array.hpp"
#include "detail/stack.hpp"

namespace meta::graph {

namespace {

template <typename G>
struct visitor {
  G const& g;
  static std::size_t const V = std::decay_t<G>::vertices_size;
  detail::array<std::size_t, V> comp{};
  detail::array<std::size_t, V> time{};
  detail::array<std::size_t, V> root{};
  detail::array<std::size_t, V> parent{};
  std::size_t now = 0;
  std::size_t component = 0;
  detail::stack<std::size_t, V> s;

  constexpr visitor(G const& g) : g(g) {}

  constexpr void operator()(root_vertex_tag, std::size_t u) {
    this->operator()(tree_edge, u, u);
  }

  constexpr void operator()(tree_edge_tag, std::size_t u, std::size_t v) {
    root[v] = v;
    comp[v] = std::numeric_limits<std::size_t>::max();
    time[v] = now++;
    parent[v] = u;
    s.push(v);
  }

  constexpr void operator()(back_edge_tag, std::size_t u, std::size_t v) {
    root[u] = lowlink(root[u], root[v]);
  }

  constexpr void operator()(forward_or_cross_edge_tag, std::size_t u,
                            std::size_t v) {
    if (comp[v] == std::numeric_limits<std::size_t>::max()) {
      root[u] = lowlink(root[u], root[v]);
    }
  }

  constexpr void operator()(finish_vertex_tag, std::size_t u) {
    auto p = parent[u];
    root[p] = lowlink(root[p], root[u]);

    if (root[u] != u) return;

    std::size_t v{};
    do {
      v = s.top();
      s.pop();
      comp[v] = component;
      root[v] = u;
    } while (u != v);
    ++component;
  }

 private:
  constexpr std::size_t lowlink(std::size_t u, std::size_t v) {
    return time[u] < time[v] ? u : v;
  }
};

template <typename G>
struct boost_visitor {
  G const& g;
  static std::size_t const V = std::decay_t<G>::vertices_size;
  detail::array<std::size_t, V> comp{};
  detail::array<std::size_t, V> time{};
  detail::array<std::size_t, V> root{};
  std::size_t now = 0;
  std::size_t component = 0;
  detail::stack<std::size_t, V> s;

  constexpr boost_visitor(G const& g) : g(g) {}

  constexpr void operator()(discover_vertex_tag, std::size_t u) {
    root[u] = u;
    comp[u] = std::numeric_limits<std::size_t>::max();
    time[u] = now++;
    s.push(u);
  }

  constexpr void operator()(finish_vertex_tag, std::size_t u) {
    for (auto v : g.get(u)) {
      if (comp[v] == std::numeric_limits<std::size_t>::max()) {
        root[u] = lowlink(root[u], root[v]);
      }
    }

    if (root[u] != u) return;

    std::size_t v{};
    do {
      v = s.top();
      s.pop();
      comp[v] = component;
      root[v] = u;
    } while (u != v);
    ++component;
  }

 private:
  constexpr std::size_t lowlink(std::size_t u, std::size_t v) {
    return time[u] < time[v] ? u : v;
  }
};

}  // namespace

template <typename G>
constexpr auto strongly_connected_components(G&& g) {
  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;

  visitor<graph_t> vis(static_cast<G const&>(g));
  depth_first_search(std::forward<G>(g), vis);

  return vis.comp;
}

template <typename G>
constexpr auto boost_strongly_connected_components(G&& g) {
  using graph_t = std::decay_t<G>;
  constexpr std::size_t V = graph_t::vertices_size;

  boost_visitor<graph_t> vis(static_cast<G const&>(g));
  depth_first_search(std::forward<G>(g), vis);

  return vis.comp;
}

}  // namespace meta::graph
#endif
