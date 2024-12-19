#include <catch2/catch_test_macros.hpp>

#include <maelstrom/sequence.hpp>

struct TestStruct {};

template <typename T>
struct debug : public T::SOME_NONEXITENT_TYPE {};

TEST_CASE("Sequences are constructed", "[sequence]") {
  STATIC_REQUIRE(maelstrom::sequence::sequence<void, int, TestStruct>::size ==
                 3);
  STATIC_REQUIRE(maelstrom::sequence::sequence<>::size == 0);
}

TEST_CASE("Sequence operations", "[sequence]") {
  using TestType = maelstrom::sequence::sequence<void, int, TestStruct>;

  SECTION("head") {
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::sequence::head<TestType>::type, void>);
    STATIC_REQUIRE(std::is_same_v<maelstrom::sequence::head_t<TestType>, void>);
  }

  SECTION("tail") {
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::sequence::tail<TestType>::type,
                       maelstrom::sequence::sequence<int, TestStruct>>);
    STATIC_REQUIRE(
        std::is_same_v<maelstrom::sequence::tail_t<TestType>,
                       maelstrom::sequence::sequence<int, TestStruct>>);
  }

  SECTION("last") {
    // STATIC_REQUIRE(std::is_same_v<maelstrom::sequence::last<TestType>::type,
    //                               TestStruct>);
    // STATIC_REQUIRE(std::is_same_v<maelstrom::sequence::last_t<TestType>,
    //                               TestStruct>);
  }
}
