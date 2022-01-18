#include "../SlimApp.h"

struct MouseApp : public SlimApp {
    void OnWindowRedraw() override {
        // Clear the window content to black:
        window_content.fill(Color(Black));

        static vec2i raw_pos;
        Rect rect;
        Mouse &mouse = controls.mouse;
        MouseButton &left = mouse.left_button;
        MouseButton &right = mouse.right_button;
        MouseButton &middle = mouse.middle_button;

        // Draw the mouse
        {
            // Draw the mouse contour:
            rect.min.x = 48;
            rect.max.x = 172;
            rect.min.y = 98;
            rect.max.y = 320;
            window_content.drawRect(Color(White), rect);

            // Draw the left mouse button:
            rect.min.x = 50;
            rect.max.x = 90;
            rect.min.y = 100;
            rect.max.y = 180;
            window_content.fillRect(Color(left.is_pressed ? Blue : Cyan), rect);

            // Draw the middle mouse button:
            rect.min.x += 40;
            rect.max.x += 40;
            window_content.fillRect(Color(middle.is_pressed ? Green : Yellow), rect);

            // Draw the right mouse button:
            rect.min.x += 40;
            rect.max.x += 40;
            window_content.fillRect(Color(right.is_pressed ? Red : Magenta), rect);

            // Draw the mouse wheel:
            rect.min.x = 100;
            rect.max.x = 120;
            rect.min.y = 120;
            rect.max.y = 160;
            window_content.fillRect(Color(Grey), rect);

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
            window_content.fillRect(Color(White), rect);
        }

        { // Draw mouse coords
            window_content.drawText(Color(White), (char*)"X", 340, 7);
            window_content.drawText(Color(White), (char*)"Y", 390, 7);

            window_content.drawText(Color(White),(char*)"  Cursor:", 230, 20);
            window_content.drawText(Color(Grey ),(char*)"RawInput:", 230, 32);

            window_content.drawText(Color(Blue),(char*)"LMB Down:", 230, 70);
            window_content.drawText(Color(Cyan),(char*)"LMB   Up:", 230, 90);

            window_content.drawText(Color(Green ),(char*)"MMB Down:", 230, 130);
            window_content.drawText(Color(Yellow),(char*)"MMB   Up:", 230, 150);

            window_content.drawText(Color(Red    ),(char*)"RMB Down:", 230, 190);
            window_content.drawText(Color(Magenta),(char*)"RMB   Up:", 230, 210);

            // Draw Cursor position coordinates:
            window_content.drawNumber(Color(White), mouse.pos.x, 350, 20);
            window_content.drawNumber(Color(White), mouse.pos.y, 400, 20);

            // Draw Raw position coordinates:
            if (mouse.moved) {
                mouse.moved = false;
                raw_pos.x += mouse.pos_raw_diff.x;
                raw_pos.y += mouse.pos_raw_diff.y;
                mouse.pos_raw_diff.x = 0;
                mouse.pos_raw_diff.y = 0;
            }
            window_content.drawNumber(Color(Grey), raw_pos.x, 350, 32);
            window_content.drawNumber(Color(Grey), raw_pos.y, 400, 32);

            // Draw LMB position coordinates:
            window_content.drawNumber(Color(Blue), left.down_pos.x, 350, 70);
            window_content.drawNumber(Color(Blue), left.down_pos.y, 400, 70);
            window_content.drawNumber(Color(Cyan), left.up_pos.x, 350, 90);
            window_content.drawNumber(Color(Cyan), left.up_pos.y, 400, 90);

            // Draw MMB position coordinates:
            window_content.drawNumber(Color(Green), middle.down_pos.x, 350, 130);
            window_content.drawNumber(Color(Green), middle.down_pos.y, 400, 130);
            window_content.drawNumber(Color(Yellow), middle.up_pos.x, 350, 150);
            window_content.drawNumber(Color(Yellow), middle.up_pos.y, 400, 150);

            // Draw MMB position coordinates:
            window_content.drawNumber(Color(Red), right.down_pos.x, 350, 190);
            window_content.drawNumber(Color(Red), right.down_pos.y, 400, 190);
            window_content.drawNumber(Color(Magenta), right.up_pos.x, 350, 210);
            window_content.drawNumber(Color(Magenta), right.up_pos.y, 400, 210);
        }

        { // Draw mouse double-click area:
            // Draw double-click area:
            rect.min.x = 200;
            rect.max.x = 400;
            rect.min.y = 250;
            rect.max.y = 300;
            window_content.drawRect(Color(White), rect);

            rect.min.x += 20;
            rect.min.y += 20;
            if (mouse.is_captured) {
                window_content.drawText(Color(Red), (char*)"Captured!", rect.min.x, rect.min.y);
                window_content.drawText(Color(Cyan), (char*)"(Double-click anywhere to release...)", rect.min.x - 40, rect.min.y + 50);
            } else
                window_content.drawText(Color(Green), (char*)"Double-click me!", rect.min.x, rect.min.y);

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
    }
};

SlimApp* createApp() { return new MouseApp(); }