#include <catch2/catch_test_macros.hpp>
#include <myoptional.h>

struct DefClass {
    DefClass() = default;

    int mVal{ 123 };
};

struct NonDefClass {
    NonDefClass() = delete;

    NonDefClass(int val)
        : mVal(val)
    {
    }

    int mVal{ 123 };
};

// REQ: must be possible to check if error is present (provide nice impl for if usage)
TEST_CASE("", "[basic]") {}

// REQ: creating from Status must indicate error
TEST_CASE("", "[basic]") {}

// REQ: creating from value must indicate success
TEST_CASE("", "[basic]") {}

// REQ: must have value getter
TEST_CASE("", "[basic]") {}

// REQ: must have error getter
TEST_CASE("", "[basic]") {}

// REQ: value type can be default constructible
TEST_CASE("", "[basic]") {}

// REQ: value type does not need to be default constructible (most important feature)
TEST_CASE("", "[all-inclusive]") {}

// REQ: constructors shall be compile-time disabled when they do not match
TEST_CASE("", "[all-inclusive]") {}

// REQ: require from enum Status to have member OK with value 0
TEST_CASE("", "[all-inclusive]") {}

