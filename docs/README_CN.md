
```markdown
# zinc

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/compiler_support)

一个现代化的单头文件、跨平台 C++17 基础库。

[English](../README.md)

## 特性

- **单头文件**：只需将 `zinc.h` 放入你的项目
- **跨平台**：Windows、Linux、macOS、Android、iOS
- **零依赖**：仅使用标准库
- **现代 C++17**：折叠表达式、`if constexpr`、结构化绑定
- **简化语法**：无需 `std::` 前缀，直接使用 `println`、`vec`、`str` 等
- **丰富的工具集**：字符串操作、文件 I/O、时间、随机数、线程等

## 快速开始

```cpp
#include "zinc.h"

// 无需命令行参数的简单 main
MAIN {
    println("你好，世界！");

    str cwd = current_dir();
    println("当前目录：", cwd);

    Timer timer;
    // ... 你的代码 ...
    println("耗时：", timer.elapsed_ms(), " 毫秒");

    return 0;
}