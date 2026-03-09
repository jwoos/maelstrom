#include <type_traits>

#include "null.hpp"

namespace maelstrom {

namespace option {

template <typename T> struct option {
  using type = T;
};

// TODO constrain with concepts or SFINAE
template <typename T> struct has_value {
  static constexpr bool value =
      !std::is_same_v<std::decay_t<typename T::type>, null>;
};

template <typename T> constexpr bool has_value_v = has_value<T>::value;

} // namespace option
} // namespace maelstrom
