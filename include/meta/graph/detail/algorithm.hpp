#ifndef _4EAE5E39_5EFB_409B_A8E6_641669802316_HPP
#define _4EAE5E39_5EFB_409B_A8E6_641669802316_HPP

namespace meta::graph::detail {

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

template <typename Input1, typename Input2>
constexpr bool equal(Input1 b1, Input1 e1, Input2 b2, Input2 e2) {
  for (; b1 != e1 && b2 != e2; ++b1, ++b2) {
    if (*b1 != *b2) return false;
  }
  return b1 == e1 && b2 == e2;
}

template <typename T>
constexpr void swap(T& a, T& b) {
  T t = a;
  a = b;
  b = t;
}

template <typename Input>
constexpr void reverse(Input first, Input last) {
  while (first != last && first != --last) {
    swap(*first++, *last);
  }
}
}  // namespace meta::graph::detail
#endif
