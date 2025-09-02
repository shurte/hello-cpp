#include <catch2/catch_test_macros.hpp>

#include <hello.hpp>

TEST_CASE("Hello", "[hello]") {
    Hello hello;
    REQUIRE(&hello != nullptr);
}

