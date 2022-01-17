#include "../SlimApp.h"

void drawMouse(PixelGrid &canvas, Mouse &mouse) {
    Rect rect;

    // Draw the mouse contour:
    rect.min.x = 48;
    rect.max.x = 172;
    rect.min.y = 98;
    rect.max.y = 320;
    canvas.drawRect(Color(White), rect);

    // Draw the left mouse button:
    rect.min.x = 50;
    rect.max.x = 90;
    rect.min.y = 100;
    rect.max.y = 180;
    canvas.fillRect(Color(mouse.left_button.is_pressed ? Blue : Cyan), rect);

    // Draw the middle mouse button:
    rect.min.x += 40;
    rect.max.x += 40;
    canvas.fillRect(Color(mouse.middle_button.is_pressed ? Green : Yellow), rect);

    // Draw the right mouse button:
    rect.min.x += 40;
    rect.max.x += 40;
    canvas.fillRect(Color(mouse.right_button.is_pressed ? Red : Magenta), rect);

    // Draw the mouse wheel:
    rect.min.x = 100;
    rect.max.x = 120;
    rect.min.y = 120;
    rect.max.y = 160;
    canvas.fillRect(Color(Grey), rect);

    // Draw a marker representing the state of the mouse wheel:
    rect.min.x += 2;
    rect.max.x -= 2;
    rect.min.y += 18;
    rect.max.y -= 18;
    if (mouse.wheel_scrolled) {
        rect.min.y -= (int) (mouse.wheel_scroll_amount * 0.01f);
        rect.max.y -= (int) (mouse.wheel_scroll_amount * 0.01f);
        if (rect.min.y < 120 ||
            rect.max.y > 160)
            mouse.wheel_scroll_amount = -mouse.wheel_scroll_amount;
    }
    canvas.fillRect(Color(White), rect);
}

void drawMouseDoubleClickArea(PixelGrid &canvas, Mouse &mouse) {
    Rect rect;

    // Draw double-click area:
    rect.min.x = 200;
    rect.max.x = 400;
    rect.min.y = 250;
    rect.max.y = 300;
    canvas.drawRect(Color(White), rect);

    rect.min.x += 20;
    rect.min.y += 20;
    if (mouse.is_captured) {
        canvas.drawText(Color(Red), (char*)"Captured!", rect.min.x, rect.min.y);
        canvas.drawText(Color(Cyan), (char*)"(Double-click anywhere to release...)", rect.min.x - 40, rect.min.y + 50);
    } else
        canvas.drawText(Color(Green), (char*)"Double-click me!", rect.min.x, rect.min.y);

    if (mouse.double_clicked) {
        mouse.double_clicked = false;
        if (mouse.is_captured) {
            mouse.is_captured = false;
            os::setWindowCapture(false);
            os::setCursorVisibility(true);
        }
        else if (mouse.pos.x > rect.min.x && mouse.pos.x < rect.max.x &&
                 mouse.pos.y > rect.min.y && mouse.pos.y < rect.max.y) {
            mouse.is_captured = true;
            os::setWindowCapture(true);
            os::setCursorVisibility(false);
        }
    }
}

void drawMouseCoords(PixelGrid &canvas, Mouse &mouse) {
    canvas.drawText(Color(White), (char*)"X", 340, 7);
    canvas.drawText(Color(White), (char*)"Y", 390, 7);

    canvas.drawText(Color(White),(char*)"  Cursor:", 230, 20);
    canvas.drawText(Color(Grey ),(char*)"RawInput:", 230, 32);

    canvas.drawText(Color(Blue),(char*)"LMB Down:", 230, 70);
    canvas.drawText(Color(Cyan),(char*)"LMB   Up:", 230, 90);

    canvas.drawText(Color(Green ),(char*)"MMB Down:", 230, 130);
    canvas.drawText(Color(Yellow),(char*)"MMB   Up:", 230, 150);

    canvas.drawText(Color(Red    ),(char*)"RMB Down:", 230, 190);
    canvas.drawText(Color(Magenta),(char*)"RMB   Up:", 230, 210);

    // Draw Cursor position coordinates:
    canvas.drawNumber(Color(White), mouse.pos.x, 350, 20);
    canvas.drawNumber(Color(White), mouse.pos.y, 400, 20);

    // Draw Raw position coordinates:
    static vec2i raw_pos;
    if (mouse.moved) {
        mouse.moved = false;
        raw_pos.x += mouse.pos_raw_diff.x;
        raw_pos.y += mouse.pos_raw_diff.y;
        mouse.pos_raw_diff.x = 0;
        mouse.pos_raw_diff.y = 0;
    }
    canvas.drawNumber(Color(Grey), raw_pos.x, 350, 32);
    canvas.drawNumber(Color(Grey), raw_pos.y, 400, 32);

    // Draw LMB position coordinates:
    canvas.drawNumber(Color(Blue), mouse.left_button.down_pos.x, 350, 70);
    canvas.drawNumber(Color(Blue), mouse.left_button.down_pos.y, 400, 70);
    canvas.drawNumber(Color(Cyan), mouse.left_button.up_pos.x, 350, 90);
    canvas.drawNumber(Color(Cyan), mouse.left_button.up_pos.y, 400, 90);

    // Draw MMB position coordinates:
    canvas.drawNumber(Color(Green), mouse.middle_button.down_pos.x, 350, 130);
    canvas.drawNumber(Color(Green), mouse.middle_button.down_pos.y, 400, 130);
    canvas.drawNumber(Color(Yellow), mouse.middle_button.up_pos.x, 350, 150);
    canvas.drawNumber(Color(Yellow), mouse.middle_button.up_pos.y, 400, 150);

    // Draw MMB position coordinates:
    canvas.drawNumber(Color(Red), mouse.right_button.down_pos.x, 350, 190);
    canvas.drawNumber(Color(Red), mouse.right_button.down_pos.y, 400, 190);
    canvas.drawNumber(Color(Magenta), mouse.right_button.up_pos.x, 350, 210);
    canvas.drawNumber(Color(Magenta), mouse.right_button.up_pos.y, 400, 210);
}

void draw() {
    PixelGrid &canvas = app->window_content;
    canvas.fill(Color(Black));

    Mouse &mouse = app->controls.mouse;
    drawMouse(canvas, mouse);
    drawMouseCoords(canvas, mouse);
    drawMouseDoubleClickArea(canvas, mouse);
}

void App::init(Defaults *defaults) {
    // Tell the app what to do whenever it needs to redraw the window:
    on.windowRedraw = draw;
}
