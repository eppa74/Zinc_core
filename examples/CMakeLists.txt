add_executable(basic_usage basic_usage.cpp)
target_link_libraries(basic_usage PRIVATE zinc::zinc)

add_executable(file_operations file_operations.cpp)
target_link_libraries(file_operations PRIVATE zinc::zinc)

add_executable(thread_pool_demo thread_pool.cpp)
target_link_libraries(thread_pool_demo PRIVATE zinc::zinc)
