#include <doctest/doctest.h>
#include "zinc.h"

TEST_CASE("string split") {
    auto parts = split("a,b,c", ',');
    CHECK(parts.size() == 3);
    CHECK(parts[0] == "a");
    CHECK(parts[1] == "b");
    CHECK(parts[2] == "c");
}

TEST_CASE("string trim") {
    CHECK(trim("  hello  ") == "hello");
    CHECK(trim_left("  hello") == "hello");
    CHECK(trim_right("hello  ") == "hello");
}

TEST_CASE("string case conversion") {
    CHECK(to_upper("hello") == "HELLO");
    CHECK(to_lower("WORLD") == "world");
}

TEST_CASE("string format") {
    auto s = format("Hello, {}!", "World");
    CHECK(s == "Hello, World!");
}
