#pragma once

#include <type_traits>

#define MAELSTROM_ARG(...) __VA_ARGS__

#define MAELSTROM_TYPE_EQUAL(a, b) std::is_same_v<a, b>
