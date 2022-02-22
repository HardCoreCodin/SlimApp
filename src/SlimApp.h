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

#include <cmath>

INLINE f32 clampedValue(f32 value, f32 from, f32 to) {
    f32 mn = value < to ? value : to;
    return mn > from ? mn : from;
}

INLINE i32 clampedValue(i32 value, i32 from, i32 to) {
    i32 mn = value < to ? value : to;
    return mn > from ? mn : from;
}

INLINE f32 clampedValue(f32 value, f32 to) {
    return value < to ? value : to;
}

INLINE i32 clampedValue(i32 value, i32 to) {
    return value < to ? value : to;
}

INLINE f32 clampedValue(f32 value) {
    f32 mn = value < 1.0f ? value : 1.0f;
    return mn > 0.0f ? mn : 0.0f;
}

INLINE i32 clampedValue(i32 value) {
    i32 mn = value < 1 ? value : 1;
    return mn > 0 ? mn : 0;
}


#ifdef SLIM_APP__INCLUDE_MATH

struct vec2i {
    i32 x, y;

    vec2i() : vec2i{0} {}
    vec2i(i32 x, i32 y) : x(x), y(y) {}
    vec2i(vec2i &other) : vec2i{other.x, other.y} {}
    vec2i(const vec2i &other) : vec2i{other.x, other.y} {}
    explicit vec2i(i32 value) : vec2i{value, value} {}

    INLINE bool operator == (const vec2i &other) const {
        return other.x == x &&
               other.y == y;
    }

    INLINE bool operator ! () const {
        return nonZero();
    }

    INLINE vec2i operator - () const {
        return {
                -x,
                -y
        };
    }

    INLINE vec2i operator - (const vec2i &rhs) const {
        return {
                x - rhs.x,
                y - rhs.y
        };
    }

    INLINE vec2i operator + (const vec2i &rhs) const {
        return {
                x + rhs.x,
                y + rhs.y
        };
    }

    INLINE vec2i operator * (const vec2i &rhs) const {
        return {
                x * rhs.x,
                y * rhs.y
        };
    }

    INLINE vec2i operator / (const vec2i &rhs) const {
        return {
                x / rhs.x,
                y / rhs.y
        };
    }

    INLINE vec2i& operator -= (const vec2i &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    INLINE vec2i& operator += (const vec2i &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    INLINE vec2i& operator *= (const vec2i &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    INLINE vec2i& operator /= (const vec2i &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    INLINE vec2i operator - (i32 rhs) const {
        return {
                x - rhs,
                y - rhs
        };
    }

    INLINE vec2i operator + (i32 rhs) const {
        return {
                x + rhs,
                y + rhs
        };
    }

    INLINE vec2i operator * (i32 rhs) const {
        return {
                x * rhs,
                y * rhs
        };
    }

    INLINE vec2i operator / (i32 rhs) const {
        return {
                x / rhs,
                y / rhs
        };
    }

    INLINE vec2i& operator -= (i32 rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    INLINE vec2i& operator += (i32 rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    INLINE vec2i& operator *= (i32 rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    INLINE vec2i& operator /= (i32 rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    INLINE vec2i operator - (f32 rhs) const {
        return {
                (i32)((f32)x - rhs),
                (i32)((f32)y - rhs)
        };
    }

    INLINE vec2i operator + (f32 rhs) const {
        return {
                (i32)((f32)x + rhs),
                (i32)((f32)y + rhs)
        };
    }

    INLINE vec2i operator * (f32 rhs) const {
        return {
                (i32)((f32)x * rhs),
                (i32)((f32)y * rhs)
        };
    }

    INLINE vec2i operator / (f32 rhs) const {
        return {
                (i32)((f32)x / rhs),
                (i32)((f32)y / rhs)
        };
    }

    INLINE vec2i& operator -= (f32 rhs) {
        x -= (i32)rhs;
        y -= (i32)rhs;
        return *this;
    }

    INLINE vec2i& operator += (f32 rhs) {
        x += (i32)rhs;
        y += (i32)rhs;
        return *this;
    }

    INLINE vec2i& operator *= (f32 rhs) {
        x *= (i32)rhs;
        y *= (i32)rhs;
        return *this;
    }

    INLINE vec2i& operator /= (f32 rhs) {
        x /= (i32)rhs;
        y /= (i32)rhs;
        return *this;
    }

    INLINE bool nonZero() const {
        return x != 0 ||
               y != 0;
    }

    INLINE i32 min() const {
        return x < y ? x : y;
    }

    INLINE i32 max() const {
        return x > y ? x : y;
    }

    INLINE vec2i clamped() const {
        return {
                clampedValue(x),
                clampedValue(y)
        };
    }

    INLINE vec2i clamped(const vec2i &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y)
        };
    }

    INLINE vec2i clamped(const f32 min_value, const f32 max_value) const {
        return {
                (i32)(clampedValue((f32)x, min_value, max_value)),
                (i32)(clampedValue((f32)y, min_value, max_value))
        };
    }

    INLINE vec2i clamped(const i32 min_value, const i32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value)
        };
    }

    INLINE vec2i approachTo(const vec2i &trg, f32 diff) const {
        return {
                (i32)(approach((f32)x, (f32)trg.x, diff)),
                (i32)(approach((f32)y, (f32)trg.y, diff))
        };
    }

    INLINE vec2i scaleAdd(f32 factor, const vec2i &to_be_added) const {
        return {
                (i32)fast_mul_add((f32)x, factor, (f32)to_be_added.x),
                (i32)fast_mul_add((f32)y, factor, (f32)to_be_added.y)
        };
    }
};


union vec2 {
    struct {f32 components[2]; };
    struct {f32 x, y; };
    struct {f32 u, v; };
    struct {f32 r, g, b; };

    vec2() : vec2{0} {}
    vec2(f32 x, f32 y) : x(x), y(y) {}
    vec2(i32 x, i32 y) : x((f32)x), y((f32)y) {}
    vec2(vec2 &other) : vec2{other.x, other.y} {}
    vec2(const vec2 &other) : vec2{other.x, other.y} {}
    explicit vec2(f32 value) : vec2{value, value} {}
    explicit vec2(vec2i &other) : vec2{(f32)other.x, (f32)other.y} {}
    explicit vec2(const vec2i &other) : vec2{(f32)other.x, (f32)other.y} {}

    INLINE bool operator == (const vec2 &other) const {
        return other.x == x &&
               other.y == y;
    }

    INLINE bool operator ! () const {
        return nonZero();
    }

    INLINE f32 operator | (const vec2 &rhs) const {
        return dot(rhs);
    }

    INLINE vec2 operator % (const vec2 &rhs) const {
        return reflectAround(rhs);
    }

    INLINE vec2 operator ~ () const {
        return this->perp();
    }

    INLINE f32 operator ^ (const vec2 &rhs) const {
        return cross(rhs);
    }

    INLINE vec2 operator - () const {
        return {
                -x,
                -y
        };
    }

    INLINE vec2 operator - (const vec2 &rhs) const {
        return {
                x - rhs.x,
                y - rhs.y
        };
    }

    INLINE vec2 operator + (const vec2 &rhs) const {
        return {
                x + rhs.x,
                y + rhs.y
        };
    }

    INLINE vec2 operator * (const vec2 &rhs) const {
        return {
                x * rhs.x,
                y * rhs.y
        };
    }

    INLINE vec2 operator / (const vec2 &rhs) const {
        return {
                x / rhs.x,
                y / rhs.y
        };
    }

    INLINE vec2& operator -= (const vec2 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    INLINE vec2& operator += (const vec2 &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    INLINE vec2& operator *= (const vec2 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    INLINE vec2& operator /= (const vec2 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    INLINE vec2 operator - (f32 rhs) const {
        return {
                x - rhs,
                y - rhs
        };
    }

    INLINE vec2 operator + (f32 rhs) const {
        return {
                x + rhs,
                y + rhs
        };
    }

    INLINE vec2 operator * (f32 rhs) const {
        return {
                x * rhs,
                y * rhs
        };
    }

    INLINE vec2 operator / (f32 rhs) const {
        return {
                x / rhs,
                y / rhs
        };
    }

    INLINE vec2& operator -= (f32 rhs) {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    INLINE vec2& operator += (f32 rhs) {
        x += rhs;
        y += rhs;
        return *this;
    }

    INLINE vec2& operator *= (f32 rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    INLINE vec2& operator /= (f32 rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    INLINE vec2 operator - (i32 rhs) const {
        return {
                x - (f32)rhs,
                y - (f32)rhs
        };
    }

    INLINE vec2 operator + (i32 rhs) const {
        return {
                x + (f32)rhs,
                y + (f32)rhs
        };
    }

    INLINE vec2 operator * (i32 rhs) const {
        return {
                x * (f32)rhs,
                y * (f32)rhs
        };
    }

    INLINE vec2 operator / (i32 rhs) const {
        return {
                x / (f32)rhs,
                y / (f32)rhs
        };
    }

    INLINE vec2& operator -= (i32 rhs) {
        x -= (f32)rhs;
        y -= (f32)rhs;
        return *this;
    }

    INLINE vec2& operator += (i32 rhs) {
        x += (f32)rhs;
        y += (f32)rhs;
        return *this;
    }

    INLINE vec2& operator *= (i32 rhs) {
        x *= (f32)rhs;
        y *= (f32)rhs;
        return *this;
    }

    INLINE vec2& operator /= (i32 rhs) {
        x /= (f32)rhs;
        y /= (f32)rhs;
        return *this;
    }

    INLINE vec2 operator - (const vec2i &rhs) const {
        return {
                x - (f32)rhs.x,
                y - (f32)rhs.y
        };
    }

    INLINE vec2 operator + (const vec2i &rhs) const {
        return {
                x + (f32)rhs.x,
                y + (f32)rhs.y
        };
    }

    INLINE vec2 operator * (const vec2i &rhs) const {
        return {
                x * (f32)rhs.x,
                y * (f32)rhs.y
        };
    }

    INLINE vec2 operator / (const vec2i &rhs) const {
        return {
                x / (f32)rhs.x,
                y / (f32)rhs.y
        };
    }

    INLINE vec2& operator -= (const vec2i &rhs) {
        x -= (f32)rhs.x;
        y -= (f32)rhs.y;
        return *this;
    }

    INLINE vec2& operator += (const vec2i &rhs) {
        x += (f32)rhs.x;
        y += (f32)rhs.y;
        return *this;
    }

    INLINE vec2& operator *= (const vec2i &rhs) {
        x *= (f32)rhs.x;
        y *= (f32)rhs.y;
        return *this;
    }

    INLINE vec2& operator /= (const vec2i &rhs) {
        x /= (f32)rhs.x;
        y /= (f32)rhs.y;
        return *this;
    }

    INLINE bool nonZero() const {
        return x != 0.0f ||
               y != 0.0f;
    }

    INLINE f32 min() const {
        return x < y ? x : y;
    }

    INLINE f32 max() const {
        return x > y ? x : y;
    }

    INLINE vec2 perp() const {
        return {
                -y,
                x
        };
    }

    INLINE f32 dot(const vec2 &rhs) const {
        return (x * rhs.x) + (y * rhs.y);
    }

    INLINE f32 cross(const vec2 &rhs) const {
        return (x * rhs.y) - (y * rhs.x);
    }

    INLINE f32 squaredLength() const {
        return x*x + y*y;
    }

    INLINE f32 length() const {
        return sqrtf(squaredLength());
    }

    INLINE vec2 normalized() const {
        return *this / length();
    }

    INLINE vec2 reflectAround(const vec2 &N) const {
        return N.scaleAdd(-2 * dot(N), *this);
    }

    INLINE vec2 clamped() const {
        return {
                clampedValue(x),
                clampedValue(y)
        };
    }

    INLINE vec2 clamped(const vec2 &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y)
        };
    }

    INLINE vec2 clamped(const f32 min_value, const f32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value)
        };
    }

    INLINE vec2 approachTo(const vec2 &trg, f32 diff) const {
        return {
                approach(x, trg.x, diff),
                approach(y, trg.y, diff)
        };
    }

    INLINE vec2 lerpTo(const vec2 &to, f32 by) const {
        return (to - *this).scaleAdd(by, *this);
    }

    INLINE vec2 scaleAdd(f32 factor, const vec2 &to_be_added) const {
        return {
                fast_mul_add(x, factor, to_be_added.x),
                fast_mul_add(y, factor, to_be_added.y)
        };
    }
};

INLINE vec2 min(const vec2 &a, const vec2 &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y
    };
}

INLINE vec2 max(const vec2 &a, const vec2 &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y
    };
}

INLINE vec2i min(const vec2i &a, const vec2i &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y
    };
}

INLINE vec2i max(const vec2i &a, const vec2i &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y
    };
}

INLINE vec2i operator - (const vec2i &lhs, const vec2 &rhs) {
    return {
            lhs.x - (i32)rhs.x,
            lhs.y - (i32)rhs.y
    };
}

INLINE vec2i operator + (const vec2i &lhs, const vec2 &rhs) {
    return {
            lhs.x + (i32)rhs.x,
            lhs.y + (i32)rhs.y
    };
}

INLINE vec2i operator * (const vec2i &lhs, const vec2 &rhs) {
    return {
            lhs.x * (i32)rhs.x,
            lhs.y * (i32)rhs.y
    };
}

INLINE vec2i operator / (const vec2i &lhs, const vec2 &rhs) {
    return {
            lhs.x / (i32)rhs.x,
            lhs.y / (i32)rhs.y
    };
}

INLINE vec2i operator - (i32 lhs, const vec2 &rhs) {
    return {
            lhs - (i32)rhs.x,
            lhs - (i32)rhs.y
    };
}

INLINE vec2i operator + (i32 lhs, const vec2 &rhs) {
    return {
            lhs + (i32)rhs.x,
            lhs + (i32)rhs.y
    };
}

INLINE vec2i operator * (i32 lhs, const vec2 &rhs) {
    return {
            lhs * (i32)rhs.x,
            lhs * (i32)rhs.y
    };
}

INLINE vec2i operator / (i32 lhs, const vec2 &rhs) {
    return {
            lhs / (i32)rhs.x,
            lhs / (i32)rhs.y
    };
}

INLINE vec2i operator - (i32 lhs, const vec2i &rhs) {
    return {
            lhs - rhs.x,
            lhs - rhs.y
    };
}

INLINE vec2i operator + (i32 lhs, const vec2i &rhs) {
    return {
            lhs + rhs.x,
            lhs + rhs.y
    };
}

INLINE vec2i operator * (i32 lhs, const vec2i &rhs) {
    return {
            lhs * rhs.x,
            lhs * rhs.y
    };
}

INLINE vec2i operator / (i32 lhs, const vec2i &rhs) {
    return {
            lhs / rhs.x,
            lhs / rhs.y
    };
}

INLINE vec2 operator - (f32 lhs, const vec2 &rhs) {
    return {
            lhs - rhs.x,
            lhs - rhs.y
    };
}

INLINE vec2 operator + (f32 lhs, const vec2 &rhs) {
    return {
            lhs + rhs.x,
            lhs + rhs.y
    };
}

INLINE vec2 operator / (f32 lhs, const vec2 &rhs) {
    return {
            lhs / rhs.x,
            lhs / rhs.y
    };
}

INLINE vec2 operator * (f32 lhs, const vec2 &rhs) {
    return {
            lhs * rhs.x,
            lhs * rhs.y
    };
}

INLINE vec2 lerp(const vec2 &from, const vec2 &to, f32 by) {
    return (to - from).scaleAdd(by, from);
}



union vec3 {
    struct {f32 components[3]; };
    struct {f32 x, y, z; };
    struct {f32 u, v, w; };
    struct {f32 r, g, b; };

    vec3() : vec3{0} {}
    vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
    vec3(vec3 &other) : vec3{other.x, other.y, other.z} {}
    vec3(const vec3 &other) : vec3{other.x, other.y, other.z} {}
    explicit vec3(f32 value) : vec3{value, value, value} {}

    INLINE bool operator == (const vec3 &other) const {
        return other.x == x &&
               other.y == y &&
               other.z == z;
    }

    INLINE bool operator ! () const {
        return nonZero();
    }

    INLINE f32 operator | (const vec3 &rhs) const {
        return dot(rhs);
    }

    INLINE vec3 operator ^ (const vec3 &rhs) const {
        return cross(rhs);
    }

    INLINE vec3 operator % (const vec3 &rhs) const {
        return reflectAround(rhs);
    }

    INLINE vec3 operator - () const {
        return {
                -x,
                -y,
                -z
        };
    }

    INLINE vec3 operator - (const vec3 &rhs) const {
        return {
                x - rhs.x,
                y - rhs.y,
                z - rhs.z
        };
    }

    INLINE vec3 operator + (const vec3 &rhs) const {
        return {
                x + rhs.x,
                y + rhs.y,
                z + rhs.z
        };
    }

    INLINE vec3 operator * (const vec3 &rhs) const {
        return {
                x * rhs.x,
                y * rhs.y,
                z * rhs.z
        };
    }

    INLINE vec3 operator / (const vec3 &rhs) const {
        return {
                x / rhs.x,
                y / rhs.y,
                z / rhs.z
        };
    }

    INLINE vec3& operator -= (const vec3 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    INLINE vec3& operator += (const vec3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    INLINE vec3& operator *= (const vec3 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    INLINE vec3& operator /= (const vec3 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    INLINE vec3 operator - (f32 rhs) const {
        return {
                x - rhs,
                y - rhs,
                z - rhs
        };
    }

    INLINE vec3 operator + (f32 rhs) const {
        return {
                x + rhs,
                y + rhs,
                z + rhs
        };
    }

    INLINE vec3 operator * (f32 rhs) const {
        return {
                x * rhs,
                y * rhs,
                z * rhs
        };
    }

    INLINE vec3 operator / (f32 rhs) const {
        return {
                x / rhs,
                y / rhs,
                z / rhs
        };
    }

    INLINE vec3& operator -= (f32 rhs) {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        return *this;
    }

    INLINE vec3& operator += (f32 rhs) {
        x += rhs;
        y += rhs;
        z += rhs;
        return *this;
    }

    INLINE vec3& operator *= (f32 rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    INLINE vec3& operator /= (f32 rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    INLINE vec3 operator - (i32 rhs) const {
        return {
                x - (f32)rhs,
                y - (f32)rhs,
                z - (f32)rhs
        };
    }

    INLINE vec3 operator + (i32 rhs) const {
        return {
                x + (f32)rhs,
                y + (f32)rhs,
                z + (f32)rhs
        };
    }

    INLINE vec3 operator * (i32 rhs) const {
        return {
                x * (f32)rhs,
                y * (f32)rhs,
                z * (f32)rhs
        };
    }

    INLINE vec3 operator / (i32 rhs) const {
        return {
                x / (f32)rhs,
                y / (f32)rhs,
                z / (f32)rhs
        };
    }

    INLINE vec3& operator -= (i32 rhs) {
        x -= (f32)rhs;
        y -= (f32)rhs;
        z -= (f32)rhs;
        return *this;
    }

    INLINE vec3& operator += (i32 rhs) {
        x += (f32)rhs;
        y += (f32)rhs;
        z += (f32)rhs;
        return *this;
    }

    INLINE vec3& operator *= (i32 rhs) {
        x *= (f32)rhs;
        y *= (f32)rhs;
        z *= (f32)rhs;
        return *this;
    }

    INLINE vec3& operator /= (i32 rhs) {
        x /= (f32)rhs;
        y /= (f32)rhs;
        z /= (f32)rhs;
        return *this;
    }

    INLINE bool nonZero() const {
        return x != 0.0f ||
               y != 0.0f ||
               z != 0.0f;
    }

    INLINE vec3 perpZ() const {
        return {
                -y,
                x,
                z
        };
    }

    INLINE f32 min() const {
        return x < y ? (x < z ? x : z) : (y < z ? y : z);
    }

    INLINE f32 max() const {
        return x > y ? (x > z ? x : z) : (y > z ? y : z);
    }

    INLINE f32 dot(const vec3 &rhs) const {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    }

    INLINE vec3 cross(const vec3 &rhs) const {
        return {
                (y * rhs.z) - (z * rhs.y),
                (z * rhs.x) - (x * rhs.z),
                (x * rhs.y) - (y * rhs.x)
        };
    }

    INLINE f32 squaredLength() const {
        return x*x + y*y + z*z;
    }

    INLINE f32 length() const {
        return sqrtf(squaredLength());
    }

    INLINE vec3 normalized() const {
        return *this / length();
    }

    INLINE vec3 reflectAround(const vec3 &N) const {
        return N.scaleAdd(-2 * dot(N), *this);
    }

    INLINE vec3 clamped() const {
        return {
                clampedValue(x),
                clampedValue(y),
                clampedValue(z)
        };
    }

    INLINE vec3 clamped(const vec3 &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y),
                clampedValue(z, upper.z)
        };
    }

    INLINE vec3 clamped(const f32 min_value, const f32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value),
                clampedValue(z, min_value, max_value)
        };
    }

    INLINE vec3 approachTo(const vec3 &trg, f32 diff) const {
        return {
                approach(x, trg.x, diff),
                approach(y, trg.y, diff),
                approach(z, trg.z, diff)
        };
    }

    INLINE vec3 lerpTo(const vec3 &to, f32 by) const {
        return (to - *this).scaleAdd(by, *this);
    }

    INLINE vec3 scaleAdd(f32 factor, const vec3 &to_be_added) const {
        return {
                fast_mul_add(x, factor, to_be_added.x),
                fast_mul_add(y, factor, to_be_added.y),
                fast_mul_add(z, factor, to_be_added.z)
        };
    }
};

INLINE vec3 min(const vec3 &a, const vec3 &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y,
            a.z < b.y ? a.z : b.z
    };
}

INLINE vec3 max(const vec3 &a, const vec3 &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y,
            a.z > b.z ? a.z : b.z
    };
}

INLINE vec3 operator - (f32 lhs, const vec3 &rhs) {
    return {
            lhs - rhs.x,
            lhs - rhs.y,
            lhs - rhs.z
    };
}

INLINE vec3 operator + (f32 lhs, const vec3 &rhs) {
    return {
            lhs + rhs.x,
            lhs + rhs.y,
            lhs + rhs.z
    };
}

INLINE vec3 operator / (f32 lhs, const vec3 &rhs) {
    return {
            lhs / rhs.x,
            lhs / rhs.y,
            lhs / rhs.z
    };
}

INLINE vec3 operator * (f32 lhs, const vec3 &rhs) {
    return {
            lhs * rhs.x,
            lhs * rhs.y,
            lhs * rhs.z
    };
}

INLINE vec3 lerp(const vec3 &from, const vec3 &to, f32 by) {
    return (to - from).scaleAdd(by, from);
}



union mat2  {
    vec2 axis[2];
    struct {
        vec2 X, Y;
    };

    mat2() : mat2{
            vec2{1.0f, 0.0f},
            vec2{0.0f, 1.0f}
    } {}
    mat2(vec2i x, vec2i y) : X{x}, Y{y} {}
    mat2(vec2i x, vec2 y) : X{x}, Y{y} {}
    mat2(vec2 x, vec2i y) : X{x}, Y{y} {}
    mat2(vec2 x, vec2 y) : X{x}, Y{y} {}
    mat2(f32 Xx, f32 Xy, f32 Yx, f32 Yy) : X{Xx, Xy}, Y{Yx, Yy} {}
    mat2(i32 Xx, i32 Xy, i32 Yx, i32 Yy) : X{(f32)Xx, (f32)Xy}, Y{(f32)Yx, (f32)Yy} {}
    mat2(mat2 &other) : mat2{other.X, other.Y} {}
    mat2(const mat2 &other) : mat2{other.X, other.Y} {}

    INLINE f32 det() const {
        return X.x*Y.y - X.y*Y.x;
    }

    INLINE bool has_inverse() const {
        return det() != 0;
    }

    INLINE mat2 operator ! () const {
        return inverted();
    }

    INLINE mat2 operator ~ () const {
        return transposed();
    }

    INLINE mat2 operator + (f32 rhs) const {
        return {
                X.x + rhs, X.y + rhs,
                Y.x + rhs, Y.y + rhs
        };
    }

    INLINE mat2 operator - (f32 rhs) const {
        return {
                X.x - rhs, X.y - rhs,
                Y.x - rhs, Y.y - rhs
        };
    }

    INLINE mat2 operator * (f32 rhs) const {
        return {
                X.x * rhs, X.y * rhs,
                Y.x * rhs, Y.y * rhs
        };
    }

    INLINE mat2 operator / (f32 rhs) const {
        f32 factor = 1.0f / rhs;
        return {
                X.x * factor, X.y * factor,
                Y.x * factor, Y.y * factor
        };
    }

    INLINE mat2 operator + (const mat2 &rhs) const {
        return {
                X.x + rhs.X.x, X.y + rhs.X.y,
                Y.x + rhs.Y.x, Y.y + rhs.Y.y
        };
    }

    INLINE mat2 operator - (const mat2 &rhs) const {
        return {
                X.x - rhs.X.x, X.y - rhs.X.y,
                Y.x - rhs.Y.x, Y.y - rhs.Y.y
        };
    }

    INLINE mat2 operator * (const mat2 &rhs) const {
        return {
                X.x*rhs.X.x + X.y*rhs.Y.x, // Row 1 | Column 1
                X.x*rhs.X.y + X.y*rhs.Y.y, // Row 1 | Column 2
                Y.x*rhs.X.x + Y.y*rhs.Y.x, // Row 2 | Column 1
                Y.x*rhs.X.y + Y.y*rhs.Y.y  // Row 2 | Column 2
        };
    }

    INLINE vec2 operator * (const vec2 &rhs) const {
        return {
                X.x*rhs.x + Y.x*rhs.y,
                X.y*rhs.x + Y.y*rhs.y
        };
    }

    INLINE void operator += (const mat2 &rhs) {
        X.x += rhs.X.x;
        X.y += rhs.X.y;
        Y.x += rhs.Y.x;
        Y.y += rhs.Y.y;
    }

    INLINE void operator -= (const mat2 &rhs) {
        X.x -= rhs.X.x;
        X.y -= rhs.X.y;
        Y.x -= rhs.Y.x;
        Y.y -= rhs.Y.y;
    }

    INLINE void operator *= (const mat2 &rhs) {
        mat2 lhs{*this};
        X.x = lhs.X.x*rhs.X.x + lhs.X.y*rhs.Y.x; // Row 1 | Column 1
        X.y = lhs.X.x*rhs.X.y + lhs.X.y*rhs.Y.y; // Row 1 | Column 2
        Y.x = lhs.Y.x*rhs.X.x + lhs.Y.y*rhs.Y.x; // Row 2 | Column 1
        Y.y = lhs.Y.x*rhs.X.y + lhs.Y.y*rhs.Y.y; // Row 2 | Column 2
    }

    INLINE void operator += (f32 rhs) {
        X.x += rhs;
        X.y += rhs;
        Y.x += rhs;
        Y.y += rhs;
    }

    INLINE void operator -= (f32 rhs) {
        X.x -= rhs;
        X.y -= rhs;
        Y.x -= rhs;
        Y.y -= rhs;
    }

    INLINE void operator *= (f32 rhs) {
        X.x *= rhs;
        X.y *= rhs;
        Y.x *= rhs;
        Y.y *= rhs;
    }

    INLINE void operator /= (f32 rhs) {
        f32 factor = 1.0f / rhs;
        X.x *= factor;
        X.y *= factor;
        Y.x *= factor;
        Y.y *= factor;
    }

    INLINE void setRotation(f32 angle) {
        X.x = Y.y = cos(angle);
        Y.x = X.y = sin(angle);
        X.y = -X.y;
    }

    INLINE void rotate(f32 angle) {
        f32 c = cos(angle);
        f32 s = sin(angle);
        mat2 lhs{*this};
        X.x = c*lhs.X.x + s*lhs.X.y; // Row 1 | Column 1
        X.y = c*lhs.X.y - s*lhs.X.x; // Row 1 | Column 2
        Y.x = c*lhs.Y.x + s*lhs.Y.y; // Row 2 | Column 1
        Y.y = c*lhs.Y.y - s*lhs.Y.x; // Row 2 | Column 2
    }

    INLINE mat2 rotated_by(f32 angle) const {
        f32 c = cos(angle);
        f32 s = sin(angle);
        return {
                c*X.x + s*X.y, c*Y.x + s*Y.y,
                c*X.y - s*X.x, c*Y.y - s*Y.x
        };
    }

    INLINE mat2 transposed() const {
        return {
                X.x, Y.x,
                X.y, Y.y
        };
    }

    INLINE mat2 inverted() const {
        return mat2{
                Y.y, -X.y,
                -Y.x, X.x
        } / det();
    }
};

INLINE mat2 operator * (f32 lhs, const mat2 &rhs) {
    return rhs * lhs;
}

INLINE mat2 operator + (f32 lhs, const mat2 &rhs) {
    return rhs + lhs;
}

INLINE mat2 outer(const vec2 &lhs, const vec2 &rhs) {
    return {
            lhs * rhs.x,
            lhs * rhs.y
    };
}



union mat3 {
    vec3 axis[3];
    struct {
        vec3 X, Y, Z;
    };

    mat3() : X{1.0f, 0.0f, 0.0f},
             Y{0.0f, 1.0f, 0.0f},
             Z{0.0f, 0.0f, 1.0f} {}
    mat3(vec3 X, vec3 Y, vec3 Z) : X{X}, Y{Y}, Z{Z} {}
    mat3(f32 Xx, f32 Xy, f32 Xz,
         f32 Yx, f32 Yy, f32 Yz,
         f32 Zx, f32 Zy, f32 Zz) :
            X{Xx, Xy, Xz},
            Y{Yx, Yy, Yz},
            Z{Zx, Zy, Zz} {}
    mat3(mat3 &other) : mat3{other.X, other.Y, other.Z} {}
    mat3(const mat3 &other) : mat3{other.X, other.Y, other.Z} {}

    INLINE void setRotationAroundX(f32 angle) {
        Z.z = Y.y = cos(angle);
        Y.z = Z.y = sin(angle);
        Y.z = -Y.z;
        X.z = X.y = Y.x = Z.x = 0;
        X.x = 1;
    }

    INLINE void setRotationAroundY(f32 angle) {
        X.x = Z.z = cos(angle);
        Z.x = X.z = sin(angle);
        Z.x = -Z.x;
        Y.x = Y.z = X.y = Z.y = 0;
        Y.y = 1;
    }

    INLINE void setRotationAroundZ(f32 angle) {
        X.x = Y.y = cos(angle);
        Y.x = X.y = sin(angle);
        X.y = -X.y;
        X.z = Y.z = Z.x = Z.y = 0;
        Z.z = 1;
    }

    INLINE void rotateAroundX(f32 angle) {
        f32 c = cos(angle);
        f32 s = sin(angle);
        mat3 lhs = *this;
        X.y = c*lhs.X.y + s*lhs.X.z; // Row 1 | Column 1
        Y.y = c*lhs.Y.y + s*lhs.Y.z; // Row 2 | Column 1
        Z.y = c*lhs.Z.y + s*lhs.Z.z; // Row 3 | Column 1

        X.z = c*lhs.X.z - s*lhs.X.y; // Row 1 | Column 2
        Y.z = c*lhs.Y.z - s*lhs.Y.y; // Row 2 | Column 2
        Z.z = c*lhs.Z.z - s*lhs.Z.y; // Row 3 | Column 2
    }

    INLINE void rotateAroundY(f32 angle) {
        f32 c = cos(angle);
        f32 s = sin(angle);
        mat3 lhs = *this;
        X.x = c*lhs.X.x - s*lhs.X.z; // Row 1 | Column 1
        Y.x = c*lhs.Y.x - s*lhs.Y.z; // Row 2 | Column 1
        Z.x = c*lhs.Z.x - s*lhs.Z.z; // Row 3 | Column 1

        X.z = c*lhs.X.z + s*lhs.X.x; // Row 1 | Column 2
        Y.z = c*lhs.Y.z + s*lhs.Y.x; // Row 2 | Column 2
        Z.z = c*lhs.Z.z + s*lhs.Z.x; // Row 3 | Column 2
    }

    INLINE void rotateAroundZ(f32 angle) {
        f32 c = cos(angle);
        f32 s = sin(angle);
        mat3 lhs = *this;
        X.x = c*lhs.X.x + s*lhs.X.y; // Row 1 | Column 1
        Y.x = c*lhs.Y.x + s*lhs.Y.y; // Row 2 | Column 1
        Z.x = c*lhs.Z.x + s*lhs.Z.y; // Row 3 | Column 1

        X.y = c*lhs.X.y - s*lhs.X.x; // Row 1 | Column 2
        Y.y = c*lhs.Y.y - s*lhs.Y.x; // Row 2 | Column 2
        Z.y = c*lhs.Z.y - s*lhs.Z.x; // Row 3 | Column 2
    }

    INLINE mat3 rotatedAroundXby(f32 angle) const {
        mat3 out{*this};
        out.rotateAroundX(angle);
        return out;
    }

    INLINE mat3 rotatedAroundYby(f32 angle) const {
        mat3 out{*this};
        out.rotateAroundY(angle);
        return out;
    }

    INLINE mat3 rotatedAroundZby(f32 angle) const {
        mat3 out{*this};
        out.rotateAroundZ(angle);
        return out;
    }

    INLINE f32 det() const {
        return (
                + X.x * (Y.y * Z.z - Z.y * Y.z)
                - Y.x * (X.y * Z.z - Z.y * X.z)
                + Z.x * (X.y * Y.z - Y.y * X.z)
        );
    }

    INLINE bool has_inverse() const {
        return det() != 0;
    }

    INLINE mat3 transposed() const {
        return {
                X.x, Y.x, Z.x,
                X.y, Y.y, Z.y,
                X.z, Y.z, Z.z
        };
    }

    INLINE mat3 inverted() const {
        return mat3{
                +(Y.y * Z.z - Z.y * Y.z),
                -(Y.x * Z.z - Z.x * Y.z),
                +(Y.x * Z.y - Z.x * Y.y),

                -(X.y * Z.z - Z.y * X.z),
                +(X.x * Z.z - Z.x * X.z),
                -(X.x * Z.y - Z.x * X.y),

                +(X.y * Y.z - Y.y * X.z),
                -(X.x * Y.z - Y.x * X.z),
                +(X.x * Y.y - Y.x * X.y)
        } / det();
    }

    INLINE mat3 operator ! () const {
        return inverted();
    }

    INLINE mat3 operator ~ () const {
        return transposed();
    }

    INLINE mat3 operator + (f32 rhs) const {
        return {
                X.x + rhs, X.y + rhs, X.z + rhs,
                Y.x + rhs, Y.y + rhs, Y.z + rhs,
                Z.x + rhs, Z.y + rhs, Z.z + rhs
        };
    }

    INLINE mat3 operator - (f32 rhs) const {
        return {
                X.x - rhs, X.y - rhs, X.z - rhs,
                Y.x - rhs, Y.y - rhs, Y.z - rhs,
                Z.x - rhs, Z.y - rhs, Z.z - rhs
        };
    }

    INLINE mat3 operator * (f32 rhs) const {
        return {
                X.x * rhs, X.y * rhs, X.z * rhs,
                Y.x * rhs, Y.y * rhs, Y.z * rhs,
                Z.x * rhs, Z.y * rhs, Z.z * rhs
        };
    }

    INLINE mat3 operator / (f32 rhs) const {
        f32 factor = 1.0f / rhs;
        return mat3{
                X.x, X.y, X.z,
                Y.x, Y.y, Y.z,
                Z.x, Z.y, Z.z
        } * factor;
    }

    INLINE mat3 operator + (const mat3 &rhs) const {
        return {
                X.x + rhs.X.x, X.y + rhs.X.y, X.z + rhs.X.z,
                Y.x + rhs.Y.x, Y.y + rhs.Y.y, Y.z + rhs.Y.z,
                Z.x + rhs.Z.x, Z.y + rhs.Z.y, Z.z + rhs.Z.z
        };
    }

    INLINE mat3 operator - (const mat3 &rhs) const {
        return {
                X.x - rhs.X.x, X.y - rhs.X.y, X.z - rhs.X.z,
                Y.x - rhs.Y.x, Y.y - rhs.Y.y, Y.z - rhs.Y.z,
                Z.x - rhs.Z.x, Z.y - rhs.Z.y, Z.z - rhs.Z.z
        };
    }

    INLINE mat3 operator * (const mat3 &rhs) const {
        return {
                X.x*rhs.X.x + X.y*rhs.Y.x + X.z*rhs.Z.x, // Row 1 | Column 1
                X.x*rhs.X.y + X.y*rhs.Y.y + X.z*rhs.Z.y, // Row 1 | Column 2
                X.x*rhs.X.z + X.y*rhs.Y.z + X.z*rhs.Z.z, // Row 1 | Column 3

                Y.x*rhs.X.x + Y.y*rhs.Y.x + Y.z*rhs.Z.x, // Row 2 | Column 1
                Y.x*rhs.X.y + Y.y*rhs.Y.y + Y.z*rhs.Z.y, // Row 2 | Column 2
                Y.x*rhs.X.z + Y.y*rhs.Y.z + Y.z*rhs.Z.z, // Row 2 | Column 3

                Z.x*rhs.X.x + Z.y*rhs.Y.x + Z.z*rhs.Z.x, // Row 3 | Column 1
                Z.x*rhs.X.y + Z.y*rhs.Y.y + Z.z*rhs.Z.y, // Row 3 | Column 2
                Z.x*rhs.X.z + Z.y*rhs.Y.z + Z.z*rhs.Z.z, // Row 3 | Column 3
        };
    }

    INLINE vec3 operator * (const vec3 &rhs) const {
        return {
                X.x*rhs.x + Y.x*rhs.y + Z.x*rhs.z,
                X.y*rhs.x + Y.y*rhs.y + Z.y*rhs.z,
                X.z*rhs.x + Y.z*rhs.y + Z.z*rhs.z
        };
    }

    INLINE void operator += (const mat3 &rhs) {
        X.x += rhs.X.x; Y.x += rhs.Y.x; Z.x += rhs.Z.x;
        X.y += rhs.X.y; Y.y += rhs.Y.y; Z.y += rhs.Z.y;
        X.z += rhs.X.z; Y.z += rhs.Y.z; Z.z += rhs.Z.z;
    }

    INLINE void operator -= (const mat3 &rhs) {
        X.x -= rhs.X.x; Y.x -= rhs.Y.x; Z.x -= rhs.Z.x;
        X.y -= rhs.X.y; Y.y -= rhs.Y.y; Z.y -= rhs.Z.y;
        X.z -= rhs.X.z; Y.z -= rhs.Y.z; Z.z -= rhs.Z.z;
    }

    INLINE void operator *= (const mat3 &rhs) {
        mat3 lhs = *this;
        X.x = lhs.X.x*rhs.X.x + lhs.X.y*rhs.Y.x + lhs.X.z*rhs.Z.x; // Row 1 | Column 1
        X.y = lhs.X.x*rhs.X.y + lhs.X.y*rhs.Y.y + lhs.X.z*rhs.Z.y; // Row 1 | Column 2
        X.z = lhs.X.x*rhs.X.z + lhs.X.y*rhs.Y.z + lhs.X.z*rhs.Z.z; // Row 1 | Column 3

        Y.x = lhs.Y.x*rhs.X.x + lhs.Y.y*rhs.Y.x + lhs.Y.z*rhs.Z.x; // Row 2 | Column 1
        Y.y = lhs.Y.x*rhs.X.y + lhs.Y.y*rhs.Y.y + lhs.Y.z*rhs.Z.y; // Row 2 | Column 2
        Y.z = lhs.Y.x*rhs.X.z + lhs.Y.y*rhs.Y.z + lhs.Y.z*rhs.Z.z; // Row 2 | Column 3

        Z.x = lhs.Z.x*rhs.X.x + lhs.Z.y*rhs.Y.x + lhs.Z.z*rhs.Z.x; // Row 3 | Column 1
        Z.y = lhs.Z.x*rhs.X.y + lhs.Z.y*rhs.Y.y + lhs.Z.z*rhs.Z.y; // Row 3 | Column 2
        Z.z = lhs.Z.x*rhs.X.z + lhs.Z.y*rhs.Y.z + lhs.Z.z*rhs.Z.z; // Row 3 | Column 3
    }

    INLINE void operator += (f32 rhs) {
        X.x += rhs; Y.x += rhs; Z.x += rhs;
        X.y += rhs; Y.y += rhs; Z.y += rhs;
        X.z += rhs; Y.z += rhs; Z.z += rhs;
    }

    INLINE void operator -= (f32 rhs) {
        X.x -= rhs; Y.x -= rhs; Z.x -= rhs;
        X.y -= rhs; Y.y -= rhs; Z.y -= rhs;
        X.z -= rhs; Y.z -= rhs; Z.z -= rhs;
    }

    INLINE void operator *= (f32 rhs) {
        X.x *= rhs; Y.x *= rhs; Z.x *= rhs;
        X.y *= rhs; Y.y *= rhs; Z.y *= rhs;
        X.z *= rhs; Y.z *= rhs; Z.z *= rhs;
    }

    INLINE void operator /= (f32 rhs) {
        f32 factor = 1.0f / rhs;
        X.x *= factor; Y.x *= factor; Z.x *= factor;
        X.y *= factor; Y.y *= factor; Z.y *= factor;
        X.z *= factor; Y.z *= factor; Z.z *= factor;
    }
};

INLINE mat3 operator * (f32 lhs, const mat3 &rhs) {
    return rhs * lhs;
}

INLINE mat3 operator + (f32 lhs, const mat3 &rhs) {
    return rhs + lhs;
}

INLINE mat3 outerVec3(const vec3 &lhs, const vec3 &rhs) {
    return {
            lhs * rhs.x,
            lhs * rhs.y,
            lhs * rhs.z
    };
}


#else

struct vec2i {
    i32 x, y;

    vec2i() : vec2i{0} {}
    vec2i(i32 x, i32 y) : x(x), y(y) {}
    vec2i(vec2i &other) : vec2i{other.x, other.y} {}
    vec2i(const vec2i &other) : vec2i{other.x, other.y} {}
    explicit vec2i(i32 value) : vec2i{value, value} {}

    INLINE bool operator == (const vec2i &other) const {
        return other.x == x &&
               other.y == y;
    }

    INLINE bool nonZero() const {
        return x != 0 ||
               y != 0;
    }

    INLINE i32 min() const {
        return x < y ? x : y;
    }

    INLINE i32 max() const {
        return x > y ? x : y;
    }

    INLINE vec2i clamped() const {
        return {
                clampedValue(x),
                clampedValue(y)
        };
    }

    INLINE vec2i clamped(const vec2i &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y)
        };
    }

    INLINE vec2i clamped(const f32 min_value, const f32 max_value) const {
        return {
                (i32)(clampedValue((f32)x, min_value, max_value)),
                (i32)(clampedValue((f32)y, min_value, max_value))
        };
    }

    INLINE vec2i clamped(const i32 min_value, const i32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value)
        };
    }
};

union vec2 {
    struct {f32 components[2]; };
    struct {f32 x, y; };
    struct {f32 u, v; };
    struct {f32 r, g, b; };

    vec2() : vec2{0} {}
    vec2(f32 x, f32 y) : x(x), y(y) {}
    vec2(i32 x, i32 y) : x((f32)x), y((f32)y) {}
    vec2(vec2 &other) : vec2{other.x, other.y} {}
    vec2(const vec2 &other) : vec2{other.x, other.y} {}
    explicit vec2(f32 value) : vec2{value, value} {}
    explicit vec2(vec2i &other) : vec2{(f32)other.x, (f32)other.y} {}
    explicit vec2(const vec2i &other) : vec2{(f32)other.x, (f32)other.y} {}

    INLINE bool operator == (const vec2 &other) const {
        return other.x == x &&
               other.y == y;
    }

    INLINE f32 min() const {
        return x < y ? x : y;
    }

    INLINE f32 max() const {
        return x > y ? x : y;
    }

    INLINE vec2 clamped() const {
        return {
                clampedValue(x),
                clampedValue(y)
        };
    }

    INLINE vec2 clamped(const vec2 &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y)
        };
    }

    INLINE vec2 clamped(const f32 min_value, const f32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value)
        };
    }
};

union vec3 {
    struct { f32 components[3]; };
    struct { f32 x, y, z; };
    struct { f32 u, v, w; };
    struct { f32 r, g, b; };

    vec3() : vec3{0} {}
    vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
    vec3(vec3 &other) : vec3{other.x, other.y, other.z} {}
    vec3(const vec3 &other) : vec3{other.x, other.y, other.z} {}
    explicit vec3(f32 value) : vec3{value, value, value} {}

    INLINE bool operator==(const vec3 &other) const {
        return other.x == x &&
               other.y == y &&
               other.z == z;
    }

    INLINE f32 min() const {
        return x < y ? (x < z ? x : z) : (y < z ? y : z);
    }

    INLINE f32 max() const {
        return x > y ? (x > z ? x : z) : (y > z ? y : z);
    }
    INLINE vec3 clamped() const {
        return {
                clampedValue(x),
                clampedValue(y),
                clampedValue(z)
        };
    }

    INLINE vec3 clamped(const vec3 &upper) const {
        return {
                clampedValue(x, upper.x),
                clampedValue(y, upper.y),
                clampedValue(z, upper.z)
        };
    }

    INLINE vec3 clamped(const f32 min_value, const f32 max_value) const {
        return {
                clampedValue(x, min_value, max_value),
                clampedValue(y, min_value, max_value),
                clampedValue(z, min_value, max_value)
        };
    }
};

INLINE vec2 min(const vec2 &a, const vec2 &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y
    };
}

INLINE vec2 max(const vec2 &a, const vec2 &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y
    };
}

INLINE vec2i min(const vec2i &a, const vec2i &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y
    };
}

INLINE vec2i max(const vec2i &a, const vec2i &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y
    };
}
INLINE vec3 min(const vec3 &a, const vec3 &b) {
    return {
            a.x < b.x ? a.x : b.x,
            a.y < b.y ? a.y : b.y,
            a.z < b.y ? a.z : b.z
    };
}

INLINE vec3 max(const vec3 &a, const vec3 &b) {
    return {
            a.x > b.x ? a.x : b.x,
            a.y > b.y ? a.y : b.y,
            a.z > b.z ? a.z : b.z
    };
}
INLINE vec2i operator - (const vec2i &lhs, const vec2 &rhs) {
    return {
            lhs.x - (i32)rhs.x,
            lhs.y - (i32)rhs.y
    };
}

#endif

struct Rect {
    vec2i min, max;

    Rect() : Rect{0, 0, 0 ,0} {}
    Rect(const vec2i &min, const vec2i &max) : min{min}, max{max} {}
    Rect(i32 min_x, i32 min_y, i32 max_x, i32 max_y) : min{min_x, min_y}, max{max_x, max_y} {}

    INLINE bool contains(const vec2i &pos) const {
        return pos.x >= min.x &&
               pos.x <= max.x &&
               pos.y >= min.y &&
               pos.y <= max.y;
    }

    INLINE bool bounds(const vec2i &pos) const {
        return pos.x > min.x &&
               pos.x < max.x &&
               pos.y > min.y &&
               pos.y < max.y;
    }

    INLINE bool is_zero() const {
        return min.x == max.x &&
               min.y == max.y;
    }

    INLINE bool operator ! () const {
        return is_zero();
    }

    INLINE bool operator [] (const vec2i &pos) const {
        return contains(pos);
    }

    INLINE bool operator () (const vec2i &pos) const {
        return bounds(pos);
    }
};

INLINE Rect operator >> (const vec2i &min, const vec2i &max) {
    return {min, max};
}

INLINE Rect operator << (const vec2i &max, const vec2i &min) {
    return {min, max};
}


struct RangeI {
    i32 from, to;

    RangeI() : RangeI{0, 0} {}
    RangeI(i32 from, i32 to) : from{from}, to{to} {}

    INLINE bool contains(i32 v) const {
        return from <= v &&
               v <= to;
    }

    INLINE bool bounds(i32 v) const {
        return from < v &&
               v < to;
    }

    INLINE bool is_zero() const {
        return from == 0 &&
               to == 0;
    }

    INLINE bool operator ! () const {
        return is_zero();
    }

    INLINE bool operator [] (i32 v) const {
        return contains(v);
    }

    INLINE bool operator () (i32 v) const {
        return bounds(v);
    }
};

struct Range {
    f32 from, to;

    Range() : Range{0, 0} {}
    Range(f32 from, f32 to) : from{from}, to{to} {}

    INLINE bool contains(f32 v) const {
        return from <= v && v <= to;
    }

    INLINE bool bounds(f32 v) const {
        return from < v && v < to;
    }

    INLINE bool is_zero() const {
        return from == 0 && to == 0;
    }

    INLINE bool operator ! () const {
        return is_zero();
    }

    INLINE bool operator [] (f32 v) const {
        return contains(v);
    }

    INLINE bool operator () (f32 v) const {
        return bounds(v);
    }
};

INLINE void swap(i32 *a, i32 *b) {
    i32 t = *a;
    *a = *b;
    *b = t;
}

INLINE void subRange(i32 from, i32 to, i32 end, i32 start, i32 *first, i32 *last) {
    *first = from;
    *last  = to;
    if (to < from) swap(first, last);
    *first = *first > start ? *first : start;
    *last  = (*last < end ? *last : end) - 1;
}

INLINE bool inRange(i32 value, i32 end, i32 start = 0) {
    return start <= value && value < end;
}


#define MAX_COLOR_VALUE 0xFF
#define THREE_QUARTERS_COLOR_VALUE 0xC0
#define HALF_COLOR_VALUE 0x80
#define QUARTER_COLOR_VALUE 0x40

enum ColorID {
    Black,
    White,
    Grey,

    Red,
    Green,
    Blue,

    Cyan,
    Magenta,
    Yellow,

    DarkRed,
    DarkGreen,
    DarkBlue,
    DarkGrey,

    BrightRed,
    BrightGreen,
    BrightBlue,
    BrightGrey,

    BrightCyan,
    BrightMagenta,
    BrightYellow,

    DarkCyan,
    DarkMagenta,
    DarkYellow
};

struct RGBA {
    u8 B, G, R, A;

    RGBA() : RGBA{0, 0, 0, 0} {}
    RGBA(u8 r, u8 g, u8 b, u8 a) : B{b}, G{g}, R{r}, A{a} {}

    explicit RGBA(const vec3 &rgb) :
            B{(u8)(255.0f * fmaxf(0, fminf(rgb.z, 1.0f)))},
            G{(u8)(255.0f * fmaxf(0, fminf(rgb.y, 1.0f)))},
            R{(u8)(255.0f * fmaxf(0, fminf(rgb.x, 1.0f)))},
            A{0} {}

    RGBA& operator=(vec3 rgb) { *this = RGBA{rgb}; return *this; }
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
            color.R = HALF_COLOR_VALUE;
            color.G = HALF_COLOR_VALUE;
            color.B = HALF_COLOR_VALUE;
            break;
        case DarkGrey:
            color.R = QUARTER_COLOR_VALUE;
            color.G = QUARTER_COLOR_VALUE;
            color.B = QUARTER_COLOR_VALUE;
            break;
        case BrightGrey:
            color.R = THREE_QUARTERS_COLOR_VALUE;
            color.G = THREE_QUARTERS_COLOR_VALUE;
            color.B = THREE_QUARTERS_COLOR_VALUE;
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

        case DarkRed:
            color.R = HALF_COLOR_VALUE;
            color.G = 0;
            color.B = 0;
            break;
        case DarkGreen:
            color.R = 0;
            color.G = HALF_COLOR_VALUE;
            color.B = 0;
            break;
        case DarkBlue:
            color.R = 0;
            color.G = 0;
            color.B = HALF_COLOR_VALUE;
            break;

        case DarkCyan:
            color.R = 0;
            color.G = HALF_COLOR_VALUE;
            color.B = HALF_COLOR_VALUE;
            break;
        case DarkMagenta:
            color.R = HALF_COLOR_VALUE;
            color.G = 0;
            color.B = HALF_COLOR_VALUE;
            break;
        case DarkYellow:
            color.R = HALF_COLOR_VALUE;
            color.G = HALF_COLOR_VALUE;
            color.B = 0;
            break;

        case BrightRed:
            color.R = MAX_COLOR_VALUE;
            color.G = HALF_COLOR_VALUE;
            color.B = HALF_COLOR_VALUE;
            break;
        case BrightGreen:
            color.R = HALF_COLOR_VALUE;
            color.G = MAX_COLOR_VALUE;
            color.B = HALF_COLOR_VALUE;
            break;
        case BrightBlue:
            color.R = HALF_COLOR_VALUE;
            color.G = HALF_COLOR_VALUE;
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

        case BrightCyan:
            color.R = 0;
            color.G = THREE_QUARTERS_COLOR_VALUE;
            color.B = THREE_QUARTERS_COLOR_VALUE;
            break;
        case BrightMagenta:
            color.R = THREE_QUARTERS_COLOR_VALUE;
            color.G = 0;
            color.B = THREE_QUARTERS_COLOR_VALUE;
            break;
        case BrightYellow:
            color.R = THREE_QUARTERS_COLOR_VALUE;
            color.G = THREE_QUARTERS_COLOR_VALUE;
            color.B = 0.0f;
            break;
    }

    return color;
}

union Pixel {
    RGBA color;
    u32 value;

    Pixel() : value{0} {}
    Pixel(u8 r, u8 g, u8 b, u8 a) : color{r, g, b, a} {}
    explicit Pixel(const vec3 &rgb) : color(rgb) {}

    Pixel& operator = (const vec3 &rgb) {
        color = rgb;
        return *this;
    }
};


struct String {
    u32 length;
    char *char_ptr;

    String() : String{nullptr, 0} {}
    String(char *char_ptr, u32 length) : length{length}, char_ptr{char_ptr} {}

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

    String& operator = (char* CharPtr) {
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
    u8 float_digits_count = 3;
    String string{_buffer, 0};
    char _buffer[13]{};

    explicit NumberString(u8 digit_count = 3) : string{_buffer, 1}, float_digits_count{digit_count} {
        _buffer[12] = 0;
        for (u8 i = 0; i < 12; i++)
            _buffer[i] = ' ';
    }
    explicit NumberString(const char *str) : string{_buffer, 1} {
        _buffer[12] = 0;
        char *char_ptr = (char*)str;
        float_digits_count = String::getLength(char_ptr);
        if (float_digits_count > 12) float_digits_count = 12;
        char_ptr += float_digits_count;
        char_ptr--;
        for (u8 i = 11; i >= 0; i--, char_ptr--)
            _buffer[i] = (11 - i) < float_digits_count ? *char_ptr : ' ';
    }

    NumberString& operator = (i32 number) {
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

        return *this;
    }

    NumberString& operator = (f32 number) {
        f32 factor = 1;
        for (u8 i = 0; i < float_digits_count; i++) factor *= 10;
        i32 int_num = (i32)(number * factor);
        if (int_num == 0) {
            *this = (i32)factor;
            string.length++;
            string.char_ptr[0] = '.';
            string.char_ptr--;
            string.char_ptr[0] = '0';
            return *this;
        }

        bool is_negative = number < 0;
        bool is_fraction = is_negative ? number > -1 : number < 1;

        *this = int_num;

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

        return *this;
    }
};


struct PerTick {
    const f64 seconds, milliseconds, microseconds, nanoseconds;
    PerTick() = delete;
    explicit PerTick(const f64 tps) :
            seconds{     1          / tps},
            milliseconds{1000       / tps},
            microseconds{1000000    / tps},
            nanoseconds{ 1000000000 / tps} {}
};

struct Ticks {
    const PerTick per_tick;
    const u64 per_second;
    Ticks() = delete;
    explicit Ticks(const u64 tps) : per_second{tps}, per_tick{(f64)tps} {}
};

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
    explicit Timer(Ticks *tks) : ticks{tks}, ticks_before{os::getTicks()}, ticks_of_last_report{os::getTicks()} {};
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
    explicit Timers(Ticks *ticks) : update{ticks}, render{ticks}, aux{ticks} {}
};

struct Time {
    Ticks ticks;
    Timers timers;
    Time() : ticks{os::ticks_per_second}, timers{&ticks} {}
};


#define MAX_WIDTH 3840
#define MAX_HEIGHT 2160

#define PIXEL_SIZE 4
#define RENDER_SIZE Megabytes(8 * PIXEL_SIZE)

struct Dimensions {
    u32 width_times_height{0};
    f32 width_over_height{0};
    f32 height_over_width{0};
    f32 f_width{0};
    f32 f_height{0};
    f32 h_width{0};
    f32 h_height{0};
    u16 width{0};
    u16 height{0};

    Dimensions() = delete;
    Dimensions(u16 Width, u16 Height) :
            width_times_height{(u32)Width * (u32)Height},
            width_over_height{(f32)Width / (f32)Height},
            height_over_width{(f32)Height / (f32)Width},
            f_width{(f32)Width},
            f_height{(f32)Height},
            h_width{(f32)Width * 0.5f},
            h_height{(f32)Height * 0.5f},
            width{Width},
            height{Height} {}

    void update(u16 Width, u16 Height) {
        width = Width;
        height = Height;
        width_times_height = width * height;
        f_width  = (f32)width;
        f_height = (f32)height;
        h_width  = f_width  * 0.5f;
        h_height = f_height * 0.5f;
        width_over_height  = f_width  / f_height;
        height_over_width  = f_height / f_width;
    }
};

struct PixelGrid {
    Pixel* pixels = nullptr;
    Dimensions dimensions;

    PixelGrid() : dimensions(MAX_WIDTH, MAX_HEIGHT) {}

    INLINE Pixel* row(u32 y) const { return pixels + y * (u32)dimensions.width; }
    INLINE Pixel* operator[](u32 y) const { return row(y); }

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
    void fillTriangle(RGBA color, vec2 v1, vec2 v2, vec2 v3) const {
        // Cull this triangle against the edges of the viewport:
        vec2 pixel_min = min(v1, min(v2, v3));
        if (pixel_min.x >= dimensions.f_width ||
            pixel_min.y >= dimensions.f_height)
            return;

        vec2 pixel_max = max(v1, max(v2, v3));
        if (pixel_max.x < 0 ||
            pixel_max.y < 0)
            return;

        // Clip the bounds of the triangle to the viewport:
        pixel_min = pixel_min.clamped();
        pixel_max = pixel_max.clamped(vec2(dimensions.f_width - 1, dimensions.f_height - 1));

        // Compute area components:
        f32 ABy = v2.y - v1.y;
        f32 ABx = v2.x - v1.x;

        f32 ACy = v3.y - v1.y;
        f32 ACx = v3.x - v1.x;

        f32 ABC = ACx*ABy - ACy*ABx;

        // Cull faces facing backwards:
        if (ABC < 0) {
            vec2 tmp = v3;
            v3 = v2;
            v2 = tmp;

            ABy = v2.y - v1.y;
            ABx = v2.x - v1.x;

            ACy = v3.y - v1.y;
            ACx = v3.x - v1.x;
            ABC = ACx*ABy - ACy*ABx;
        } else if (ABC == 0)
            return;

        // Floor bounds coordinates down to their integral component:
        u32 first_x = (u32)pixel_min.x;
        u32 first_y = (u32)pixel_min.y;
        u32 last_x  = (u32)pixel_max.x;
        u32 last_y  = (u32)pixel_max.y;

        pixel_min.x = (f32)first_x;
        pixel_min.y = (f32)first_y;
        pixel_max.x = (f32)last_x;
        pixel_max.y = (f32)last_y;

        // Drawing: Top-down
        // Origin: Top-left

        // Compute weight constants:
        f32 one_over_ABC = 1.0f / ABC;

        f32 Cdx =  ABy * one_over_ABC;
        f32 Bdx = -ACy * one_over_ABC;

        f32 Cdy = -ABx * one_over_ABC;
        f32 Bdy =  ACx * one_over_ABC;

        // Compute initial areal coordinates for the first pixel center:
        pixel_min = vec2{pixel_min.x + 0.5f, pixel_min.y + 0.5f};
        f32 C_start = Cdx*pixel_min.x + Cdy*pixel_min.y + (v1.y*v2.x - v1.x*v2.y) * one_over_ABC;
        f32 B_start = Bdx*pixel_min.x + Bdy*pixel_min.y + (v3.y*v1.x - v3.x*v1.y) * one_over_ABC;

        f32 A, B, C;

        // Scan the bounds:
        for (u32 y = first_y; y <= last_y; y++, C_start += Cdy, B_start += Bdy) {
            B = B_start;
            C = C_start;

            for (u32 x = first_x; x <= last_x; x++, B += Bdx, C += Cdx) {
                if (Bdx < 0 && B < 0 ||
                    Cdx < 0 && C < 0)
                    break;

                A = 1 - B - C;

                // Skip the pixel if it's outside:
                if (fminf(A, fminf(B, C)) < 0)
                    continue;

                pixels[dimensions.width * y + x].color = color;
            }
        }
    }
    void fillTriangle(RGBA color, f32 *X, f32 *Y) const {
        vec2 v1{*X++, *Y++};
        vec2 v2{*X++, *Y++};
        vec2 v3{*X, *Y};
        return fillTriangle(color, v1, v2, v3);
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
    u8* address;
    u64 capacity, occupied;

    Memory(u8* address, const u64 capacity) : address{address}, capacity{capacity}, occupied{0} {}

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
    bool is_pressed{false}, is_handled{false}, double_clicked{false};

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
    f32 wheel_scroll_amount{0};

    bool moved{false};
    bool is_captured{false};
    bool move_handled{false};
    bool double_clicked{false};
    bool double_clicked_handled{false};
    bool wheel_scrolled{false};
    bool wheel_scroll_handled{false};
    bool raw_movement_handled{false};

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

struct KeyMap { u8 ctrl{0}, alt{0}, shift{0}, space{0}, tab{0}; };
struct IsPressed { bool ctrl{false}, alt{false}, shift{false}, space{false}, tab{false}; };
struct Controls {
    KeyMap key_map;
    IsPressed is_pressed;
    Mouse mouse;
};


struct SlimApp {
    Controls controls;
    PixelGrid window_content;
    Time time;

    bool is_running{true};
    void *user_data{nullptr};
    char* window_title{(char*)""};
    u16 window_width{480};
    u16 window_height{360};
    u64 additional_memory_size{0};

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

        memory = Memory{(u8*)memory_address, size};
        return true;
    }

    void* allocateMemory(u64 size) {
        void *new_memory = memory.allocate(size);
        if (new_memory) return new_memory;

        is_running = false;
        return nullptr;
    }

private:
    Memory memory{nullptr, 0};
};

SlimApp* createApp();

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

SlimApp *CURRENT_APP;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    MouseButton *mouse_button;
    IsPressed *is_pressed = &CURRENT_APP->controls.is_pressed;
    bool pressed = message == WM_SYSKEYDOWN || message == WM_KEYDOWN;
    u8 key = (u8)wParam;
    i32 x, y;
    f32 scroll_amount;

    switch (message) {
        case WM_DESTROY:
            CURRENT_APP->is_running = false;
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            GetClientRect(window, &win_rect);

            info.bmiHeader.biWidth = win_rect.right - win_rect.left;
            info.bmiHeader.biHeight = win_rect.top - win_rect.bottom;
            CURRENT_APP->window_content.dimensions.update((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            CURRENT_APP->OnWindowResize((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);
            CURRENT_APP->OnWindowRedraw();

            break;

        case WM_PAINT:
            SetDIBitsToDevice(win_dc,
                              0, 0, CURRENT_APP->window_content.dimensions.width, CURRENT_APP->window_content.dimensions.height,
                              0, 0, 0, CURRENT_APP->window_content.dimensions.height,
                              (u32*)CURRENT_APP->window_content.pixels, &info, DIB_RGB_COLORS);

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
            CURRENT_APP->OnKeyChanged(key, pressed);

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
                case WM_MBUTTONDBLCLK: mouse_button = &CURRENT_APP->controls.mouse.middle_button; break;
                case WM_RBUTTONUP:
                case WM_RBUTTONDOWN:
                case WM_RBUTTONDBLCLK: mouse_button = &CURRENT_APP->controls.mouse.right_button; break;
                default: mouse_button = &CURRENT_APP->controls.mouse.left_button;
            }

            switch (message) {
                case WM_MBUTTONDBLCLK:
                case WM_RBUTTONDBLCLK:
                case WM_LBUTTONDBLCLK: mouse_button->doubleClick(x, y); CURRENT_APP->controls.mouse.double_clicked = true; CURRENT_APP->OnMouseButtonDoubleClicked(mouse_button); break;
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                case WM_LBUTTONUP:     mouse_button->up(x, y);   CURRENT_APP->OnMouseButtonUp(mouse_button); break;
                default:               mouse_button->down(x, y); CURRENT_APP->OnMouseButtonDown(mouse_button); break;
            }

            break;

        case WM_MOUSEWHEEL:
            scroll_amount = (f32)(GET_WHEEL_DELTA_WPARAM(wParam)) / (f32)(WHEEL_DELTA);
            CURRENT_APP->controls.mouse.scroll(scroll_amount); CURRENT_APP->OnMouseWheelScrolled(scroll_amount);
            break;

        case WM_MOUSEMOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
            CURRENT_APP->controls.mouse.move(x, y);        CURRENT_APP->OnMouseMovementSet(x, y);
            CURRENT_APP->controls.mouse.setPosition(x, y); CURRENT_APP->OnMousePositionSet(x, y);
            break;

        case WM_INPUT:
            if ((hasRawMouseInput(lParam)) && (
                    raw_inputs.data.mouse.lLastX != 0 ||
                    raw_inputs.data.mouse.lLastY != 0)) {
                x = raw_inputs.data.mouse.lLastX;
                y = raw_inputs.data.mouse.lLastY;
                CURRENT_APP->controls.mouse.moveRaw(x, y); CURRENT_APP->OnMouseRawMovementSet(x, y);
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

    CURRENT_APP = createApp();
    CURRENT_APP->window_content.pixels = (Pixel*)window_content_memory;
    CURRENT_APP->controls.key_map.ctrl = VK_CONTROL;
    CURRENT_APP->controls.key_map.alt = VK_MENU;
    CURRENT_APP->controls.key_map.shift = VK_SHIFT;
    CURRENT_APP->controls.key_map.space = VK_SPACE;
    CURRENT_APP->controls.key_map.tab = VK_TAB;
    if (!CURRENT_APP->OnReady()) return -1;

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
    win_rect.right  = CURRENT_APP->window_width;
    win_rect.bottom = CURRENT_APP->window_height;
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    window = CreateWindowA(
            window_class.lpszClassName,
            CURRENT_APP->window_title,
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
    while (CURRENT_APP->is_running) {
        while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        CURRENT_APP->OnWindowRedraw();
        InvalidateRgn(window, nullptr, false);
    }

    return 0;
}

#endif