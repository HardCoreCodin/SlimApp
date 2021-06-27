#pragma once

#include "./pixels.h"

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