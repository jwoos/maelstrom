#include <catch2/catch_test_macros.hpp>

#include <maelstrom/list.hpp>
#include <maelstrom/macro.hpp>

struct TestStruct {};

TEST_CASE("Construct a list", "[list]") {
  STATIC_REQUIRE(maelstrom::list::list<void, int, void *>::size == 3);
  STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
      MAELSTROM_ARG(maelstrom::list::list<void, int, void *>::sequence),
      MAELSTROM_ARG(maelstrom::sequence::sequence<void, int, void *>)));
}

TEST_CASE("List operations", "[list]") {
  using TestType = maelstrom::list::list<void, int, TestStruct, void *>;

  SECTION("index") {
    STATIC_REQUIRE(
        MAELSTROM_TYPE_EQUAL(MAELSTROM_ARG(maelstrom::list::index<0, TestType>::type),
                             MAELSTROM_ARG(void)));
    STATIC_REQUIRE(
        MAELSTROM_TYPE_EQUAL(MAELSTROM_ARG(maelstrom::list::index_t<0, TestType>),
                             MAELSTROM_ARG(void)));

    STATIC_REQUIRE(
        MAELSTROM_TYPE_EQUAL(MAELSTROM_ARG(maelstrom::list::index<1, TestType>::type),
                             MAELSTROM_ARG(int)));
    STATIC_REQUIRE(
        MAELSTROM_TYPE_EQUAL(MAELSTROM_ARG(maelstrom::list::index_t<1, TestType>),
                             MAELSTROM_ARG(int)));
  }
}
