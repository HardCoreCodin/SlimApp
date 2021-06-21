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

#ifdef __cplusplus
    #define null nullptr
#else
    #define null 0
    typedef unsigned char      bool;
 #endif

#ifndef false
  #define false 0
#endif

#ifndef true
  #define true 1
#endif

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef signed   short     i16;
typedef signed   int       i32;

typedef float  f32;
typedef double f64;

typedef void* (*CallbackWithInt)(u64 size);
typedef void (*CallbackWithBool)(bool on);
typedef void (*CallbackWithCharPtr)(char* str);

#define MAX_COLOR_VALUE 0xFF

typedef struct vec2  { f32 x, y; } vec2;
typedef struct vec2i { i32 x, y; } vec2i;
typedef struct Rect { vec2i min, max; } Rect;
typedef struct RGBA { u8 B, G, R, A; } RGBA;
typedef union  Pixel { RGBA color; u32 value; } Pixel;

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

INLINE bool inRange(i32 value, i32 end, i32 start) {
    return value >= start && value < end;
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

typedef struct NumberStringBuffer {
    char _buffer[12];
    char *string;
    u8 digit_count;
} NumberStringBuffer;

void printNumberIntoString(i32 number, NumberStringBuffer *number_string) {
    char *buffer = number_string->_buffer;
    buffer[11] = 0;
    for (u8 i = 0; i < 11; i++) buffer[i] = ' ';

    bool is_negative = number < 0;
    if (is_negative) number = -number;

    if (number) {
        u32 temp;
        buffer += 11;
        number_string->string = buffer;
        number_string->digit_count = 0;

        for (u8 i = 0; i < 11; i++) {
            temp = number;
            number /= 10;
            number_string->digit_count++;
            *buffer-- = (char)('0' + temp - number * 10);
            if (!number) {
                if (is_negative) {
                    *buffer = '-';
                    number_string->string--;
                    number_string->digit_count++;
                }

                break;
            }
            number_string->string--;
        }
    } else {
        buffer[11] = '0';
        number_string->digit_count = 1;
        number_string->string = buffer + 11;
    }
}