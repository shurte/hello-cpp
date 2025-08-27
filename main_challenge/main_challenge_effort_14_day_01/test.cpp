#include <catch2/catch_test_macros.hpp>

#include <test.hpp>

TEST_CASE("Factorial are computed", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
}