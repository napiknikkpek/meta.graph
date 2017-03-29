#ifndef _4EAE5E39_5EFB_409B_A8E6_641669802316_HPP
#define _4EAE5E39_5EFB_409B_A8E6_641669802316_HPP

namespace meta {
namespace graph {
namespace detail {

template <typename Iter>
constexpr auto next(Iter i) {
  return ++i;
}

template <typename Iter>
constexpr auto prev(Iter i) {
  return --i;
}

template <typename Input, typename Output>
constexpr Output partial_sum(Input first, Input last, Output out) {
  if (first == last) return out;

  auto sum = *first;
  *out = sum;

  while (++first != last) {
    sum += *first;
    *++out = sum;
  }
  return ++out;
}

template <typename Input, typename Output>
constexpr Output copy(Input first, Input last, Output out) {
  while (first != last) {
    *out++ = *first++;
  }
  return out;
}
}
}
}
#endif
