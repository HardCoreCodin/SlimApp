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