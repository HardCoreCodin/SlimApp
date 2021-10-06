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


typedef u64 (*GetTicks)();

typedef struct PerTick {
    f64 seconds, milliseconds, microseconds, nanoseconds;
} PerTick;

typedef struct Ticks {
    PerTick per_tick;
    u64 per_second;
} Ticks;

typedef struct Timer {
    GetTicks getTicks;
    Ticks *ticks;

    f32 delta_time;
    u64 ticks_before,
            ticks_after,
            ticks_diff,
            accumulated_ticks,
            accumulated_frame_count,
            ticks_of_last_report,
            seconds,
            milliseconds,
            microseconds,
            nanoseconds;
    f64 average_frames_per_tick,
            average_ticks_per_frame;
    u16 average_frames_per_second,
            average_milliseconds_per_frame,
            average_microseconds_per_frame,
            average_nanoseconds_per_frame;
} Timer;

void initTimer(Timer *timer, GetTicks getTicks, Ticks *ticks) {
    timer->getTicks = getTicks;
    timer->ticks    = ticks;

    timer->delta_time = 0;
    timer->ticks_before = 0;
    timer->ticks_after = 0;
    timer->ticks_diff = 0;

    timer->accumulated_ticks = 0;
    timer->accumulated_frame_count = 0;

    timer->ticks_of_last_report = 0;

    timer->seconds = 0;
    timer->milliseconds = 0;
    timer->microseconds = 0;
    timer->nanoseconds = 0;

    timer->average_frames_per_tick = 0;
    timer->average_ticks_per_frame = 0;
    timer->average_frames_per_second = 0;
    timer->average_milliseconds_per_frame = 0;
    timer->average_microseconds_per_frame = 0;
    timer->average_nanoseconds_per_frame = 0;
}

typedef struct Timers {
    Timer update, render, aux;
} Timers;

typedef struct Time {
    Timers timers;
    Ticks ticks;
    GetTicks getTicks;
} Time;

void initTime(Time *time, GetTicks getTicks, u64 ticks_per_second) {
    time->getTicks = getTicks;
    time->ticks.per_second = ticks_per_second;

    time->ticks.per_tick.seconds      = 1          / (f64)(time->ticks.per_second);
    time->ticks.per_tick.milliseconds = 1000       / (f64)(time->ticks.per_second);
    time->ticks.per_tick.microseconds = 1000000    / (f64)(time->ticks.per_second);
    time->ticks.per_tick.nanoseconds  = 1000000000 / (f64)(time->ticks.per_second);

    initTimer(&time->timers.update, getTicks, &time->ticks);
    initTimer(&time->timers.render, getTicks, &time->ticks);
    initTimer(&time->timers.aux,    getTicks, &time->ticks);

    time->timers.update.ticks_before = time->timers.update.ticks_of_last_report = getTicks();
}

void accumulateTimer(Timer* timer) {
    timer->ticks_diff = timer->ticks_after - timer->ticks_before;
    timer->accumulated_ticks += timer->ticks_diff;
    timer->accumulated_frame_count++;

    timer->seconds      = (u64)(timer->ticks->per_tick.seconds      * (f64)(timer->ticks_diff));
    timer->milliseconds = (u64)(timer->ticks->per_tick.milliseconds * (f64)(timer->ticks_diff));
    timer->microseconds = (u64)(timer->ticks->per_tick.microseconds * (f64)(timer->ticks_diff));
    timer->nanoseconds  = (u64)(timer->ticks->per_tick.nanoseconds  * (f64)(timer->ticks_diff));
}

void averageTimer(Timer *timer) {
    timer->average_frames_per_tick = (f64)timer->accumulated_frame_count / timer->accumulated_ticks;
    timer->average_ticks_per_frame = (f64)timer->accumulated_ticks / timer->accumulated_frame_count;
    timer->average_frames_per_second = (u16)(timer->average_frames_per_tick      * timer->ticks->per_second);
    timer->average_milliseconds_per_frame = (u16)(timer->average_ticks_per_frame * timer->ticks->per_tick.milliseconds);
    timer->average_microseconds_per_frame = (u16)(timer->average_ticks_per_frame * timer->ticks->per_tick.microseconds);
    timer->average_nanoseconds_per_frame = (u16)(timer->average_ticks_per_frame  * timer->ticks->per_tick.nanoseconds);
    timer->accumulated_ticks = timer->accumulated_frame_count = 0;
}

INLINE void startFrameTimer(Timer *timer) {
    timer->ticks_after = timer->ticks_before;
    timer->ticks_before = timer->getTicks();
    timer->ticks_diff = timer->ticks_before - timer->ticks_after;
    timer->delta_time = (f32)(timer->ticks_diff * timer->ticks->per_tick.seconds);
}

INLINE void endFrameTimer(Timer *timer) {
    timer->ticks_after = timer->getTicks();
    accumulateTimer(timer);
    if (timer->accumulated_ticks >= timer->ticks->per_second / 4)
        averageTimer(timer);
}


#define MAX_WIDTH 3840
#define MAX_HEIGHT 2160

#define PIXEL_SIZE 4
#define RENDER_SIZE Megabytes(8 * PIXEL_SIZE)

typedef struct Dimensions {
    u16 width, height;
    u32 width_times_height;
    f32 height_over_width,
            width_over_height,
            f_height, f_width,
            h_height, h_width;
} Dimensions;

void updateDimensions(Dimensions *dimensions, u16 width, u16 height) {
    dimensions->width = width;
    dimensions->height = height;
    dimensions->width_times_height = dimensions->width * dimensions->height;
    dimensions->f_width  =      (f32)dimensions->width;
    dimensions->f_height =      (f32)dimensions->height;
    dimensions->h_width  =           dimensions->f_width  / 2;
    dimensions->h_height =           dimensions->f_height / 2;
    dimensions->width_over_height  = dimensions->f_width  / dimensions->f_height;
    dimensions->height_over_width  = dimensions->f_height / dimensions->f_width;
}

typedef struct PixelGrid {
    Dimensions dimensions;
    Pixel* pixels;
} PixelGrid;

void initPixelGrid(PixelGrid *pixel_grid, Pixel* pixels_memory) {
    pixel_grid->pixels = pixels_memory;
    updateDimensions(&pixel_grid->dimensions, MAX_WIDTH, MAX_HEIGHT);
}

void fillPixelGrid(PixelGrid *pixel_grid, RGBA color) {
    for (u32 i = 0; i < pixel_grid->dimensions.width_times_height; i++)
        pixel_grid->pixels[i].color = color;
}

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define MEMORY_SIZE Gigabytes(1)
#define MEMORY_BASE Terabytes(2)

typedef struct Memory {
    u8* address;
    u64 occupied, capacity;
} Memory;

void initMemory(Memory *memory, u8* address, u64 capacity) {
    memory->address = (u8*)address;
    memory->capacity = capacity;
    memory->occupied = 0;
}

void* allocateMemory(Memory *memory, u64 size) {
    if (!memory->address) return null;
    memory->occupied += size;
    if (memory->occupied > memory->capacity) return null;

    void* address = memory->address;
    memory->address += size;
    return address;
}

typedef struct MouseButton {
    vec2i down_pos, up_pos, double_click_pos;
    bool is_pressed, is_handled;
} MouseButton;

typedef struct Mouse {
    MouseButton middle_button, right_button, left_button;
    vec2i pos, pos_raw_diff, movement;
    f32 wheel_scroll_amount;
    bool moved, is_captured,
            move_handled,
            double_clicked,
            double_clicked_handled,
            wheel_scrolled,
            wheel_scroll_handled,
            raw_movement_handled;
} Mouse;

void initMouse(Mouse *mouse) {
    mouse->is_captured = false;

    mouse->moved = false;
    mouse->move_handled = false;

    mouse->double_clicked = false;
    mouse->double_clicked_handled = false;

    mouse->wheel_scrolled = false;
    mouse->wheel_scroll_amount = 0;
    mouse->wheel_scroll_handled = false;

    mouse->pos.x = 0;
    mouse->pos.y = 0;
    mouse->pos_raw_diff.x = 0;
    mouse->pos_raw_diff.y = 0;
    mouse->raw_movement_handled = false;

    mouse->middle_button.is_pressed = false;
    mouse->middle_button.is_handled = false;
    mouse->middle_button.up_pos.x = 0;
    mouse->middle_button.down_pos.x = 0;

    mouse->right_button.is_pressed = false;
    mouse->right_button.is_handled = false;
    mouse->right_button.up_pos.x = 0;
    mouse->right_button.down_pos.x = 0;

    mouse->left_button.is_pressed = false;
    mouse->left_button.is_handled = false;
    mouse->left_button.up_pos.x = 0;
    mouse->left_button.down_pos.x = 0;
}

void resetMouseChanges(Mouse *mouse) {
    if (mouse->move_handled) {
        mouse->move_handled = false;
        mouse->moved = false;
    }
    if (mouse->double_clicked_handled) {
        mouse->double_clicked_handled = false;
        mouse->double_clicked = false;
    }
    if (mouse->raw_movement_handled) {
        mouse->raw_movement_handled = false;
        mouse->pos_raw_diff.x = 0;
        mouse->pos_raw_diff.y = 0;
    }
    if (mouse->wheel_scroll_handled) {
        mouse->wheel_scroll_handled = false;
        mouse->wheel_scrolled = false;
        mouse->wheel_scroll_amount = 0;
    }
}

typedef struct KeyMap      { u8 ctrl, alt, shift, space, tab; } KeyMap;
typedef struct IsPressed { bool ctrl, alt, shift, space, tab; } IsPressed;
typedef struct Controls {
    IsPressed is_pressed;
    KeyMap key_map;
    Mouse mouse;
} Controls;

void initControls(Controls *controls) {
    initMouse(&controls->mouse);
}


void drawHLine2D(PixelGrid *canvas, RGBA color, i32 from, i32 to, i32 at) {
    if (!inRange(at, canvas->dimensions.height, 0)) return;

    i32 offset = at * (i32)canvas->dimensions.width;
    i32 first, last;
    subRange(from, to, canvas->dimensions.width, 0, &first, &last);
    first += offset;
    last += offset;
    for (i32 i = first; i <= last; i++) canvas->pixels[i].color = color;
}

void drawVLine2D(PixelGrid *canvas, RGBA color, i32 from, i32 to, i32 at) {
    if (!inRange(at, canvas->dimensions.width, 0)) return;
    i32 first, last;

    subRange(from, to, canvas->dimensions.height, 0, &first, &last);
    first *= canvas->dimensions.width; first += at;
    last  *= canvas->dimensions.width; last  += at;
    for (i32 i = first; i <= last; i += canvas->dimensions.width) canvas->pixels[i].color = color;
}

void drawLine2D(PixelGrid *canvas, RGBA color, i32 x0, i32 y0, i32 x1, i32 y1) {
    if (x0 < 0 &&
        y0 < 0 &&
        x1 < 0 &&
        y1 < 0)
        return;

    if (x0 == x1) {
        drawVLine2D(canvas, color, y0, y1, x1);
        return;
    }

    if (y0 == y1) {
        drawHLine2D(canvas, color, x0, x1, y1);
        return;
    }

    i32 width  = (i32)canvas->dimensions.width;
    i32 height = (i32)canvas->dimensions.height;

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
        if (inRange(index, canvas->dimensions.width_times_height, 0)) {
            if (is_steap) {
                if (inRange(current1, height, 0) &&
                    inRange(current2, width, 0))
                    canvas->pixels[index].color = color;
            } else {
                if (inRange(current2, height, 0) &&
                    inRange(current1, width, 0))
                    canvas->pixels[index].color = color;
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

void drawRect(PixelGrid *canvas, RGBA color, Rect *rect) {
    if (rect->max.x < 0 || rect->min.x >= canvas->dimensions.width ||
        rect->max.y < 0 || rect->min.y >= canvas->dimensions.height)
        return;

    drawHLine2D(canvas, color, rect->min.x, rect->max.x, rect->min.y);
    drawHLine2D(canvas, color, rect->min.x, rect->max.x, rect->max.y);
    drawVLine2D(canvas, color, rect->min.y, rect->max.y, rect->min.x);
    drawVLine2D(canvas, color, rect->min.y, rect->max.y, rect->max.x);
}

void fillRect(PixelGrid *canvas, RGBA color, Rect *rect) {
    if (rect->max.x < 0 || rect->min.x >= canvas->dimensions.width ||
        rect->max.y < 0 || rect->min.y >= canvas->dimensions.height)
        return;

    i32 min_x, min_y, max_x, max_y;
    subRange(rect->min.x, rect->max.x, canvas->dimensions.width,  0, &min_x, &max_x);
    subRange(rect->min.y, rect->max.y, canvas->dimensions.height, 0, &min_y, &max_y);
    for (i32 y = min_y; y <= max_y; y++)
        drawHLine2D(canvas, color, min_x, max_x, y);
}

void fillTriangle(PixelGrid *canvas, RGBA color, f32 *X, f32 *Y) {
    u16 W = canvas->dimensions.width;
    u16 H = canvas->dimensions.height;
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
                canvas->pixels[offset + x].color = color;
        }
        offset += W;
        xs += y < y3i ? dx3 : dx2;
        xe += y < y2i ? dx1 : dx2;
    }
}

void drawCircle(PixelGrid *canvas, RGBA color, i32 center_x, i32 center_y, i32 radius) {
    if (radius <= 1) {
        if (inRange(0, center_x, canvas->dimensions.width - 1) &&
            inRange(0, center_y, canvas->dimensions.height - 1))
            canvas->pixels[canvas->dimensions.width * center_y + center_x].color = color;

        return;
    }

    i32 width = canvas->dimensions.width;
    i32 size  = canvas->dimensions.width_times_height;

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
            if (Sx1 >= 0 && Sx1 < width) canvas->pixels[Sy1 + Sx1].color = color;
            if (Ex1 >= 0 && Ex1 < width) canvas->pixels[Sy1 + Ex1].color = color;
        }
        if (Ey1 >= 0 && Ey1 < size) {
            if (Sx1 >= 0 && Sx1 < width) canvas->pixels[Ey1 + Sx1].color = color;
            if (Ex1 >= 0 && Ex1 < width) canvas->pixels[Ey1 + Ex1].color = color;
        }

        if (Sy2 >= 0 && Sy2 < size) {
            if (Sx2 >= 0 && Sx2 < width) canvas->pixels[Sy2 + Sx2].color = color;
            if (Ex2 >= 0 && Ex2 < width) canvas->pixels[Sy2 + Ex2].color = color;
        }
        if (Ey2 >= 0 && Ey2 < size) {
            if (Sx2 >= 0 && Sx2 < width) canvas->pixels[Ey2 + Sx2].color = color;
            if (Ex2 >= 0 && Ex2 < width) canvas->pixels[Ey2 + Ex2].color = color;
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

void fillCircle(PixelGrid *canvas, RGBA color, i32 center_x, i32 center_y, i32 radius) {
    if (radius <= 1) {
        if (inRange(0, center_x, canvas->dimensions.width - 1) &&
            inRange(0, center_y, canvas->dimensions.height - 1))
            canvas->pixels[canvas->dimensions.width * center_y + center_x].color = color;

        return;
    }

    i32 width = canvas->dimensions.width;
    i32 size  = canvas->dimensions.width_times_height;

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
        if (Sy1 >= 0 && Sy1 < size) for (i = start; i <= end; i++) canvas->pixels[Sy1 + i].color = color;
        if (Ey1 >= 0 && Ey1 < size) for (i = start; i <= end; i++) canvas->pixels[Ey1 + i].color = color;

        start = Sx2 > 0 ? Sx2 : 0;
        end   = Ex2 < (width - 1) ? Ex2 : (width - 1);
        if (Sy2 >= 0 && Sy2 < size) for (i = start; i <= end; i++) canvas->pixels[Sy2 + i].color = color;
        if (Ey2 >= 0 && Ey2 < size) for (i = start; i <= end; i++) canvas->pixels[Ey2 + i].color = color;

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

void drawText(PixelGrid *canvas, RGBA color, char *str, i32 x, i32 y) {
    if (x < 0 || x > canvas->dimensions.width - FONT_WIDTH ||
        y < 0 || y > canvas->dimensions.height - FONT_HEIGHT)
        return;

    u16 current_x = (u16)x;
    u16 current_y = (u16)y;
    u16 t_offset;
    u16 pixel_line_step = canvas->dimensions.width - FONT_WIDTH;
    u32 char_line_step  = canvas->dimensions.width * LINE_HEIGHT;
    Pixel* pixel = canvas->pixels + canvas->dimensions.width * y + x;
    Pixel* character_pixel;
    u8* byte;
    char character = *str;

    while (character) {
        if (character == '\n') {
            if (current_y + FONT_HEIGHT > canvas->dimensions.height)
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
            if (current_x + FONT_WIDTH > canvas->dimensions.width)
                return;
        }
        character = *++str;
    }
}

void drawNumber(PixelGrid *canvas, RGBA color, i32 number, i32 x, i32 y) {
    static NumberString number_string;
    printNumberIntoString(number, &number_string);
    drawText(canvas, color, number_string.string.char_ptr, x - number_string.string.length * FONT_WIDTH, y);
}

typedef struct AppCallbacks {
    void (*windowRedraw)();
    void (*windowResize)(u16 width, u16 height);
    void (*keyChanged)(  u8 key, bool pressed);
    void (*mouseButtonUp)(  MouseButton *mouse_button);
    void (*mouseButtonDown)(MouseButton *mouse_button);
    void (*mouseButtonDoubleClicked)(MouseButton *mouse_button);
    void (*mouseWheelScrolled)(f32 amount);
    void (*mousePositionSet)(i32 x, i32 y);
    void (*mouseMovementSet)(i32 x, i32 y);
    void (*mouseRawMovementSet)(i32 x, i32 y);
} AppCallbacks;

typedef void* (*CallbackForFileOpen)(const char* file_path);
typedef bool  (*CallbackForFileRW)(void *out, unsigned long, void *handle);
typedef void  (*CallbackForFileClose)(void *handle);

typedef struct Platform {
    GetTicks             getTicks;
    CallbackWithInt      getMemory;
    CallbackWithCharPtr  setWindowTitle;
    CallbackWithBool     setWindowCapture;
    CallbackWithBool     setCursorVisibility;
    CallbackForFileClose closeFile;
    CallbackForFileOpen  openFileForReading;
    CallbackForFileOpen  openFileForWriting;
    CallbackForFileRW    readFromFile;
    CallbackForFileRW    writeToFile;
    u64 ticks_per_second;
} Platform;

typedef struct Defaults {
    char* title;
    u16 width, height;
    u64 additional_memory_size;
} Defaults;

typedef struct App {
    Memory memory;
    Platform platform;
    Controls controls;
    PixelGrid window_content;
    AppCallbacks on;
    Time time;
    bool is_running;
    void *user_data;
} App;

App *app;

void initApp(Defaults *defaults);

void _windowRedraw() {
    if (!app->is_running) return;
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _windowResize(u16 width, u16 height) {
    if (!app->is_running) return;
    updateDimensions(&app->window_content.dimensions, width, height);

    if (app->on.windowResize) app->on.windowResize(width, height);
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _keyChanged(u8 key, bool pressed) {
    if (key == app->controls.key_map.ctrl)  app->controls.is_pressed.ctrl  = pressed;
    else if (key == app->controls.key_map.alt)   app->controls.is_pressed.alt   = pressed;
    else if (key == app->controls.key_map.shift) app->controls.is_pressed.shift = pressed;
    else if (key == app->controls.key_map.space) app->controls.is_pressed.space = pressed;
    else if (key == app->controls.key_map.tab)   app->controls.is_pressed.tab   = pressed;

    if (app->on.keyChanged) app->on.keyChanged(key, pressed);
}

void _mouseButtonDown(MouseButton *mouse_button, i32 x, i32 y) {
    mouse_button->is_pressed = true;
    mouse_button->is_handled = false;

    mouse_button->down_pos.x = x;
    mouse_button->down_pos.y = y;

    if (app->on.mouseButtonDown) app->on.mouseButtonDown(mouse_button);
}

void _mouseButtonUp(MouseButton *mouse_button, i32 x, i32 y) {
    mouse_button->is_pressed = false;
    mouse_button->is_handled = false;

    mouse_button->up_pos.x = x;
    mouse_button->up_pos.y = y;

    if (app->on.mouseButtonUp) app->on.mouseButtonUp(mouse_button);
}

void _mouseButtonDoubleClicked(MouseButton *mouse_button, i32 x, i32 y) {
    app->controls.mouse.double_clicked = true;
    mouse_button->double_click_pos.x = x;
    mouse_button->double_click_pos.y = y;
    if (app->on.mouseButtonDoubleClicked) app->on.mouseButtonDoubleClicked(mouse_button);
}

void _mouseWheelScrolled(f32 amount) {
    app->controls.mouse.wheel_scroll_amount += amount * 100;
    app->controls.mouse.wheel_scrolled = true;

    if (app->on.mouseWheelScrolled) app->on.mouseWheelScrolled(amount);
}

void _mousePositionSet(i32 x, i32 y) {
    app->controls.mouse.pos.x = x;
    app->controls.mouse.pos.y = y;

    if (app->on.mousePositionSet) app->on.mousePositionSet(x, y);
}

void _mouseMovementSet(i32 x, i32 y) {
    app->controls.mouse.movement.x = x - app->controls.mouse.pos.x;
    app->controls.mouse.movement.y = y - app->controls.mouse.pos.y;
    app->controls.mouse.moved = true;

    if (app->on.mouseMovementSet) app->on.mouseMovementSet(x, y);
}

void _mouseRawMovementSet(i32 x, i32 y) {
    app->controls.mouse.pos_raw_diff.x += x;
    app->controls.mouse.pos_raw_diff.y += y;
    app->controls.mouse.moved = true;

    if (app->on.mouseRawMovementSet) app->on.mouseRawMovementSet(x, y);
}

bool initAppMemory(u64 size) {
    if (app->memory.address) return false;

    void* memory_address = app->platform.getMemory(size);
    if (!memory_address) {
        app->is_running = false;
        return false;
    }

    initMemory(&app->memory, (u8*)memory_address, size);
    return true;
}

void* allocateAppMemory(u64 size) {
    void *new_memory = allocateMemory(&app->memory, size);
    if (new_memory) return new_memory;

    app->is_running = false;
    return null;
}

void _initApp(Defaults *defaults, void* window_content_memory) {
    app->is_running = true;
    app->user_data = null;
    app->memory.address = null;

    app->on.windowRedraw = null;
    app->on.keyChanged = null;
    app->on.mouseButtonUp = null;
    app->on.mouseButtonDown = null;
    app->on.mouseButtonDoubleClicked = null;
    app->on.mouseWheelScrolled = null;
    app->on.mousePositionSet = null;
    app->on.mouseMovementSet = null;
    app->on.mouseRawMovementSet = null;

    initTime(&app->time, app->platform.getTicks, app->platform.ticks_per_second);
    initControls(&app->controls);
    initPixelGrid(&app->window_content, (Pixel*)window_content_memory);

    defaults->title = (char*)"";
    defaults->width = 480;
    defaults->height = 360;
    defaults->additional_memory_size = 0;
    initApp(defaults);
}

#ifdef __linux__
    //linux code goes here
#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifndef NDEBUG
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

void DisplayError(LPTSTR lpszFunction) {
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    unsigned int last_error = GetLastError();

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            null, last_error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf, 0, null);

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

u64 Win32_ticksPerSecond;
LARGE_INTEGER performance_counter;

void Win32_setWindowTitle(char* str) { SetWindowTextA(window, str); }
void Win32_setCursorVisibility(bool on) { ShowCursor(on); }
void Win32_setWindowCapture(bool on) { if (on) SetCapture(window); else ReleaseCapture(); }
u64 Win32_getTicks() {
    QueryPerformanceCounter(&performance_counter);
    return (u64)performance_counter.QuadPart;
}
void* Win32_getMemory(u64 size) {
    return VirtualAlloc((LPVOID)MEMORY_BASE, (SIZE_T)size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}

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

void Win32_closeFile(void *handle) { CloseHandle(handle); }
void* Win32_openFileForReading(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_READ,          // open for reading
                               FILE_SHARE_READ,       // share for reading
                               null,                  // default security
                               OPEN_EXISTING,         // existing file only
                               FILE_ATTRIBUTE_NORMAL, // normal file
                               null);                 // no attr. template
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), path);
        return null;
    }
#endif
    return handle;
}
void* Win32_openFileForWriting(const char* path) {
    HANDLE handle = CreateFile(path,           // file to open
                               GENERIC_WRITE,          // open for writing
                               0,                      // do not share
                               null,                   // default security
                               OPEN_ALWAYS,            // create new or open existing
                               FILE_ATTRIBUTE_NORMAL,  // normal file
                               null);
#ifndef NDEBUG
    if (handle == INVALID_HANDLE_VALUE) {
        DisplayError(TEXT((LPTSTR)"CreateFile"));
        _tprintf(TEXT("Terminal failure: unable to open file \"%s\" for write.\n"), path);
        return null;
    }
#endif
    return handle;
}
bool Win32_readFromFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_read = 0;
    BOOL result = ReadFile(handle, out, size, &bytes_read, null);
#ifndef NDEBUG
    if (result == FALSE) {
        DisplayError(TEXT((LPTSTR)"ReadFile"));
        printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", (unsigned int)GetLastError());
        CloseHandle(handle);
    }
#endif
    return result != FALSE;
}

bool Win32_writeToFile(LPVOID out, DWORD size, HANDLE handle) {
    DWORD bytes_written = 0;
    BOOL result = WriteFile(handle, out, size, &bytes_written, null);
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
    switch (message) {
        case WM_DESTROY:
            app->is_running = false;
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            GetClientRect(window, &win_rect);

            info.bmiHeader.biWidth = win_rect.right - win_rect.left;
            info.bmiHeader.biHeight = win_rect.top - win_rect.bottom;

            _windowResize((u16)info.bmiHeader.biWidth, (u16)-info.bmiHeader.biHeight);

            break;

        case WM_PAINT:
            SetDIBitsToDevice(win_dc,
                              0, 0, app->window_content.dimensions.width, app->window_content.dimensions.height,
                              0, 0, 0, app->window_content.dimensions.height,
                              (u32*)app->window_content.pixels, &info, DIB_RGB_COLORS);

            ValidateRgn(window, null);
            break;

        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            _keyChanged((u8)wParam, true);
            break;

        case WM_SYSKEYUP:
        case WM_KEYUP: _keyChanged((u8)wParam, false); break;

        case WM_MBUTTONUP:     _mouseButtonUp(  &app->controls.mouse.middle_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_MBUTTONDOWN:   _mouseButtonDown(&app->controls.mouse.middle_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_LBUTTONDOWN:   _mouseButtonDown(&app->controls.mouse.left_button,   GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_LBUTTONUP  :   _mouseButtonUp(  &app->controls.mouse.left_button,   GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_RBUTTONDOWN:   _mouseButtonDown(&app->controls.mouse.right_button,  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_RBUTTONUP:     _mouseButtonUp(  &app->controls.mouse.right_button,  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_LBUTTONDBLCLK: _mouseButtonDoubleClicked(&app->controls.mouse.left_button,   GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_RBUTTONDBLCLK: _mouseButtonDoubleClicked(&app->controls.mouse.right_button,  GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_MBUTTONDBLCLK: _mouseButtonDoubleClicked(&app->controls.mouse.middle_button, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
        case WM_MOUSEWHEEL:    _mouseWheelScrolled((f32)(GET_WHEEL_DELTA_WPARAM(wParam)) / (f32)(WHEEL_DELTA)); break;
        case WM_MOUSEMOVE:
            _mouseMovementSet(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            _mousePositionSet(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            break;

        case WM_INPUT:
            if ((hasRawMouseInput(lParam)) && (
                    raw_inputs.data.mouse.lLastX != 0 ||
                    raw_inputs.data.mouse.lLastY != 0))
                _mouseRawMovementSet(
                        raw_inputs.data.mouse.lLastX,
                        raw_inputs.data.mouse.lLastY
                );

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {

    void* app_memory = GlobalAlloc(GPTR, sizeof(App));
    if (!app_memory)
        return -1;

    app = (App*)app_memory;

    void* window_content_memory = GlobalAlloc(GPTR, RENDER_SIZE);
    if (!window_content_memory)
        return -1;

    LARGE_INTEGER performance_frequency;
    QueryPerformanceFrequency(&performance_frequency);
    Win32_ticksPerSecond = (u64)performance_frequency.QuadPart;

    app->controls.key_map.space = VK_SPACE;
    app->controls.key_map.shift = VK_SHIFT;
    app->controls.key_map.ctrl  = VK_CONTROL;
    app->controls.key_map.alt   = VK_MENU;
    app->controls.key_map.tab   = VK_TAB;

    app->platform.ticks_per_second    = Win32_ticksPerSecond;
    app->platform.getTicks            = Win32_getTicks;
    app->platform.getMemory           = Win32_getMemory;
    app->platform.setWindowTitle      = Win32_setWindowTitle;
    app->platform.setWindowCapture    = Win32_setWindowCapture;
    app->platform.setCursorVisibility = Win32_setCursorVisibility;
    app->platform.closeFile           = Win32_closeFile;
    app->platform.openFileForReading  = Win32_openFileForReading;
    app->platform.openFileForWriting  = Win32_openFileForWriting;
    app->platform.readFromFile        = Win32_readFromFile;
    app->platform.writeToFile         = Win32_writeToFile;

    Defaults defaults;
    _initApp(&defaults, window_content_memory);

    info.bmiHeader.biSize        = sizeof(info.bmiHeader);
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biBitCount    = 32;
    info.bmiHeader.biPlanes      = 1;

    window_class.lpszClassName  = "RnDer";
    window_class.hInstance      = hInstance;
    window_class.lpfnWndProc    = WndProc;
    window_class.style          = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
    window_class.hCursor        = LoadCursorA(null, IDC_ARROW);

    if (!RegisterClassA(&window_class)) return -1;

    win_rect.top = 0;
    win_rect.left = 0;
    win_rect.right  = defaults.width;
    win_rect.bottom = defaults.height;
    AdjustWindowRect(&win_rect, WS_OVERLAPPEDWINDOW, false);

    window = CreateWindowA(
            window_class.lpszClassName,
            defaults.title,
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,
            CW_USEDEFAULT,
            win_rect.right - win_rect.left,
            win_rect.bottom - win_rect.top,

            null,
            null,
            hInstance,
            null
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
        while (PeekMessageA(&message, null, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        _windowRedraw();
        InvalidateRgn(window, null, false);
    }

    return 0;
}

#endif