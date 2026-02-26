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
- **Simplified Syntax**: No `std::` prefix needed – just use `println`, `vec`, `str`, etc.
- **Rich Utilities**: String manipulation, file I/O, time, random, threading, and more

## Quick Start

```cpp
#include "zinc.h"

// Simple main without arguments
MAIN {
    println("Hello, World!");

    str cwd = current_dir();
    println("Current directory: ", cwd);

    Timer timer;
    // ... your code ...
    println("Elapsed: ", timer.elapsed_ms(), " ms");

    return 0;
}