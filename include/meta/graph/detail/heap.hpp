#ifndef _50DA175C_4D00_44B6_9553_66A186CEB031_HPP
#define _50DA175C_4D00_44B6_9553_66A186CEB031_HPP

#include "algorithm.hpp"
#include "array.hpp"

namespace meta::graph::detail {

template <std::size_t N, std::size_t K = 2>
struct heap {
  static std::size_t const capacity = N;
  static std::size_t const arity = K;

  array<std::size_t, N> elems;
  array<std::size_t, N> indices;
  array<std::size_t, N> const& weights;

  std::size_t size;

  constexpr auto top() { return elems[0]; }

  constexpr auto pop() {
    auto r = elems[0];
    swap_elems(0, size - 1);
    --size;
    down(0);
    return r;
  }

  constexpr std::size_t push(std::size_t val) {
    auto r = elems[size++];
    weights[r] = val;
    up(size - 1);
    return indices[size - 1];
  }

  constexpr void increase(std::size_t idx) { up(indices[idx]); }

  constexpr void decrease(std::size_t idx) { down(indices[idx]); }

  constexpr auto parent(std::size_t e) { return (e - 1) / K; }

  constexpr auto child(std::size_t e, std::size_t c) { return e * K + c + 1; }

  constexpr void up(std::size_t e) {
    auto p = parent(e);
    while (e && weights[elems[p]] > weights[elems[e]]) {
      swap_elems(p, e);
      e = p;
      p = parent(e);
    }
  }

  constexpr void down(std::size_t e) {
    while (true) {
      auto cur = e;
      auto w = weights[elems[cur]];
      for (auto c = 0; c < K; ++c) {
        auto t = child(e, c);
        if (t < size && weights[elems[t]] < w) {
          cur = t;
          w = weights[elems[cur]];
        }
      }
      if (e != cur) {
        swap_elems(e, cur);
        e = cur;
      } else {
        break;
      }
    }
  }

  constexpr void swap_elems(std::size_t e1, std::size_t e2) {
    auto i1 = elems[e1];
    auto i2 = elems[e2];
    elems[e1] = i2;
    elems[e2] = i1;
    indices[i1] = e2;
    indices[i2] = e1;
  }
};

template <std::size_t N, std::size_t K = 2>
constexpr auto make_heap(array<std::size_t, N>& weights) {
  heap<N, K> h{{}, {}, weights, N};
  for (std::size_t i = 0; i < N; ++i) {
    h.elems[i] = i;
    h.indices[i] = i;
  }

  for (std::size_t i = (N - 1) / heap<N>::arity + 1; i > 0; --i) {
    h.down(i - 1);
  }

  return h;
}
}  // namespace meta::graph::detail
#endif
