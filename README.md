# zinc

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)

A modern, single-header, cross-platform C++17 core library.

[中文文档](docs/README_CN.md)

## Features

- **Single Header**: Just drop `zinc.h` into your project
- **Cross-Platform**: Windows, Linux, macOS, Android, iOS
- **Zero Dependencies**: Only standard library
- **Modern C++17**: Fold expressions, `if constexpr`, structured bindings

## Quick Start

```cpp
#include "zinc.h"

YU_MAIN {
    Args args(argc, argv);
    
    println("Hello, {}!", "World");
    
    Path cwd_path = cwd();
    println("Current: {}", cwd_path.string());
    
    Timer timer("Operation");
    // ... code ...
    
    return 0;
}
