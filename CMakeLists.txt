cmake_minimum_required(VERSION 3.14)
project(yu_core VERSION 1.0.0 LANGUAGES CXX)

# 选项
option(YU_CORE_BUILD_TESTS "Build tests" OFF)
option(YU_CORE_BUILD_EXAMPLES "Build examples" OFF)

# 创建接口库（仅头文件）
add_library(yu_core INTERFACE)
add_library(yu_core::yu_core ALIAS yu_core)

target_include_directories(yu_core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(yu_core INTERFACE cxx_std_17)

# 测试
if(YU_CORE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# 示例
if(YU_CORE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# 安装规则
include(GNUInstallDirs)
install(FILES include/yu_core.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS yu_core
    EXPORT yu_core-targets
)

install(EXPORT yu_core-targets
    FILE yu_core-targets.cmake
    NAMESPACE yu_core::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/yu_core
)

# 包配置文件
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/yu_core-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/yu_core-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/yu_core-config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/yu_core-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/yu_core-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/yu_core
)
