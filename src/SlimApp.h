#pragma once

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
typedef struct RGBA  { u8 B, G, R, A; } RGBA;
typedef struct Rect  { vec2i min, max; } Rect;
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

inline bool inRange(i32 value, i32 end, i32 start) {
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
            number_string->string--;
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
        }
    } else {
        buffer[11] = '0';
        number_string->digit_count = 1;
        number_string->string = buffer + 10;
    }
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

inline void startFrameTimer(Timer *timer) {
    timer->ticks_after = timer->ticks_before;
    timer->ticks_before = timer->getTicks();
    timer->ticks_diff = timer->ticks_before - timer->ticks_after;
    timer->delta_time = (f32)(timer->ticks_diff * timer->ticks->per_tick.seconds);
}

inline void endFrameTimer(Timer *timer) {
    timer->ticks_after = timer->getTicks();
    accumulateTimer(timer);
    if (timer->accumulated_ticks >= timer->ticks->per_tick.seconds) averageTimer(timer);
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

typedef struct ArenaAllocator {
    u8* address;
    u64 occupied;
} ArenaAllocator;

void initArenaAllocator(ArenaAllocator *arena_allocator, u8* memory) {
    arena_allocator->address = (u8*)memory;
    arena_allocator->occupied = 0;
}

void* allocateMemory(ArenaAllocator *memory, u64 size) {
    if (!memory->address) return null;

    memory->occupied += size;

    void* address = memory->address;
    memory->address += size;
    return address;
}

typedef struct MouseButton {
    vec2i down_pos, up_pos;
    bool is_pressed, is_handled;
} MouseButton;

typedef struct Mouse {
    MouseButton middle_button, right_button, left_button;
    vec2i pos, pos_raw_diff, movement;
    f32 wheel_scroll_amount;
    bool moved, is_captured, double_clicked, wheel_scrolled;
} Mouse;

void initMouse(Mouse *mouse) {
    mouse->moved = false;
    mouse->is_captured = false;
    mouse->double_clicked = false;
    mouse->wheel_scrolled= false;

    mouse->wheel_scroll_amount = 0;
    mouse->pos.x = 0;
    mouse->pos.y = 0;
    mouse->pos_raw_diff.x = 0;
    mouse->pos_raw_diff.y = 0;

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
        current1 += inc1;

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
    for (u16 y = min_y; y <= max_y; y++)
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
    u8* id = ysi ? (ysi == 1 ?
                    (u8[3]){1, 2, 0} :
                    (u8[3]){2, 0, 1}) :
             (u8[3]){0, 1, 2};
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
    for (y = ysi; y < yei; y++){
        if (y == y3i) xs = dx2 ? (x3 + dx2 * (1 - (y3 - (f32)y3i))) : x3;
        if (y == y2i) xe = dx2 ? (x2 + dx2 * (1 - (y2 - (f32)y2i))) : x2;
        xsi = (i32)xs;
        xei = (i32)xe;
        for (x = xsi; x < xei; x++)
            if (x > 0 && x < W && y > 0 && y < H)
                canvas->pixels[offset + x].color = color;
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

    u16 current_x = x;
    u16 current_y = y;
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
            current_x = x;
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
    static NumberStringBuffer number_string;
    printNumberIntoString(number, &number_string);
    drawText(canvas, color, number_string.string, x - number_string.digit_count * FONT_WIDTH, y);
}


typedef struct AppCallbacks {
    void (*windowRedraw)();
    void (*windowResize)(u16 width, u16 height);
    void (*keyChanged)(  u8 key, bool pressed);
    void (*mouseButtonUp)(  MouseButton *mouse_button);
    void (*mouseButtonDown)(MouseButton *mouse_button);
    void (*mouseWheelScrolled)(f32 amount);
    void (*mousePositionSet)(i32 x, i32 y);
    void (*mouseMovementSet)(i32 x, i32 y);
    void (*mouseRawMovementSet)(i32 x, i32 y);
} AppCallbacks;

typedef struct Platform {
    CallbackWithCharPtr setWindowTitle;
    CallbackWithBool    setWindowCapture;
    CallbackWithBool    setCursorVisibility;
    CallbackWithInt getMemory;
    GetTicks getTicks;
    u64 ticks_per_second;
} Platform;

typedef struct Defaults {
    char* title;
    u16 width, height;
} Defaults;

typedef struct App {
    Platform platform;
    Controls controls;
    PixelGrid window_content;
    AppCallbacks on;
    Time time;
    bool is_running;
    void *user_data;

    ArenaAllocator arena_allocator;
    bool (*initMemory)(u64 size);
    void* (*allocateMemory)(u64 size);
} App;

App *app;

void initApp(Defaults *defaults);

void _windowRedraw() {
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _windowResize(u16 width, u16 height) {
    updateDimensions(&app->window_content.dimensions, width, height);

    if (app->on.windowResize) app->on.windowResize(width, height);
    if (app->on.windowRedraw) app->on.windowRedraw();
}

void _keyChanged(u8 key, bool pressed) {
         if (key == app->controls.key_map.ctrl) app->controls.is_pressed.ctrl  = pressed;
    else if (key == app->controls.key_map.alt) app->controls.is_pressed.alt   = pressed;
    else if (key == app->controls.key_map.shift) app->controls.is_pressed.shift = pressed;
    else if (key == app->controls.key_map.space) app->controls.is_pressed.space = pressed;
    else if (key == app->controls.key_map.tab) app->controls.is_pressed.tab   = pressed;

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

bool _initMemory(u64 size) {
    if (app->arena_allocator.address) return false;

    void* memory_address = app->platform.getMemory(size);
    if (!memory_address) {
        app->is_running = false;
        return false;
    }

    initArenaAllocator(&app->arena_allocator, (u8*)memory_address);
    return true;
}

void* _allocateMemory(u64 size) {
    void* memory = allocateMemory(&app->arena_allocator, size);
    if (memory) return memory;

    app->is_running = false;
    return null;
}

void _initApp(Defaults *defaults, void* window_content_memory) {
    defaults->title = "";
    defaults->width = 480;
    defaults->height = 360;

    app->is_running = true;
    app->user_data = null;
    app->arena_allocator.address = null;
    app->initMemory     = _initMemory;
    app->allocateMemory = _allocateMemory;

    app->on.windowRedraw = null;
    app->on.keyChanged = null;
    app->on.mouseButtonUp = null;
    app->on.mouseButtonDown = null;
    app->on.mouseWheelScrolled = null;
    app->on.mousePositionSet = null;
    app->on.mouseMovementSet = null;
    app->on.mouseRawMovementSet = null;

    initTime(&app->time, app->platform.getTicks, app->platform.ticks_per_second);
    initControls(&app->controls);
    initPixelGrid(&app->window_content, (Pixel*)window_content_memory);
    initApp(defaults);
}

#include "./platforms/win32.h"