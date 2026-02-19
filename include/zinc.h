#ifndef YU_CORE_H
#define YU_CORE_H

// ============================================
// 平台检测
// ============================================
#ifdef _WIN32
    #define PLATFORM_WINDOWS
    #ifdef _WIN64
        #define PLATFORM_WIN64
    #else
        #define PLATFORM_WIN32
    #endif
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define PLATFORM_IOS_SIM
    #elif TARGET_OS_IPHONE
        #define PLATFORM_IOS
    #elif TARGET_OS_MAC
        #define PLATFORM_MACOS
    #endif
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID
#elif defined(__linux__)
    #define PLATFORM_LINUX
#elif defined(__unix__)
    #define PLATFORM_UNIX
#endif

// ============================================
// 标准头文件（C++17）
// ============================================
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <array>
#include <tuple>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <future>
#include <optional>
#include <variant>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <random>
#include <cstdint>
#include <limits>
#include <fstream>
#include <sstream>
#include <functional>
#include <regex>
#include <initializer_list>

// 平台特定头文件
#ifdef PLATFORM_WINDOWS
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

#ifdef PLATFORM_MACOS
    #include <mach-o/dyld.h>
#endif

// C++17 文件系统
#if __cplusplus >= 201703L
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#endif

// ============================================
// 1. 类型系统
// ============================================
using i8  = std::int8_t;   using u8  = std::uint8_t;
using i16 = std::int16_t;  using u16 = std::uint16_t;
using i32 = std::int32_t;  using u32 = std::uint32_t;
using i64 = std::int64_t;  using u64 = std::uint64_t;
using f32 = float;         using f64 = double;
using str = std::string;
using cstr = const char*;

#ifdef PLATFORM_WINDOWS
    using handle = HANDLE;
    using dword = DWORD;
#else
    using handle = int;
    using dword = unsigned int;
#endif

// ============================================
// 2. 容器模板
// ============================================
template<class T> using Vec = std::vector<T>;
template<class T> using List = std::list<T>;
template<class T> using Set = std::set<T>;
template<class T> using USet = std::unordered_set<T>;
template<class K, class V> using Map = std::map<K, V>;
template<class K, class V> using UMap = std::unordered_map<K, V>;
template<class T> using Queue = std::queue<T>;
template<class T> using PQueue = std::priority_queue<T>;
template<class T> using Stack = std::stack<T>;
template<class T> using Deque = std::deque<T>;
template<class T, size_t N> using Arr = std::array<T, N>;
template<class... Ts> using Tup = std::tuple<Ts...>;

template<class T> using UP = std::unique_ptr<T>;
template<class T> using SP = std::shared_ptr<T>;
template<class T> using WP = std::weak_ptr<T>;

template<class T, class... Args>
inline auto mkup(Args&&... args) { 
    return std::make_unique<T>(std::forward<Args>(args)...); 
}

template<class T, class... Args>
inline auto mksp(Args&&... args) { 
    return std::make_shared<T>(std::forward<Args>(args)...); 
}

// ============================================
// 3. 跨平台打印
// ============================================
template<typename... Args>
inline void print(Args&&... args) {
    (std::cout << ... << args);
}

template<typename... Args>
inline void println(Args&&... args) {
    (std::cout << ... << args) << '\n';
}

#ifdef PLATFORM_WINDOWS
inline void enable_utf8_console() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
}
#else
inline void enable_utf8_console() {}
#endif

namespace console {
    inline constexpr cstr RESET   = "\033[0m";
    inline constexpr cstr RED     = "\033[31m";
    inline constexpr cstr GREEN   = "\033[32m";
    inline constexpr cstr YELLOW  = "\033[33m";
    inline constexpr cstr BLUE    = "\033[34m";
    inline constexpr cstr MAGENTA = "\033[35m";
    inline constexpr cstr CYAN    = "\033[36m";
    inline constexpr cstr WHITE   = "\033[37m";
    inline constexpr cstr BOLD    = "\033[1m";
}

template<typename... Args>
inline void print_info(Args&&... args) {
    print(console::BLUE, "[INFO] ", console::RESET);
    println(std::forward<Args>(args)...);
}

template<typename... Args>
inline void print_warn(Args&&... args) {
    print(console::YELLOW, "[WARN] ", console::RESET);
    println(std::forward<Args>(args)...);
}

template<typename... Args>
inline void print_error(Args&&... args) {
    print(console::RED, "[ERROR] ", console::RESET);
    println(std::forward<Args>(args)...);
}

template<typename... Args>
inline void print_success(Args&&... args) {
    print(console::GREEN, "[OK] ", console::RESET);
    println(std::forward<Args>(args)...);
}

// ============================================
// 4. 跨平台文件路径
// ============================================
class Path {
    fs::path p_;
public:
    Path() = default;
    Path(const str& s) : p_(s) {}
    Path(const char* s) : p_(s) {}
    Path(const fs::path& p) : p_(p) {}
    Path(const std::wstring& ws) : p_(ws) {}
    
    static Path join(const str& a, const str& b) {
        return Path((fs::path(a) / fs::path(b)).string());
    }
    
    static Path join(const Path& a, const Path& b) {
        return Path(a.p_ / b.p_);
    }
    
    template<typename... Paths>
    static Path join(const Path& first, const Path& second, const Paths&... rest) {
        return join(join(first, second), rest...);
    }
    
    str string() const { return p_.string(); }
    
    str native() const { 
#ifdef PLATFORM_WINDOWS
        auto wstr = p_.wstring();
        if (wstr.empty()) return "";
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (size_needed <= 0) return "";
        str result(size_needed - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], size_needed, nullptr, nullptr);
        return result;
#else
        return p_.string();
#endif
    }
    
#ifdef PLATFORM_WINDOWS
    std::wstring wstring() const { return p_.wstring(); }
#endif
    
    bool exists() const { 
        try { return fs::exists(p_); } catch (...) { return false; }
    }
    bool is_file() const { 
        try { return fs::is_regular_file(p_); } catch (...) { return false; }
    }
    bool is_dir() const { 
        try { return fs::is_directory(p_); } catch (...) { return false; }
    }
    size_t size() const { 
        try { return fs::file_size(p_); } catch (...) { return 0; }
    }
    
    Path parent() const { return Path(p_.parent_path()); }
    Path filename() const { return Path(p_.filename()); }
    Path stem() const { return Path(p_.stem()); }
    Path ext() const { return Path(p_.extension()); }
    
    Path absolute() const { 
        try { return Path(fs::absolute(p_)); } catch (...) { return *this; }
    }
    
    Path canonical() const {
        try { return Path(fs::canonical(p_)); } catch (...) { return *this; }
    }
    
    Path relative_to(const Path& base) const {
        try { return Path(fs::relative(p_, base.p_)); } catch (...) { return *this; }
    }
    
    Vec<Path> list() const {
        Vec<Path> result;
        if (is_dir()) {
            try {
                for (const auto& entry : fs::directory_iterator(p_)) {
                    result.push_back(Path(entry.path()));
                }
            } catch (...) {}
        }
        return result;
    }
    
    Vec<Path> list_recursive() const {
        Vec<Path> result;
        if (is_dir()) {
            try {
                for (const auto& entry : fs::recursive_directory_iterator(p_)) {
                    result.push_back(Path(entry.path()));
                }
            } catch (...) {}
        }
        return result;
    }
    
    bool mkdir() const {
        try { return fs::create_directories(p_); } catch (...) { return false; }
    }
    
    bool remove() const {
        try { return fs::remove(p_); } catch (...) { return false; }
    }
    
    bool remove_all() const {
        try { return fs::remove_all(p_) > 0; } catch (...) { return false; }
    }
    
    bool rename(const Path& to) const {
        try { fs::rename(p_, to.p_); return true; } catch (...) { return false; }
    }
    
    bool copy_to(const Path& dest, bool overwrite = false) const {
        try {
            auto options = overwrite ? fs::copy_options::overwrite_existing : fs::copy_options::none;
            fs::copy_file(p_, dest.p_, options);
            return true;
        } catch (...) { return false; }
    }
    
    Path operator/(const Path& other) const {
        return Path(p_ / other.p_);
    }
    
    Path& operator/=(const Path& other) {
        p_ /= other.p_;
        return *this;
    }
    
    bool operator==(const Path& other) const { return p_ == other.p_; }
    bool operator!=(const Path& other) const { return p_ != other.p_; }
    bool operator<(const Path& other) const { return p_ < other.p_; }
    
    friend std::ostream& operator<<(std::ostream& os, const Path& p) {
        return os << p.string();
    }
};

inline Path cwd() {
    try { return Path(fs::current_path()); } catch (...) { return Path("."); }
}

inline Path exe_path() {
#ifdef PLATFORM_WINDOWS
    wchar_t buf[MAX_PATH];
    DWORD len = GetModuleFileNameW(nullptr, buf, MAX_PATH);
    if (len == 0) return Path(".");
    return Path(std::wstring(buf, len));
#elif defined(PLATFORM_MACOS)
    char buf[1024];
    uint32_t size = sizeof(buf);
    if (_NSGetExecutablePath(buf, &size) != 0) return Path(".");
    return Path(buf);
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    char buf[1024];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf)-1);
    if (len <= 0) return Path(".");
    buf[len] = '\0';
    return Path(buf);
#else
    return Path(".");
#endif
}

inline Path home_dir() {
#ifdef PLATFORM_WINDOWS
    const char* userprofile = std::getenv("USERPROFILE");
    if (userprofile) return Path(userprofile);
    const char* homedrive = std::getenv("HOMEDRIVE");
    const char* homepath = std::getenv("HOMEPATH");
    if (homedrive && homepath) return Path(str(homedrive) + homepath);
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
    const char* home = std::getenv("HOME");
    if (home) return Path(home);
#endif
    return Path(".");
}

inline Path temp_dir() {
#ifdef PLATFORM_WINDOWS
    wchar_t buf[MAX_PATH];
    DWORD len = GetTempPathW(MAX_PATH, buf);
    if (len == 0) return Path(".");
    return Path(std::wstring(buf, len));
#else
    const char* tmpdir = std::getenv("TMPDIR");
    if (tmpdir) return Path(tmpdir);
    return Path("/tmp");
#endif
}

// ============================================
// 5. 跨平台时间
// ============================================
using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::steady_clock::time_point;
using SystemClock = std::chrono::system_clock;

inline TimePoint now() { return Clock::now(); }

inline void sleep_ms(i32 ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

inline void sleep_s(i32 s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}

inline void sleep_us(i64 us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

inline i64 timestamp_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        SystemClock::now().time_since_epoch()).count();
}

inline i64 timestamp_us() {
    return std::chrono::duration_cast<std::chrono::microseconds>(
        SystemClock::now().time_since_epoch()).count();
}

inline str format_time(const str& fmt = "%Y-%m-%d %H:%M:%S") {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    char buf[128];
    std::strftime(buf, sizeof(buf), fmt.c_str(), &tm);
    return str(buf);
}

inline str format_time(i64 timestamp_ms_val, const str& fmt = "%Y-%m-%d %H:%M:%S") {
    auto t = static_cast<std::time_t>(timestamp_ms_val / 1000);
    auto tm = *std::localtime(&t);
    char buf[128];
    std::strftime(buf, sizeof(buf), fmt.c_str(), &tm);
    return str(buf);
}

class Timer {
    TimePoint start_;
    str name_;
    bool print_on_destroy_;
public:
    explicit Timer(str name = "", bool print_on_destroy = true) 
        : start_(now()), name_(std::move(name)), print_on_destroy_(print_on_destroy) {}
    
    ~Timer() {
        if (print_on_destroy_ && !name_.empty()) {
            print_info(name_, " took ", elapsed_ms(), " ms");
        }
    }
    
    void restart() { start_ = now(); }
    
    f64 elapsed_ms() const {
        return std::chrono::duration<f64, std::milli>(now() - start_).count();
    }
    
    f64 elapsed_s() const {
        return std::chrono::duration<f64>(now() - start_).count();
    }
    
    i64 elapsed_us() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(now() - start_).count();
    }
};

// ============================================
// 6. 跨平台线程
// ============================================
using Thread = std::thread;
using Mutex = std::mutex;
using LockGuard = std::lock_guard<std::mutex>;
using UniqueLock = std::unique_lock<std::mutex>;
using CondVar = std::condition_variable;

template<class T>
using Future = std::future<T>;

template<class F, class... Args>
inline auto async(F&& f, Args&&... args) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
}

inline u32 hardware_concurrency() {
    return std::thread::hardware_concurrency();
}

class ThreadPool {
    Vec<Thread> workers_;
    Queue<std::function<void()>> tasks_;
    Mutex queue_mutex_;
    CondVar condition_;
    bool stop_ = false;
    
public:
    explicit ThreadPool(size_t threads = 0) {
        if (threads == 0) threads = hardware_concurrency();
        for (size_t i = 0; i < threads; ++i) {
            workers_.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        UniqueLock lock(queue_mutex_);
                        condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
                        if (stop_ && tasks_.empty()) return;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }
    
    ~ThreadPool() {
        {
            LockGuard lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (auto& worker : workers_) {
            if (worker.joinable()) worker.join();
        }
    }
    
    // C++17: 使用 std::result_of（注意：C++17 废弃，C++20 移除，但 C++17 编译器仍支持）
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> Future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        Future<return_type> res = task->get_future();
        {
            LockGuard lock(queue_mutex_);
            if (stop_) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return res;
    }
};

// C++17 shared_mutex 支持检测
#ifdef __cpp_lib_shared_mutex
    #include <shared_mutex>
    using RWLock = std::shared_mutex;
    using ReadLock = std::shared_lock<std::shared_mutex>;
    using WriteLock = std::unique_lock<std::shared_mutex>;
#else
    using RWLock = std::mutex;
    using ReadLock = LockGuard;
    using WriteLock = LockGuard;
#endif

// ============================================
// 7. 跨平台环境变量
// ============================================
inline str get_env(const str& name) {
#ifdef PLATFORM_WINDOWS
    size_t sz = 0;
    if (getenv_s(&sz, nullptr, 0, name.c_str()) != 0 || sz == 0) return "";
    str result(sz - 1, 0);
    if (getenv_s(&sz, &result[0], sz, name.c_str()) != 0) return "";
    return result;
#else
    const char* val = std::getenv(name.c_str());
    return val ? str(val) : str("");
#endif
}

inline bool set_env(const str& name, const str& value) {
#ifdef PLATFORM_WINDOWS
    return _putenv_s(name.c_str(), value.c_str()) == 0;
#else
    return setenv(name.c_str(), value.c_str(), 1) == 0;
#endif
}

inline bool unset_env(const str& name) {
#ifdef PLATFORM_WINDOWS
    return _putenv_s(name.c_str(), "") == 0;
#else
    return unsetenv(name.c_str()) == 0;
#endif
}

// ============================================
// 8. 跨平台文件操作
// ============================================
inline str read_file(const Path& path) {
    std::ifstream f(path.string(), std::ios::binary);
    if (!f) return "";
    return str((std::istreambuf_iterator<char>(f)),
               std::istreambuf_iterator<char>());
}

inline Vec<u8> read_file_bytes(const Path& path) {
    std::ifstream f(path.string(), std::ios::binary);
    if (!f) return {};
    f.seekg(0, std::ios::end);
    auto size = f.tellg();
    f.seekg(0, std::ios::beg);
    if (size <= 0) return {};
    Vec<u8> result(static_cast<size_t>(size));
    f.read(reinterpret_cast<char*>(result.data()), size);
    return result;
}

inline bool write_file(const Path& path, const str& content) {
    std::ofstream f(path.string(), std::ios::binary);
    if (!f) return false;
    f << content;
    return f.good();
}

inline bool write_file_bytes(const Path& path, const Vec<u8>& bytes) {
    std::ofstream f(path.string(), std::ios::binary);
    if (!f) return false;
    f.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    return f.good();
}

inline bool append_file(const Path& path, const str& content) {
    std::ofstream f(path.string(), std::ios::binary | std::ios::app);
    if (!f) return false;
    f << content;
    return f.good();
}

inline Vec<str> read_lines(const Path& path) {
    Vec<str> lines;
    std::ifstream f(path.string());
    if (!f) return lines;
    str line;
    while (std::getline(f, line)) {
        lines.push_back(line);
    }
    return lines;
}

inline bool write_file_atomic(const Path& path, const str& content) {
    Path tmp = path.parent() / Path(path.filename().string() + ".tmp");
    if (!write_file(tmp, content)) return false;
    tmp.remove();
    return tmp.rename(path);
}

// ============================================
// 9. 跨平台随机数
// ============================================
class Random {
    std::mt19937_64 gen_;
public:
    Random() {
        std::random_device rd;
        if (rd.entropy() > 0) {
            gen_.seed(rd());
        } else {
            gen_.seed(timestamp_us());
        }
    }
    
    explicit Random(u64 seed) : gen_(seed) {}
    
    i64 next_i64(i64 min, i64 max) {
        return std::uniform_int_distribution<i64>(min, max)(gen_);
    }
    
    i64 next_i64(i64 max) { return next_i64(0, max); }
    
    f64 next_f64(f64 min = 0.0, f64 max = 1.0) {
        return std::uniform_real_distribution<f64>(min, max)(gen_);
    }
    
    bool next_bool() { return next_i64(0, 1) == 1; }
    
    i32 next_i32(i32 min, i32 max) {
        return std::uniform_int_distribution<i32>(min, max)(gen_);
    }
    
    f64 next_normal(f64 mean = 0.0, f64 stddev = 1.0) {
        return std::normal_distribution<f64>(mean, stddev)(gen_);
    }
    
    i64 next_poisson(f64 mean) {
        return std::poisson_distribution<i64>(mean)(gen_);
    }
    
    template<class C>
    void shuffle(C& c) {
        std::shuffle(c.begin(), c.end(), gen_);
    }
    
    template<class C>
    auto& choice(C& c) { return c[next_i64(c.size() - 1)]; }
    
    template<class C>
    const auto& choice(const C& c) { return c[next_i64(c.size() - 1)]; }
};

inline Random& global_random() {
    static Random rnd;
    return rnd;
}

inline i64 rand_i64(i64 min, i64 max) { return global_random().next_i64(min, max); }
inline f64 rand_f64(f64 min = 0.0, f64 max = 1.0) { return global_random().next_f64(min, max); }
inline bool rand_bool() { return global_random().next_bool(); }

// ============================================
// 10. 跨平台数学
// ============================================
inline constexpr f64 PI = 3.14159265358979323846;
inline constexpr f64 E = 2.71828182845904523536;
inline constexpr f64 EPSILON = 1e-9;
inline constexpr f64 GOLDEN_RATIO = 1.618033988749895;

template<typename T>
inline T to_rad(T deg) { return deg * static_cast<T>(PI) / static_cast<T>(180); }

template<typename T>
inline T to_deg(T rad) { return rad * static_cast<T>(180) / static_cast<T>(PI); }

template<typename T>
inline T clamp(T v, T min, T max) {
    return std::max(min, std::min(v, max));
}

template<typename T>
inline T lerp(T a, T b, f64 t) {
    return a + static_cast<T>((b - a) * t);
}

template<typename T>
inline T smoothstep(T edge0, T edge1, T x) {
    T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return t * t * (T(3) - T(2) * t);
}

template<typename T>
inline T smootherstep(T edge0, T edge1, T x) {
    T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return t * t * t * (t * (t * T(6) - T(15)) + T(10));
}

template<typename T>
inline bool approx_eq(T a, T b, T epsilon = static_cast<T>(EPSILON)) {
    return std::abs(a - b) <= epsilon * std::max({T(1), std::abs(a), std::abs(b)});
}

template<typename T>
inline T map_range(T x, T in_min, T in_max, T out_min, T out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
inline T wrap_angle(T angle) {
    T res = std::fmod(angle, T(360));
    if (res < 0) res += T(360);
    return res;
}

// ============================================
// 11. 跨平台字节序（C++17 兼容）
// ============================================
namespace byteorder {
    // C++17: 运行期检测（不能使用 constexpr 联合体）
    inline bool is_little_endian() {
        const u16 test = 0x0102;
        return *reinterpret_cast<const u8*>(&test) == 0x02;
    }
    
    inline bool is_big_endian() { return !is_little_endian(); }

    inline u16 swap_bytes(u16 v) {
        return (v >> 8) | (v << 8);
    }

    inline u32 swap_bytes(u32 v) {
        return ((v >> 24) & 0xFF) | ((v >> 8) & 0xFF00) |
               ((v << 8) & 0xFF0000) | ((v << 24) & 0xFF000000);
    }

    inline u64 swap_bytes(u64 v) {
        return ((v >> 56) & 0xFFULL) | ((v >> 40) & 0xFF00ULL) |
               ((v >> 24) & 0xFF0000ULL) | ((v >> 8) & 0xFF000000ULL) |
               ((v << 8) & 0xFF00000000ULL) | ((v << 24) & 0xFF0000000000ULL) |
               ((v << 40) & 0xFF000000000000ULL) | ((v << 56) & 0xFF00000000000000ULL);
    }

    inline u16 to_network(u16 v) { return is_little_endian() ? swap_bytes(v) : v; }
    inline u32 to_network(u32 v) { return is_little_endian() ? swap_bytes(v) : v; }
    inline u64 to_network(u64 v) { return is_little_endian() ? swap_bytes(v) : v; }

    inline u16 from_network(u16 v) { return to_network(v); }
    inline u32 from_network(u32 v) { return to_network(v); }
    inline u64 from_network(u64 v) { return to_network(v); }
    
    inline u16 htons(u16 v) { return to_network(v); }
    inline u32 htonl(u32 v) { return to_network(v); }
    inline u64 htonll(u64 v) { return to_network(v); }
    inline u16 ntohs(u16 v) { return from_network(v); }
    inline u32 ntohl(u32 v) { return from_network(v); }
    inline u64 ntohll(u64 v) { return from_network(v); }
}

// ============================================
// 12. 字符串工具
// ============================================
inline Vec<str> split(const str& s, char delim) {
    Vec<str> tokens;
    std::stringstream ss(s);
    str token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

inline Vec<str> split(const str& s, const str& delim) {
    Vec<str> tokens;
    size_t start = 0;
    size_t end = s.find(delim);
    while (end != str::npos) {
        if (end > start) tokens.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    if (start < s.length()) tokens.push_back(s.substr(start));
    return tokens;
}

inline str trim_left(const str& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    return (start == str::npos) ? "" : s.substr(start);
}

inline str trim_right(const str& s) {
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return (end == str::npos) ? "" : s.substr(0, end + 1);
}

inline str trim(const str& s) {
    return trim_right(trim_left(s));
}

inline str replace_all(str s, const str& from, const str& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != str::npos) {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
    return s;
}

inline str to_lower(str s) {
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){ return std::tolower(c); });
    return s;
}

inline str to_upper(str s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::toupper(c); });
    return s;
}

inline bool starts_with(const str& s, const str& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

inline bool ends_with(const str& s, const str& suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

// C++17 简易 format（使用 {} 占位符）
template<typename... Args>
inline str format(const str& fmt_str, Args&&... args) {
    std::ostringstream oss;
    size_t pos = 0;
    auto process = [&](const auto& arg) {
        auto next = fmt_str.find("{}", pos);
        if (next != str::npos) {
            oss << fmt_str.substr(pos, next - pos) << arg;
            pos = next + 2;
        }
    };
    (process(args), ...);
    oss << fmt_str.substr(pos);
    return oss.str();
}

template<typename... Args>
inline str join(const str& delim, Args&&... args) {
    str result;
    bool first = true;
    auto append = [&](const auto& s) {
        if (!first) result += delim;
        result += s;
        first = false;
    };
    (append(args), ...);
    return result;
}

namespace detail {
    inline constexpr u64 fnv1a_hash(const char* str, u64 hash = 1469598103934665603ULL) {
        return *str ? fnv1a_hash(str + 1, (hash ^ u8(*str)) * 1099511628211ULL) : hash;
    }
}
inline constexpr u64 operator""_hash(const char* str, size_t) { 
    return detail::fnv1a_hash(str); 
}

// ============================================
// 13. 调试工具
// ============================================
template<typename... T>
inline constexpr bool always_false = false;

template<typename... T>
inline constexpr void todo() {
    static_assert(always_false<T...>, "TODO: not implemented");
}

#ifndef NDEBUG
    #define ASSERT(cond) \
        do { if (!(cond)) { \
            print_error("ASSERT failed: {} at {}:{}", #cond, __FILE__, __LINE__); \
            std::abort(); \
        } } while(0)
    #define DEBUG_PRINT(...) println(__VA_ARGS__)
#else
    #define ASSERT(cond) ((void)0)
    #define DEBUG_PRINT(...) ((void)0)
#endif

template<typename F>
class ScopeGuard {
    F f_;
    bool active_ = true;
public:
    explicit ScopeGuard(F f) : f_(std::move(f)) {}
    ~ScopeGuard() { if (active_) f_(); }
    void dismiss() { active_ = false; }
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard(ScopeGuard&& other) noexcept : f_(std::move(other.f_)), active_(other.active_) {
        other.active_ = false;
    }
};

template<typename F>
inline auto scope_guard(F&& f) { 
    return ScopeGuard<std::decay_t<F>>(std::forward<F>(f)); 
}

#define DEFER(code) auto _defer_##__LINE__ = scope_guard([&]() { code; })

// ============================================
// 14. 跨平台主函数封装
// ============================================
#define YU_MAIN int main(int argc, char** argv)

class Args {
    Vec<str> args_;
    UMap<str, str> opts_;
public:
    Args(int argc, char** argv) {
        for (int i = 0; i < argc; i++) {
            args_.push_back(argv[i]);
        }
        for (size_t i = 1; i  < args_.size(); ++i) {
            const str& arg = args_[i];
            if (starts_with(arg, "--")) {
                size_t eq = arg.find('=');
                if (eq != str::npos) {
                    opts_[arg.substr(2, eq - 2)] = arg.substr(eq + 1);
                } else if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                    opts_[arg.substr(2)] = args_[i + 1];
                    ++i;
                } else {
                    opts_[arg.substr(2)] = "true";
                }
            } else if (starts_with(arg, "-") && arg.length() > 1) {
                for (size_t j = 1; j < arg.length(); ++j) {
                    str key(1, arg[j]);
                    if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                        opts_[key] = args_[i + 1];
                        if (j == arg.length() - 1) ++i;
                    } else {
                        opts_[key] = "true";
                    }
                }
            }
        }
    }
    
    size_t count() const { return args_.size(); }
    str get(size_t i) const { return i < args_.size() ? args_[i] : ""; }
    str program() const { return get(0); }
    
    bool has(const str& opt) const {
        if (starts_with(opt, "--")) return opts_.count(opt.substr(2)) > 0;
        if (starts_with(opt, "-")) return opts_.count(opt.substr(1)) > 0;
        return opts_.count(opt) > 0 || 
               std::find(args_.begin(), args_.end(), "--" + opt) != args_.end() ||
               std::find(args_.begin(), args_.end(), "-" + opt) != args_.end();
    }
    
    str value(const str& opt, const str& default_val = "") const {
        str key = starts_with(opt, "--") ? opt.substr(2) : 
                  starts_with(opt, "-") ? opt.substr(1) : opt;
        auto it = opts_.find(key);
        return it != opts_.end() ? it->second : default_val;
    }
    
    Vec<str> positional() const {
        Vec<str> result;
        for (size_t i = 1; i < args_.size(); ++i) {
            if (!starts_with(args_[i], "-")) {
                result.push_back(args_[i]);
            } else if (i + 1 < args_.size() && !starts_with(args_[i + 1], "-")) {
                ++i;
            }
        }
        return result;
    }
};

// ============================================
// 15. 其他实用工具
// ============================================
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
inline T bit_or(T a, T b) { 
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) | 
                          static_cast<std::underlying_type_t<T>>(b)); 
}

template<typename T>
inline T bit_and(T a, T b) { 
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) & 
                          static_cast<std::underlying_type_t<T>>(b)); 
}

template<typename T>
inline T bit_xor(T a, T b) { 
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(a) ^ 
                          static_cast<std::underlying_type_t<T>>(b)); 
}

template<typename T>
inline T bit_not(T a) { 
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(a)); 
}

template<typename T>
inline bool bit_test(T a, T flag) { 
    return (static_cast<std::underlying_type_t<T>>(a) & 
            static_cast<std::underlying_type_t<T>>(flag)) != 0; 
}

// 字节操作（C++17 原始指针版本）
inline u8 read_u8(const u8* p) { return p[0]; }
inline u16 read_u16_le(const u8* p) { return p[0] | (p[1] << 8); }
inline u32 read_u32_le(const u8* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24); }
inline u64 read_u64_le(const u8* p) { 
    return (u64)p[0] | ((u64)p[1] << 8) | ((u64)p[2] << 16) | ((u64)p[3] << 24) |
           ((u64)p[4] << 32) | ((u64)p[5] << 40) | ((u64)p[6] << 48) | ((u64)p[7] << 56); 
}
inline u16 read_u16_be(const u8* p) { return (p[0] << 8) | p[1]; }
inline u32 read_u32_be(const u8* p) { return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]; }
inline u64 read_u64_be(const u8* p) {
    return ((u64)p[0] << 56) | ((u64)p[1] << 48) | ((u64)p[2] << 40) | ((u64)p[3] << 32) |
           ((u64)p[4] << 24) | ((u64)p[5] << 16) | ((u64)p[6] << 8) | (u64)p[7];
}

inline void write_u8(u8* p, u8 v) { p[0] = v; }
inline void write_u16_le(u8* p, u16 v) { p[0] = v; p[1] = v >> 8; }
inline void write_u32_le(u8* p, u32 v) { p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24; }
inline void write_u64_le(u8* p, u64 v) { 
    p[0] = v; p[1] = v >> 8; p[2] = v >> 16; p[3] = v >> 24;
    p[4] = v >> 32; p[5] = v >> 40; p[6] = v >> 48; p[7] = v >> 56;
}
inline void write_u16_be(u8* p, u16 v) { p[0] = v >> 8; p[1] = v; }
inline void write_u32_be(u8* p, u32 v) { p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v; }
inline void write_u64_be(u8* p, u64 v) {
    p[0] = v >> 56; p[1] = v >> 48; p[2] = v >> 40; p[3] = v >> 32;
    p[4] = v >> 24; p[5] = v >> 16; p[6] = v >> 8; p[7] = v;
}

// 性能计数器
class PerfCounter {
#ifdef PLATFORM_WINDOWS
    LARGE_INTEGER start_;
    static inline LARGE_INTEGER freq_ = []() {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return f;
    }();
#else
    timespec start_;
#endif
public:
    PerfCounter() { reset(); }
    
    void reset() {
#ifdef PLATFORM_WINDOWS
        QueryPerformanceCounter(&start_);
#else
        clock_gettime(CLOCK_MONOTONIC, &start_);
#endif
    }
    
    i64 elapsed_us() const {
#ifdef PLATFORM_WINDOWS
        LARGE_INTEGER end;
        QueryPerformanceCounter(&end);
        return ((end.QuadPart - start_.QuadPart) * 1000000) / freq_.QuadPart;
#else
        timespec end;
        clock_gettime(CLOCK_MONOTONIC, &end);
        return (end.tv_sec - start_.tv_sec) * 1000000 + (end.tv_nsec - start_.tv_nsec) / 1000;
#endif
    }
    
    f64 elapsed_ms() const { return elapsed_us() / 1000.0; }
    f64 elapsed_s() const { return elapsed_us() / 1000000.0; }
};

// 内存池
template<size_t BlockSize, size_t NumBlocks = 1024>
class MemoryPool {
    static_assert(BlockSize >= sizeof(void*), "BlockSize too small");
    union Block {
        char data[BlockSize];
        Block* next;
    };
    Vec<UP<Block[]>> chunks_;
    Block* free_list_ = nullptr;
    Mutex mutex_;
    
public:
    MemoryPool() { allocate_chunk(); }
    
    void* allocate() {
        LockGuard lock(mutex_);
        if (!free_list_) allocate_chunk();
        Block* block = free_list_;
        free_list_ = block->next;
        return block;
    }
    
    void deallocate(void* p) {
        if (!p) return;
        LockGuard lock(mutex_);
        Block* block = static_cast<Block*>(p);
        block->next = free_list_;
        free_list_ = block;
    }
    
private:
    void allocate_chunk() {
        auto chunk = mkup<Block[]>(NumBlocks);
        for (size_t i = 0; i < NumBlocks; ++i) {
            chunk[i].next = free_list_;
            free_list_ = &chunk[i];
        }
        chunks_.push_back(std::move(chunk));
    }
};

template<typename T, size_t NumBlocks = 1024>
class ObjectPool {
    MemoryPool<sizeof(T), NumBlocks> pool_;
public:
    template<typename... Args>
    T* acquire(Args&&... args) {
        void* p = pool_.allocate();
        return new (p) T(std::forward<Args>(args)...);
    }
    void release(T* p) {
        if (p) { p->~T(); pool_.deallocate(p); }
    }
};

#endif // YU_CORE_H
