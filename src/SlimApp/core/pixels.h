#pragma once

#include "./base.h"

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