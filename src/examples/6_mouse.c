#include "../app.h"
#include "../text.h"
#include "../shapes.h"
// Or using the single-header file:
// #include "../SlimApp.h"

void drawMouse(PixelGrid *canvas, Mouse *mouse) {
    Rect rect;

    // Draw the mouse contour:
    rect.min.x = 48;
    rect.max.x = 172;
    rect.min.y = 98;
    rect.max.y = 320;
    drawRect(canvas, Color(White), &rect);

    // Draw the left mouse button:
    rect.min.x = 50;
    rect.max.x = 90;
    rect.min.y = 100;
    rect.max.y = 180;
    fillRect(canvas, Color(mouse->left_button.is_pressed ? Blue : Cyan), &rect);

    // Draw the middle mouse button:
    rect.min.x += 40;
    rect.max.x += 40;
    fillRect(canvas, Color(mouse->middle_button.is_pressed ? Green : Yellow), &rect);

    // Draw the right mouse button:
    rect.min.x += 40;
    rect.max.x += 40;
    fillRect(canvas, Color(mouse->right_button.is_pressed ? Red : Magenta), &rect);

    // Draw the mouse wheel:
    rect.min.x = 100;
    rect.max.x = 120;
    rect.min.y = 120;
    rect.max.y = 160;
    fillRect(canvas, Color(Grey), &rect);

    // Draw a marker representing the state of the mouse wheel:
    rect.min.x += 2;
    rect.max.x -= 2;
    rect.min.y += 18;
    rect.max.y -= 18;
    if (mouse->wheel_scrolled) {
        rect.min.y -= (int) (mouse->wheel_scroll_amount * 0.01f);
        rect.max.y -= (int) (mouse->wheel_scroll_amount * 0.01f);
        if (rect.min.y < 120 ||
            rect.max.y > 160)
            mouse->wheel_scroll_amount = -mouse->wheel_scroll_amount;
    }
    fillRect(canvas, Color(White), &rect);
}

void drawMouseDoubleClickArea(PixelGrid *canvas, Mouse *mouse) {
    Platform *os = &app->platform;

    Rect rect;

    // Draw double-click area:
    rect.min.x = 200;
    rect.max.x = 400;
    rect.min.y = 250;
    rect.max.y = 300;
    drawRect(canvas, Color(White), &rect);

    rect.min.x += 20;
    rect.min.y += 20;
    if (mouse->is_captured) {
        drawText(canvas, Color(Red), "Captured!", rect.min.x, rect.min.y);
        drawText(canvas, Color(Cyan), "(Double-click anywhere to release...)", rect.min.x - 40, rect.min.y + 50);
    } else
        drawText(canvas, Color(Green), "Double-click me!", rect.min.x, rect.min.y);

    if (mouse->double_clicked) {
        mouse->double_clicked = false;
        if (mouse->is_captured) {
            mouse->is_captured = false;
            os->setWindowCapture(false);
            os->setCursorVisibility(true);
        } else if (mouse->pos.x > rect.min.x &&
                   mouse->pos.x < rect.max.x &&
                   mouse->pos.y > rect.min.y &&
                   mouse->pos.y < rect.max.y) {
            mouse->is_captured = true;
            os->setWindowCapture(true);
            os->setCursorVisibility(false);
        }
    }
}

void drawMouseCoords(PixelGrid *canvas, Mouse *mouse) {
    drawText(canvas, Color(White), "X", 350, 7);
    drawText(canvas, Color(White), "Y", 400, 7);

    drawText(canvas, Color(White),"  Cursor:", 240, 20);
    drawText(canvas, Color(Grey ),"RawInput:", 240, 32);

    drawText(canvas, Color(Blue),"LMB Down:", 240, 70);
    drawText(canvas, Color(Cyan),"LMB   Up:", 240, 90);

    drawText(canvas, Color(Green ),"MMB Down:", 240, 130);
    drawText(canvas, Color(Yellow),"MMB   Up:", 240, 150);

    drawText(canvas, Color(Red    ),"RMB Down:", 240, 190);
    drawText(canvas, Color(Magenta),"RMB   Up:", 240, 210);

    // Draw Cursor position coordinates:
    drawNumber(canvas, Color(White), mouse->pos.x, 350, 20);
    drawNumber(canvas, Color(White), mouse->pos.y, 400, 20);

    // Draw Raw position coordinates:
    static vec2i raw_pos;
    if (mouse->moved) {
        mouse->moved = false;
        raw_pos.x += mouse->pos_raw_diff.x;
        raw_pos.y += mouse->pos_raw_diff.y;
        mouse->pos_raw_diff.x = 0;
        mouse->pos_raw_diff.y = 0;
    }
    drawNumber(canvas, Color(Grey), raw_pos.x, 350, 32);
    drawNumber(canvas, Color(Grey), raw_pos.y, 400, 32);

    // Draw LMB position coordinates:
    drawNumber(canvas, Color(Blue), mouse->left_button.down_pos.x, 350, 70);
    drawNumber(canvas, Color(Blue), mouse->left_button.down_pos.y, 400, 70);
    drawNumber(canvas, Color(Cyan), mouse->left_button.up_pos.x, 350, 90);
    drawNumber(canvas, Color(Cyan), mouse->left_button.up_pos.y, 400, 90);

    // Draw MMB position coordinates:
    drawNumber(canvas, Color(Green), mouse->middle_button.down_pos.x, 350, 130);
    drawNumber(canvas, Color(Green), mouse->middle_button.down_pos.y, 400, 130);
    drawNumber(canvas, Color(Yellow), mouse->middle_button.up_pos.x, 350, 150);
    drawNumber(canvas, Color(Yellow), mouse->middle_button.up_pos.y, 400, 150);

    // Draw MMB position coordinates:
    drawNumber(canvas, Color(Red), mouse->right_button.down_pos.x, 350, 190);
    drawNumber(canvas, Color(Red), mouse->right_button.down_pos.y, 400, 190);
    drawNumber(canvas, Color(Magenta), mouse->right_button.up_pos.x, 350, 210);
    drawNumber(canvas, Color(Magenta), mouse->right_button.up_pos.y, 400, 210);
}

void draw() {
    // Get the window content from the app and clear it all to black:
    PixelGrid *canvas = &app->window_content;
    fillPixelGrid(canvas, Color(Black));

    Mouse *mouse = &app->controls.mouse;

    drawMouse(canvas, mouse);
    drawMouseCoords(canvas, mouse);
    drawMouseDoubleClickArea(canvas, mouse);
}

void initApp(Defaults *defaults) {
    // Tell the app what to do whenever it needs to redraw the window:
    app->on.windowRedraw = draw;
}
