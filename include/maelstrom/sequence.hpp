#pragma once

#include <cstddef>
#include <utility>

namespace maelstrom::sequence {

struct Null;

template <typename... Vals> struct sequence {
  static constexpr size_t size = sizeof...(Vals);
};

template <typename T> struct inner_sequence;

template <typename... Inner>
struct inner_sequence<sequence<Inner...>> : public sequence<Inner...> {};

namespace detail {

template <typename First, typename... Rest> struct head_impl {
  using type = First;
};

template <typename First, typename... Rest> struct tail_impl {
  using type = sequence<Rest...>;
};

} // namespace detail

template <typename T> struct head;

template <typename... Vals>
struct head<sequence<Vals...>> : public detail::head_impl<Vals...> {};

template <typename... Vals>
using head_t = head<Vals...>::type;

template <typename T> struct tail;

template <typename... Vals>
struct tail<sequence<Vals...>> : public detail::tail_impl<Vals...> {};

template <typename... Vals>
using tail_t = tail<Vals...>::type;

namespace detail {
template <typename First, typename Second> struct last_impl {
  using type = Second;
};

template <typename First> struct last_impl<First, Null> {
  using type = First;
};

template <typename First, typename... Rest>
struct last_impl<First, sequence<Rest...>> {
  using type = last_impl<Rest...>;
};

} // namespace detail

template <typename T> struct last;

template <typename... Vals>
struct last<sequence<Vals...>> : public detail::last_impl<Vals...> {};

template <typename T> struct tuple_to_sequence;

template <typename... Inner> struct tuple_to_sequence<std::tuple<Inner...>> {
  using type = sequence<Inner...>;
};

template <typename T, typename U> struct concat;

template <typename T, typename... Rest>
struct concat<sequence<T>, sequence<Rest...>> : public sequence<T, Rest...> {};

// template <typename T, size_t... Idx>
// struct repeat {
// 	// FIXME: this doesn't actually do what I want it to do...
// 	using type = repeat<T, Idx...>::type;
// };

// template <typename T>
// struct repeat<T, 0> {
// 	using type = sequence<T>;
// };

// template <typename T, size_t Size>
// struct array_to_sequence;
//
// template <typename T, size_t Size>
// struct array_to_sequence<std::array<T, Size>, Size> {
// 	using type = repeat<T, Size>;
// };

template <size_t Width, size_t Height> struct Dimensions {
  static constexpr size_t width = Width;
  static constexpr size_t height = Height;
};

namespace detail {

template <typename T, typename U> struct tup_from_arr_impl;

template <typename Arr, typename... Ts>
struct tup_from_arr_impl<Arr, sequence<Ts...>> {
  using type = std::tuple<Ts...>;
};

} // namespace detail

// template <typename T, size_t Size, typename Arr = std::array<T, Size>>
// struct tup_from_arr : public detail::tup_from_arr_impl<
// 											T,
// 											sequence<size_t,
// > > {
// };

template <typename T, typename U> struct concat;

} // namespace maelstrom::sequence
