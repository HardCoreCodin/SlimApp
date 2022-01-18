#include "../SlimApp.h"

struct KeyboardApp : public SlimApp {
    struct Nav { u8 left, right, up, down; };
    Nav nav_keys{'A', 'D', 'W', 'S'};
    Nav nav_keys_pressed{false, false, false, false};

    void OnKeyChanged(u8 key, bool pressed) override {
        // Capture changes to custom-bound keys and store their state:
        if (key == nav_keys.left)  nav_keys_pressed.left  = pressed;
        if (key == nav_keys.right) nav_keys_pressed.right = pressed;
        if (key == nav_keys.up)    nav_keys_pressed.up    = pressed;
        if (key == nav_keys.down)  nav_keys_pressed.down  = pressed;
    }

    void OnWindowRedraw() override {
        // Clear the window content to black:
        window_content.fill(Color(Black));

        Rect rect;

        // Draw the keyboard contour:
        rect.min.x = 220;
        rect.max.x = 450;
        rect.min.y = 180;
        rect.max.y = 280;
        window_content.drawRect(Color(White), rect);

        // Draw the 'A' key:
        rect.min.x = 256;
        rect.max.x = 276;
        rect.min.y = 216;
        rect.max.y = 236;
        window_content.fillRect(Color(nav_keys_pressed.left ? White : Grey), rect);
        window_content.drawText(Color(nav_keys_pressed.left ? Grey : White), (char*)"A", rect.min.x + 5, rect.min.y + 5);

        // Draw the 'S' key:
        rect.min.x += 22;
        rect.max.x += 22;
        window_content.fillRect(Color(nav_keys_pressed.down ? White : Grey), rect);
        window_content.drawText(Color(nav_keys_pressed.down ? Grey : White), (char*)"S", rect.min.x + 5, rect.min.y + 5);

        // Draw the 'D' key:
        rect.min.x += 22;
        rect.max.x += 22;
        window_content.fillRect(Color(nav_keys_pressed.right ? White : Grey), rect);
        window_content.drawText(Color(nav_keys_pressed.right ? Grey : White), (char*)"D", rect.min.x + 5, rect.min.y + 5);

        // Draw the 'W' key:
        rect.min.x -= 28;
        rect.max.x -= 28;
        rect.min.y -= 22;
        rect.max.y -= 22;
        window_content.fillRect(Color(nav_keys_pressed.up ? White : Grey), rect);
        window_content.drawText(Color(nav_keys_pressed.up ? Grey : White), (char*)"W", rect.min.x + 5, rect.min.y + 5);

        // Draw the left Ctrl key:
        rect.min.x = 222;
        rect.max.x = 250;
        rect.min.y = 260;
        rect.max.y = 278;
        window_content.fillRect(Color(app->controls.is_pressed.ctrl ? Blue : Cyan), rect);

        // Draw the left Alt key:
        rect.min.x += 30;
        rect.max.x += 30;
        window_content.fillRect(Color(app->controls.is_pressed.alt ? Red : Magenta), rect);

        // Draw the left Shift key:
        rect.min.x -= 30;
        rect.max.x -= 15;
        rect.min.y -= 20;
        rect.max.y -= 20;
        window_content.fillRect(Color(app->controls.is_pressed.shift ? Green : Yellow), rect);

        // Draw the right Ctrl key:
        rect.min.x = 420;
        rect.max.x = 448;
        rect.min.y = 260;
        rect.max.y = 278;
        window_content.fillRect(Color(app->controls.is_pressed.ctrl ? Blue : Cyan), rect);

        // Draw the right Alt key:
        rect.min.x -= 30;
        rect.max.x -= 30;
        window_content.fillRect(Color(app->controls.is_pressed.alt ? Red : Magenta), rect);

        // Draw the right Shift key:
        rect.min.x += 15;
        rect.max.x += 30;
        rect.min.y -= 20;
        rect.max.y -= 20;
        window_content.fillRect(Color(app->controls.is_pressed.shift ? Green : Yellow), rect);

        // Draw the Space key:
        rect.min.x = 280;
        rect.max.x = 390;
        rect.min.y = 260;
        rect.max.y = 278;
        window_content.fillRect(Color(app->controls.is_pressed.space ? White : Grey), rect);
    }
};
SlimApp* createApp() { return new KeyboardApp(); }