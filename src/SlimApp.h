#pragma once

#if defined(__clang__)
#define COMPILER_CLANG 1
#define COMPILER_CLANG_OR_GCC 1
#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER_GCC 1
    #define COMPILER_CLANG_OR_GCC 1
#elif defined(_MSC_VER)
    #define COMPILER_MSVC 1
#endif

#ifndef NDEBUG
#define INLINE
#elif defined(COMPILER_MSVC)
#define INLINE inline __forceinline
#elif defined(COMPILER_CLANG_OR_GCC)
    #define INLINE inline __attribute__((always_inline))
#else
    #define INLINE inline
#endif

#ifdef COMPILER_CLANG
#define ENABLE_FP_CONTRACT \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"") \
        _Pragma("STDC FP_CONTRACT ON") \
        _Pragma("clang diagnostic pop")
#else
#define ENABLE_FP_CONTRACT
#endif

#ifdef FP_FAST_FMAF
#define fast_mul_add(a, b, c) fmaf(a, b, c)
#else
ENABLE_FP_CONTRACT
#define fast_mul_add(a, b, c) ((a) * (b) + (c))
#endif

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long int  u32;
typedef unsigned long long u64;
typedef signed   short     i16;
typedef signed   long int  i32;

typedef float  f32;
typedef double f64;


#define FONT_HEIGHT 8
#define FONT_WIDTH 8

unsigned char Font[768] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18,
        0x18, 0x00, 0x18, 0x00, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00, 0x18, 0x3e, 0x60, 0x3c,
        0x06, 0x7c, 0x18, 0x00, 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00,
        0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00, 0x18, 0x18, 0x30, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00,
        0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00, 0x00, 0x66, 0x3c, 0xff,
        0x3c, 0x66, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x7e,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00,
        0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x38, 0x6c, 0xc6, 0xd6,
        0xc6, 0x6c, 0x38, 0x00, 0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00,
        0x7c, 0xc6, 0x06, 0x1c, 0x30, 0x66, 0xfe, 0x00, 0x7c, 0xc6, 0x06, 0x3c,
        0x06, 0xc6, 0x7c, 0x00, 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00,
        0xfe, 0xc0, 0xc0, 0xfc, 0x06, 0xc6, 0x7c, 0x00, 0x38, 0x60, 0xc0, 0xfc,
        0xc6, 0xc6, 0x7c, 0x00, 0xfe, 0xc6, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00,
        0x7c, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0x7c, 0x00, 0x7c, 0xc6, 0xc6, 0x7e,
        0x06, 0x0c, 0x78, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00,
        0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30, 0x06, 0x0c, 0x18, 0x30,
        0x18, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00,
        0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00, 0x7c, 0xc6, 0x0c, 0x18,
        0x18, 0x00, 0x18, 0x00, 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00,
        0x38, 0x6c, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x00, 0xfc, 0x66, 0x66, 0x7c,
        0x66, 0x66, 0xfc, 0x00, 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00,
        0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00, 0xfe, 0x62, 0x68, 0x78,
        0x68, 0x62, 0xfe, 0x00, 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00,
        0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3a, 0x00, 0xc6, 0xc6, 0xc6, 0xfe,
        0xc6, 0xc6, 0xc6, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00,
        0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00, 0xe6, 0x66, 0x6c, 0x78,
        0x6c, 0x66, 0xe6, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00,
        0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00, 0xc6, 0xe6, 0xf6, 0xde,
        0xce, 0xc6, 0xc6, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00,
        0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00, 0x7c, 0xc6, 0xc6, 0xc6,
        0xc6, 0xce, 0x7c, 0x0e, 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00,
        0x3c, 0x66, 0x30, 0x18, 0x0c, 0x66, 0x3c, 0x00, 0x7e, 0x7e, 0x5a, 0x18,
        0x18, 0x18, 0x3c, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00,
        0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0xc6, 0xc6, 0xc6, 0xd6,
        0xd6, 0xfe, 0x6c, 0x00, 0xc6, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0xc6, 0x00,
        0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x3c, 0x00, 0xfe, 0xc6, 0x8c, 0x18,
        0x32, 0x66, 0xfe, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00,
        0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00, 0x3c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0c, 0x3c, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x30, 0x18, 0x0c, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00,
        0xe0, 0x60, 0x7c, 0x66, 0x66, 0x66, 0xdc, 0x00, 0x00, 0x00, 0x7c, 0xc6,
        0xc0, 0xc6, 0x7c, 0x00, 0x1c, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00,
        0x00, 0x00, 0x7c, 0xc6, 0xfe, 0xc0, 0x7c, 0x00, 0x3c, 0x66, 0x60, 0xf8,
        0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8,
        0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00, 0x18, 0x00, 0x38, 0x18,
        0x18, 0x18, 0x3c, 0x00, 0x06, 0x00, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3c,
        0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00, 0x38, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 0xec, 0xfe, 0xd6, 0xd6, 0xd6, 0x00,
        0x00, 0x00, 0xdc, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x7c, 0xc6,
        0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0,
        0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e, 0x00, 0x00, 0xdc, 0x76,
        0x60, 0x60, 0xf0, 0x00, 0x00, 0x00, 0x7e, 0xc0, 0x7c, 0x06, 0xfc, 0x00,
        0x30, 0x30, 0xfc, 0x30, 0x30, 0x36, 0x1c, 0x00, 0x00, 0x00, 0xcc, 0xcc,
        0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00,
        0x00, 0x00, 0xc6, 0xd6, 0xd6, 0xfe, 0x6c, 0x00, 0x00, 0x00, 0xc6, 0x6c,
        0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0x7e, 0x06, 0xfc,
        0x00, 0x00, 0x7e, 0x4c, 0x18, 0x32, 0x7e, 0x00, 0x0e, 0x18, 0x18, 0x70,
        0x18, 0x18, 0x0e, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,
        0x70, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x70, 0x00, 0x76, 0xdc, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0xfe, 0x00
};

#define LINE_HEIGHT 12
#define FIRST_CHARACTER_CODE 32
#define LAST_CHARACTER_CODE 127

struct os {
    os() = delete;
    static u64 ticks_per_second;
    static u64 getTicks();
    static void* getMemory(u64 size);
    static void setWindowTitle(char* str);
    static void setWindowCapture(bool on);
    static void setCursorVisibility(bool on);
    static void closeFile(void *handle);
    static void* openFileForReading(const char* file_path);
    static void* openFileForWriting(const char* file_path);
    static bool readFromFile(void *out, unsigned long, void *handle);
    static bool writeToFile(void *out, unsigned long, void *handle);
};

u64 os::ticks_per_second{0};

INLINE f32 approach(f32 src, f32 trg, f32 diff) {
    f32 out;

    out = src + diff; if (trg > out) return out;
    out = src - diff; if (trg < out) return out;

    return trg;
}

#define MAX_COLOR_VALUE 0xFF

#ifndef INCLUDE_SLIMAPP_MATH
#include <cmath>

struct vec2i {
    i32 x = 0, y = 0;

    vec2i() : x(0), y(0) {}
    explicit vec2i(i32 X, i32 Y) : x(X), y(Y) {}
    explicit vec2i(i32 value) : x(value), y(value) {}
    INLINE vec2i operator!() const { return vec2i{-x, -y}; }
    INLINE vec2i operator~() const { return this->perp(); }
    INLINE bool operator==(vec2i other) const { return other.x == x && other.y == y; }
    INLINE vec2i& operator-=(vec2i rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    INLINE vec2i& operator+=(vec2i rhs) { x += rhs.x; y += rhs.y; return *this; }
    INLINE vec2i& operator*=(vec2i rhs) { x *= rhs.x; y *= rhs.y; return *this; }
    INLINE vec2i& operator/=(vec2i rhs) { x /= rhs.x; y /= rhs.y; return *this; }
    INLINE vec2i& operator-=(i32 rhs) { x -= rhs; y -= rhs; return *this; }
    INLINE vec2i& operator+=(i32 rhs) { x += rhs; y += rhs; return *this; }
    INLINE vec2i& operator*=(i32 rhs) { x *= rhs; y *= rhs; return *this; }
    INLINE vec2i& operator/=(i32 rhs) { x /= rhs; y /= rhs; return *this; }
    INLINE vec2i operator-(vec2i rhs) const { return vec2i{x - rhs.x, y - rhs.y}; }
    INLINE vec2i operator+(vec2i rhs) const { return vec2i{x + rhs.x, y + rhs.y}; }
    INLINE vec2i operator*(vec2i rhs) const { return vec2i{x * rhs.x, y * rhs.y}; }
    INLINE vec2i operator/(vec2i rhs) const { return vec2i{x / rhs.x, y / rhs.y}; }
    INLINE vec2i operator-(i32 rhs) const { return vec2i{x - rhs, y - rhs}; }
    INLINE vec2i operator+(i32 rhs) const { return vec2i{x + rhs, y + rhs}; }
    INLINE vec2i operator*(i32 rhs) const { return vec2i{x * rhs, y * rhs}; }
    INLINE vec2i operator/(i32 rhs) const { return vec2i{x / rhs, y / rhs}; }

    INLINE vec2i operator-(f32 rhs) const { return vec2i{x - (i32)rhs, y - (i32)rhs}; }
    INLINE vec2i operator+(f32 rhs) const { return vec2i{x + (i32)rhs, y + (i32)rhs}; }
    INLINE vec2i operator*(f32 rhs) const { return vec2i{x * (i32)rhs, y * (i32)rhs}; }
    INLINE vec2i operator/(f32 rhs) const { return vec2i{x / (i32)rhs, y / (i32)rhs}; }
    INLINE vec2i& operator-=(f32 rhs) { x -= (i32)rhs; y -= (i32)rhs; return *this; }
    INLINE vec2i& operator+=(f32 rhs) { x += (i32)rhs; y += (i32)rhs; return *this; }
    INLINE vec2i& operator*=(f32 rhs) { x *= (i32)rhs; y *= (i32)rhs; return *this; }
    INLINE vec2i& operator/=(f32 rhs) { x /= (i32)rhs; y /= (i32)rhs; return *this; }

    INLINE bool nonZero() const { return x != 0 || y != 0; }
    INLINE vec2i perp() const { return vec2i{-y, x}; }
    INLINE i32 min() const { return x < y ? x : y; }
    INLINE i32 max() const { return x > y ? x : y; }
    INLINE i32 length() const { return (i32)sqrtf((f32)(x*x + y*y)); }
    INLINE i32 squaredLength() const { return x*x + y*y; }
    INLINE vec2i cloned() const { return vec2i{x, y}; }
    INLINE vec2i clampedToZero() const { return vec2i{x > 0 ? x : 0, y > 0 ? y : 0 }; }
    INLINE vec2i clampedToUpper(vec2i upper) const { return vec2i{x < upper.x ? x : upper.x, y < upper.y ? y : upper.y }; }
    INLINE vec2i clampedToRange(const i32 min_value, const i32 max_value) const {
        vec2i out{x > min_value ? x : min_value, y > min_value ? y : min_value};
        out.x = out.x < max_value ? out.x : max_value;
        out.y = out.y < max_value ? out.y : max_value;
        return *this;
    }
    INLINE vec2i scaleAdd(f32 factor, vec2i to_be_added) const {
        return vec2i{
                (i32)fast_mul_add((f32)x, factor, (f32)to_be_added.x),
                (i32)fast_mul_add((f32)y, factor, (f32)to_be_added.y)
        };
    }
};


struct mat2;
struct vec2 {
    f32 x = 0, y = 0;

    explicit vec2(f32 X, f32 Y) : x(X), y(Y) {}
    explicit vec2(f32 value) : x(value), y(value) {}
    explicit vec2(vec2i v) : x((f32)v.x), y((f32)v.y) {}
    INLINE bool operator==(vec2 other) const { return other.x == x && other.y == y; }
    INLINE f32 operator|(vec2 rhs) const { return dot(rhs); }
    INLINE f32 operator^(vec2 rhs) const { return cross(rhs); }
    INLINE vec2 operator%(vec2 rhs) const { return reflectAround(rhs); }
    INLINE vec2 operator!() const { return vec2{-x, -y}; }
    INLINE vec2 operator~() const { return this->perp(); }
    INLINE vec2 operator-(vec2 rhs) const { return vec2{x - rhs.x, y - rhs.y}; }
    INLINE vec2 operator+(vec2 rhs) const { return vec2{x + rhs.x, y + rhs.y}; }
    INLINE vec2 operator*(vec2 rhs) const { return vec2{x * rhs.x, y * rhs.y}; }
    INLINE vec2 operator/(vec2 rhs) const { return vec2{x / rhs.x, y / rhs.y}; }
    INLINE vec2& operator-=(vec2 rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    INLINE vec2& operator+=(vec2 rhs) { x += rhs.x; y += rhs.y; return *this; }
    INLINE vec2& operator*=(vec2 rhs) { x *= rhs.x; y *= rhs.y; return *this; }
    INLINE vec2& operator/=(vec2 rhs) { x /= rhs.x; y /= rhs.y; return *this; }
    INLINE vec2 operator-(f32 rhs) const { return vec2{x - rhs, y - rhs}; }
    INLINE vec2 operator+(f32 rhs) const { return vec2{x + rhs, y + rhs}; }
    INLINE vec2 operator*(f32 rhs) const { return vec2{x * rhs, y * rhs}; }
    INLINE vec2 operator/(f32 rhs) const { return vec2{x / rhs, y / rhs}; }
    INLINE vec2& operator-=(f32 rhs) { x -= rhs; y -= rhs; return *this; }
    INLINE vec2& operator+=(f32 rhs) { x += rhs; y += rhs; return *this; }
    INLINE vec2& operator*=(f32 rhs) { x *= rhs; y *= rhs; return *this; }
    INLINE vec2& operator/=(f32 rhs) { x /= rhs; y /= rhs; return *this; }

    INLINE vec2 operator-(vec2i rhs) const { return vec2{x - (f32)rhs.x, y - (f32)rhs.y}; }
    INLINE vec2 operator+(vec2i rhs) const { return vec2{x + (f32)rhs.x, y + (f32)rhs.y}; }
    INLINE vec2 operator*(vec2i rhs) const { return vec2{x * (f32)rhs.x, y * (f32)rhs.y}; }
    INLINE vec2 operator/(vec2i rhs) const { return vec2{x / (f32)rhs.x, y / (f32)rhs.y}; }
    INLINE vec2& operator-=(vec2i rhs) { x -= (f32)rhs.x; y -= (f32)rhs.y; return *this; }
    INLINE vec2& operator+=(vec2i rhs) { x += (f32)rhs.x; y += (f32)rhs.y; return *this; }
    INLINE vec2& operator*=(vec2i rhs) { x *= (f32)rhs.x; y *= (f32)rhs.y; return *this; }
    INLINE vec2& operator/=(vec2i rhs) { x /= (f32)rhs.x; y /= (f32)rhs.y; return *this; }
    INLINE vec2 operator-(i32 rhs) const { return vec2{x - (f32)rhs, y - (f32)rhs}; }
    INLINE vec2 operator+(i32 rhs) const { return vec2{x + (f32)rhs, y + (f32)rhs}; }
    INLINE vec2 operator*(i32 rhs) const { return vec2{x * (f32)rhs, y * (f32)rhs}; }
    INLINE vec2 operator/(i32 rhs) const { return vec2{x / (f32)rhs, y / (f32)rhs}; }
    INLINE vec2& operator-=(i32 rhs) { x -= (f32)rhs; y -= (f32)rhs; return *this; }
    INLINE vec2& operator+=(i32 rhs) { x += (f32)rhs; y += (f32)rhs; return *this; }
    INLINE vec2& operator*=(i32 rhs) { x *= (f32)rhs; y *= (f32)rhs; return *this; }
    INLINE vec2& operator/=(i32 rhs) { x /= (f32)rhs; y /= (f32)rhs; return *this; }

    INLINE bool nonZero() const { return x != 0.0f || y != 0.0f; }
    INLINE vec2 perp() const { return vec2{-y, x}; }
    INLINE f32 min() const { return x < y ? x : y; }
    INLINE f32 max() const { return x > y ? x : y; }
    INLINE f32 dot(vec2 rhs) const { return (x * rhs.x) + (y * rhs.y); }
    INLINE f32 cross(vec2 rhs) const { return (x * rhs.y) - (y * rhs.x); }
    INLINE f32 length() const { return sqrtf(x*x + y*y); }
    INLINE f32 squaredLength() const { return x*x + y*y; }
    INLINE vec2 cloned() const { return vec2{x, y}; }
    INLINE vec2 normalized() const { f32 f = sqrtf(x*x + y*y); return vec2{x * f, y * f}; }
    INLINE f32 clampedDot(vec2 rhs) const { f32 r = x*rhs.x + y*rhs.y; r = r < 0 ? 0 : r; return r > 1 ? 1 : r; }
    INLINE vec2 clampedToZero() const { return vec2{x > 0.0f ? x : 0.0f, y > 0.0f ? y : 0.0f }; }
    INLINE vec2 clampedToUpper(vec2 upper) const { return vec2{x < upper.x ? x : upper.x, y < upper.y ? y : upper.y }; }
    INLINE vec2 clampedToRange(const f32 min_value, const f32 max_value) const {
        vec2 out{x > min_value ? x : min_value, y > min_value ? y : min_value};
        out.x = out.x < max_value ? out.x : max_value;
        out.y = out.y < max_value ? out.y : max_value;
        return *this;
    }
    INLINE vec2 reflectAround(vec2 N) const {
        f32 f = -2 * (x * N.x + y * N.y);
        return vec2{
                fast_mul_add(N.x, f, x),
                fast_mul_add(N.y, f, y)
        };
    }
    INLINE vec2 clamped() const {
        vec2 out{x > 0.0f ? x : 0.0f, y > 0.0f ? y : 0.0f};
        out.x = out.x < 1.0f ? out.x : 1.0f;
        out.y = out.y < 1.0f ? out.y : 1.0f;
        return *this;
    }
    INLINE vec2 approachTo(vec2 trg, f32 diff) const {
        return vec2{
                approach(x, trg.x, diff),
                approach(y, trg.y, diff)
        };
    }
    INLINE vec2 scaleAdd(f32 factor, vec2 to_be_added) const {
        return vec2{
                fast_mul_add(x, factor, to_be_added.x),
                fast_mul_add(y, factor, to_be_added.y)
        };
    }
};

INLINE vec2 min(vec2 a, vec2 b) { return vec2{a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y}; }
INLINE vec2 max(vec2 a, vec2 b) { return vec2{a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y}; }

INLINE vec2i operator-(vec2i lhs, vec2 rhs) { return vec2i{lhs.x - (i32)rhs.x, lhs.y - (i32)rhs.y}; }
INLINE vec2i operator+(vec2i lhs, vec2 rhs) { return vec2i{lhs.x + (i32)rhs.x, lhs.y + (i32)rhs.y}; }
INLINE vec2i operator*(vec2i lhs, vec2 rhs) { return vec2i{lhs.x * (i32)rhs.x, lhs.y * (i32)rhs.y}; }
INLINE vec2i operator/(vec2i lhs, vec2 rhs) { return vec2i{lhs.x / (i32)rhs.x, lhs.y / (i32)rhs.y}; }

INLINE vec2i operator-(i32 lhs, vec2 rhs) { return vec2i{lhs - (i32)rhs.x, lhs - (i32)rhs.y}; }
INLINE vec2i operator+(i32 lhs, vec2 rhs) { return vec2i{lhs + (i32)rhs.x, lhs + (i32)rhs.y}; }
INLINE vec2i operator*(i32 lhs, vec2 rhs) { return vec2i{lhs * (i32)rhs.x, lhs * (i32)rhs.y}; }
INLINE vec2i operator/(i32 lhs, vec2 rhs) { return vec2i{lhs / (i32)rhs.x, lhs / (i32)rhs.y}; }

INLINE vec2i operator-(i32 lhs, vec2i rhs) { return vec2i{lhs - rhs.x, lhs - rhs.y}; }
INLINE vec2i operator+(i32 lhs, vec2i rhs) { return vec2i{lhs + rhs.x, lhs + rhs.y}; }
INLINE vec2i operator*(i32 lhs, vec2i rhs) { return vec2i{lhs * rhs.x, lhs * rhs.y}; }
INLINE vec2i operator/(i32 lhs, vec2i rhs) { return vec2i{lhs / rhs.x, lhs / rhs.y}; }

INLINE vec2 operator-(f32 lhs, vec2 rhs) { return vec2{lhs - rhs.x, lhs - rhs.y}; }
INLINE vec2 operator+(f32 lhs, vec2 rhs) { return vec2{lhs + rhs.x, lhs + rhs.y}; }
INLINE vec2 operator*(f32 lhs, vec2 rhs) { return vec2{lhs * rhs.x, lhs * rhs.y}; }
INLINE vec2 operator/(f32 lhs, vec2 rhs) { return vec2{lhs / rhs.x, lhs / rhs.y}; }

struct mat2 {
    union {
        vec2 axis[2];
        struct {
            vec2 X, Y;
        };
    };

    explicit mat2(vec2 x, vec2 y) : X(x), Y(y) {}
};

INLINE vec2 operator*(vec2 v, mat2 m) { return vec2{v.x*m.X.x + v.y*m.Y.x, v.x*m.X.y + v.y*m.Y.y}; }
INLINE mat2 outer(vec2 a, vec2 b) { return mat2{vec2{a.x*b.x, a.y*b.x}, vec2{a.x*b.y, a.y*b.y}}; }

#else
struct vec2  { f32 x = 0, y = 0; };
struct vec2i { i32 x = 0, y = 0; };
#endif

struct Rect {
    vec2i min, max;
    Rect() : min(vec2i{0,0,}), max(vec2i{0,0,}) {}
    explicit Rect(vec2i min, vec2i max) : min(min), max(max) {}
    INLINE bool contains(vec2i p) const { return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y; }
    INLINE bool bounds(vec2i p) const { return p.x > min.x && p.x < max.x && p.y > min.y && p.y < max.y; }
    INLINE bool is_zero() const { return min.x == max.x && min.y == max.y; }
    INLINE bool operator!() const { return is_zero(); }
    INLINE bool operator[](vec2i p) const { return contains(p); }
    INLINE bool operator()(vec2i p) const { return bounds(p); }
};

INLINE Rect operator>>(vec2i min, vec2i max) { return Rect{min, max}; }
INLINE Rect operator<<(vec2i max, vec2i min) { return Rect{min, max}; }

struct RangeI {
    i32 from = 0, to = 0;
    RangeI() : from(0), to(0) {}
    explicit RangeI(i32 from, i32 to) : from(from), to(to) {}
    INLINE bool contains(i32 v) const { return from <= v && v <= to; }
    INLINE bool bounds(i32 v) const { return from < v && v < to; }
    INLINE bool is_zero() const { return from == 0 && to == 0; }
    INLINE bool operator!() const { return is_zero(); }
    INLINE bool operator[](i32 v) const { return contains(v); }
    INLINE bool operator()(i32 v) const { return bounds(v); }
};

struct Range {
    f32 from = 0, to = 0;
    Range() : from(0), to(0) {}
    explicit Range(f32 from, f32 to) : from(from), to(to) {}
    INLINE bool contains(f32 v) const { return from <= v && v <= to; }
    INLINE bool bounds(f32 v) const { return from < v && v < to; }
    INLINE bool is_zero() const { return from == 0 && to == 0; }
    INLINE bool operator!() const { return is_zero(); }
    INLINE bool operator[](f32 v) const { return contains(v); }
    INLINE bool operator()(f32 v) const { return bounds(v); }
};

struct RGBA { u8 B, G, R, A; };
union  Pixel { RGBA color; u32 value; };

void swap(i32 *a, i32 *b) {
    i32 t = *a;
    *a = *b;
    *b = t;
}

void subRange(i32 from, i32 to, i32 end, i32 start, i32 *first, i32 *last) {
    *first = from;
    *last  = to;
    if (to < from) swap(first, last);
    *first = *first > start ? *first : start;
    *last  = (*last < end ? *last : end) - 1;
}

INLINE bool inRange(i32 value, i32 end, i32 start = 0) {
    return start <= value && value < end;
}

enum ColorID {
    Black,
    White,
    Grey,

    Red,
    Green,
    Blue,

    Cyan,
    Magenta,
    Yellow
};

RGBA Color(enum ColorID color_id) {
    RGBA color;
    color.A = MAX_COLOR_VALUE;

    switch (color_id) {
        case Black:
            color.R = 0;
            color.G = 0;
            color.B = 0;
            break;
        case White:
            color.R = MAX_COLOR_VALUE;
            color.G = MAX_COLOR_VALUE;
            color.B = MAX_COLOR_VALUE;

            break;
        case Grey:
            color.R = MAX_COLOR_VALUE/2;
            color.G = MAX_COLOR_VALUE/2;
            color.B = MAX_COLOR_VALUE/2;
            break;

        case Red:
            color.R = MAX_COLOR_VALUE;
            color.G = 0;
            color.B = 0;
            break;
        case Green:
            color.R = 0;
            color.G = MAX_COLOR_VALUE;
            color.B = 0;
            break;
        case Blue:
            color.R = 0;
            color.G = 0;
            color.B = MAX_COLOR_VALUE;
            break;

        case Cyan:
            color.R = 0;
            color.G = MAX_COLOR_VALUE;
            color.B = MAX_COLOR_VALUE;
            break;
        case Magenta:
            color.R = MAX_COLOR_VALUE;
            color.G = 0;
            color.B = MAX_COLOR_VALUE;
            break;
        case Yellow:
            color.R = MAX_COLOR_VALUE;
            color.G = MAX_COLOR_VALUE;
            color.B = 0;
            break;
    }

    return color;
}

struct String {
    u32 length;
    char *char_ptr;
    void set(char *CharPtr) {
        char_ptr = CharPtr;
        length = 0;
        if (CharPtr)
            while (CharPtr[length])
                length++;
    }

    void copyFrom(char* CharPtr, u32 offset) {
        length = offset;
        char *source_char = CharPtr;
        char *string_char = char_ptr + offset;
        while (source_char[0]) {
            *string_char = *source_char;
            string_char++;
            source_char++;
            length++;
        }
        *string_char = 0;
    }

    String& operator=(char* CharPtr) {
        copyFrom(CharPtr, 0);
        return *this;
    }

    static u32 getLength(char *string) {
        char *ptr = string;
        u32 length = 0;
        if (ptr) while (ptr[length]) length++;
        return length;
    }
};

struct NumberString {
    char _buffer[13];
    String string;

    NumberString() {
        string.char_ptr = _buffer;
        string.length = 1;
        _buffer[12] = 0;
        for (u8 i = 0; i < 12; i++)
            _buffer[i] = ' ';
    }

    NumberString& operator=(i32 number) {
        set(number);
        return *this;
    }

    NumberString& operator=(f32 number) {
        set(number);
        return *this;
    }

    void set(i32 number) {
        char *buffer = _buffer;
        buffer[12] = 0;

        bool is_negative = number < 0;
        if (is_negative) number = -number;

        if (number) {
            u32 temp;
            buffer += 11;
            string.char_ptr = buffer;
            string.length = 0;

            for (u8 i = 0; i < 11; i++) {
                temp = number;
                number /= 10;
                string.length++;
                *buffer-- = (char)('0' + temp - number * 10);
                if (!number) {
                    if (is_negative) {
                        *buffer = '-';
                        string.char_ptr--;
                        string.length++;
                    }

                    break;
                }
                string.char_ptr--;
            }
        } else {
            buffer[11] = '0';
            string.length = 1;
            string.char_ptr = buffer + 11;
        }
    }

    void set(f32 number, u8 float_digits_count = 3) {
        f32 factor = 1;
        for (u8 i = 0; i < float_digits_count; i++) factor *= 10;
        i32 int_num = (i32)(number * factor);
        if (int_num == 0) {
            set((i32)factor);
            string.length++;
            string.char_ptr[0] = '.';
            string.char_ptr--;
            string.char_ptr[0] = '0';
            return;
        }

        bool is_negative = number < 0;
        bool is_fraction = is_negative ? number > -1 : number < 1;

        set(int_num);

        if (is_fraction) {
            u32 len = string.length;
            string.length++;
            string.char_ptr--;
            if (is_negative) {
                string.char_ptr[0] = '-';
                string.char_ptr[1] = '0';
            } else
                string.char_ptr[0] = '0';

            if (len < float_digits_count) {
                for (u32 i = 0; i < (float_digits_count - len); i++) {
                    string.length++;
                    string.char_ptr--;
                    string.char_ptr[0] = '0';
                }
            }
        }

        static char tmp[13];
        tmp[string.length + 1] = 0;
        for (u8 i = 0; i < (u8)string.length; i++) {
            u8 char_count_from_right_to_left = (u8)string.length - i - 1;
            if (char_count_from_right_to_left >= float_digits_count) tmp[i] = string.char_ptr[i];
            else                                                     tmp[i + 1] = string.char_ptr[i];
        }
        tmp[string.length - float_digits_count] = '.';
        string.copyFrom(tmp, 0);
        if (is_negative) string.length++;
    }
};

struct PerTick {
    const f64 seconds, milliseconds, microseconds, nanoseconds;
    PerTick() = delete;
    explicit PerTick(const f64 tps) :
            seconds(     1          / tps),
            milliseconds(1000       / tps),
            microseconds(1000000    / tps),
            nanoseconds( 1000000000 / tps) {}
};

typedef struct Ticks {
    const PerTick per_tick;
    const u64 per_second;
    Ticks() = delete;
    explicit Ticks(const u64 tps) : per_second(tps), per_tick((f64)tps) {}
} Ticks;

struct Timer {
    f32 delta_time = 0;
    u64 ticks_before = 0,
            ticks_after = 0,
            ticks_diff = 0,
            accumulated_ticks = 0,
            accumulated_frame_count = 0,
            ticks_of_last_report = 0,
            seconds = 0,
            milliseconds = 0,
            microseconds = 0,
            nanoseconds = 0;
    f64 average_frames_per_tick = 0,
            average_ticks_per_frame = 0;
    u16 average_frames_per_second = 0,
            average_milliseconds_per_frame = 0,
            average_microseconds_per_frame = 0,
            average_nanoseconds_per_frame = 0;

    Timer() = delete;
    Ticks *ticks = nullptr;
    explicit Timer(Ticks *tks) : ticks(tks), ticks_before(os::getTicks()), ticks_of_last_report(os::getTicks()) {};
    void accumulate() {
        ticks_diff = ticks_after - ticks_before;
        accumulated_ticks += ticks_diff;
        accumulated_frame_count++;

        seconds      = (u64)(ticks->per_tick.seconds      * (f64)(ticks_diff));
        milliseconds = (u64)(ticks->per_tick.milliseconds * (f64)(ticks_diff));
        microseconds = (u64)(ticks->per_tick.microseconds * (f64)(ticks_diff));
        nanoseconds  = (u64)(ticks->per_tick.nanoseconds  * (f64)(ticks_diff));
    }

    void average() {
        average_frames_per_tick = (f64)accumulated_frame_count / (f64)accumulated_ticks;
        average_ticks_per_frame = (f64)accumulated_ticks / (f64)accumulated_frame_count;
        average_frames_per_second = (u16)(average_frames_per_tick      * (f64)ticks->per_second);
        average_milliseconds_per_frame = (u16)(average_ticks_per_frame * ticks->per_tick.milliseconds);
        average_microseconds_per_frame = (u16)(average_ticks_per_frame * ticks->per_tick.microseconds);
        average_nanoseconds_per_frame = (u16)(average_ticks_per_frame  * ticks->per_tick.nanoseconds);
        accumulated_ticks = accumulated_frame_count = 0;
    }

    INLINE void startFrame() {
        ticks_after = ticks_before;
        ticks_before = os::getTicks();
        ticks_diff = ticks_before - ticks_after;
        delta_time = (f32)((f64)ticks_diff * ticks->per_tick.seconds);
    }

    INLINE void endFrame() {
        ticks_after = os::getTicks();
        accumulate();
        if (accumulated_ticks >= ticks->per_second / 4)
            average();
    }
};

struct Timers {
    Timer update, render, aux;
    Timers() = delete;
    explicit Timers(Ticks *ticks) : update(ticks), render(ticks), aux(ticks) {}
};

struct Time {
    Ticks ticks;
    Timers timers;
    Time() : ticks(os::ticks_per_second), timers(&ticks) {}
};


#define MAX_WIDTH 3840
#define MAX_HEIGHT 2160

#define PIXEL_SIZE 4
#define RENDER_SIZE Megabytes(8 * PIXEL_SIZE)

struct Dimensions {
    u16 width = 0, height = 0;
    u32 width_times_height;
    f32 height_over_width = 0,
            width_over_height = 0,
            f_height = 0, f_width = 0,
            h_height = 0, h_width = 0;

    Dimensions() = delete;
    explicit Dimensions(u16 Width, u16 Height) :
            width(Width),
            height(Height),
            width_times_height(Width * Height),
            f_width((f32)Width),
            f_height((f32)Height),
            h_width((f32)Width / 2.0f),
            h_height((f32)Height / 2.0f),
            width_over_height((f32)Width / (f32)Height),
            height_over_width((f32)Height / (f32)Width) {}

    void update(u16 Width, u16 Height) {
        width = Width;
        height = Height;
        width_times_height = width * height;
        f_width  = (f32)width;
        f_height = (f32)height;
        h_width  = f_width  / 2;
        h_height = f_height / 2;
        width_over_height  = f_width  / f_height;
        height_over_width  = f_height / f_width;
    }
};

struct PixelGrid {
    Pixel* pixels = nullptr;
    Dimensions dimensions;

    PixelGrid() : dimensions(MAX_WIDTH, MAX_HEIGHT) {}

    void fill(RGBA color) const {
        for (u32 i = 0; i < dimensions.width_times_height; i++)
            pixels[i].color = color;
    }

    void drawHLine2D(RGBA color, i32 from, i32 to, i32 at) {
        if (!inRange(at, dimensions.height, 0)) return;

        i32 offset = at * (i32)dimensions.width;
        i32 first, last;
        subRange(from, to, dimensions.width, 0, &first, &last);
        first += offset;
        last += offset;
        for (i32 i = first; i <= last; i++) pixels[i].color = color;
    }

    void drawVLine2D(RGBA color, i32 from, i32 to, i32 at) {
        if (!inRange(at, dimensions.width, 0)) return;
        i32 first, last;

        subRange(from, to, dimensions.height, 0, &first, &last);
        first *= dimensions.width; first += at;
        last  *= dimensions.width; last  += at;
        for (i32 i = first; i <= last; i += dimensions.width) pixels[i].color = color;
    }

    void drawLine2D(RGBA color, i32 x0, i32 y0, i32 x1, i32 y1) {
        if (x0 < 0 &&
            y0 < 0 &&
            x1 < 0 &&
            y1 < 0)
            return;

        if (x0 == x1) {
            drawVLine2D(color, y0, y1, x1);
            return;
        }

        if (y0 == y1) {
            drawHLine2D(color, x0, x1, y1);
            return;
        }

        i32 width  = (i32)dimensions.width;
        i32 height = (i32)dimensions.height;

        i32 pitch = width;
        i32 index = x0 + y0 * pitch;

        i32 run  = x1 - x0;
        i32 rise = y1 - y0;

        i32 dx = 1;
        i32 dy = 1;
        if (run < 0) {
            dx = -dx;
            run = -run;
        }
        if (rise < 0) {
            dy = -dy;
            rise = -rise;
            pitch = -pitch;
        }

        // Configure for a shallow line:
        i32 end = x1 + dx;
        i32 start1 = x0;  i32 inc1 = dx;  i32 index_inc1 = dx;
        i32 start2 = y0;  i32 inc2 = dy;  i32 index_inc2 = pitch;
        i32 rise_twice = rise + rise;
        i32 run_twice = run + run;
        i32 threshold = run;
        i32 error_dec = run_twice;
        i32 error_inc = rise_twice;
        bool is_steap = rise > run;
        if (is_steap) { // Reconfigure for a steep line:
            swap(&inc1, &inc2);
            swap(&start1, &start2);
            swap(&index_inc1, &index_inc2);
            swap(&error_dec, &error_inc);
            end = y1 + dy;
            threshold = rise;
        }

        i32 error = 0;
        i32 current1 = start1;
        i32 current2 = start2;
        while (current1 != end) {
            if (inRange(index, (i32)dimensions.width_times_height, 0)) {
                if (is_steap) {
                    if (inRange(current1, height, 0) &&
                        inRange(current2, width, 0))
                        pixels[index].color = color;
                } else {
                    if (inRange(current2, height, 0) &&
                        inRange(current1, width, 0))
                        pixels[index].color = color;
                }
            }

            index += index_inc1;
            error += error_inc;
            current1 += inc1;
            if (error > threshold) {
                error -= error_dec;
                index += index_inc2;
                current2 += inc2;
            }
        }
    }
    INLINE void drawLine(RGBA color, vec2i src, vec2i trg) {
        return drawLine2D(color, src.x, src.y, trg.x, trg.y);
    }
    void drawRect(RGBA color, Rect &rect) {
        if (rect.max.x < 0 || rect.min.x >= dimensions.width ||
            rect.max.y < 0 || rect.min.y >= dimensions.height)
            return;

        drawHLine2D(color, rect.min.x, rect.max.x, rect.min.y);
        drawHLine2D(color, rect.min.x, rect.max.x, rect.max.y);
        drawVLine2D(color, rect.min.y, rect.max.y, rect.min.x);
        drawVLine2D(color, rect.min.y, rect.max.y, rect.max.x);
    }

    void fillRect(RGBA color, const Rect &rect) {
        if (rect.max.x < 0 || rect.min.x >= dimensions.width ||
            rect.max.y < 0 || rect.min.y >= dimensions.height)
            return;

        i32 min_x, min_y, max_x, max_y;
        subRange(rect.min.x, rect.max.x, dimensions.width,  0, &min_x, &max_x);
        subRange(rect.min.y, rect.max.y, dimensions.height, 0, &min_y, &max_y);
        for (i32 y = min_y; y <= max_y; y++)
            drawHLine2D(color, min_x, max_x, y);
    }

    void fillTriangle(RGBA color, f32 *X, f32 *Y) {
        u16 W = dimensions.width;
        u16 H = dimensions.height;
        f32 dx1, x1, y1, xs,
                dx2, x2, y2, xe,
                dx3, x3, y3, dy;
        i32 offset,
                x, x1i, y1i, x2i, xsi, ysi = 0,
                y, y2i, x3i, y3i, xei, yei = 0;
        for (u8 i = 1; i <= 2; i++) {
            if (Y[i] < Y[ysi]) ysi = i;
            if (Y[i] > Y[yei]) yei = i;
        }
        u8 id[3];
        if (ysi) {
            if (ysi == 1) {
                id[0] = 1;
                id[1] = 2;
                id[2] = 0;
            } else {
                id[0] = 2;
                id[1] = 0;
                id[2] = 1;
            }
        } else {
            id[0] = 0;
            id[1] = 1;
            id[2] = 2;
        }
        x1 = X[id[0]]; y1 = Y[id[0]]; x1i = (i32)x1; y1i = (i32)y1;
        x2 = X[id[1]]; y2 = Y[id[1]]; x2i = (i32)x2; y2i = (i32)y2;
        x3 = X[id[2]]; y3 = Y[id[2]]; x3i = (i32)x3; y3i = (i32)y3;
        dx1 = x1i == x2i || y1i == y2i ? 0 : (x2 - x1) / (y2 - y1);
        dx2 = x2i == x3i || y2i == y3i ? 0 : (x3 - x2) / (y3 - y2);
        dx3 = x1i == x3i || y1i == y3i ? 0 : (x3 - x1) / (y3 - y1);
        dy = 1 - (y1 - (f32)y1);
        xs = dx3 ? x1 + dx3 * dy : x1; ysi = (i32)Y[ysi];
        xe = dx1 ? x1 + dx1 * dy : x1; yei = (i32)Y[yei];
        offset = W * y1i;
        for (y = ysi; y < yei; y++) {
            if (y == y3i) xs = dx2 ? (x3 + dx2 * (1 - (y3 - (f32)y3i))) : x3;
            if (y == y2i) xe = dx2 ? (x2 + dx2 * (1 - (y2 - (f32)y2i))) : x2;
            xsi = (i32)xs;
            xei = (i32)xe;
            for (x = xsi; x < xei; x++) {
                if (x > 0 && x < W && y > 0 && y < H)
                    pixels[offset + x].color = color;
            }
            offset += W;
            xs += y < y3i ? dx3 : dx2;
            xe += y < y2i ? dx1 : dx2;
        }
    }

    void drawCircle(RGBA color, i32 center_x, i32 center_y, i32 radius) const {
        if (radius <= 1) {
            if (inRange(0, center_x, dimensions.width - 1) &&
                inRange(0, center_y, dimensions.height - 1))
                pixels[dimensions.width * center_y + center_x].color = color;

            return;
        }

        i32 width = (i32)dimensions.width;
        i32 size  = (i32)dimensions.width_times_height;

        i32 x = radius, y = 0, y2 = 0;
        i32 r2 = radius * radius;
        i32 x2 = r2;

        i32 Sx1 = center_x - radius;
        i32 Ex1 = center_x + radius;
        i32 Sy1 = center_y * width;
        i32 Ey1 = Sy1;

        i32 Sx2 = center_x;
        i32 Ex2 = center_x;
        i32 Sy2 = (center_y - radius) * width;
        i32 Ey2 = (center_y + radius) * width;

        while (y <= x) {
            if (Sy1 >= 0 && Sy1 < size) {
                if (Sx1 >= 0 && Sx1 < width) pixels[Sy1 + Sx1].color = color;
                if (Ex1 >= 0 && Ex1 < width) pixels[Sy1 + Ex1].color = color;
            }
            if (Ey1 >= 0 && Ey1 < size) {
                if (Sx1 >= 0 && Sx1 < width) pixels[Ey1 + Sx1].color = color;
                if (Ex1 >= 0 && Ex1 < width) pixels[Ey1 + Ex1].color = color;
            }

            if (Sy2 >= 0 && Sy2 < size) {
                if (Sx2 >= 0 && Sx2 < width) pixels[Sy2 + Sx2].color = color;
                if (Ex2 >= 0 && Ex2 < width) pixels[Sy2 + Ex2].color = color;
            }
            if (Ey2 >= 0 && Ey2 < size) {
                if (Sx2 >= 0 && Sx2 < width) pixels[Ey2 + Sx2].color = color;
                if (Ex2 >= 0 && Ex2 < width) pixels[Ey2 + Ex2].color = color;
            }

            if ((x2 + y2) > r2) {
                x -= 1;
                x2 = x * x;

                Sx1 += 1;
                Ex1 -= 1;

                Sy2 += width;
                Ey2 -= width;
            }

            y += 1;
            y2 = y * y;

            Sy1 -= width;
            Ey1 += width;

            Sx2 -= 1;
            Ex2 += 1;
        }
    }
    INLINE void drawCircle(RGBA color, vec2i center, i32 radius) const {
        return drawCircle(color, center.x, center.y, radius);
    }
    void fillCircle(RGBA color, i32 center_x, i32 center_y, i32 radius) const {
        if (radius <= 1) {
            if (inRange(0, center_x, dimensions.width - 1) &&
                inRange(0, center_y, dimensions.height - 1))
                pixels[dimensions.width * center_y + center_x].color = color;

            return;
        }

        i32 width = (i32)dimensions.width;
        i32 size  = (i32)dimensions.width_times_height;

        i32 x = radius, y = 0, y2 = 0;
        i32 r2 = radius * radius;
        i32 x2 = r2;

        i32 Sx1 = center_x - radius;
        i32 Ex1 = center_x + radius;
        i32 Sy1 = center_y * width;
        i32 Ey1 = Sy1;

        i32 Sx2 = center_x;
        i32 Ex2 = center_x;
        i32 Sy2 = (center_y - radius) * width;
        i32 Ey2 = (center_y + radius) * width;

        i32 i, start, end;

        while (y <= x) {
            start = Sx1 > 0 ? Sx1 : 0;
            end   = Ex1 < (width - 1) ? Ex1 : (width - 1);
            if (Sy1 >= 0 && Sy1 < size) for (i = start; i <= end; i++) pixels[Sy1 + i].color = color;
            if (Ey1 >= 0 && Ey1 < size) for (i = start; i <= end; i++) pixels[Ey1 + i].color = color;

            start = Sx2 > 0 ? Sx2 : 0;
            end   = Ex2 < (width - 1) ? Ex2 : (width - 1);
            if (Sy2 >= 0 && Sy2 < size) for (i = start; i <= end; i++) pixels[Sy2 + i].color = color;
            if (Ey2 >= 0 && Ey2 < size) for (i = start; i <= end; i++) pixels[Ey2 + i].color = color;

            if ((x2 + y2) > r2) {
                x -= 1;
                x2 = x * x;

                Sx1 += 1;
                Ex1 -= 1;

                Sy2 += width;
                Ey2 -= width;
            }

            y += 1;
            y2 = y * y;

            Sy1 -= width;
            Ey1 += width;

            Sx2 -= 1;
            Ex2 += 1;
        }
    }
    INLINE void fillCircle(RGBA color, vec2i center, i32 radius) const {
        return fillCircle(color, center.x, center.y, radius);
    }
    void drawText(RGBA color, char *str, i32 x, i32 y) const {
        if (x < 0 || x > dimensions.width - FONT_WIDTH ||
            y < 0 || y > dimensions.height - FONT_HEIGHT)
            return;

        u16 current_x = (u16)x;
        u16 current_y = (u16)y;
        u16 t_offset;
        u16 pixel_line_step = dimensions.width - FONT_WIDTH;
        u32 char_line_step  = dimensions.width * LINE_HEIGHT;
        Pixel* pixel = pixels + dimensions.width * y + x;
        Pixel* character_pixel;
        u8* byte;
        char character = *str;

        while (character) {
            if (character == '\n') {
                if (current_y + FONT_HEIGHT > dimensions.height)
                    break;

                pixel += char_line_step - current_x + x;
                current_x = (u16)x;
                current_y += LINE_HEIGHT;
            } else if (character == '\t') {
                t_offset = FONT_WIDTH * (4 - ((current_x / FONT_WIDTH) & 3));
                current_x += t_offset;
                pixel += t_offset;
            } else if (character >= FIRST_CHARACTER_CODE &&
                       character <= LAST_CHARACTER_CODE) {
                byte = Font + FONT_WIDTH*(character - FIRST_CHARACTER_CODE);
                character_pixel = pixel;
                for (int h = 0; h < FONT_HEIGHT ; h++) {
                    for (int w = 0; w < FONT_WIDTH; w++) {
                        /* skip background bits */
                        if (*byte & (0x80 >> w))
                            character_pixel->color = color;

                        character_pixel++;
                    }
                    byte++;
                    character_pixel += pixel_line_step;
                }

                pixel += FONT_WIDTH;
                current_x += FONT_WIDTH;
                if (current_x + FONT_WIDTH > dimensions.width)
                    return;
            }
            character = *++str;
        }
    }

    void drawNumber(RGBA color, i32 number, i32 x, i32 y) {
        static NumberString number_string;
        number_string = number;
        drawText(color, number_string.string.char_ptr, x - (i32)number_string.string.length * FONT_WIDTH, y);
    }
};

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

struct Memory {
    u8* address = nullptr;
    u64 capacity = 0;
    u64 occupied = 0;

    void init(u8* Address, const u64 Capacity) {
        address = Address;
        capacity = Capacity;
    }
    void* allocate(u64 size) {
        if (!address) return nullptr;
        occupied += size;
        if (occupied > capacity) return nullptr;

        void* current_address = address;
        address += size;
        return current_address;
    }
};

struct MouseButton {
    vec2i down_pos, up_pos, double_click_pos;
    bool is_pressed = false,
            is_handled = false,
            double_clicked = false;

    void down(i32 x, i32 y) {
        is_pressed = true;
        is_handled = false;

        down_pos.x = x;
        down_pos.y = y;
    }

    void up(i32 x, i32 y) {
        is_pressed = false;
        is_handled = false;

        up_pos.x = x;
        up_pos.y = y;
    }

    void doubleClick(i32 x, i32 y) {
        double_clicked = true;
        double_click_pos.x = x;
        double_click_pos.y = y;
    }
};

struct Mouse {
    MouseButton middle_button, right_button, left_button;
    vec2i pos, pos_raw_diff, movement;
    f32 wheel_scroll_amount = 0;
    bool moved = false, is_captured = false,
            move_handled = false,
            double_clicked = false,
            double_clicked_handled = false,
            wheel_scrolled = false,
            wheel_scroll_handled = false,
            raw_movement_handled = false;

    void resetChanges() {
        if (move_handled) {
            move_handled = false;
            moved = false;
        }
        if (double_clicked_handled) {
            double_clicked_handled = false;
            double_clicked = false;
        }
        if (raw_movement_handled) {
            raw_movement_handled = false;
            pos_raw_diff.x = 0;
            pos_raw_diff.y = 0;
        }
        if (wheel_scroll_handled) {
            wheel_scroll_handled = false;
            wheel_scrolled = false;
            wheel_scroll_amount = 0;
        }
    }

    void scroll(f32 amount) {
        wheel_scroll_amount += amount * 100;
        wheel_scrolled = true;
    }

    void setPosition(i32 x, i32 y) {
        pos.x = x;
        pos.y = y;
    }

    void move(i32 x, i32 y) {
        movement.x = x - pos.x;
        movement.y = y - pos.y;
        moved = true;
    }

    void moveRaw(i32 x, i32 y) {
        pos_raw_diff.x += x;
        pos_raw_diff.y += y;
        moved = true;
    }
};

struct KeyMap {
    u8 ctrl = 0,
       alt = 0,
       shift = 0,
       space = 0,
       tab = 0;
};
struct IsPressed {
    bool ctrl = false,
         alt = false,
         shift = false,
         space = false,
         tab = false;
};
struct Controls {
    KeyMap key_map;
    IsPressed is_pressed;
    Mouse mouse;
};


struct SlimApp {
    Controls controls;
    PixelGrid window_content;
    Time time;

    bool is_running = true;
    void *user_data = nullptr;
    char* window_title = (char*)"";
    u16 window_width = 480,
            window_height = 360;
    u64 additional_memory_size = 0;

    virtual bool OnReady() { return true; }
    virtual void OnWindowRedraw() {};
    virtual void OnWindowResize(u16 width, u16 height) {};
    virtual void OnKeyChanged(  u8 key, bool pressed) {};
    virtual void OnMouseButtonUp(  MouseButton *mouse_button) {};
    virtual void OnMouseButtonDown(MouseButton *mouse_button) {};
    virtual void OnMouseButtonDoubleClicked(MouseButton *mouse_button) {};
    virtual void OnMouseWheelScrolled(f32 amount) {};
    virtual void OnMousePositionSet(i32 x, i32 y) {};
    virtual void OnMouseMovementSet(i32 x, i32 y) {};
    virtual void OnMouseRawMovementSet(i32 x, i32 y) {};

    bool initMemory(u64 size) {
        if (memory.address) return false;

        void* memory_address = os::getMemory(size);
        if (!memory_address) {
            is_running = false;
            return false;
        }

        memory.init((u8*)memory_address, size);
        return true;
    }

    void* allocateMemory(u64 size) {
        void *new_memory = memory.allocate(size);
        if (new_memory) return new_memory;

        is_running = false;
        return nullptr;
    }

private:
    Memory memory;
};

SlimApp* createApp();
SlimApp *app;

#ifdef __linux__
    //linux code goes here
#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef NDEBUG
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <new.h>

void DisplayError(LPTSTR lpszFunction) {
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    unsigned int last_error = GetLastError();

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, last_error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf, 0, nullptr);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

    if (FAILED( StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                                TEXT("%s failed with error code %d as follows:\n%s"), lpszFunction, last_error, lpMsgBuf)))
        printf("FATAL ERROR: Unable to output error code.\n");

    _tprintf(TEXT((LPTSTR)"ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
#endif

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

WNDCLASSA window_class;
HWND window;
HDC win_dc;
BITMAPINFO info;
RECT win_rect;
RAWINPUT raw_inputs;
HRAWINPUT raw_input_handle;
RAWINPUTDEVICE raw_input_device;
UINT raw_input_size;
PUINT raw_input_size_ptr = (PUINT)(&raw_input_size);
UINT raw_input_header_size = sizeof(RAWINPUTHEADER);

inline UINT getRawInput(LPVOID data) {
    return GetRawInputData(raw_input_handle, RID_INPUT, data, raw_input_size_ptr, raw_input_header_size);
}
inline bool hasRawInput() {
    return getRawInput(0) == 0 && raw_input_size != 0;
}
inline bool hasRawMouseInput(LPARAM lParam) {
    raw_input_handle = (HRAWINPUT)(lParam);
    return (
            hasRawInput() &&
            getRawInput((LPVOID)&raw_inputs) == raw_input_size &&
            raw_inputs.header.dwType == RIM_TYPEMOUSE
    );
}

LARGE_INTEGER performance_counter;

void os::setWindowTitle(char* str) {
    SetWindowTextA(window, str);
}

void os::setCursorVisibility(bool on) {
    ShowCursor(on);
}

void os::setWindowCapture(bool on) {
    if (on) SetCapture(window);
    else ReleaseCapture();
}

u64 os::getTicks() {
    QueryPerformanceCounter(&performance_counter);
    return (u64)performance_counter.QuadPart;
}

void* os::getMemory(u64 size) {
    return VirtualAlloc((LPVOID)MEMORY_BASE, (SIZE_T)size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

void os::closeFile(void *handle) {
    CloseHandle(handle);
}

void* os::openFileForReading(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_READ,          // open for reading
                               FILE_SHARE_READ,       // share for reading
                               nullptr,                  // default security
                               OPEN_EXISTING,         // existing file only
                               FILE_ATTRIBUTE_NORMAL, // normal file
                               nullptr);                 // no attr. template
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), path);
        return nullptr;
    }
#endif
    return handle;
}

void* os::openFileForWriting(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_WRITE,          // open for writing
                               0,                      // do not share
                               nullptr,                   // default security
                               OPEN_ALWAYS,            // create new or open existing
                               FILE_ATTRIBUTE_NORMAL,  // normal file
                               nullptr);
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for write.\n"), path);
        return nullptr;
    }
#endif
    return handle;
}

bool os::readFromFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_read = 0;
    BOOL result = ReadFile(handle, out, size, &bytes_read, nullptr);
#ifndef NDEBUG
    if (result == FALSE) {
        DisplayError(TEXT((LPTSTR)"ReadFile"));
        printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", (unsigned int)GetLastError());
        CloseHandle(handle);
    }
#endif
    return result != FALSE;
}

bool os::writeToFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_written = 0;
    BOOL result = WriteFile(handle, out, size, &bytes_written, nullptr);
#ifndef NDEBUG
    if (result == FALSE) {
        DisplayError(TEXT((LPTSTR)"WriteFile"));
        printf("Terminal failure: Unable to write from file.\n GetLastError=%08x\n", (unsigned int)GetLastError());
        CloseHandle(handle);
    }
#endif
    return result != FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    MouseButton *mouse_button;
    IsPressed *is_pressed = &app->controls.is_pressed;
    bool pressed = message == WM_SYSKEYDOWN || message == WM_KEYDOWN;
    u8 key = (u8)wParam;
    i32 x, y;
    f32 scroll_amount;

    switch (message) {
        case WM_DESTROY:
            app->is_running = false;
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            GetClientRect(window, &win_rect);

            info.bmiHeader.biWidth = win_rect.right - win_rect.left;
            info.bmiHeader.biHeight = win_rect.top - win_rect.bottom;
            app->window_content.dimensions.update((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            app->OnWindowResize((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            app->OnWindowRedraw();

            break;

        case WM_PAINT:
            SetDIBitsToDevice(win_dc,
                              0, 0, app->window_content.dimensions.width, app->window_content.dimensions.height,
                              0, 0, 0, app->window_content.dimensions.height,
                              (u32*)app->window_content.pixels, &info, DIB_RGB_COLORS);

            ValidateRgn(window, nullptr);
            break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
            switch (key) {
                case VK_CONTROL: is_pressed->ctrl  = pressed; break;
                case VK_MENU   : is_pressed->alt   = pressed; break;
                case VK_SHIFT  : is_pressed->shift = pressed; break;
                case VK_SPACE  : is_pressed->space = pressed; break;
                case VK_TAB    : is_pressed->tab   = pressed; break;
                default: break;
            }
            app->OnKeyChanged(key, pressed);

            break;

        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_LBUTTONDBLCLK:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);

            switch (message) {
                case WM_MBUTTONUP:
                case WM_MBUTTONDOWN:
                case WM_MBUTTONDBLCLK: mouse_button = &app->controls.mouse.middle_button; break;
                case WM_RBUTTONUP:
                case WM_RBUTTONDOWN:
                case WM_RBUTTONDBLCLK: mouse_button = &app->controls.mouse.right_button; break;
                default: mouse_button = &app->controls.mouse.left_button;
            }

            switch (message) {
                case WM_MBUTTONDBLCLK:
                case WM_RBUTTONDBLCLK:
                case WM_LBUTTONDBLCLK: mouse_button->doubleClick(x, y); app->controls.mouse.double_clicked = true; app->OnMouseButtonDoubleClicked(mouse_button); break;
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                case WM_LBUTTONUP:     mouse_button->up(x, y);   app->OnMouseButtonUp(mouse_button); break;
                default:               mouse_button->down(x, y); app->OnMouseButtonDown(mouse_button); break;
            }

            break;

        case WM_MOUSEWHEEL:
            scroll_amount = (f32)(GET_WHEEL_DELTA_WPARAM(wParam)) / (f32)(WHEEL_DELTA);
            app->controls.mouse.scroll(scroll_amount); app->OnMouseWheelScrolled(scroll_amount);
            break;

        case WM_MOUSEMOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            app->controls.mouse.move(x, y);        app->OnMouseMovementSet(x, y);
            app->controls.mouse.setPosition(x, y); app->OnMousePositionSet(x, y);
            break;

        case WM_INPUT:
            if ((hasRawMouseInput(lParam)) && (
                    raw_inputs.data.mouse.lLastX != 0 ||
                    raw_inputs.data.mouse.lLastY != 0)) {
                x = raw_inputs.data.mouse.lLastX;
                y = raw_inputs.data.mouse.lLastY;
                app->controls.mouse.moveRaw(x, y); app->OnMouseRawMovementSet(x, y);
            }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
    void* window_content_memory = GlobalAlloc(GPTR, RENDER_SIZE);
    if (!window_content_memory)
        return -1;

    LARGE_INTEGER performance_frequency;
    QueryPerformanceFrequency(&performance_frequency);
    os::ticks_per_second = (u64)performance_frequency.QuadPart;

    app = createApp();
    app->window_content.pixels = (Pixel*)window_content_memory;
    app->controls.key_map.ctrl = VK_CONTROL;
    app->controls.key_map.alt = VK_MENU;
    app->controls.key_map.shift = VK_SHIFT;
    app->controls.key_map.space = VK_SPACE;
    app->controls.key_map.tab = VK_TAB;
    if (!app->OnReady()) return -1;

    info.bmiHeader.biSize        = sizeof(info.bmiHeader);
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biBitCount    = 32;
    info.bmiHeader.biPlanes      = 1;

    window_class.lpszClassName  = "RnDer";
    window_class.hInstance      = hInstance;
    window_class.lpfnWndProc    = WndProc;
    window_class.style          = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
    window_class.hCursor        = LoadCursorA(nullptr, IDC_ARROW);

    if (!RegisterClassA(&window_class)) return -1;

    win_rect.top = 0;
    win_rect.left = 0;
    win_rect.right  = app->window_width;
    win_rect.bottom = app->window_height;
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    window = CreateWindowA(
            window_class.lpszClassName,
            app->window_title,
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,
            CW_USEDEFAULT,
            win_rect.right - win_rect.left,
            win_rect.bottom - win_rect.top,

            nullptr,
            nullptr,
            hInstance,
            nullptr
    );
    if (!window)
        return -1;

    raw_input_device.usUsagePage = 0x01;
    raw_input_device.usUsage = 0x02;
    if (!RegisterRawInputDevices(&raw_input_device, 1, sizeof(raw_input_device)))
        return -1;

    win_dc = GetDC(window);

    SetICMMode(win_dc, ICM_OFF);

    ShowWindow(window, nCmdShow);

    MSG message;
    while (app->is_running) {
        while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        app->OnWindowRedraw();
        InvalidateRgn(window, nullptr, false);
    }

    return 0;
}

#endif