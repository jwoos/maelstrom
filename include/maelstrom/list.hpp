#pragma once

#include <cstddef>
#include <utility>

namespace maelstrom::list {

namespace detail {

template <size_t I, typename T> struct list_unit {
  using type = T;
  static constexpr size_t index = I;
};

template <typename, typename...> struct list_impl;

template <size_t... Is, typename... Types>
struct list_impl<std::index_sequence<Is...>, Types...>
    : public list_unit<Is, Types>... {};

} // namespace detail

template <typename... Types>
struct list
    : public detail::list_impl<std::make_index_sequence<sizeof...(Types)>,
                               Types...> {
  static constexpr size_t size = sizeof...(Types);
};

/**
 * maelstrom::list::head
 *
 * Get the first element of a list
 */
namespace detail {

template <typename First, typename... Rest> struct head_impl {
  using type = First;
};

} // namespace detail
template <typename T> struct head;

template <typename... Vals>
struct head<list<Vals...>> : public detail::head_impl<Vals...> {};

template <typename... Vals> using head_t = head<Vals...>::type;

/**
 * maelstrom::list::tail
 *
 * Get the list minus the head (first element)
 */
namespace detail {

template <typename First, typename... Rest> struct tail_impl {
  using type = list<Rest...>;
};

} // namespace detail

template <typename T> struct tail;

template <typename... Vals>
struct tail<list<Vals...>> : public detail::tail_impl<Vals...> {};

template <typename... Vals> using tail_t = tail<Vals...>::type;

/**
 * maelstrom::list::last
 *
 * Get the last element of a list
 */
namespace detail {

template <typename First, typename... Rest> struct last_impl {
  using type = std::conditional_t<sizeof...(Rest) == 0, First,
                                  typename last_impl<Rest...>::type>;
};

template <typename T> struct last_impl<T> {
  using type = T;
};

} // namespace detail

template <typename T> struct last;

// template <typename... Vals>
template <typename... Vals> struct last<list<Vals...>> {
  using type = detail::last_impl<Vals...>::type;
};

template <typename... Vals> using last_t = last<Vals...>::type;

/**
 * maelstrom::list::init
 *
 * Get all elements except the last
 */
namespace detail {

template <typename T, typename... Acc> struct init_impl;

template <typename Last, typename... Acc>
struct init_impl<list<Last>, list<Acc...>> {
  using type = list<Acc...>;
};

template <typename First, typename... Rest, typename... Acc>
struct init_impl<list<First, Rest...>, list<Acc...>> {
  using type = typename init_impl<list<Rest...>, list<Acc..., First>>::type;
};

} // namespace detail

template <typename T> struct init;

template <typename... Vals> struct init<list<Vals...>> {
  using type = detail::init_impl<list<Vals...>, list<>>::type;
};

template <typename... Vals> using init_t = init<Vals...>::type;

/**
 * maelstrom::list::index
 *
 * Get the element at the index
 */
template <size_t, typename> struct index;

template <size_t Idx, typename Head, typename... Tail>
struct index<Idx, list<Head, Tail...>> : public index<Idx - 1, list<Tail...>> {
};

template <typename Head, typename... Tail>
struct index<0, list<Head, Tail...>> {
  using type = Head;
};

template <size_t Idx, typename T> using index_t = index<Idx, T>::type;

// leave out for now since it's a C++2c extension
// but this would make it make the above so easy...
#if defined(__cpp_pack_indexing) && false
template <std::size_t Idx, class... Types> struct index<Idx, list<Types...>> {
  using type = Types...[Idx];
};
#endif

/**
 * maelstrom::list::tuple_to_list
 *
 * Transforms a tuple to a list
 */
template <typename T> struct tuple_to_list;

template <typename... Inner> struct tuple_to_list<std::tuple<Inner...>> {
  using type = list<Inner...>;
};

/**
 * maelstrom::list::concat
 *
 * Concatenates multiple sequences together
 */
template <typename T, typename U> struct concat;

template <typename T, typename... Rest>
struct concat<list<T>, list<Rest...>> : public list<T, Rest...> {};

// template <typename T, size_t... Idx>
// struct repeat {
// 	// FIXME: this doesn't actually do what I want it to do...
// 	using type = repeat<T, Idx...>::type;
// };

// template <typename T>
// struct repeat<T, 0> {
// 	using type = list<T>;
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
struct tup_from_arr_impl<Arr, list<Ts...>> {
  using type = std::tuple<Ts...>;
};

} // namespace detail

// template <typename T, size_t Size, typename Arr = std::array<T, Size>>
// struct tup_from_arr : public detail::tup_from_arr_impl<
// 											T,
// 											list<size_t,
// > > {
// };

template <typename T, typename U> struct concat;

} // namespace maelstrom::list
