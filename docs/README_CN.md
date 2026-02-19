# zinc 中文文档

现代 C++17 单头文件跨平台核心库。

## 特性

- **单头文件**：只需复制 `zinc.h`
- **跨平台**：Windows、Linux、macOS、Android、iOS
- **零依赖**：仅使用标准库
- **现代 C++17**：折叠表达式、编译期 if、结构化绑定

## 快速开始

```cpp
#include "zinc.h"

YU_MAIN {
    println("你好，{}！", "世界");
    return 0;
}
