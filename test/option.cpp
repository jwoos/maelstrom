#include <catch2/catch_test_macros.hpp>

#include <maelstrom/macro.hpp>
#include <maelstrom/option.hpp>

TEST_CASE("Construct an option", "[option]") {
  STATIC_REQUIRE(
      MAELSTROM_TYPE_EQUAL(maelstrom::option::option<void>::type, void));
  STATIC_REQUIRE(MAELSTROM_TYPE_EQUAL(
      maelstrom::option::option<maelstrom::null>::type, maelstrom::null));
}

TEST_CASE("Methods", "[option]") {
  STATIC_REQUIRE(
      maelstrom::option::has_value<maelstrom::option::option<void>>::value ==
      true);
  STATIC_REQUIRE(
      maelstrom::option::has_value_v<maelstrom::option::option<void>> == true);

  STATIC_REQUIRE(maelstrom::option::has_value<
                     maelstrom::option::option<maelstrom::null>>::value ==
                 false);
  STATIC_REQUIRE(maelstrom::option::has_value_v<
                     maelstrom::option::option<maelstrom::null>> == false);
}
