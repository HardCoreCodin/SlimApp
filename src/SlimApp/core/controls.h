#pragma once

struct MouseButton {
    vec2i down_pos, up_pos, double_click_pos;
    bool is_pressed = false,
         is_handled = false,
         double_clicked = false;

    void down(i32 x, i32 y) {
        is_pressed = true;
        is_handled = false;

        down_pos.x = x;
        down_pos.y = y;
    }

    void up(i32 x, i32 y) {
        is_pressed = false;
        is_handled = false;

        up_pos.x = x;
        up_pos.y = y;
    }

    void doubleClick(i32 x, i32 y) {
        double_clicked = true;
        double_click_pos.x = x;
        double_click_pos.y = y;
    }
};

struct Mouse {
    MouseButton middle_button, right_button, left_button;
    vec2i pos, pos_raw_diff, movement;
    f32 wheel_scroll_amount = 0;
    bool moved = false, is_captured = false,
         move_handled = false,
         double_clicked = false,
         double_clicked_handled = false,
         wheel_scrolled = false,
         wheel_scroll_handled = false,
         raw_movement_handled = false;

    void resetChanges() {
        if (move_handled) {
            move_handled = false;
            moved = false;
        }
        if (double_clicked_handled) {
            double_clicked_handled = false;
            double_clicked = false;
        }
        if (raw_movement_handled) {
            raw_movement_handled = false;
            pos_raw_diff.x = 0;
            pos_raw_diff.y = 0;
        }
        if (wheel_scroll_handled) {
            wheel_scroll_handled = false;
            wheel_scrolled = false;
            wheel_scroll_amount = 0;
        }
    }

    void scroll(f32 amount) {
        wheel_scroll_amount += amount * 100;
        wheel_scrolled = true;
    }

    void setPosition(i32 x, i32 y) {
        pos.x = x;
        pos.y = y;
    }

    void move(i32 x, i32 y) {
        movement.x = x - pos.x;
        movement.y = y - pos.y;
        moved = true;
    }

    void moveRaw(i32 x, i32 y) {
        pos_raw_diff.x += x;
        pos_raw_diff.y += y;
        moved = true;
    }
};

struct KeyMap {
    u8 ctrl = 0,
       alt = 0,
       shift = 0,
       space = 0,
       tab = 0;
};
struct IsPressed {
    bool ctrl = false,
         alt = false,
         shift = false,
         space = false,
         tab = false;
};
struct Controls {
    KeyMap key_map;
    IsPressed is_pressed;
    Mouse mouse;
};