#include "zinc.h"


YU_MAIN {
    println("=== zinc Thread Pool Demo ===");
    
    ThreadPool pool(4);
    println("Created pool with 4 threads");
    
    Vec<Future<i32>> futures;
    
    for (int i = 0; i < 10; ++i) {
        futures.push_back(pool.enqueue([i]() {
            sleep_ms(10);
            return i * i;
        }));
    }
    
    for (size_t i = 0; i < futures.size(); ++i) {
        println("Task {} result: {}", i, futures[i].get());
    }
    
    print_success("All tasks completed");
    return 0;
}
