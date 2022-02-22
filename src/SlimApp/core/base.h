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