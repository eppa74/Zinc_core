include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(zinc_tests
    test_main.cpp
    test_types.cpp
    test_path.cpp
    test_string.cpp
    test_thread.cpp
)

target_link_libraries(zinc_tests PRIVATE zinc::zinc doctest::doctest)

include(doctest)
doctest_discover_tests(zinc_tests)
