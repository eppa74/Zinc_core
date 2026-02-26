

#ifndef ZINC_H
#define ZINC_H

// ============================================================================
// 版本检测
// ============================================================================
#define ZINC_CPP_VERSION __cplusplus

#if __cplusplus >= 202600L
    #define ZINC_CPP26 1
    #define ZINC_CPP23 1
    #define ZINC_CPP20 1
    #define ZINC_CPP17 1
    #define ZINC_CPP14 1
    #define ZINC_CPP11 1
#elif __cplusplus >= 202302L
    #define ZINC_CPP26 0
    #define ZINC_CPP23 1
    #define ZINC_CPP20 1
    #define ZINC_CPP17 1
    #define ZINC_CPP14 1
    #define ZINC_CPP11 1
#elif __cplusplus >= 202002L
    #define ZINC_CPP26 0
    #define ZINC_CPP23 0
    #define ZINC_CPP20 1
    #define ZINC_CPP17 1
    #define ZINC_CPP14 1
    #define ZINC_CPP11 1
#elif __cplusplus >= 201703L
    #define ZINC_CPP26 0
    #define ZINC_CPP23 0
    #define ZINC_CPP20 0
    #define ZINC_CPP17 1
    #define ZINC_CPP14 1
    #define ZINC_CPP11 1
#elif __cplusplus >= 201402L
    #define ZINC_CPP26 0
    #define ZINC_CPP23 0
    #define ZINC_CPP20 0
    #define ZINC_CPP17 0
    #define ZINC_CPP14 1
    #define ZINC_CPP11 1
#elif __cplusplus >= 201103L
    #define ZINC_CPP26 0
    #define ZINC_CPP23 0
    #define ZINC_CPP20 0
    #define ZINC_CPP17 0
    #define ZINC_CPP14 0
    #define ZINC_CPP11 1
#else
    #error "Zinc requires C++11 or higher"
#endif

// ============================================================================
// 平台检测
// ============================================================================
#ifdef _WIN32
    #define ZINC_PLATFORM_WINDOWS
    #ifdef _WIN64
        #define ZINC_PLATFORM_WIN64
    #else
        #define ZINC_PLATFORM_WIN32
    #endif
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE && TARGET_OS_SIMULATOR
        #define ZINC_PLATFORM_IOS_SIMULATOR
    #elif TARGET_OS_IPHONE
        #define ZINC_PLATFORM_IOS
    #elif TARGET_OS_MAC
        #define ZINC_PLATFORM_MACOS
    #endif
#elif defined(__linux__)
    #define ZINC_PLATFORM_LINUX
    #if defined(__ANDROID__)
        #define ZINC_PLATFORM_ANDROID
    #endif
#elif defined(__unix__)
    #define ZINC_PLATFORM_UNIX
#endif

// ============================================================================
// 标准库头文件（基础部分，始终包含）
// ============================================================================
#include <cfloat>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <typeinfo>
#include <exception>
#include <initializer_list>
#include <cassert>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <utility>
#include <tuple>
#include <bitset>
#include <functional>
#include <memory>
#include <type_traits>
#include <ratio>
#include <chrono>
#include <ctime>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>
#include <cctype>
#include <cwctype>
#include <cuchar>
#include <regex>
#include <locale>
#include <clocale>
#include <cmath>
#include <complex>
#include <random>
#include <valarray>
#include <iostream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <filesystem>

// ============================================================================
// C++17 可选头文件（条件包含）
// ============================================================================
#if ZINC_CPP17
    #if __has_include(<optional>)
        #include <optional>
    #endif
    #if __has_include(<variant>)
        #include <variant>
    #endif
    #if __has_include(<any>)
        #include <any>
    #endif
    #if __has_include(<string_view>)
        #include <string_view>
    #endif
    #if __has_include(<memory_resource>)
        #include <memory_resource>
    #endif
    #if __has_include(<shared_mutex>)
        #include <shared_mutex>
    #endif
    #if __has_include(<execution>)
        #include <execution>
    #endif
    #if __has_include(<scoped_allocator>)
        #include <scoped_allocator>
    #endif
#endif

// ============================================================================
// C++20 可选头文件（条件包含）
// ============================================================================
#if ZINC_CPP20
    #if __has_include(<concepts>)
        #include <concepts>
    #endif
    #if __has_include(<ranges>)
        #include <ranges>
    #endif
    #if __has_include(<span>)
        #include <span>
    #endif
    #if __has_include(<bit>)
        #include <bit>
    #endif
    #if __has_include(<numbers>)
        #include <numbers>
    #endif
    #if __has_include(<source_location>)
        #include <source_location>
    #endif
    #if __has_include(<syncstream>)
        #include <syncstream>
    #endif
    #if __has_include(<version>)
        #include <version>
    #endif
    #if __has_include(<compare>)
        #include <compare>
    #endif
    #if __has_include(<format>)
        #include <format>
    #endif
    #if __has_include(<coroutine>)
        #include <coroutine>
    #endif
#endif

// ============================================================================
// C++23 可选头文件（条件包含）
// ============================================================================
#if ZINC_CPP23
    #if __has_include(<stdfloat>)
        #include <stdfloat>
    #endif
    #if __has_include(<stacktrace>)
        #include <stacktrace>
    #endif
    #if __has_include(<expected>)
        #include <expected>
    #endif
    #if __has_include(<mdspan>)
        #include <mdspan>
    #endif
    #if __has_include(<flat_set>)
        #include <flat_set>
    #endif
    #if __has_include(<flat_map>)
        #include <flat_map>
    #endif
    #if __has_include(<generator>)
        #include <generator>
    #endif
    #if __has_include(<print>)
        #include <print>
    #endif
    #if __has_include(<spanstream>)
        #include <spanstream>
    #endif
    #if __has_include(<text_encoding>)
        #include <text_encoding>
    #endif
    #include <stdatomic.h>
#endif

// ============================================================================
// C++26 可选头文件（条件包含）
// ============================================================================
#if ZINC_CPP26
    #if __has_include(<contracts>)
        #include <contracts>
    #endif
    #if __has_include(<debugging>)
        #include <debugging>
    #endif
    #if __has_include(<inplace_vector>)
        #include <inplace_vector>
    #endif
    #if __has_include(<hive>)
        #include <hive>
    #endif
    #if __has_include(<hazard_pointer>)
        #include <hazard_pointer>
    #endif
    #if __has_include(<rcu>)
        #include <rcu>
    #endif
#endif

// ============================================================================
// 平台特定头文件
// ============================================================================
#ifdef ZINC_PLATFORM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    #include <direct.h>
    #include <io.h>
    #include <intrin.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <dlfcn.h>
#endif
#ifdef ZINC_PLATFORM_MACOS
    #include <mach-o/dyld.h>
#endif

// ============================================================================
// C 兼容头文件（始终包含）
// ============================================================================
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++23 重新启用的 C 头文件（如果支持）
#if __has_include(<assert.h>)
    #include <assert.h>
#endif
#if __has_include(<ctype.h>)
    #include <ctype.h>
#endif
#if __has_include(<errno.h>)
    #include <errno.h>
#endif
#if __has_include(<fenv.h>)
    #include <fenv.h>
#endif
#if __has_include(<float.h>)
    #include <float.h>
#endif
#if __has_include(<inttypes.h>)
    #include <inttypes.h>
#endif
#if __has_include(<limits.h>)
    #include <limits.h>
#endif
#if __has_include(<locale.h>)
    #include <locale.h>
#endif
#if __has_include(<math.h>)
    #include <math.h>
#endif
#if __has_include(<setjmp.h>)
    #include <setjmp.h>
#endif
#if __has_include(<signal.h>)
    #include <signal.h>
#endif
#if __has_include(<stdarg.h>)
    #include <stdarg.h>
#endif
#if __has_include(<stddef.h>)
    #include <stddef.h>
#endif
#if __has_include(<stdint.h>)
    #include <stdint.h>
#endif
#if __has_include(<stdio.h>)
    #include <stdio.h>
#endif
#if __has_include(<stdlib.h>)
    #include <stdlib.h>
#endif
#if __has_include(<string.h>)
    #include <string.h>
#endif
#if __has_include(<time.h>)
    #include <time.h>
#endif
#if __has_include(<uchar.h>)
    #include <uchar.h>
#endif
#if __has_include(<wchar.h>)
    #include <wchar.h>
#endif
#if __has_include(<wctype.h>)
    #include <wctype.h>
#endif

// ============================================================================
// 使用标准命名空间（极致简化）
// ============================================================================
using namespace std;

// ============================================================================
// 基础类型别名
// ============================================================================
using i8    = int8_t;
using i16   = int16_t;
using i32   = int32_t;
using i64   = int64_t;
using u8    = uint8_t;
using u16   = uint16_t;
using u32   = uint32_t;
using u64   = uint64_t;
using f32   = float;
using f64   = double;
using f128  = long double;
using byte  = uint8_t;
using cstr  = const char*;
using str   = string;
using wstr  = wstring;

// UTF 字符串别名（仅在支持时定义）
#ifdef __cpp_lib_char8_t  // C++20 特性，表示支持 char8_t 和 u8string
    using str8  = u8string;
#endif
// u16string 和 u32string 自 C++11 起一直存在
using str16 = u16string;
using str32 = u32string;

// ============================================================================
// 容器别名（全覆盖，但仅在头文件存在时定义）
// ============================================================================
template<typename T> using vec          = vector<T>;
template<typename T> using deq          = deque<T>;
template<typename T> using lst          = list<T>;
template<typename T> using flst         = forward_list<T>;
template<typename T> using set          = set<T>;
template<typename T> using uset         = unordered_set<T>;
template<typename T> using multiset     = multiset<T>;
template<typename T> using umultiset    = unordered_multiset<T>;
template<typename K, typename V> using map          = map<K, V>;
template<typename K, typename V> using umap         = unordered_map<K, V>;
template<typename K, typename V> using multimap     = multimap<K, V>;
template<typename K, typename V> using umultimap    = unordered_multimap<K, V>;
template<typename T> using stack        = stack<T>;
template<typename T> using queue        = queue<T>;
template<typename T> using pqueue       = priority_queue<T>;
template<typename T, size_t N> using arr = array<T, N>;
template<typename... Ts> using tup       = tuple<Ts...>;

#ifdef __cpp_lib_optional
    template<typename T> using opt = optional<T>;
#endif
#ifdef __cpp_lib_variant
    template<typename... Ts> using var = variant<Ts...>;
#endif
#ifdef __cpp_lib_any
    using any_t = any;
#endif
#ifdef __cpp_lib_span
    template<typename T> using span = span<T>;
#endif
#ifdef __cpp_lib_mdspan
    template<typename T, size_t Extent = dynamic_extent> using mdspan = mdspan<T, extents<size_t, Extent>>;
#endif
#ifdef __cpp_lib_expected
    template<typename T, typename E> using expected = expected<T, E>;
#endif

// ============================================================================
// 智能指针别名
// ============================================================================
template<typename T> using uptr = unique_ptr<T>;
template<typename T> using sptr = shared_ptr<T>;
template<typename T> using wptr = weak_ptr<T>;

template<typename T, typename... Args>
inline uptr<T> make_uptr(Args&&... args) {
    return make_unique<T>(forward<Args>(args)...);
}
template<typename T, typename... Args>
inline sptr<T> make_sptr(Args&&... args) {
    return make_shared<T>(forward<Args>(args)...);
}

// ============================================================================
// 迭代器别名
// ============================================================================
template<typename C> using iter       = typename C::iterator;
template<typename C> using citer      = typename C::const_iterator;
template<typename C> using riter      = typename C::reverse_iterator;
template<typename C> using criter     = typename C::const_reverse_iterator;

// ============================================================================
// 简化输出函数（print/println 系列）
// ============================================================================
template<typename T>
void print(const T& t) { cout << t; }
void print() {}

template<typename T, typename... Args>
void print(const T& t, const Args&... args) {
    cout << t;
    print(args...);
}
template<typename... Args>
void println(const Args&... args) {
    print(args...);
    cout << '\n';
}
template<typename... Args>
void print_err(const Args&... args) {
    print(args...);
    cerr << '\n';
}
template<typename... Args>
void println_err(const Args&... args) {
    print(args...);
    cerr << '\n';
}

// 容器打印（覆盖所有常见容器，使用 std:: 前缀避免歧义）
template<typename T>
void print(const vec<T>& v) {
    cout << '[';
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ", ";
        print(v[i]);
    }
    cout << ']';
}
template<typename T>
void print(const deq<T>& v) {
    cout << '[';
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ", ";
        print(v[i]);
    }
    cout << ']';
}
template<typename T>
void print(const lst<T>& v) {
    cout << '[';
    bool first = true;
    for (const auto& e : v) {
        if (!first) cout << ", ";
        print(e);
        first = false;
    }
    cout << ']';
}
template<typename K, typename V>
void print(const std::map<K,V>& m) {
    cout << '{';
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) cout << ", ";
        print(k); cout << ": "; print(v);
        first = false;
    }
    cout << '}';
}
template<typename K, typename V>
void print(const std::unordered_map<K,V>& m) {
    cout << '{';
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) cout << ", ";
        print(k); cout << ": "; print(v);
        first = false;
    }
    cout << '}';
}
template<typename T>
void print(const std::set<T>& s) {
    cout << '{';
    bool first = true;
    for (const auto& e : s) {
        if (!first) cout << ", ";
        print(e);
        first = false;
    }
    cout << '}';
}
template<typename T>
void print(const std::unordered_set<T>& s) {
    cout << '{';
    bool first = true;
    for (const auto& e : s) {
        if (!first) cout << ", ";
        print(e);
        first = false;
    }
    cout << '}';
}
template<typename T>
void print(const std::multiset<T>& s) {
    cout << '{';
    bool first = true;
    for (const auto& e : s) {
        if (!first) cout << ", ";
        print(e);
        first = false;
    }
    cout << '}';
}
template<typename T>
void print(const std::unordered_multiset<T>& s) {
    cout << '{';
    bool first = true;
    for (const auto& e : s) {
        if (!first) cout << ", ";
        print(e);
        first = false;
    }
    cout << '}';
}
template<typename K, typename V>
void print(const std::multimap<K,V>& m) {
    cout << '{';
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) cout << ", ";
        print(k); cout << ": "; print(v);
        first = false;
    }
    cout << '}';
}
template<typename K, typename V>
void print(const std::unordered_multimap<K,V>& m) {
    cout << '{';
    bool first = true;
    for (const auto& [k, v] : m) {
        if (!first) cout << ", ";
        print(k); cout << ": "; print(v);
        first = false;
    }
    cout << '}';
}
template<typename T, size_t N>
void print(const arr<T, N>& a) {
    cout << '[';
    for (size_t i = 0; i < N; ++i) {
        if (i) cout << ", ";
        print(a[i]);
    }
    cout << ']';
}
template<typename... Ts>
void print(const tup<Ts...>& t) {
    cout << '(';
    apply([&](const auto&... args) {
        size_t n = 0;
        ((cout << (n++ ? ", " : ""), print(args)), ...);
    }, t);
    cout << ')';
}
#ifdef __cpp_lib_optional
template<typename T>
void print(const opt<T>& o) {
    if (o.has_value()) { cout << "opt("; print(*o); cout << ')'; }
    else cout << "nullopt";
}
#endif
#ifdef __cpp_lib_variant
template<typename... Ts>
void print(const var<Ts...>& v) {
    visit([](const auto& val) {
        cout << "var(";
        print(val);
        cout << ')';
    }, v);
}
#endif
#ifdef __cpp_lib_any
void print(const any_t& a) {
    if (a.has_value()) cout << "any(...)";
    else cout << "nullany";
}
#endif
#ifdef __cpp_lib_span
template<typename T>
void print(const span<T>& s) {
    cout << '[';
    for (size_t i = 0; i < s.size(); ++i) {
        if (i) cout << ", ";
        print(s[i]);
    }
    cout << ']';
}
#endif
#ifdef __cpp_lib_expected
template<typename T, typename E>
void print(const expected<T, E>& e) {
    if (e.has_value()) { cout << "expected("; print(*e); cout << ')'; }
    else { cout << "unexpected("; print(e.error()); cout << ')'; }
}
#endif

// ============================================================================
// 字符串工具（最完整）
// ============================================================================
vec<str> split(const str& s, char delim = ' ') {
    vec<str> tokens;
    stringstream ss(s);
    str token;
    while (getline(ss, token, delim))
        if (!token.empty()) tokens.push_back(token);
    return tokens;
}
vec<str> split(const str& s, const str& delim) {
    vec<str> tokens;
    size_t start = 0, end;
    while ((end = s.find(delim, start)) != str::npos) {
        if (end > start) tokens.push_back(s.substr(start, end - start));
        start = end + delim.length();
    }
    if (start < s.length()) tokens.push_back(s.substr(start));
    return tokens;
}
vec<wstr> split(const wstr& s, wchar_t delim = L' ') {
    vec<wstr> tokens;
    wstringstream ss(s);
    wstr token;
    while (getline(ss, token, delim))
        if (!token.empty()) tokens.push_back(token);
    return tokens;
}
str join(const vec<str>& parts, const str& delim = " ") {
    str res;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i) res += delim;
        res += parts[i];
    }
    return res;
}
wstr join(const vec<wstr>& parts, const wstr& delim = L" ") {
    wstr res;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i) res += delim;
        res += parts[i];
    }
    return res;
}
str trim_left(const str& s) {
    auto it = find_if_not(s.begin(), s.end(), [](unsigned char ch) { return isspace(ch); });
    return str(it, s.end());
}
str trim_right(const str& s) {
    auto it = find_if_not(s.rbegin(), s.rend(), [](unsigned char ch) { return isspace(ch); });
    return str(s.begin(), it.base());
}
str trim(const str& s) {
    return trim_left(trim_right(s));
}
str to_lower(str s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}
str to_upper(str s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return toupper(c); });
    return s;
}
wstr to_lower(wstr s) {
    transform(s.begin(), s.end(), s.begin(), [](wchar_t c) { return towlower(c); });
    return s;
}
wstr to_upper(wstr s) {
    transform(s.begin(), s.end(), s.begin(), [](wchar_t c) { return towupper(c); });
    return s;
}
bool starts_with(const str& s, const str& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}
bool ends_with(const str& s, const str& suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}
bool starts_with(const wstr& s, const wstr& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}
bool ends_with(const wstr& s, const wstr& suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}
str replace_all(str s, const str& from, const str& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != str::npos) {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
    return s;
}
wstr replace_all(wstr s, const wstr& from, const wstr& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != wstr::npos) {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
    return s;
}
bool contains(const str& s, const str& sub) {
    return s.find(sub) != str::npos;
}
bool contains(const str& s, char c) {
    return s.find(c) != str::npos;
}
size_t count(const str& s, char c) {
    return count_if(s.begin(), s.end(), [c](char ch) { return ch == c; });
}
size_t count(const str& s, const str& sub) {
    size_t cnt = 0, pos = 0;
    while ((pos = s.find(sub, pos)) != str::npos) {
        ++cnt;
        pos += sub.length();
    }
    return cnt;
}
str repeat(const str& s, size_t n) {
    str res;
    res.reserve(s.size() * n);
    for (size_t i = 0; i < n; ++i) res += s;
    return res;
}
str reverse(str s) {
    reverse(s.begin(), s.end());
    return s;
}
vec<str> split_lines(const str& s) {
    return split(s, '\n');
}
str to_hex(const vec<u8>& data, bool upper = false) {
    static const char* digits_lower = "0123456789abcdef";
    static const char* digits_upper = "0123456789ABCDEF";
    const char* digits = upper ? digits_upper : digits_lower;
    str res;
    res.reserve(data.size() * 2);
    for (u8 b : data) {
        res += digits[b >> 4];
        res += digits[b & 0x0F];
    }
    return res;
}
vec<u8> from_hex(const str& hex) {
    vec<u8> res;
    str h = trim(hex);
    if (h.size() % 2 != 0) return res;
    res.reserve(h.size() / 2);
    for (size_t i = 0; i < h.size(); i += 2) {
        char c1 = h[i], c2 = h[i+1];
        auto hex_val = [](char c) -> u8 {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            return 0;
        };
        res.push_back((hex_val(c1) << 4) | hex_val(c2));
    }
    return res;
}
str to_base64(const vec<u8>& data) {
    static const char* base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    str res;
    int i = 0, j = 0;
    u8 char_array_3[3], char_array_4[4];
    for (u8 byte : data) {
        char_array_3[i++] = byte;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; i < 4; i++) res += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 3; j++) char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        for (j = 0; j < i + 1; j++) res += base64_chars[char_array_4[j]];
        while (i++ < 3) res += '=';
    }
    return res;
}
vec<u8> from_base64(const str& b64) {
    static const char* base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    vec<u8> res;
    int in_len = b64.size();
    int i = 0, j = 0, in_ = 0;
    u8 char_array_4[4], char_array_3[3];
    str s = b64;
    while (in_len-- && (s[in_] != '=') && isalnum(s[in_]) || s[in_] == '+' || s[in_] == '/') {
        char_array_4[i++] = s[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = strchr(base64_chars, char_array_4[i]) - base64_chars;
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i = 0; i < 3; i++) res.push_back(char_array_3[i]);
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 4; j++) char_array_4[j] = 0;
        for (j = 0; j < 4; j++)
            char_array_4[j] = strchr(base64_chars, char_array_4[j]) - base64_chars;
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (j = 0; j < i - 1; j++) res.push_back(char_array_3[j]);
    }
    return res;
}

// ============================================================================
// 格式化字符串（简易版）
// ============================================================================
template<typename... Args>
str format(const str& fmt, Args&&... args) {
    stringstream ss;
    size_t pos = 0;
    auto process = [&](const auto& arg) {
        size_t next = fmt.find("{}", pos);
        if (next != str::npos) {
            ss << fmt.substr(pos, next - pos) << arg;
            pos = next + 2;
        }
    };
    (process(args), ...);
    ss << fmt.substr(pos);
    return ss.str();
}

// ============================================================================
// 文件操作（最完整）
// ============================================================================
str read_file(const str& path) {
    ifstream f(path, ios::binary);
    if (!f) return "";
    stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}
vec<u8> read_file_bytes(const str& path) {
    ifstream f(path, ios::binary);
    if (!f) return {};
    f.seekg(0, ios::end);
    size_t size = f.tellg();
    f.seekg(0, ios::beg);
    vec<u8> buf(size);
    f.read(reinterpret_cast<char*>(buf.data()), size);
    return buf;
}
bool write_file(const str& path, const str& content) {
    ofstream f(path, ios::binary);
    if (!f) return false;
    f << content;
    return f.good();
}
bool write_file_bytes(const str& path, const vec<u8>& bytes) {
    ofstream f(path, ios::binary);
    if (!f) return false;
    f.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    return f.good();
}
bool append_file(const str& path, const str& content) {
    ofstream f(path, ios::binary | ios::app);
    if (!f) return false;
    f << content;
    return f.good();
}
vec<str> read_lines(const str& path) {
    vec<str> lines;
    ifstream f(path);
    str line;
    while (getline(f, line))
        lines.push_back(line);
    return lines;
}
bool write_lines(const str& path, const vec<str>& lines) {
    ofstream f(path);
    if (!f) return false;
    for (const auto& line : lines) {
        f << line << '\n';
    }
    return f.good();
}
bool file_exists(const str& path) {
    return filesystem::exists(path);
}
bool is_file(const str& path) {
    return filesystem::is_regular_file(path);
}
bool is_dir(const str& path) {
    return filesystem::is_directory(path);
}
bool mkdir(const str& path) {
    return filesystem::create_directories(path);
}
bool mkdir_single(const str& path) {
    return filesystem::create_directory(path);
}
bool remove_file(const str& path) {
    return filesystem::remove(path);
}
bool remove_all(const str& path) {
    return filesystem::remove_all(path) > 0;
}
u64 file_size(const str& path) {
    return filesystem::file_size(path);
}
str current_dir() {
    return filesystem::current_path().string();
}
bool set_current_dir(const str& path) {
    error_code ec;
    filesystem::current_path(path, ec);
    return !ec;
}
bool copy_file(const str& from, const str& to, bool overwrite = true) {
    auto options = overwrite ? filesystem::copy_options::overwrite_existing : filesystem::copy_options::none;
    error_code ec;
    return filesystem::copy_file(from, to, options, ec);
}
bool copy_dir(const str& from, const str& to, bool recursive = true) {
    auto options = recursive ? filesystem::copy_options::recursive : filesystem::copy_options::none;
    error_code ec;
    filesystem::copy(from, to, options, ec);
    return !ec;
}
bool move_file(const str& from, const str& to) {
    error_code ec;
    filesystem::rename(from, to, ec);
    return !ec;
}
vec<str> list_dir(const str& path) {
    vec<str> res;
    error_code ec;
    for (const auto& entry : filesystem::directory_iterator(path, ec)) {
        res.push_back(entry.path().string());
    }
    return res;
}
vec<str> list_dir_recursive(const str& path) {
    vec<str> res;
    error_code ec;
    for (const auto& entry : filesystem::recursive_directory_iterator(path, ec)) {
        res.push_back(entry.path().string());
    }
    return res;
}
str temp_dir() {
    return filesystem::temp_directory_path().string();
}
str home_dir() {
#ifdef ZINC_PLATFORM_WINDOWS
    const char* home = getenv("USERPROFILE");
    if (home) return home;
    const char* drive = getenv("HOMEDRIVE");
    const char* path = getenv("HOMEPATH");
    if (drive && path) return str(drive) + path;
#else
    const char* home = getenv("HOME");
    if (home) return home;
#endif
    return "";
}
str exe_path() {
#ifdef ZINC_PLATFORM_WINDOWS
    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return buf;
#elif defined(ZINC_PLATFORM_MACOS)
    char buf[1024];
    uint32_t size = sizeof(buf);
    _NSGetExecutablePath(buf, &size);
    return buf;
#elif defined(ZINC_PLATFORM_LINUX)
    char buf[1024];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len != -1) {
        buf[len] = '\0';
        return buf;
    }
#endif
    return "";
}

// ============================================================================
// 时间工具（最完整）
// ============================================================================
using TimePoint = chrono::steady_clock::time_point;
inline TimePoint now() { return chrono::steady_clock::now(); }
inline chrono::system_clock::time_point now_system() { return chrono::system_clock::now(); }

inline i64 timestamp_ms() {
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
}
inline i64 timestamp_us() {
    return chrono::duration_cast<chrono::microseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
}
inline i64 timestamp_ns() {
    return chrono::duration_cast<chrono::nanoseconds>(
        chrono::system_clock::now().time_since_epoch()).count();
}
inline i64 timestamp_s() {
    return chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()).count();
}

inline void sleep_ms(i64 ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}
inline void sleep_us(i64 us) {
    this_thread::sleep_for(chrono::microseconds(us));
}
inline void sleep_s(i64 s) {
    this_thread::sleep_for(chrono::seconds(s));
}
inline void sleep_ns(i64 ns) {
    this_thread::sleep_for(chrono::nanoseconds(ns));
}

str format_time(const str& fmt = "%Y-%m-%d %H:%M:%S") {
    auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm tm = *localtime(&t);
    char buf[128];
    strftime(buf, sizeof(buf), fmt.c_str(), &tm);
    return buf;
}
str format_time(i64 ts_ms, const str& fmt = "%Y-%m-%d %H:%M:%S") {
    time_t t = ts_ms / 1000;
    tm tm = *localtime(&t);
    char buf[128];
    strftime(buf, sizeof(buf), fmt.c_str(), &tm);
    return buf;
}
str format_time_utc(const str& fmt = "%Y-%m-%d %H:%M:%S") {
    auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm tm = *gmtime(&t);
    char buf[128];
    strftime(buf, sizeof(buf), fmt.c_str(), &tm);
    return buf;
}

class Timer {
    TimePoint start_;
public:
    Timer() { reset(); }
    void reset() { start_ = now(); }
    f64 elapsed_ms() const {
        return chrono::duration<f64, milli>(now() - start_).count();
    }
    f64 elapsed_s() const {
        return chrono::duration<f64>(now() - start_).count();
    }
    i64 elapsed_us() const {
        return chrono::duration_cast<chrono::microseconds>(now() - start_).count();
    }
    i64 elapsed_ns() const {
        return chrono::duration_cast<chrono::nanoseconds>(now() - start_).count();
    }
    bool elapsed_ms(i64 ms, bool reset_if_true = false) {
        if (elapsed_ms() >= ms) {
            if (reset_if_true) reset();
            return true;
        }
        return false;
    }
};

struct DateTime {
    i32 year, month, day, hour, minute, second, millisecond;
    DateTime() { *this = now(); }
    DateTime(i32 y, i32 mo, i32 d, i32 h = 0, i32 mi = 0, i32 s = 0, i32 ms = 0)
        : year(y), month(mo), day(d), hour(h), minute(mi), second(s), millisecond(ms) {}
    static DateTime now() {
        auto tp = chrono::system_clock::now();
        auto tt = chrono::system_clock::to_time_t(tp);
        tm tm = *localtime(&tt);
        auto ms = chrono::duration_cast<chrono::milliseconds>(tp.time_since_epoch()) % 1000;
        return DateTime(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                        tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count());
    }
    str to_string(const str& fmt = "%Y-%m-%d %H:%M:%S") const {
        tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        mktime(&tm); // 确保字段归一化
        char buf[128];
        strftime(buf, sizeof(buf), fmt.c_str(), &tm);
        return buf;
    }
    i64 timestamp_ms() const {
        tm tm = {};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        time_t tt = mktime(&tm);
        return tt * 1000LL + millisecond;
    }
};

// ============================================================================
// 随机数工具（最完整）
// ============================================================================
class Random {
    mt19937_64 rng_;
public:
    Random() {
        random_device rd;
        if (rd.entropy() > 0) rng_.seed(rd());
        else rng_.seed(timestamp_ns());
    }
    explicit Random(u64 seed) : rng_(seed) {}

    i64 next(i64 min, i64 max) {
        return uniform_int_distribution<i64>(min, max)(rng_);
    }
    i64 next(i64 max) { return next(0, max); }
    i32 next_i32(i32 min, i32 max) {
        return uniform_int_distribution<i32>(min, max)(rng_);
    }
    u64 next_u64(u64 min = 0, u64 max = UINT64_MAX) {
        return uniform_int_distribution<u64>(min, max)(rng_);
    }
    u32 next_u32(u32 min = 0, u32 max = UINT32_MAX) {
        return uniform_int_distribution<u32>(min, max)(rng_);
    }
    f32 next_f32(f32 min = 0.0f, f32 max = 1.0f) {
        return uniform_real_distribution<f32>(min, max)(rng_);
    }
    f64 next_f64(f64 min = 0.0, f64 max = 1.0) {
        return uniform_real_distribution<f64>(min, max)(rng_);
    }
    bool next_bool() {
        return bernoulli_distribution(0.5)(rng_);
    }
    bool next_bool(f64 probability) {
        return bernoulli_distribution(probability)(rng_);
    }
    f64 next_normal(f64 mean = 0.0, f64 stddev = 1.0) {
        return normal_distribution<f64>(mean, stddev)(rng_);
    }
    f32 next_normal_f32(f32 mean = 0.0f, f32 stddev = 1.0f) {
        return normal_distribution<f32>(mean, stddev)(rng_);
    }
    i64 next_poisson(f64 mean) {
        return poisson_distribution<i64>(mean)(rng_);
    }
    i64 next_geometric(f64 p) {
        return geometric_distribution<i64>(p)(rng_);
    }
    f64 next_exponential(f64 lambda) {
        return exponential_distribution<f64>(lambda)(rng_);
    }
    template<typename C>
    void shuffle(C& c) {
        std::shuffle(c.begin(), c.end(), rng_);
    }
    template<typename C>
    auto& choice(C& c) {
        return c[next(c.size() - 1)];
    }
    template<typename C>
    const auto& choice(const C& c) {
        return c[next(c.size() - 1)];
    }
    template<typename C>
    vec<typename C::value_type> sample(const C& c, size_t n) {
        vec<typename C::value_type> res;
        sample(c.begin(), c.end(), back_inserter(res), n, rng_);
        return res;
    }
    vec<u8> bytes(size_t n) {
        vec<u8> res(n);
        for (size_t i = 0; i < n; ++i) res[i] = next(0, 255);
        return res;
    }
    str string(size_t len, const str& charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") {
        str res;
        res.reserve(len);
        for (size_t i = 0; i < len; ++i) {
            res += charset[next(charset.size() - 1)];
        }
        return res;
    }
};

inline Random& global_rng() {
    static Random rng;
    return rng;
}
inline i64 rand_i64(i64 min, i64 max) { return global_rng().next(min, max); }
inline i32 rand_i32(i32 min, i32 max) { return global_rng().next_i32(min, max); }
inline u64 rand_u64(u64 min = 0, u64 max = UINT64_MAX) { return global_rng().next_u64(min, max); }
inline f64 rand_f64(f64 min = 0.0, f64 max = 1.0) { return global_rng().next_f64(min, max); }
inline f32 rand_f32(f32 min = 0.0f, f32 max = 1.0f) { return global_rng().next_f32(min, max); }
inline bool rand_bool() { return global_rng().next_bool(); }
inline bool rand_bool(f64 p) { return global_rng().next_bool(p); }
inline str rand_str(size_t len, const str& charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") {
    return global_rng().string(len, charset);
}

// ============================================================================
// 线程工具（最完整）
// ============================================================================
using Thread = thread;
using Mutex = mutex;
using RMutex = recursive_mutex;
using TimedMutex = timed_mutex;
using LockGuard = lock_guard<mutex>;
using UniqueLock = unique_lock<mutex>;
using CondVar = condition_variable;
#ifdef __cpp_lib_jthread
    using JThread = jthread;
#endif
#ifdef __cpp_lib_shared_mutex
    using SharedMutex = shared_mutex;
    using SharedLock = shared_lock<shared_mutex>;
#endif
#ifdef __cpp_lib_semaphore
    using Semaphore = counting_semaphore<>;
    using BinarySemaphore = binary_semaphore;
#endif
#ifdef __cpp_lib_latch
    using Latch = latch;
#endif
#ifdef __cpp_lib_barrier
    using Barrier = barrier<>;
#endif
#ifdef __cpp_lib_stop_token
    using StopSource = stop_source;
    using StopToken = stop_token;
    using StopCallback = stop_callback<function<void()>>;
#endif

template<typename T>
using Future = future<T>;
template<typename T>
using SharedFuture = shared_future<T>;
template<typename T>
using Promise = promise<T>;

template<typename F, typename... Args>
auto async(F&& f, Args&&... args) {
    return std::async(launch::async, forward<F>(f), forward<Args>(args)...);
}
template<typename F, typename... Args>
auto async_deferred(F&& f, Args&&... args) {
    return std::async(launch::deferred, forward<F>(f), forward<Args>(args)...);
}

// 线程安全队列
template<typename T>
class ThreadQueue {
    std::queue<T> q_;
    mutable Mutex mtx_;
    CondVar cv_;
public:
    void push(T value) {
        LockGuard lock(mtx_);
        q_.push(std::move(value));
        cv_.notify_one();
    }
    bool try_pop(T& value) {
        LockGuard lock(mtx_);
        if (q_.empty()) return false;
        value = std::move(q_.front());
        q_.pop();
        return true;
    }
    void wait_pop(T& value) {
        UniqueLock lock(mtx_);
        cv_.wait(lock, [this] { return !q_.empty(); });
        value = std::move(q_.front());
        q_.pop();
    }
    bool empty() const {
        LockGuard lock(mtx_);
        return q_.empty();
    }
    size_t size() const {
        LockGuard lock(mtx_);
        return q_.size();
    }
};

// 线程池
class ThreadPool {
    vec<Thread> workers_;
    ThreadQueue<function<void()>> tasks_;
    atomic<bool> stop_{false};
public:
    explicit ThreadPool(size_t threads = 0) {
        if (threads == 0) threads = thread::hardware_concurrency();
        for (size_t i = 0; i < threads; ++i) {
            workers_.emplace_back([this] {
                while (!stop_) {
                    function<void()> task;
                    if (tasks_.try_pop(task)) {
                        task();
                    } else {
                        this_thread::sleep_for(chrono::milliseconds(1));
                    }
                }
            });
        }
    }
    ~ThreadPool() {
        stop_ = true;
        for (auto& w : workers_) if (w.joinable()) w.join();
    }
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> Future<invoke_result_t<F, Args...>> {
        using return_type = invoke_result_t<F, Args...>;
        auto task = make_shared<packaged_task<return_type()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        Future<return_type> res = task->get_future();
        tasks_.push([task]() { (*task)(); });
        return res;
    }
    void enqueue_detach(function<void()> task) {
        tasks_.push(std::move(task));
    }
    size_t task_count() const { return tasks_.size(); }
};

// ============================================================================
// 数学常量与函数
// ============================================================================
namespace math {
    constexpr f64 PI      = 3.14159265358979323846;
    constexpr f64 PI_2    = PI * 2.0;
    constexpr f64 PI_HALF = PI / 2.0;
    constexpr f64 E       = 2.71828182845904523536;
    constexpr f64 SQRT2   = 1.41421356237309504880;
    constexpr f64 SQRT1_2 = 0.70710678118654752440;
    constexpr f64 PHI     = 1.61803398874989484820;
    constexpr f64 EPSILON = 1e-9;
}
using namespace math;

template<typename T>
T to_rad(T deg) { return deg * T(PI) / T(180); }
template<typename T>
T to_deg(T rad) { return rad * T(180) / T(PI); }

template<typename T>
T clamp(T v, T lo, T hi) {
    return max(lo, min(v, hi));
}
template<typename T>
T lerp(T a, T b, f64 t) {
    return a + (b - a) * t;
}
template<typename T>
T smoothstep(T edge0, T edge1, T x) {
    T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return t * t * (T(3) - T(2) * t);
}
template<typename T>
T smootherstep(T edge0, T edge1, T x) {
    T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return t * t * t * (t * (t * T(6) - T(15)) + T(10));
}
template<typename T>
bool approx_eq(T a, T b, T epsilon = T(EPSILON)) {
    return abs(a - b) <= epsilon * max({T(1), abs(a), abs(b)});
}
template<typename T>
T map_range(T x, T in_min, T in_max, T out_min, T out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
template<typename T>
T wrap_angle(T angle) {
    T res = fmod(angle, T(360));
    if (res < 0) res += T(360);
    return res;
}
template<typename T>
T wrap_angle_rad(T angle) {
    T res = fmod(angle, T(PI_2));
    if (res < 0) res += T(PI_2);
    return res;
}
template<typename T>
T fract(T x) {
    return x - floor(x);
}
template<typename T>
T sign(T x) {
    return (x > T(0)) - (x < T(0));
}
template<typename T>
T step(T edge, T x) {
    return x < edge ? T(0) : T(1);
}
template<typename T>
T pulse(T start, T end, T x) {
    return step(start, x) - step(end, x);
}

// 向量类型
template<typename T> struct vec2 { T x, y; };
template<typename T> struct vec3 { T x, y, z; };
template<typename T> struct vec4 { T x, y, z, w; };
using vec2f = vec2<f32>;
using vec2d = vec2<f64>;
using vec2i = vec2<i32>;
using vec3f = vec3<f32>;
using vec3d = vec3<f64>;
using vec3i = vec3<i32>;
using vec4f = vec4<f32>;
using vec4d = vec4<f64>;
using vec4i = vec4<i32>;

// 简单向量运算（可扩展）
template<typename T> vec2<T> operator+(const vec2<T>& a, const vec2<T>& b) { return {a.x+b.x, a.y+b.y}; }
template<typename T> vec2<T> operator-(const vec2<T>& a, const vec2<T>& b) { return {a.x-b.x, a.y-b.y}; }
template<typename T> vec2<T> operator*(const vec2<T>& a, T s) { return {a.x*s, a.y*s}; }
template<typename T> T dot(const vec2<T>& a, const vec2<T>& b) { return a.x*b.x + a.y*b.y; }
template<typename T> T length(const vec2<T>& a) { return sqrt(dot(a,a)); }

// ============================================================================
// 位操作与字节序
// ============================================================================
namespace bitops {
    inline bool is_little_endian() {
        constexpr u16 test = 0x0102;
        return reinterpret_cast<const u8*>(&test)[0] == 0x02;
    }
    inline bool is_big_endian() { return !is_little_endian(); }

    inline u16 swap16(u16 v) { return (v >> 8) | (v << 8); }
    inline u32 swap32(u32 v) {
        return ((v >> 24) & 0xFF) | ((v >> 8) & 0xFF00) |
               ((v << 8) & 0xFF0000) | ((v << 24) & 0xFF000000);
    }
    inline u64 swap64(u64 v) {
        return ((v >> 56) & 0xFFULL) | ((v >> 40) & 0xFF00ULL) |
               ((v >> 24) & 0xFF0000ULL) | ((v >> 8) & 0xFF000000ULL) |
               ((v << 8) & 0xFF00000000ULL) | ((v << 24) & 0xFF0000000000ULL) |
               ((v << 40) & 0xFF000000000000ULL) | ((v << 56) & 0xFF00000000000000ULL);
    }

    inline u16 to_be16(u16 v) { return is_little_endian() ? swap16(v) : v; }
    inline u32 to_be32(u32 v) { return is_little_endian() ? swap32(v) : v; }
    inline u64 to_be64(u64 v) { return is_little_endian() ? swap64(v) : v; }
    inline u16 to_le16(u16 v) { return is_big_endian() ? swap16(v) : v; }
    inline u32 to_le32(u32 v) { return is_big_endian() ? swap32(v) : v; }
    inline u64 to_le64(u64 v) { return is_big_endian() ? swap64(v) : v; }

    inline u16 htons(u16 v) { return to_be16(v); }
    inline u32 htonl(u32 v) { return to_be32(v); }
    inline u64 htonll(u64 v) { return to_be64(v); }
    inline u16 ntohs(u16 v) { return to_be16(v); }
    inline u32 ntohl(u32 v) { return to_be32(v); }
    inline u64 ntohll(u64 v) { return to_be64(v); }
}
using namespace bitops;

// 内存读写（小端）
inline u8  read_u8 (const u8* p) { return p[0]; }
inline u16 read_u16(const u8* p) { return p[0] | (p[1] << 8); }
inline u32 read_u32(const u8* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24); }
inline u64 read_u64(const u8* p) {
    return (u64)p[0] | ((u64)p[1] << 8) | ((u64)p[2] << 16) | ((u64)p[3] << 24) |
           ((u64)p[4] << 32) | ((u64)p[5] << 40) | ((u64)p[6] << 48) | ((u64)p[7] << 56);
}
inline u16 read_u16_be(const u8* p) { return (p[0] << 8) | p[1]; }
inline u32 read_u32_be(const u8* p) { return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; }

inline void write_u8 (u8* p, u8 v) { p[0] = v; }
inline void write_u16(u8* p, u16 v) { p[0] = v; p[1] = v >> 8; }
inline void write_u32(u8* p, u32 v) { p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24; }
inline void write_u64(u8* p, u64 v) {
    p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24;
    p[4] = v >> 32; p[5] = v >> 40; p[6] = v >> 48; p[7] = v >> 56;
}
inline void write_u16_be(u8* p, u16 v) { p[0] = v >> 8; p[1] = v; }
inline void write_u32_be(u8* p, u32 v) { p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v; }

// ============================================================================
// 调试辅助
// ============================================================================
#ifndef NDEBUG
    #define ASSERT(cond) \
        do { if (!(cond)) { \
            println("ASSERT failed: ", #cond, " at ", __FILE__, ":", __LINE__); \
            abort(); \
        } } while(0)
    #define ASSERT_MSG(cond, msg) \
        do { if (!(cond)) { \
            println("ASSERT failed: ", #cond, " - ", msg, " at ", __FILE__, ":", __LINE__); \
            abort(); \
        } } while(0)
    #define DEBUG_PRINT(...) println(__VA_ARGS__)
    #define DEBUG_PRINT_ERR(...) println_err(__VA_ARGS__)
    #define TODO(msg) println("TODO: ", msg, " at ", __FILE__, ":", __LINE__)
#else
    #define ASSERT(cond) ((void)0)
    #define ASSERT_MSG(cond, msg) ((void)0)
    #define DEBUG_PRINT(...) ((void)0)
    #define DEBUG_PRINT_ERR(...) ((void)0)
    #define TODO(msg) ((void)0)
#endif

template<typename F>
class ScopeGuard {
    F f_;
    bool active_ = true;
public:
    explicit ScopeGuard(F f) : f_(move(f)) {}
    ~ScopeGuard() { if (active_) f_(); }
    void dismiss() { active_ = false; }
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&& other) noexcept : f_(move(other.f_)), active_(other.active_) {
        other.active_ = false;
    }
};
template<typename F>
ScopeGuard<F> defer(F&& f) {
    return ScopeGuard<F>(forward<F>(f));
}
#define DEFER(code) auto _defer_##__LINE__ = defer([&]() { code; })

// ============================================================================
// 环境变量
// ============================================================================
inline str get_env(const str& name) {
#ifdef ZINC_PLATFORM_WINDOWS
    char* val = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&val, &sz, name.c_str()) == 0 && val) {
        str res(val);
        free(val);
        return res;
    }
    return "";
#else
    const char* val = getenv(name.c_str());
    return val ? str(val) : "";
#endif
}
inline bool set_env(const str& name, const str& value) {
#ifdef ZINC_PLATFORM_WINDOWS
    return _putenv_s(name.c_str(), value.c_str()) == 0;
#else
    return setenv(name.c_str(), value.c_str(), 1) == 0;
#endif
}
inline bool unset_env(const str& name) {
#ifdef ZINC_PLATFORM_WINDOWS
    return _putenv_s(name.c_str(), "") == 0;
#else
    return unsetenv(name.c_str()) == 0;
#endif
}

// ============================================================================
// 命令行参数解析
// ============================================================================
class Args {
    vec<str> args_;
    umap<str, str> opts_;
public:
    Args(int argc, char** argv) {
        for (int i = 0; i < argc; ++i) {
            args_.push_back(argv[i]);
        }
        for (size_t i = 1; i < args_.size(); ++i) {
            const str& arg = args_[i];
            if (starts_with(arg, "--")) {
                size_t eq = arg.find('=');
                if (eq != str::npos) {
                    opts_[arg.substr(2, eq - 2)] = arg.substr(eq + 1);
                } else if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                    opts_[arg.substr(2)] = args_[++i];
                } else {
                    opts_[arg.substr(2)] = "true";
                }
            } else if (starts_with(arg, "-") && arg.size() > 1) {
                for (size_t j = 1; j < arg.size(); ++j) {
                    str key(1, arg[j]);
                    if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                        opts_[key] = args_[++i];
                    } else {
                        opts_[key] = "true";
                    }
                }
            }
        }
    }
    str program() const { return args_.empty() ? "" : args_[0]; }
    bool has(const str& opt) const {
        if (starts_with(opt, "--")) return opts_.count(opt.substr(2)) > 0;
        if (starts_with(opt, "-")) return opts_.count(opt.substr(1)) > 0;
        return opts_.count(opt) > 0;
    }
    str value(const str& opt, const str& default_val = "") const {
        str key = opt;
        if (starts_with(opt, "--")) key = opt.substr(2);
        else if (starts_with(opt, "-")) key = opt.substr(1);
        auto it = opts_.find(key);
        return it != opts_.end() ? it->second : default_val;
    }
    vec<str> positional() const {
        vec<str> res;
        for (size_t i = 1; i < args_.size(); ++i) {
            if (!starts_with(args_[i], "-")) {
                res.push_back(args_[i]);
            } else if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                ++i;
            }
        }
        return res;
    }
};

// ============================================================================
// 其他实用工具
// ============================================================================
template<typename T>
class Singleton {
public:
    static T& instance() {
        static T inst;
        return inst;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
protected:
    Singleton() = default;
};

class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class NonMovable {
public:
    NonMovable() = default;
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

template<typename T>
class Counter {
    static inline atomic<T> count_{0};
public:
    Counter() { ++count_; }
    ~Counter() { --count_; }
    Counter(const Counter&) { ++count_; }
    Counter& operator=(const Counter&) = default;
    static T current() { return count_; }
};

template<typename T>
class Versioned {
    T value_;
    atomic<u64> version_{0};
public:
    Versioned() = default;
    explicit Versioned(T v) : value_(v) {}
    void set(const T& v) {
        value_ = v;
        ++version_;
    }
    T get() const { return value_; }
    u64 version() const { return version_; }
    bool changed(u64& last_version) const {
        u64 cur = version_;
        if (cur != last_version) {
            last_version = cur;
            return true;
        }
        return false;
    }
};

// ============================================================================
// 极简主函数宏（提供 ZINC_MAIN 兼容）
// ============================================================================
#define MAIN int main()
#define ZINC_MAIN int main()

#endif // ZINC_H
