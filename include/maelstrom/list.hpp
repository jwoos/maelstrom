#pragma once

#include <cstddef>
#include <utility>

#include "sequence.hpp"

namespace maelstrom::list {

namespace detail {

template <size_t I, typename T> struct list_unit {
  using type = T;
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
  using sequence = sequence::sequence<Types...>;
};

template <size_t, typename> struct index;

template <size_t Idx, typename Head, typename... Tail>
struct index<Idx, list<Head, Tail...>> : public index<Idx - 1, list<Tail...>> {
};

template <typename Head, typename... Tail>
struct index<0, list<Head, Tail...>> {
  using type = Head;
};

template <size_t Idx, typename T> using index_t = index<Idx, T>::type;

// leave out for now...
#if defined(__cpp_pack_indexing) && false
template <std::size_t Idx, class... Types> struct index<Idx, list<Types...>> {
  using type = Types...[Idx];
};
#endif

} // namespace maelstrom::list
