#include <doctest/doctest.h>
#include "zinc.h"

TEST_CASE("thread pool basic") {
    ThreadPool pool(2);
    
    auto future1 = pool.enqueue([]() { return 42; });
    auto future2 = pool.enqueue([](int x) { return x * 2; }, 21);
    
    CHECK(future1.get() == 42);
    CHECK(future2.get() == 42);
}

TEST_CASE("random generation") {
    auto r1 = rand_i64(1, 100);
    CHECK(r1 >= 1);
    CHECK(r1 <= 100);
    
    auto r2 = rand_f64(0.0, 1.0);
    CHECK(r2 >= 0.0);
    CHECK(r2 <= 1.0);
}

TEST_CASE("timer") {
    Timer timer("");
    sleep_ms(50);
    auto elapsed = timer.elapsed_ms();
    CHECK(elapsed >= 50.0);
}
