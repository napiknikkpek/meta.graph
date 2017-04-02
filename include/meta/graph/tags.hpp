#ifndef _3CB1D591_4903_4CA1_BC38_45ADCF09919E_HPP
#define _3CB1D591_4903_4CA1_BC38_45ADCF09919E_HPP

#include <type_traits>

#include <boost/hana/type.hpp>

namespace meta::graph {
enum class color { White = 0, Gray, Black };

template <typename X, typename Y>
constexpr bool is_same(X x, Y y) {
  return std::is_same<std::decay_t<decltype(x)>,
                      std::decay_t<decltype(y)>>::value;
}

struct discover_vertex_tag {};
struct finish_vertex_tag {};
struct root_vertex_tag {};

struct tree_edge_tag {};
struct back_edge_tag {};
struct forward_or_cross_edge_tag {};

constexpr discover_vertex_tag discover_vertex{};
constexpr finish_vertex_tag finish_vertex{};
constexpr root_vertex_tag root_vertex{};

constexpr tree_edge_tag tree_edge{};
constexpr back_edge_tag back_edge{};
constexpr forward_or_cross_edge_tag forward_or_cross_edge{};

template <typename Vis, typename... Args>
constexpr void call(Vis&& vis, Args... args) {
  constexpr auto cond = decltype(boost::hana::is_valid(vis, args...))::value;
  if
    constexpr(cond) { vis(args...); }
}

}  // namespace meta::graph
#endif
