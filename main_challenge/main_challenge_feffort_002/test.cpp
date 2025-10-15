#include <hello.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE() {
    Hello hello;
    REQUIRE(&hello != nullptr);
}