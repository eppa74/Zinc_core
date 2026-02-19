#include "zinc.h"

YU_MAIN {
    println("=== zinc File Operations Demo ===");
    
    Path temp = temp_dir() / "zinc_demo";
    temp.mkdir();
    println("Created: {}", temp.string());
    
    Path file = temp / "data.txt";
    write_file(file, "Line 1\nLine 2\nLine 3");
    println("Wrote: {}", file.string());
    
    auto lines = read_lines(file);
    println("Lines count: {}", lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        println("  [{}]: {}", i, lines[i]);
    }
    
    Path copy = temp / "data_copy.txt";
    file.copy_to(copy);
    println("Copied to: {}", copy.string());
    
    auto entries = temp.list();
    println("Directory contents:");
    for (const auto& entry : entries) {
        println("  {}", entry.filename().string());
    }
    
    temp.remove_all();
    print_success("Cleaned up");
    
    return 0;
}
