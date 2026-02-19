#include <doctest/doctest.h>
#include "zinc.h"

TEST_CASE("path construction") {
    Path p1("/home/user/file.txt");
    CHECK(p1.string() == "/home/user/file.txt");
    
    auto p2 = Path::join("folder", "subfolder");
    CHECK(p2.string().find("folder") != str::npos);
}

TEST_CASE("path operations") {
    Path temp = temp_dir();
    CHECK(temp.exists());
    
    Path test_dir = temp / ("zinc_test_" + std::to_string(timestamp_ms()));
    CHECK(test_dir.mkdir());
    CHECK(test_dir.exists());
    CHECK(test_dir.is_dir());
    
    CHECK(test_dir.remove_all());
}
