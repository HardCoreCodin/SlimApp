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

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long int  u32;
typedef unsigned long long u64;
typedef signed   short     i16;
typedef signed   long int  i32;

typedef float  f32;
typedef double f64;

#ifndef false
    #define false (u8)0
#endif

#ifndef true
    #define true (u8)1
#endif

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

typedef struct String {
    u32 length;
    char *char_ptr;
} String;

void setString(String *string, char *char_ptr) {
    string->char_ptr = char_ptr;
    string->length = 0;
    if (char_ptr)
        while (char_ptr[string->length])
            string->length++;
}

u32 getStringLength(char *string) {
    char *char_ptr = string;
    u32 length = 0;
    if (char_ptr) while (char_ptr[length]) length++;
    return length;
}

void copyToString(String *string, char* char_ptr, u32 offset) {
    string->length = offset;
    char *source_char = char_ptr;
    char *string_char = string->char_ptr + offset;
    while (source_char[0]) {
        *string_char = *source_char;
        string_char++;
        source_char++;
        string->length++;
    }
    *string_char = 0;
}

typedef struct NumberString {
    char _buffer[13];
    String string;
} NumberString;

void initNumberString(NumberString *number_string) {
    number_string->string.char_ptr = number_string->_buffer;
    number_string->string.length = 1;
    number_string->_buffer[12] = 0;
    for (u8 i = 0; i < 12; i++)
        number_string->_buffer[i] = ' ';
}

void printNumberIntoString(i32 number, NumberString *number_string) {
    initNumberString(number_string);
    char *buffer = number_string->_buffer;
    buffer[12] = 0;

    bool is_negative = number < 0;
    if (is_negative) number = -number;

    if (number) {
        u32 temp;
        buffer += 11;
        number_string->string.char_ptr = buffer;
        number_string->string.length = 0;

        for (u8 i = 0; i < 11; i++) {
            temp = number;
            number /= 10;
            number_string->string.length++;
            *buffer-- = (char)('0' + temp - number * 10);
            if (!number) {
                if (is_negative) {
                    *buffer = '-';
                    number_string->string.char_ptr--;
                    number_string->string.length++;
                }

                break;
            }
            number_string->string.char_ptr--;
        }
    } else {
        buffer[11] = '0';
        number_string->string.length = 1;
        number_string->string.char_ptr = buffer + 11;
    }
}

void printFloatIntoString(f32 number, NumberString *number_string, u8 float_digits_count) {
    f32 factor = 1;
    for (u8 i = 0; i < float_digits_count; i++) factor *= 10;
    i32 int_num = (i32)(number * factor);
    if (int_num == 0) {
        printNumberIntoString((i32)factor, number_string);
        number_string->string.length++;
        number_string->string.char_ptr[0] = '.';
        number_string->string.char_ptr--;
        number_string->string.char_ptr[0] = '0';
        return;
    }

    bool is_negative = number < 0;
    bool is_fraction = is_negative ? number > -1 : number < 1;

    printNumberIntoString(int_num, number_string);

    if (is_fraction) {
        u32 len = number_string->string.length;
        number_string->string.length++;
        number_string->string.char_ptr--;
        if (is_negative) {
            number_string->string.char_ptr[0] = '-';
            number_string->string.char_ptr[1] = '0';
        } else {
            number_string->string.char_ptr[0] = '0';
        }
        if (len < float_digits_count) {
            for (u32 i = 0; i < (float_digits_count - len); i++) {
                number_string->string.length++;
                number_string->string.char_ptr--;
                number_string->string.char_ptr[0] = '0';
            }
        }
    }

    static char tmp[13];
    tmp[number_string->string.length + 1] = 0;
    for (u8 i = 0; i < (u8)number_string->string.length; i++) {
        u8 char_count_from_right_to_left = (u8)number_string->string.length - i - 1;
        if (char_count_from_right_to_left >= float_digits_count) tmp[i] = number_string->string.char_ptr[i];
        else                                                     tmp[i + 1] = number_string->string.char_ptr[i];
    }
    tmp[number_string->string.length - float_digits_count] = '.';
    copyToString(&number_string->string, tmp, 0);
    if (is_negative) number_string->string.length++;
}