#include <catch2/catch_test_macros.hpp>

#include <maelstrom/list.hpp>
#include <maelstrom/macro.hpp>

struct TestStruct {};

TEST_CASE("Construct a list", "[list]") {
  STATIC_REQUIRE(maelstrom::list::list<void, int, void *>::size == 3);
	STATIC_REQUIRE(maelstrom::list::list<>::size == 0);
}

TEST_CASE("List operations", "[list]") {
  using TestType = maelstrom::list::list<void, int, TestStruct, void *>;

  SECTION("index") {
    STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
        MAELSTROM_ARG(maelstrom::list::index<0, TestType>::type),
        MAELSTROM_ARG(void)));
    STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
        MAELSTROM_ARG(maelstrom::list::index_t<0, TestType>),
        MAELSTROM_ARG(void)));

    STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
        MAELSTROM_ARG(maelstrom::list::index<1, TestType>::type),
        MAELSTROM_ARG(int)));
    STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
        MAELSTROM_ARG(maelstrom::list::index_t<1, TestType>),
        MAELSTROM_ARG(int)));
  }

  SECTION("head") {
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::list::head<TestType>::type, void>);
    STATIC_REQUIRE(std::is_same_v<maelstrom::list::head_t<TestType>, void>);
  }

  SECTION("tail") {
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::list::tail<TestType>::type,
                       maelstrom::list::list<int, TestStruct, void *>>);
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::list::tail_t<TestType>,
                       maelstrom::list::list<int, TestStruct, void *>>);
  }

  SECTION("last") {
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::list::last<TestType>::type, void *>);
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::list::last_t<TestType>, void *>);
  }

  SECTION("init") {
    STATIC_REQUIRE(std::is_same_v<maelstrom::list::init<TestType>::type,
                                  maelstrom::list::list<void, int, TestStruct>>);
    STATIC_REQUIRE(std::is_same_v<maelstrom::list::init_t<TestType>,
                                  maelstrom::list::list<void, int, TestStruct>>);
  }
}
