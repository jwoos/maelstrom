#pragma once

namespace maelstrom {

template <typename T> struct type_holder {
  using type = T;
};

template <typename T> using type_holder_t = type_holder<T>::type;

} // namespace maelstrom
