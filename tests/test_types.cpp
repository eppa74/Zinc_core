#include <doctest/doctest.h>
#include "zinc.h"


TEST_CASE("Type aliases") {
    i32 a = 42;
    u64 b = 100;
    f64 c = 3.14;
    str d = "hello";
    
    CHECK(sizeof(a) == 4);
    CHECK(sizeof(b) == 8);
    CHECK(c > 3.0);
    CHECK(d == "hello");
}

TEST_CASE("Container aliases") {
    Vec<i32> vec = {1, 2, 3};
    Map<str, i32> map = {{"a", 1}, {"b", 2}};
    
    CHECK(vec.size() == 3);
    CHECK(map["a"] == 1);
}

TEST_CASE("Smart pointer helpers") {
    auto ptr = mkup<int>(42);
    CHECK(*ptr == 42);
    
    auto shared = mksp<int>(100);
    CHECK(*shared == 100);
}
