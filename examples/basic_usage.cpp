#include "zinc.h"

using namespace yu;

YU_MAIN {
    Args args(argc, argv);
    
    println("=== zinc Basic Demo ===");
    
    if (args.has("--help")) {
        println("Usage: {} [options]", args.program());
        println("Options:");
        println("  --help    Show this help");
        println("  --name    Set name");
        return 0;
    }
    
    println("Program: {}", args.program());
    println("Args count: {}", args.count());
    
    auto name = args.value("--name", "World");
    println("Hello, {}!", name);
    
    Path cwd_path = cwd();
    print_info("Current directory: {}", cwd_path.string());
    
    Path test_file = cwd_path / "zinc_test.txt";
    write_file(test_file, "Hello from zinc!");
    
    if (test_file.exists()) {
        auto content = read_file(test_file);
        print_success("Read: {}", content);
        test_file.remove();
    }
    
    {
        Timer timer("Sleep operation");
        sleep_ms(100);
    }
    
    println("Random: {}", rand_i64(1, 100));
    println("Random float: {:.4f}", rand_f64());
    
    u32 val = 0x12345678;
    u32 net = byteorder::to_network(val);
    println("Host: 0x{:08X}, Network: 0x{:08X}", val, net);
    
    println("=== Demo Complete ===");
    return 0;
}
