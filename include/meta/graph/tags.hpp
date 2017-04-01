#ifndef _3CB1D591_4903_4CA1_BC38_45ADCF09919E_HPP
#define _3CB1D591_4903_4CA1_BC38_45ADCF09919E_HPP

#include <type_traits>

namespace meta::graph {
enum class color { White = 0, Gray, Black };

template <typename X, typename Y>
constexpr bool is_same(X x, Y y) {
  return std::is_same<std::decay_t<decltype(x)>,
                      std::decay_t<decltype(y)>>::value;
}

struct discover_tag {};
struct finish_tag {};

constexpr discover_tag discover{};
constexpr finish_tag finish{};
}  // namespace meta::graph
#endif
